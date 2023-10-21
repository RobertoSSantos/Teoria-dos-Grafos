#include "grafosPRIM.h" 

// Função para encontrar o vértice com o mínimo valor de chave, a partir do conjunto de vértices ainda não incluídos na árvore geradora mínima
Grafo* minChave(int chave[], bool mstSet[], int V, Grafo* g) {
    int min = INF;
    Grafo* min_index = NULL;
    Grafo* atu = g;
    int v = 0;
    while(atu) {
        if (mstSet[v] == false && chave[v] < min) {
            min = chave[v];
            min_index = atu;
        }
        atu = atu->lista_principal->prox_letra;
        v++;
    }
    return min_index;
}

void primMST(Grafo* g) {
    int V = 0;  // Contar o número de vértices
    Grafo* atu = g;
    while(atu) {
        V++;
        atu = atu->lista_principal->prox_letra;
    }

    int parent[V];  // Array para armazenar a árvore geradora mínima
    int chave[V];   // Valores usados para escolher o mínimo valor de aresta
    bool mstSet[V]; // Representa o conjunto de vértices incluídos na MST

    for (int i = 0; i < V; i++) {
        chave[i] = INF;
        mstSet[i] = false;
    }

    chave[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        Grafo* u = minChave(chave, mstSet, V, g);
        int u_index = 0;
        atu = g;
        while(atu != u) {
            u_index++;
            atu = atu->lista_principal->prox_letra;
        }

        mstSet[u_index] = true;

        No* adj = u->lista_principal->lista_adj;
        int v_index = 0;
        while(adj) {
            if (adj->peso && mstSet[v_index] == false && adj->peso < chave[v_index]) {
                parent[v_index] = u_index;
                chave[v_index] = adj->peso;
            }
            adj = adj->lista_adj;
            v_index++;
        }
    }

    printf("Aresta   Peso\n");
    for (int i = 1; i < V; i++) {
        printf("%c - %c    %d \n", buscaVertice(g, parent[i] + 1)->rotulo, buscaVertice(g, i + 1)->rotulo, chave[i]);
    }
}

int main() {
    FILE* arquivo = fopen("arq1.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    Grafo* g = inicializaGrafo();
    criaGrafoDeArquivo(&g, arquivo);
    fclose(arquivo);

    primMST(g);

    return 0;
}