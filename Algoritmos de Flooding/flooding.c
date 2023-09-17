/*Carlos Henrique Racobaldo Luz Montes, Joseph Samuel Neiva, 
Roberto Santana Santos*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "grafo.h"

// Função recursiva para realizar o flooding (ou DFS)
void flooding(Vertice *vertice, bool *visitado) {
    // Se o vertice já foi visitado, retorna
    if (visitado[vertice->numero]) return;
    
    // Marca o vertice atual como visitado
    visitado[vertice->numero] = true;

    // Continua o flooding para todos os vizinhos
    No *noAtual = vertice->lista->proxlista;
    while (noAtual != NULL) {
        flooding(noAtual->verticeapontado, visitado);
        noAtual = noAtual->proxlista;
    }
}
// Esta função calcula o número de componentes conexas em um grafo
int numeroComponentesConexas(Vertice *listaVertices, int numVert) {
    bool visitado[numVert];
    int i, numComponentes = 0;

    // Inicialmente, marca todos os vértices como não visitados
   for (i = 0; i < numVert; i++) {
        visitado[i] = false;
    }

    // Para cada vertice, se não foi visitado, inicia um novo flooding
    Vertice *v = listaVertices;
    while (v != NULL) {
        if (!visitado[v->numero]) {
            flooding(v, visitado);
            numComponentes++;
        }
        v = v->lista->verticeapontado;
    }

    return numComponentes;
}

int main() {
    FILE *arq1;
    // FILE *arq2;
    arq1 = fopen("arquivo1.txt", "r");
    // arq2 = fopen("arquivo2.txt", "r");

    int numVert1 = contVert(arq1);
    // int numVert2 = contVert(arq2);

    Vertice *listaVertices1 = criaListaAdj(arq1);
    // Vertice *listaVertices2 = criaListaAdj(arq2);

    int compConexas1 = numeroComponentesConexas(listaVertices1, numVert1);
    // int compConexas2 = numeroComponentesConexas(listaVertices2, numVert2);

    printf("Número de componentes conexas no arquivo1: %d\n", compConexas1);
    // printf("Número de componentes conexas no arquivo2: %d\n", compConexas2);

    fclose(arq1);
    // fclose(arq2);

    return 0;
}
