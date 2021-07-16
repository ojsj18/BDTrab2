/*
Autores: Giovani G Marciniak e Ovídio Junior
GRR20182981
GRR2018####

Arquivo: main.c
Modificado em 14/07/2021
Descrição:
Implementação da função main() do trabalho 2 de Banco de Dados.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "listas.h"

int main(void)
{

	int id;
	int tempoChegada;
	char tipo;
	char atributo;
	scanf("%d %d %c %c",&id,&tempoChegada,&tipo,&atributo);
	tipoLista *lista_teste = novaLista(novaOperacao(id, tempoChegada, tipo, atributo));
	

	while (scanf("%d %d %c %c",&id,&tempoChegada,&tipo,&atributo) != EOF)
	{
		adicionaLista (lista_teste, novaOperacao(id, tempoChegada, tipo, atributo));
		//verifica se chegou um id diferente

	}

	imprimeOperacao(lista_teste);
	

	/* COLOCANDO NUMA LISTA DE TRANSACAO */
	
	return 0;
}