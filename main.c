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

	scanf("%d %d %c %c",&tempoChegada,&id,&tipo,&atributo);

	tipoOperacao *operacao= novaOperacao(id, tempoChegada, tipo, atributo);
	tipoLista *lista_operacao = novaLista(operacao);
	
	tipoTransacao *transacao = novaTransacao(operacao);
	tipoLista *lista_transacao = novaLista(transacao);
	tipoTransacao *aux= lista_transacao->item;
	

	while (scanf("%d %d %c %c",&tempoChegada,&id,&tipo,&atributo) != EOF)
	{
		operacao= novaOperacao(id, tempoChegada, tipo, atributo);
		adicionaLista (lista_operacao,operacao);

		//verifica se chegou um id diferente
		aux = verificaLista(lista_transacao,id);

		if(aux != NULL){
			adicionaLista(aux->operacoes,novaOperacao(id, tempoChegada, tipo, atributo));
		}
		else{
			adicionaLista(lista_transacao,novaTransacao(operacao));
		}
	}

	//imprimeOperacao(lista_operacao);
	imprimeListaTransacao(lista_transacao);
	

	/* COLOCANDO NUMA LISTA DE TRANSACAO */
	
	return 0;
}