/*
Autores: Giovani G Marciniak e Ovídio Junior
GRR20182981
GRR20182667

Arquivo: main.c
Modificado em 14/07/2021
Descrição:
Implementação da função main() do trabalho 2 de Banco de Dados.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "listas.h"
#include "transacoes.h"


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
	tipoLista *lista_escalonamento = novaLista(escalonamento);
	contador++;
	
/* COLOCANDO NUMA LISTA DE TRANSACAO  */

	while (scanf("%d %d %c %c",&tempoChegada,&id,&tipo,&atributo) != EOF)
	{
		//auxop = operacao;
		operacao= novaOperacao(id, tempoChegada, tipo, atributo);
		
		adicionaLista (lista_operacao,operacao);

		//verifica se chegou um id diferente
		//printf("%d %d %c %c \n",tempoChegada,id,tipo,atributo);
		aux = verificaLista(lista_transacao,id);

		if(aux != NULL){
			adicionaLista(aux->operacoes,operacao);
		}
		else{
			if (lista_transacao == NULL)
			{
				transacao = novaTransacao(operacao);
				lista_transacao = novaLista(transacao);
				contador++;
			}
			else
			{
				adicionaLista(lista_transacao,novaTransacao(operacao));
				contador++;
			}	
		}

		if (tipo=='C')
		{
			commits++;
			if(commits==contador){
				printf("escalonamento %d\n \n",s);
				//imprimeListaTransacao(lista_transacao);
				//verficar escalonamento
				testeSerialidade (lista_transacao);
				testeVisaoEquivalente (lista_transacao);
				s++;
				contador=0;
				commits=0;
				lista_transacao = NULL;
			}
		}
	}
	printf("\n");
	//imprimeOperacao(lista_operacao);
	//imprimeListaTransacao(lista_transacao);
		
	return 0;
}