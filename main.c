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
	int s= 1;
	int commits =0;
	int contador =0;

	scanf("%d %d %c %c",&tempoChegada,&id,&tipo,&atributo);

	tipoOperacao *operacao= novaOperacao(id, tempoChegada, tipo, atributo);
	tipoLista *lista_operacao = novaLista(operacao);
	tipoOperacao *auxop;
	
	tipoTransacao *transacao = novaTransacao(operacao);
	tipoLista *lista_transacao = novaLista(transacao);
	tipoTransacao *aux= lista_transacao->item;

	tipoEscalonamento *escalonamento = novoEscalonamento(transacao,s);
	contador++;
	
/* COLOCANDO NUMA LISTA DE TRANSACAO  */

	while (scanf("%d %d %c %c",&tempoChegada,&id,&tipo,&atributo) != EOF)
	{
		auxop = operacao;
		operacao= novaOperacao(id, tempoChegada, tipo, atributo);

		if (tipo=='C')
		{
			commits++;

			if(commits==contador){
				printf("escalonamento %d\n",s);
				s++;
				contador=0;
				commits=0;
			}
		}
		
		adicionaLista (lista_operacao,operacao);

		//verifica se chegou um id diferente
		aux = verificaLista(lista_transacao,id);

		if(aux != NULL){
			adicionaLista(aux->operacoes,operacao);
		}
		else{
			adicionaLista(lista_transacao,novaTransacao(operacao));
			contador++;
		}
		//cria uma aresta olhando pro anterior

		if(operacao->atributo==auxop->atributo && (operacao->tipo =='W' ||auxop->tipo== 'W' )){ 
			//printf("cria aresta entre T(%d) e T(%d) \n");
		} 

		//se o id for diferente eu aumento o contador de transações participantes do escalonamento
		//caso eu leia um commit eu reduzo o numero de transações participantes do escalonamento
		//caso eu chegue a 0 transaçoes participantes eu posso começar a verificar as arestas
	}

	//imprimeOperacao(lista_operacao);
	imprimeListaTransacao(lista_transacao);
	

	
	
	return 0;
}