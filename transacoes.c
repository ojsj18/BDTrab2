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
void criaArestas(tipoLista *transacoes) 
{
	


}

int testaCicloGrafo (tipoLista *transacoes) 
{
	return 1;
}

int comparaVisaoEquivalente(tipoLista *s1, tipoLista *s2)
{
	
}

/* Funções Principais */
int testeSerialidade (tipoLista *transacoes)
{
	tipoLista* auxlista= transacoes;
	tipoTransacao* auxtransacao = auxlista->item;
	tipoLista* auxlistaoperacao = auxtransacao->operacoes;
	tipoOperacao* auxoperacao = auxlistaoperacao->item;
	
	while (auxlista != NULL)
	{
		while (auxoperacao != NULL)
		{
			if (auxoperacao->tipo == 'W')
			{
				//printf("%d %d %c %c \n",auxoperacao->tempoChegada,auxoperacao->id,auxoperacao->tipo,auxoperacao->atributo);
				printf("tipo escrita \n");
			}
			auxlistaoperacao= auxlistaoperacao->proximo;

			if (auxlistaoperacao != NULL){
				auxoperacao =  auxlistaoperacao->item;
			}
			else{
				auxoperacao = NULL;
			}	
		}
	auxlista = auxlista->proximo;
	if (auxlista != NULL){
		auxtransacao= auxlista->item;
		auxlistaoperacao = auxtransacao->operacoes;
	}
	}	
	return testaCicloGrafo(transacoes);
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