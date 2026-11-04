#ifndef TAM
#define TAM 50
#endif // TAM

template <typename T>
struct Fila{
    T vetor[TAM];
    int comeco, fim;
};

template <typename T>
void inicializar(Fila <T> &f){
    f.comeco = 0;
    f.fim = -1;
}

template <typename T>
bool Vazia(Fila <T> f){
    return (f.comeco > f.fim) ? true : false;
}

template <typename T>
bool Cheia(Fila <T> f){
    return (f.fim == TAM-1) ? true : false;
}

template <typename T>
bool queue(Fila <T> &f, T valor){
    if( Cheia(f) ) return false;
    f.fim++;
    f.vetor[f.fim] = valor;
    return true;
}

template <typename T>
bool dequeue(Fila <T> &f, T &valor){
    if( Vazia(f) ) return false;
    valor = f.vetor[f.comeco];
    f.comeco++;
    return true;
}

template <typename T>
void liberar(Fila <T> &f){
}






