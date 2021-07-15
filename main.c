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
	int id = 1;
	int tempoChegada = 0;
	char tipo = 'R';
	char atributo = 'X';

	listaOperacoes *lista_op_teste = novaListaOperacao(novaOperacao(id, tempoChegada, tipo, atributo));

	printf("%d, %d, %c, %c\n",lista_op_teste->op->id, lista_op_teste->op->tempoChegada, lista_op_teste->op->tipo, lista_op_teste->op->atributo);

	id = 2;
	tempoChegada = 1;
	tipo = 'W';
	atributo = 'X';

	addOperacao(lista_op_teste, novaOperacao(id, tempoChegada, tipo, atributo));

	printf("%d, %d, %c, %c\n",lista_op_teste->proximo->op->id, lista_op_teste->proximo->op->tempoChegada, lista_op_teste->proximo->op->tipo, lista_op_teste->proximo->op->atributo);

	return 0;
}