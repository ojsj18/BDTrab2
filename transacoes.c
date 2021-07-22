/*
Autores: Giovani G Marciniak e Ovídio Junior
GRR20182981
GRR20182667

Arquivo: transacoes.c
Modificado em 14/07/2021
Descrição:
Funções relacionadas aos algoritmos de detecção de conflitos de escalonamento de transações concorrentes.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "listas.h"
#include "transacoes.h"

/* Funções Auxiliares */
void criaArestas(tipoTransacao *t1,tipoTransacao* t2) 
{
	printf("id: %d \n", t1->id);
	printf("id: %d\n", t2->id);
	printf("\n");

}

int testaCicloGrafo (tipoLista *transacoes) 
{
	
}

tipoLista *CriaEscalonamentoSerial(tipoLista *transacoes, int n_transacoes, int n_trocas)
{
	if (n_trocas <= 0)
		return transacoes;

	tipoLista *novaOrdem = copiaLista(transacoes);
	tipoLista *atual = NULL;

	while (n_trocas > 0)
	{
		atual = novaOrdem;

		for (int i; i<n_transacoes; i++)
		{
			trocaItemLista(atual, atual->proximo);
			n_trocas--;

			if (n_trocas <= 0) break;
		}

		n_transacoes--;
	}
	return novaOrdem;
}

int comparaVisaoEquivalente(tipoLista *operacoes, tipoLista *serial)
{
	int escreveu;		//booleando que representa se o atributo foi escrito antes de ser lido
	int escreveu_id;	// id da transacao que escreveu antes de ler
	int ultimo; 		//booleano que representa se é a ultima escrita naquele atributo

	tipoOperacao *operacao;
	tipoOperacao *percorredor_op;

	tipoLista *aux_serial = serial;
	tipoLista *aux_transacao = aux_serial->item;
	tipoLista *aux_operacoes = operacoes;
	tipoLista *percorredor;

	// Transforma a lista de transações em uma lista de operações:
	tipoLista *operacoes_serial = novaLista(aux_transacao->item);
	aux_transacao = aux_transacao->proximo;
	while (aux_serial != NULL) {
		while (aux_transacao != NULL) {
			adicionaLista(operacoes_serial, aux_transacao->item);
			aux_transacao = aux_transacao->proximo;
		}
		aux_serial = aux_serial->proximo;
		aux_transacao = aux_serial->item;
	}


	// Percorre o escalonamento original para verificar leituras e escritas
	while (aux_operacoes != NULL)
	{
		operacao = (tipoOperacao*) aux_operacoes->item;

		if (operacao->tipo == 'R')
		{
			percorredor = aux_operacoes->anterior;
			escreveu = 0;

			// verifica se a leitura originalmente leu um valor original ou escrito por outra operação
			while (percorredor != NULL)
			{
				percorredor_op = (tipoOperacao*) percorredor->item;

				if ((percorredor_op->tipo == 'W')&&(percorredor_op->atributo == operacao->atributo))
				{
					escreveu = 1;
					escreveu_id = percorredor_op->id;
					break;
				}

				percorredor = percorredor->anterior;
			}

			// verifica se a escrita é consistente no escalonamento serial (s-linha)
			percorredor = operacoes_serial;
			if (escreveu)
			{
				while (percorredor != NULL)
				{
					percorredor_op = (tipoOperacao*) percorredor->item;
					if ((percorredor_op->tipo == 'R')
						&&(percorredor_op->atributo == operacao->atributo)
						&&(percorredor_op->id == operacao->id)) 
					{
						//a leitura foi feita sem uma escrita, não é visão equivalente
						return 0;	
					}

					if ((percorredor_op->tipo == 'W')
						&&(percorredor_op->atributo == operacao->atributo)
						&&(percorredor_op->id==escreveu_id))
					{
						//se houve uma escrita antes da leitura então está ok
						break;	
					}

					percorredor = percorredor->proximo;
				}
			}

			else
			{
				while (percorredor != NULL)
				{
					percorredor_op = (tipoOperacao*) percorredor->item;
					if ((percorredor_op->tipo == 'R')
						&&(percorredor_op->atributo == operacao->atributo)
						&&(percorredor_op->id == operacao->id))
					{
						//a leitura foi feita com o valor original, sem escrita
						break;
					}
					if ((percorredor_op->tipo == 'W')
						&&(percorredor_op->atributo == operacao->atributo))
					{
						//se houve uma escrita e deveria ser o valor original, não é visão equivalente
						return 0;	
					}
					percorredor = percorredor->proximo;
				}
			}
		}



		if (operacao->tipo == 'W')
		{
			
			percorredor = aux_operacoes->proximo;
			ultimo = 1;

			// verifica se a escrita é a ultima no atributo
			while (percorredor != NULL)
			{
				percorredor_op = (tipoOperacao*) percorredor->item;

				if ((percorredor_op->tipo == 'W')&&(percorredor_op->atributo == operacao->atributo))
				{
					ultimo = 0;
					break;
				}
				percorredor = percorredor->proximo;
			}

			if (ultimo)
			{
				percorredor = operacoes_serial;

				// percorre até o final da lista
				while (percorredor->proximo != NULL) 
					percorredor=percorredor->proximo;

				while (percorredor != NULL) 
				{
					percorredor_op = (tipoOperacao*) percorredor->item;

					if ((percorredor_op->tipo == 'W')&&(percorredor_op->atributo == operacao->atributo))
					{
						if (percorredor_op->id == operacao->id)
							break;
						else
							return 0; //descobriu que o último não é último em s-linha		
					}

					percorredor = percorredor->anterior;
				}
			}
		}
	}

	return 1;
}


/* Funções Principais */
int testeSerialidade (tipoLista *transacoes, tipoLista *linhaTempo)
{
	tipoOperacao * auxop = linhaTempo->item;
	tipoOperacao * anterior = NULL;
	tipoOperacao * proximo = NULL;

	while (linhaTempo != NULL)
	{
		if (auxop->tipo == 'W')
		{
			if (linhaTempo->anterior != NULL)
			{
				anterior = linhaTempo->anterior->item;
				if (anterior->tipo == 'W' ||anterior->tipo == 'R' ){
					printf("escrita depois de escrita ou leitura \n");
					criaArestas(verificaLista(transacoes,auxop->id),verificaLista(transacoes,anterior->id));
				}
			}
			else if (linhaTempo->proximo != NULL)
			{
				proximo = linhaTempo->proximo->item;
				if (proximo->tipo == 'R')
				{
					printf("escrita antes de leitura \n");
					criaArestas(verificaLista(transacoes,auxop->id),verificaLista(transacoes,proximo->id));
				}		
			}	
		}
		linhaTempo= linhaTempo->proximo;
		if (linhaTempo != NULL)
		{
			auxop = linhaTempo->item;
		}
		
	}
	imprimeOperacao(linhaTempo);


	return 1;
}

int testeVisaoEquivalente (tipoLista *transacoes, int n_transacoes, tipoLista *operacoes)
{
	printf("TESTE VISAO EQUIVALENTE\n");
	imprimeListaTransacao(transacoes);

	int max_visoes = n_transacoes;
	int aux_fatorial = n_transacoes-1;

	while (aux_fatorial > 1) {
		max_visoes *= aux_fatorial;
		aux_fatorial--;
	}
	printf("max_visoes: %d\n", max_visoes);

	tipoLista *nova = NULL;
	for (int i = 0; i<max_visoes; i++) {
		nova = CriaEscalonamentoSerial(transacoes, n_transacoes, i);
		printf(">>>ORDEM NUMERO %d\n", i);
		imprimeListaTransacao(nova);
		if (comparaVisaoEquivalente(operacoes, nova))
			return 1;
	}

	printf("Saiu da Visão\n");
	return 0;
}

int testeescrita(tipoLista* operacoes){
	
	tipoOperacao* operacao= operacoes->item;
	while (operacoes != NULL)
	{
		if(operacao->tipo = 'W'){
			return 1;
		}
		if (operacoes != NULL)
		{
			operacoes=operacoes->proximo;
			if (operacoes != NULL)
			{
				operacao = operacoes->item;
			}
		}
	}
	return 0;
}