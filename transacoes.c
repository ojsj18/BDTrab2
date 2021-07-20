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
#include <transacoes.h>

/* Funções Auxiliares */
void criaArestas(tipoLista *transacoes) 
{
	/*Ignorar se as arestas estão prontas*/
}

int testaCicloGrafo (tipoLista *transacoes) 
{

}

tipoLista *criaEscalonamentoSerial(ordemTransacoes)
{

}

int comparaVisaoEquivalente(tipoLista *s1, tipoLista *s2)
{
	
}

/* Funções Principais */
int testeSerialidade (tipoLista *transacoes)
{

	criaArestas(transacoes);

	return testaCicloGrafo(transacoes);

}

int testeVisaoEquivalente (tipoEscalonamento *escalonamento)
{
	tipoLista *ordemTransacoes;
	tipoLista *operacoesSerial;

	/* WHILE TODAS AS POSSIBILIDADES*/
		operacoesSerial = criaEscalonamentoSerial(ordemTransacoes);
		if (!comparaVisaoEquivalente(escalonamento->todasOperacoes, operacoesSerial));
			return 0;

	return 1;
}