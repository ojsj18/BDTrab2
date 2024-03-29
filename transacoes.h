/*
Autores: Giovani G Marciniak e Ovídio Junior
GRR20182981
GRR20182667

Arquivo: listas.c
Modificado em 22/07/2021
Descrição:
Funções relacionadas aos algoritmos de detecção de conflitos de escalonamento de transações concorrentes.
*/

void criaArestas(tipoTransacao *t1,tipoTransacao* t2);
int testaCicloGrafo (tipoLista *transacoes) ;

tipoLista *CriaEscalonamentoSerial(tipoLista *transacoes, int n_transacoes, int n_trocas);
int comparaVisaoEquivalente(tipoLista *operacoes, tipoLista *serial);
int testeSerialidade (tipoLista *transacoes, tipoLista *linhaTempo);
int testeVisaoEquivalente (tipoLista *transacoes, int n_transacoes, tipoLista *operacoes);
int testeescrita(tipoLista* operacoes);

int achaescrita(tipoLista* operacoes,tipoOperacao* w);
int achaleitura(tipoLista* operacoes,tipoOperacao* w);
void criaArestas(tipoTransacao *t1,tipoTransacao* t2);
int percorreAresta(tipoLista* arestas, int id);

