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
	
	tipoTransacao *transacao = novaTransacao(operacao);
	tipoLista *lista_transacao = novaLista(transacao);
	tipoTransacao *aux= lista_transacao->item;

	contador++;
	
/* COLOCANDO NUMA LISTA DE TRANSACAO  */

	while (scanf("%d %d %c %c",&tempoChegada,&id,&tipo,&atributo) != EOF)
	{
		operacao= novaOperacao(id, tempoChegada, tipo, atributo);

		//se iniciou um novo escalonamento criar uma nova lista de operação	
		if (lista_operacao == NULL)
		{
			lista_operacao = novaLista(operacao);
		}
		else
		{
			adicionaLista (lista_operacao,operacao);
		}
		
		//verifica se chegou um id diferente para criar as transacoes
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

		//monitora quando se fecha os commits,
		//quando esse numero fecha na mesma qt de transacoes sacabou o escalonamento
		if (tipo=='C')
		{
			commits++;
			if(commits==contador){
				printf("%d ",s);
				imprimeListaTransacao(lista_transacao);
				if(testeSerialidade (lista_transacao,lista_operacao)){
					printf(" NS");
				}
				else
				{
					printf(" SS");
				}
				if (testeVisaoEquivalente (lista_transacao, contador, lista_operacao))
				{
					printf(" SV\n");
				}
				else
				{
					printf(" NV\n");
				}
				
				s++;
				contador=0;
				commits=0;
				lista_transacao = NULL;
				lista_operacao = NULL;
			}
		}
	}
	return 0;
}