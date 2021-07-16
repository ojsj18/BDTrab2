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

	/* CRIANDO 2 OPERACOES */
	int id = 1;
	int tempoChegada = 0;
	char tipo = 'R';
	char atributo = 'X';

	tipoLista *lista_teste = novaLista(novaOperacao(id, tempoChegada, tipo, atributo));

	tipoOperacao *operacao = (tipoOperacao *) lista_teste->item;

	printf("%d, %d, %c, %c\n",operacao->id, operacao->tempoChegada, operacao->tipo, operacao->atributo);

	id = 2;
	tempoChegada = 1;
	tipo = 'W';
	atributo = 'X';

	adicionaLista (lista_teste, novaOperacao(id, tempoChegada, tipo, atributo));

	operacao = (tipoOperacao *) lista_teste->proximo->item;

	printf("%d, %d, %c, %c\n",operacao->id, operacao->tempoChegada, operacao->tipo, operacao->atributo);

	/* COLOCANDO NUMA LISTA DE TRANSACAO */
	


	return 0;
}