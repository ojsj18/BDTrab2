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

int comparaVisaoEquivalente(tipoLista *s1, tipoLista *s2)
{
	
}

/* Funções Principais */
int testeSerialidade (tipoLista *transacoes, tipoLista *linhaTempo)
{
	tipoLista *auxlista = linhaTempo;
	tipoOperacao * auxop = auxlista->item;
	tipoOperacao * anterior = NULL;
	tipoOperacao * proximo = NULL;
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
		if(operacao->tipo = 'W' && (operacao->atributo == w->atributo) && (operacao->id != w->id)){
			return operacao->id;
		}
		if(operacao->tipo = 'R' && (operacao->atributo == w->atributo) && (operacao->id != w->id)){
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
		if(operacao->tipo = 'R' && (operacao->atributo == w->atributo) && (operacao->id != w->id)){
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