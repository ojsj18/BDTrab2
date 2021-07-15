/*
Autores: Giovani G Marciniak e Ovídio Junior
GRR20182981
GRR2018####

Arquivo: listas.h
Modificado em 14/07/2021
Descrição:
Arquivo contém todas as estruturas e funções relacionadas com as listas utilizadas no trabalho.
*/

// DEFINIÇÃO DOS TIPOS (OPERAÇÃO, TRANSAÇÃO E ESCALONAMENTO)
typedef struct tipoOperacao
{
    int id;                       // identificador da transação
    int tempoChegada;
    char tipo;                   // tipo da operação (R=read, W=write, C=commit)
    char atributo;               // atributo que será lido/escrito
} tipoOperacao;

typedef struct listaOperacoes
{
    tipoOperacao *op;

    struct listaOperacoes *proximo;
    struct listaOperacoes *anterior;
} listaOperacoes;

typedef struct tipoTransacao
{
    int id;                         // identificador da transação 
    listaOperacoes *operacoes;       // lista com todas as operacoes da transacao
    listaTransacoes *arestas;        // arestas das transacoes (será usado para testar seriabilidade)
} tipoTransacao;

typedef struct tipoEscalonamento
{
    int id;                                 // identificador do escalonamento
    listaTransacoes *transacoes;             // todas as transacoes de um escalonamento 
    listaTransacoes *transacoesAtivas;       // apenas as transacoes ativas, ou seja sem commit (usado para saber quando termina um escalonamento)
    listaOperacoes *todasOperacoes;          // todas as operacoes de todas as transacoes do escalonamento, em ordem de chegada
} tipoEscalonamento;

// LISTAS
/*typedef struct lista
{
    void *item;

    void *proximo;
    void *anterior;
} lista;*/

typedef struct listaTransacoes
{
    tipoTransacao *t;

    struct listaTransacoes *proximo;
    struct listaTransacoes *anterior;
} listaTransacoes;

typedef struct listaEscalonamento
{
    tipoEscalonamento *s;

    struct listaEscalonamento *proximo;
    struct listaEscalonamento *anterior;
} listaEscalonamento;


listaOperacoes* novaListaOperacao(tipoOperacao* operacao);
tipoOperacao* novaOperacao(int id, int tempoChegada, char tipo, char atributo);
void addOperacao(listaOperacoes* lista, tipoOperacao* operacao);

tipoTransacao* novaTransacao(tipoOperacao* operacao);
listaTransacoes* novaListaTransacao(tipoTransacao* transacao);