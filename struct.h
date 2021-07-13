struct Tn{
    int tempoChegada;
    int id;
    char* op;
    char* atributo;
    struct Tn* proximo;
    struct Tn* anterior;
    //fazer a verificação caminhando nessa lista, se voltar pra ele existe ciclo 
};
typedef struct Tn* tn;

