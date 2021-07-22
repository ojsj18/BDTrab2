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
	printf("-----------------------\n");
	while (lista != NULL)
	{
		operacao = (tipoOperacao *) lista->item;
		printf("%d ",operacao->tempoChegada);
		printf("%d ",operacao->id);
		printf("%c ",operacao->tipo);
		printf("%c\n",operacao->atributo);
		lista=lista->proximo;
	}
	printf("-----------------------\n");
}
void imprimeTransacao(tipoTransacao *transacao){

	tipoLista* operacao=transacao->operacoes;
	printf("%d,",transacao->id);
	//imprimeOperacao(operacao);
}

void imprimeListaTransacao(tipoLista *lista){
	
	tipoTransacao* transacao;

	while (lista != NULL)
	{
		transacao = (tipoTransacao *) lista->item;
		printf("%d,",transacao->id);
		//imprimeTransacao(transacao);
		lista=lista->proximo;
	}

}

//procuro algo na lista retorna o ponteiro se encontrar e null se não
tipoTransacao* verificaLista(tipoLista* lista, int id){

	tipoTransacao* aux;
	tipoLista* auxlista = lista;

	while (auxlista != NULL)
	{
		aux= (tipoTransacao*)auxlista->item;
		if(aux->id==id){
			return auxlista->item;
		}
		auxlista=auxlista->proximo;
	}
	return NULL;
}

//Faz a troca a ordem apenas dos itens de 2 elementos de uma lista
void trocaItemLista(tipoLista *elemento1, tipoLista *elemento2) {
	void *aux;
	aux = elemento1->item;
	elemento1->item = elemento2->item;
	elemento2->item = aux;
}

tipoLista *copiaLista(tipoLista *original) {
	tipoLista *aux = original;

	tipoLista *copia = novaLista(aux->item);

	while (aux->proximo != NULL) {
		aux = aux->proximo;
		adicionaLista(copia, aux->item);
	}

	return copia;
}