/*
Autores: Giovani G Marciniak e Ovídio Junior
GRR20182981
GRR2018####

Arquivo: listas.h
Modificado em 14/07/2021
Descrição:
Arquivo contém todas as estruturas e funções relacionadas com as listas utilizadas no trabalho.
*/

// LISTAS
typedef struct tipoLista
{
    void *item;

    struct tipoLista *proximo;
    struct tipoLista *anterior;
} tipoLista;

// DEFINIÇÃO DOS TIPOS (OPERAÇÃO, TRANSAÇÃO E ESCALONAMENTO)
typedef struct tipoOperacao
{
    int id;                       // identificador da transação
    int tempoChegada;
    char tipo;                   // tipo da operação (R=read, W=write, C=commit)
    char atributo;               // atributo que será lido/escrito
} tipoOperacao;

typedef struct tipoTransacao
{
    int id;                         // identificador da transação 
    tipoLista *operacoes;           // lista com todas as operacoes da transacao
    tipoLista *arestas;             // arestas das transacoes (será usado para testar seriabilidade)
} tipoTransacao;

typedef struct tipoEscalonamento
{
    int id;                             // identificador do escalonamento
    tipoLista *transacoes;              // todas as transacoes de um escalonamento 
    tipoLista *todasOperacoes;          // todas as operacoes de todas as transacoes do escalonamento, em ordem de chegada
} tipoEscalonamento;


tipoOperacao* novaOperacao(int id, int tempoChegada, char tipo, char atributo);
tipoTransacao* novaTransacao(tipoOperacao* operacao);
tipoEscalonamento* novoEscalonamento(tipoTransacao* transacao, int id);

tipoLista* novaLista(void* item);
void adicionaLista(tipoLista* lista, void* item);
void imprimeOperacao(tipoLista *lista);
void imprimeTransacao(tipoTransacao *lista);
void imprimeListaTransacao(tipoLista *lista);
tipoTransacao* verificaLista(tipoLista* lista, int id);