
template <typename T>
struct NoPilha{
    T info;
    NoPilha *eloA, *eloP;
};

template <typename T>
struct Pilha{
    NoPilha <T> *topo;
};

template <typename T>
void inicializar(Pilha <T> &p){
    p.topo = NULL;
}

template <typename T>
bool Vazia(Pilha <T> p){
    return (p.topo == NULL) ? true : false;
}

template <typename T>
bool Cheia(Pilha <T> p){
    return true;
}

template <typename T>
bool push(Pilha <T> &p, T valor){
    NoPilha <T> *novo = new NoPilha<T>;

    if( novo == NULL ) return false;
    novo->info = valor;
    novo->eloA = NULL;
    novo->eloP = NULL;

    if( p.topo == NULL ){
        p.topo = novo;
    }
    else{
        p.topo->eloP = novo;
        novo->eloA = p.topo;
        p.topo = novo;
    }
    return true;
}

template <typename T>
bool pop(Pilha <T> &p, T &valor){
    if( Vazia(p) ) return false;

    valor = p.topo->info;
    NoPilha <T> *aux = p.topo;

    p.topo = p.topo->eloA;
    if( p.topo != NULL ) p.topo->eloP = NULL;

    delete aux;
    return true;
}

template <typename T>
bool top(Pilha <T> p, T &valor){
    if( Vazia(p) ) return false;
    valor = p.topo->info;
    return true;
}

template <typename T>
void liberar(Pilha <T> &p){
    NoPilha <T> *aux = p.topo;
    while( aux != NULL ){
        NoPilha <T> *ant = aux->eloA;
        delete aux;
        aux = ant;
    }
    p.topo = NULL;
}






