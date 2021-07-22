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
	//verificar se já aponta (preciso fazer)
	//printf("aresta de %d para %d \n",t1->id,t2->id);
	if (t1->id != t2->id)
	{
		if (t1->arestas == NULL)
		{
			t1->arestas = novaLista(t2);
		}
		else
		{
			adicionaLista(t1->arestas,t2);
		}
	}
}
//recebe os ids dos pais e em recursividade procura alguem nos filhos que aponte para o id pai
int percorreAresta(tipoLista* arestas, int id){
	if (arestas == NULL)
	{
		return 0;
	}

	tipoTransacao* aux = arestas->item;
	int achou= 0;

	while (arestas != NULL)
	{	
		if (aux->id == id )
		{
			return 1;
		}
		else
		{
			achou = percorreAresta(aux->arestas,id);
		}
		
		arestas= arestas->proximo;
		if (arestas != NULL)
		{
			aux= arestas->item;
		}	
	}
	return achou;
}

//Recebe a lista com todas as transacoes Pais, e envia para suas arestas filhas seus ids
int testaCicloGrafo (tipoLista *transacoes) 
{
	if (transacoes == NULL)
	{
		return 0;
	}

	tipoTransacao *aux= transacoes->item;
	int achou=0;

	while (transacoes != NULL)
	{
		aux = transacoes->item;
		achou = percorreAresta(aux->arestas,aux->id);
		transacoes = transacoes->proximo;
		if (achou == 1)
		{
			return achou;
		}
		
	}
	return achou;
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

	tipoTransacao *transacao;

	tipoLista *aux_serial;
	tipoLista *aux_transacao;
	tipoLista *aux_operacoes;
	tipoLista *percorredor;
	tipoLista *operacoes_serial = NULL;

	// Transforma a lista de transações em uma lista de operações:
	//aux_transacao = (tipoLista*) aux_serial->item; // recebe a primeira transacao
	//transacao = (tipoTransacao*) aux_serial->item;

	aux_serial = serial;
	while (aux_serial != NULL)
	{
		transacao = (tipoTransacao*) aux_serial->item;	
		aux_transacao = transacao->operacoes;

		while (aux_transacao != NULL)
		{
			if (operacoes_serial == NULL)
			{
				operacoes_serial = novaLista(aux_transacao->item);
			}

			else
			{
				adicionaLista(operacoes_serial, aux_transacao->item);
			}

			aux_transacao = aux_transacao->proximo;
		}
		aux_serial = aux_serial->proximo;
	}

	aux_operacoes = operacoes;
	
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

					//imprimeOperacao(percorredor);
					//printf("AAAAAAAA");

					if ((percorredor_op->tipo == 'W')&&(percorredor_op->atributo == operacao->atributo))
					{
						if (percorredor_op->id == operacao->id)
							break;
						else {
							return 0; //descobriu que o último não é último em s-linha		
						}
					}

					percorredor = percorredor->anterior;
				}
			}
		}
		aux_operacoes = aux_operacoes->proximo;
	}
	return 1;
}


/* Funções Principais */
int testeSerialidade (tipoLista *transacoes, tipoLista *linhaTempo)
{
	tipoLista *auxlista = linhaTempo;
	tipoOperacao * auxop = auxlista->item;
	//tipoOperacao * anterior = NULL;
	//tipoOperacao * proximo = NULL;
	int id;
	int id2;

//percorre a linha do Tempo procurando um Write, quando encontrado verifica criterios de seriabilidade
	while (auxlista != NULL)
	{	
		if (auxop->tipo == 'W'){
			id = achaescrita(auxlista,auxop);
			id2 = achaleitura(auxlista,auxop);
			if (id != -1)
			{
				criaArestas(verificaLista(transacoes,auxop->id),verificaLista(transacoes,id));
				//printf("criar aresta de escrita\n");
			}
			if (id2 != -1)
			{
				criaArestas(verificaLista(transacoes,id2),verificaLista(transacoes,auxop->id));
				//printf("criar aresta de leitura \n");
			}
		}
		auxlista = auxlista->proximo;
		if (auxlista != NULL)
		{	
			auxop = auxlista->item;
		}
	}
	
	return testaCicloGrafo(transacoes);
}

int testeVisaoEquivalente (tipoLista *transacoes, int n_transacoes, tipoLista *operacoes)
{
	//imprimeListaTransacao(transacoes);

	int max_visoes = n_transacoes;
	int aux_fatorial = n_transacoes-1;

	while (aux_fatorial > 1) {
		max_visoes *= aux_fatorial;
		aux_fatorial--;
	}

	tipoLista *nova = NULL;
	for (int i = 0; i<max_visoes; i++) {
		nova = CriaEscalonamentoSerial(transacoes, n_transacoes, i);
		if (comparaVisaoEquivalente(operacoes, nova))
			return 1;
	}
	return 0;
}


//Criar aresta Ti->Tj para cada w(x) em Ti depois de r(x) em Tj 
//Criar aresta Ti->Tj para cada w(x) em Ti depois de w(x) em Tj
int achaescrita(tipoLista* operacoes,tipoOperacao* w){
	
	if (operacoes == NULL)
	{
		return -1;
	}
	
	tipoOperacao* operacao= operacoes->item;
	tipoLista* listaoperacoes = operacoes;

	while (listaoperacoes != NULL)
	{
		if((operacao->tipo == 'W') && (operacao->atributo == w->atributo) && (operacao->id != w->id)){
			return operacao->id;
		}
		if((operacao->tipo == 'R') && (operacao->atributo == w->atributo) && (operacao->id != w->id)){
			return operacao->id;
		}
		if (listaoperacoes != NULL)
		{
			listaoperacoes=listaoperacoes->anterior;
			if (listaoperacoes != NULL)
			{
				operacao = listaoperacoes->item;
			}
			
		}
	}
	return -1;
}

//Criar aresta Ti->Tj para cada r(x) em Ti depois de w(x) em Tj
int achaleitura(tipoLista* operacoes,tipoOperacao* w){
	
	if (operacoes == NULL)
	{
		return -1;
	}
	tipoOperacao* operacao= operacoes->item;
	tipoLista* listaoperacoes = operacoes;
	while (listaoperacoes != NULL)
	{
		if((operacao->tipo == 'R') && (operacao->atributo == w->atributo) && (operacao->id != w->id)){
			return operacao->id;
		}

		if (listaoperacoes != NULL)
		{
			listaoperacoes=listaoperacoes->proximo;
			if (listaoperacoes != NULL)
			{
				operacao = listaoperacoes->item;
			}
		}
	}
	return -1;
}