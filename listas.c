/*
Autores: Giovani G Marciniak e Ovídio Junior
GRR20182981
GRR20182667

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
	tipoTransacao *transacao = (tipoTransacao*) malloc(sizeof(tipoTransacao));

	transacao->id = operacao->id;
	transacao->operacoes = novaLista(operacao);
	transacao->arestas = NULL; //arrumar aqui em seguida

	//tava sem o return
	return transacao;
}

tipoEscalonamento* novoEscalonamento(tipoTransacao* transacao, int id) {
	tipoEscalonamento *escalonamento = (tipoEscalonamento*) malloc(sizeof(tipoEscalonamento));
	
	escalonamento->transacoes = novaLista(transacao);
	//escalonamento->transacoesAtivas = novaLista(transacao);
	escalonamento->id = id;

	escalonamento->todasOperacoes = novaLista(transacao->operacoes->item);

	tipoLista *aux = transacao->operacoes->proximo;
	while (aux != NULL) {
		adicionaLista(aux, aux->item);
		aux = aux->proximo;
	}
}


tipoLista* novaLista(void* item) {
	tipoLista *lista = (tipoLista*) malloc(sizeof(tipoLista));

	lista->item = item;

    lista->proximo = NULL;
  	lista->anterior = NULL;

  	return lista;
}

void adicionaLista(tipoLista* lista, void* item) {
	/*ESTÁ ADICIONANDO NO FIM, TEM QUE IMPLEMENTAR A ADIÇÃO ORDENADA POR TEMPO*/
	//talvez implementar criar lista caso null
	while (lista->proximo!=NULL) {
		lista = lista->proximo;
	}

	tipoLista *novo = malloc(sizeof(tipoLista));

	novo->item = item;

    novo->proximo = NULL;
  	novo->anterior = lista;
  	lista->proximo = novo;

  	return;
}

void imprimeOperacao(tipoLista *lista){

	tipoOperacao *operacao;

	while (lista != NULL)
	{
		operacao = (tipoOperacao *) lista->item;
		printf("%d ",operacao->tempoChegada);
		printf("%d ",operacao->id);
		printf("%c ",operacao->tipo);
		printf("%c\n",operacao->atributo);
		lista=lista->proximo;
	}
}
void imprimeTransacao(tipoTransacao *transacao){

	tipoLista* operacao=transacao->operacoes;
	printf(" Transação: %d \n",transacao->id);
	imprimeOperacao(operacao);
}

void imprimeListaTransacao(tipoLista *lista){
	
	tipoTransacao* transacao;

	while (lista != NULL)
	{
		transacao = (tipoTransacao *) lista->item;
		imprimeTransacao(transacao);
		lista=lista->proximo;
	}

}

//procuro algo na lista retorna o ponteiro se encontrar e null se não
tipoTransacao* verificaLista(tipoLista* lista, int id){

	tipoTransacao* aux;

	while (lista != NULL)
	{
		aux= (tipoTransacao*)lista->item;
		if(aux->id==id){
			return lista->item;
		}
		lista=lista->proximo;
	}
	return NULL;
}