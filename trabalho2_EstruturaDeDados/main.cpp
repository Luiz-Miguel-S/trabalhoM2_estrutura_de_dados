// Trabalho 2
// Luiz Miguel Silvino


#include <iostream>
#include <cmath>

using namespace std;

// Escolha da estrutura (descomentar apenas uma pilha e uma fila)
//#include "PilhaEstatica.hpp"
#include "PilhaDinamica.hpp"

//#include "FilaEstatica.hpp"
//#include "FilaCircular.hpp"
#include "FilaDinamica.hpp"


enum TipoToken { TOKEN_NUMERO, TOKEN_VARIAVEL, TOKEN_OPERADOR };

// Estrutura para guardar cada elemento da expressao na fila NPI
struct Token {
    TipoToken tipo;
    double valor;        
    char var;            // Para variaveis de 1 letra
    char op;             
};

// Tabela para guardar os valores digitados para as variaveis
struct TabelaVariavel {
    char nome;
    double valor;
};

bool ehLetra(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool ehDigito(char c) {
    return (c >= '0' && c <= '9');
}

int precedencia(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

bool associativoDireita(char op) {
    return (op == '^');
}

bool eAbertura(char c) {
    return (c == '(' || c == '[' || c == '{');
}

bool eFechamento(char c) {
    return (c == ')' || c == ']' || c == '}');
}

bool combinaDelimitador(char abre, char fecha) {
    return (abre == '(' && fecha == ')') ||
           (abre == '[' && fecha == ']') ||
           (abre == '{' && fecha == '}');
}

// Busca a variavel para nao pedir o valor duas vezes
int buscarVariavel(TabelaVariavel tabela[], int qtd, char var) {
    for (int i = 0; i < qtd; i++) {
        if (tabela[i].nome == var) return i;
    }
    return -1;
}

// Imprime a fila NPI
void imprimirNPI(Fila<Token> &filaNPI) {
    cout << "\nNotacao Polonesa Invertida (NPI): ";
    
    Fila<Token> filaAuxiliar;
    inicializar(filaAuxiliar);
    
    Token t;
    bool primeiro = true;

    // Esvazia a fila NPI, imprime e guarda na fila auxiliar
    while (dequeue(filaNPI, t)) {
        if (!primeiro) cout << " ";
        primeiro = false;

        if (t.tipo == TOKEN_NUMERO) {
            cout << t.valor;
        } else if (t.tipo == TOKEN_VARIAVEL) {
            cout << t.var;
        } else if (t.tipo == TOKEN_OPERADOR) {
            cout << t.op;
        }

        queue(filaAuxiliar, t);
    }
    cout << endl;


    inicializar(filaNPI);

    while (dequeue(filaAuxiliar, t)) {
        queue(filaNPI, t);
    }
}

int main() {
    char expressao[300];

    Pilha<char> pilhaOperadores;
    Fila<Token> filaNPI;

    inicializar(pilhaOperadores);
    inicializar(filaNPI);

    cout << "Digite a expressao numerica: ";
    if (!cin.getline(expressao, 300)) {
        cout << "Erro na leitura." << endl;
        return 0;
    }

    TabelaVariavel variaveis[50];
    int qtdVariaveis = 0;

    int i = 0;
    bool ultimoFoiOpOuAbre = true; // Ajuda a validar erros sintaticos

    while (expressao[i] != '\0') {
        char c = expressao[i];

        if (c == ' ' || c == '\t') {
            i++;
            continue;
        }

        // Trata os numeros
        if (ehDigito(c)) {
            double num = 0;
            while (ehDigito(expressao[i])) {
                num = num * 10 + (expressao[i] - '0');
                i++;
            }

            Token t;
            t.tipo = TOKEN_NUMERO;
            t.valor = num;

            if (!queue(filaNPI, t)) {
                cout << "\nErro: Fila NPI cheia." << endl;
                return 0;
            }

            ultimoFoiOpOuAbre = false;
            continue;
        }

        // Trata as variaveis (apenas 1 letra)
        if (ehLetra(c)) {
            char varNome = c;
            i++;

            if (ehLetra(expressao[i])) {
                cout << "\nErro: Variaveis devem ter apenas 1 letra." << endl;
                return 0;
            }

            // Salva na tabela se for a primeira vez que aparece
            if (buscarVariavel(variaveis, qtdVariaveis, varNome) == -1) {
                variaveis[qtdVariaveis].nome = varNome;
                qtdVariaveis++;
            }

            Token t;
            t.tipo = TOKEN_VARIAVEL;
            t.var = varNome;
            queue(filaNPI, t);

            ultimoFoiOpOuAbre = false;
            continue;
        }

        // Delimitadores de abertura
        if (eAbertura(c)) {
            push(pilhaOperadores, c);
            ultimoFoiOpOuAbre = true;
            i++;
            continue;
        }

        // Delimitadores de fechamento
        if (eFechamento(c)) {
            char topoOp;
            bool casou = false;

            while (pop(pilhaOperadores, topoOp)) {
                if (eAbertura(topoOp)) {
                    if (combinaDelimitador(topoOp, c)) {
                        casou = true;
                    } else {
                        cout << "\nErro sintatico: Incompatibilidade entre " << topoOp << " e " << c << endl;
                        return 0;
                    }
                    break;
                }

                Token t;
                t.tipo = TOKEN_OPERADOR;
                t.op = topoOp;
                queue(filaNPI, t);
            }

            if (!casou) {
                cout << "\nErro sintatico: Fechamento " << c << " sem abertura correspondente." << endl;
                return 0;
            }

            ultimoFoiOpOuAbre = false;
            i++;
            continue;
        }

        // Operadores
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            if (ultimoFoiOpOuAbre) {
                cout << "\nErro sintatico: Operador " << c << " mal posicionado." << endl;
                return 0;
            }

            char topoOp;
            while (top(pilhaOperadores, topoOp) && !eAbertura(topoOp)) {
                int precAtual = precedencia(c);
                int precTopo = precedencia(topoOp);

                if ((precTopo > precAtual) || (precTopo == precAtual && !associativoDireita(c))) {
                    pop(pilhaOperadores, topoOp);
                    Token t;
                    t.tipo = TOKEN_OPERADOR;
                    t.op = topoOp;
                    queue(filaNPI, t);
                } else {
                    break;
                }
            }

            push(pilhaOperadores, c);
            ultimoFoiOpOuAbre = true;
            i++;
            continue;
        }

        cout << "\nErro: Caractere invalido '" << c << "'" << endl;
        return 0;
    }

    if (ultimoFoiOpOuAbre && i > 0) {
        cout << "\nErro sintatico: Expressao terminando em operador." << endl;
        return 0;
    }

    // Esvazia a pilha de operadores para a NPI
    char topoOp;
    while (pop(pilhaOperadores, topoOp)) {
        if (eAbertura(topoOp)) {
            cout << "\nErro sintatico: Abertura '" << topoOp << "' nao foi fechada." << endl;
            return 0;
        }
        Token t;
        t.tipo = TOKEN_OPERADOR;
        t.op = topoOp;
        queue(filaNPI, t);
    }

    imprimirNPI(filaNPI);

    // Pede os valores das variaveis
    if (qtdVariaveis > 0) {
        cout << "\n--- Valores das variaveis ---" << endl;
        for (int k = 0; k < qtdVariaveis; k++) {
            cout << variaveis[k].nome << " = ";
            cin >> variaveis[k].valor;
        }
    }

    // Calcula o resultado da NPI
    Pilha<double> pilhaValores;
    inicializar(pilhaValores);

    Token tokenAtual;
    while (dequeue(filaNPI, tokenAtual)) {
        if (tokenAtual.tipo == TOKEN_NUMERO) {
            push(pilhaValores, tokenAtual.valor);
        }
        else if (tokenAtual.tipo == TOKEN_VARIAVEL) {
            int idx = buscarVariavel(variaveis, qtdVariaveis, tokenAtual.var);
            push(pilhaValores, variaveis[idx].valor);
        }
        else if (tokenAtual.tipo == TOKEN_OPERADOR) {
            double val2, val1;
            if (!pop(pilhaValores, val2) || !pop(pilhaValores, val1)) {
                cout << "\nErro: Faltam operandos para o operador " << tokenAtual.op << endl;
                return 0;
            }

            double res = 0;
            switch (tokenAtual.op) {
                case '+': res = val1 + val2; break;
                case '-': res = val1 - val2; break;
                case '*': res = val1 * val2; break;
                case '/': 
                    if (val2 == 0) {
                        cout << "\nErro: Divisao por zero." << endl;
                        return 0;
                    }
                    res = val1 / val2; 
                    break;
                case '^': res = pow(val1, val2); break;
            }
            push(pilhaValores, res);
        }
    }

    double resultadoFinal;
    if (pop(pilhaValores, resultadoFinal) && Vazia(pilhaValores)) {
        cout << "\nResultado final: " << resultadoFinal << endl;
    } else {
        cout << "\nErro no calculo final." << endl;
    }

    // Limpa memoria
    liberar(pilhaOperadores);
    liberar(filaNPI);
    liberar(pilhaValores);

    return 0;
}