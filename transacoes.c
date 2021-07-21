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
	return 1;
}

int comparaVisaoEquivalente(tipoLista *s1, tipoLista *s2)
{
	
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

int testeVisaoEquivalente (tipoLista *transacoes)
{
	tipoLista *ordemTransacoes;
	tipoLista *operacoesSerial;

	/* WHILE TODAS AS POSSIBILIDADES
		operacoesSerial = criaEscalonamentoSerial(ordemTransacoes);
		if (!comparaVisaoEquivalente(transacoes->todasOperacoes, operacoesSerial));
			return 0;
	*/
	return 1;
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