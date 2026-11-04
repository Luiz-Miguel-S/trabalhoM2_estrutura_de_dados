template <typename T>
struct NoFila{
    T info;
    NoFila *eloA, *eloP;
};

template <typename T>
struct Fila{
    NoFila <T> *comeco;
    NoFila <T> *fim;
};

template <typename T>
void inicializar(Fila <T> &f){
    f.comeco = NULL;
    f.fim = NULL;
}

template <typename T>
bool Vazia(Fila <T> f){
    return (f.comeco == NULL) ? true : false;
}

template <typename T>
bool Cheia(Fila <T> f){
    return true;
}

template <typename T>
bool queue(Fila <T> &f, T valor){
    NoFila <T> *novo = new NoFila<T>;

    if( novo == NULL ) return false;
    novo->info = valor;
    novo->eloA = NULL;
    novo->eloP = NULL;

    if( f.fim == NULL ){
        f.fim = novo;
        f.comeco = novo;
    }
    else{
        f.fim->eloP = novo;
        novo->eloA = f.fim;
        f.fim = novo;
    }
    return true;
}

template <typename T>
bool dequeue(Fila <T> &f, T &valor){
    if( Vazia(f) ) return false;

    NoFila <T> *aux = f.comeco;
    valor = aux->info;

    f.comeco = f.comeco->eloP;
    if( f.comeco != NULL ) f.comeco->eloA = NULL;

    delete aux;
    return true;
}

template <typename T>
void liberar(Fila <T> &f){
    NoFila <T> *aux = f.comeco;
    while( aux != NULL ){
        NoFila <T> *prox = aux->eloP;
        delete aux;
        aux = prox;
    }
    f.comeco = NULL;
    f.fim = NULL;
}






