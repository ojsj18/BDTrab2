#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"
// entrada tempo de chegada, id da transação, operação, atributo que será lido/escrito
// saida id do escalonamento, transações, teste 1 e teste 2

void imprimeTempo(tn inicio){
  tn no = inicio->proximo;

    printf("%d ", no->tempoChegada);
    printf("%d ", no->id);
    printf("%s ", no->op);
    printf("%s \n", no->atributo);

}

void printno(tn no){
  printf("%d ", no->tempoChegada);
  printf("%d ", no->id);
  printf("%s ", no->op);
  printf("%s \n", no->atributo);
}

tn criaNo(tn* inicio,int tc,int id, char* op,char* atributo){
  if(inicio== NULL) return 0;
  tn aux = malloc(sizeof(struct Tn));
  if(aux== NULL) return 0;

  aux->tempoChegada= tc;
  aux->id= id;
  aux->op= op;
  aux->atributo= atributo;
  aux->proximo = NULL;
  
  if((*inicio)== NULL){
    *inicio = aux;
  }
  else
  {
    tn *a= inicio;
    while (a->proximo != NULL)
    {
      a = a->proximo;
    }
    a->proximo = aux;
  }
  
  return inicio;
}

int main(void) {
  char arg[10];
  char *token;
  char s[2] = " ";
  tn *inicio;
  int tempo;
  int id;
  char* op;
  char* atributo;
  tn aux;
  tn aux1;

  fgets(arg, 10, stdin);
  token = strtok(arg, s);
  tempo = atoi(token);
  token = strtok(NULL, s);
  id =atoi(token);
  token = strtok(NULL, s);
  op = token;
  token = strtok(NULL, s);
  atributo = token;

  inicio = criaNo(inicio,tempo,id,op,atributo);

  while(fgets(arg, 10, stdin)){

    token = strtok(arg, s);
    tempo = atoi(token);
    token = strtok(NULL, s);
    id =atoi(token);
    token = strtok(NULL, s);
    op = token;
    token = strtok(NULL, s);
    atributo = token;

  }

}
