/*
Autores: Giovani G Marciniak e Ovídio Junior
GRR20182981
GRR2018####

Arquivo: listas.c
Modificado em 14/07/2021
Descrição:
Implementação das funções relacionadas com as listas utilizadas no trabalho.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "listas.h"


tipoOperacao* novaOperacao(int id, int tempoChegada, char tipo, char atributo)
{
	/*FAZER TRATAMENTO DE ERRO NO TIPO DE OPERACAO*/
	
	tipoOperacao *operacao = (tipoOperacao*) malloc(sizeof(tipoOperacao));
	operacao->id = id;
	operacao->tempoChegada = tempoChegada;
	operacao->tipo = tipo;
	operacao->atributo = atributo;

	return operacao;
}

tipoTransacao* novaTransacao(tipoOperacao* operacao) {
	tipoTransacao *transacao = (tipoTransacao) malloc(sizeof(tipoTransacao));

	transacao->id = operacao->id;
	transacao->operacoes = novaListaOperacao(operacao);
	transacao->arestas = NULL; //arrumar aqui em seguida

}

/*tipoEscalonamento* novoEscalonamento(tipoTransacao* transacao) {
	
}*/

listaOperacoes* novaListaOperacao(tipoOperacao* operacao) {
	listaOperacoes *lista = malloc(sizeof(listaOperacoes));

	lista->op = operacao;

    lista->proximo = NULL;
  	lista->anterior = NULL;

  	return lista;
}

void addOperacao(listaOperacoes* lista, tipoOperacao* operacao) {
	/*ESTÁ ADICIONANDO NO FIM, TEM QUE IMPLEMENTAR A ADIÇÃO ORDENADA POR TEMPO*/

	while (lista->proximo!=NULL) {
		lista = lista->proximo;
	}

	listaOperacoes *novo = malloc(sizeof(listaOperacoes));

	novo->op = operacao;

    novo->proximo = NULL;
  	novo->anterior = lista;
  	lista->proximo = novo;

  	return;
}

listaTransacoes* novaListaTransacao(tipoTransacao* transacao) {
	listaTransacoes *lista = malloc(sizeof(listaTransacoes));
	lista->t = transacao;
	lista->proximo = NULL;
	lista->anterior = NULL;

	return lista;
}


/*
novaListaEscalonamento()

addTransacao()
addEscalonamento()

/*freeListaOperacao()
freeListaTransacao()
freeListaEscalonamento() depois kkk

imprimeLista() */