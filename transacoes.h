int testeVisaoEquivalente (tipoLista *transacoes);
int testeSerialidade (tipoLista *transacoes,tipoLista *linhaTempo);
int testaCicloGrafo (tipoLista *transacoes) ;
int achaescrita(tipoLista* operacoes,tipoOperacao* w);
int achaleitura(tipoLista* operacoes,tipoOperacao* w);
void criaArestas(tipoTransacao *t1,tipoTransacao* t2);
int percorreAresta(tipoLista* arestas, int id);