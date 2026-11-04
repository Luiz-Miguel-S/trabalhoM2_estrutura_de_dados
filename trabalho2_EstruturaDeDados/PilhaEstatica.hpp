#ifndef TAM
#define TAM 50
#endif // TAM

template <typename T>
struct Pilha{
    T vetor[TAM];
    int topo;
};

template <typename T>
void inicializar(Pilha <T> &p){
    p.topo = -1;
}

template <typename T>
bool Vazia(Pilha <T> p){
    return (p.topo == -1) ? true : false;
}

template <typename T>
bool Cheia(Pilha <T> p){
    return (p.topo == TAM-1) ? true : false;
}

template <typename T>
bool push(Pilha <T> &p, T valor){
    if( Cheia(p) ) return false;
    p.topo++;
    p.vetor[p.topo] = valor;
    return true;
}

template <typename T>
bool pop(Pilha <T> &p, T &valor){
    if( Vazia(p) ) return false;
    valor = p.vetor[p.topo];
    p.topo--;
    return true;
}

template <typename T>
bool top(Pilha <T> p, T &valor){
    if( Vazia(p) ) return false;
    valor = p.vetor[p.topo];
    return true;
}

template <typename T>
void liberar(Pilha <T> &p){
}






