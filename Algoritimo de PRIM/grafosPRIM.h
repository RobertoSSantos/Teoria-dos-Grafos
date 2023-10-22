#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#define INF INT_MAX  // Define o valor infinito como o valor máximo de um int

// Estrutura para representar um nó da lista de adjacência
typedef struct No {
    struct Grafo *prox_letra;  // Ponteiro para o próximo vértice na lista principal
    struct No *lista_adj;      // Ponteiro para o próximo nó na lista de adjacência
    int peso;                 // Peso da aresta
} No;

// Estrutura para representar um vértice do grafo
typedef struct Grafo {
    char rotulo;              // Rótulo do vértice
    No *lista_principal;     // Ponteiro para a lista de adjacência do vértice
    bool visitado;           // Flag para verificar se o vértice foi visitado no Algoritmo de Prim
} Grafo;

// Inicializa o grafo retornando um ponteiro nulo
Grafo* inicializaGrafo() {
    return NULL;
}

// Verifica se o grafo está vazio
int grafoVazio(Grafo *lista){
    return lista == NULL;
}

// Aloca espaço na memória para um novo vértice do grafo
Grafo* alocaGrafo() {
    return (Grafo*) malloc(sizeof(Grafo));
}

// Aloca espaço na memória para um novo nó
No* alocaNo(){
    return (No*) malloc(sizeof(No));
}

// Insere um novo vértice na lista principal do grafo
int insereListaPrincipal(Grafo** g, char rotulo) {
    Grafo* novo_no = alocaGrafo();
    novo_no->lista_principal = alocaNo();
    novo_no->rotulo = rotulo;
    novo_no->lista_principal->prox_letra = NULL; // Inicialização correta

    if(novo_no == NULL || novo_no->lista_principal == NULL) return 0;

    if(grafoVazio(*g)) {
        *g = novo_no;
    } else {
        Grafo* atu = *g;
        while(atu->lista_principal->prox_letra) {
            atu = atu->lista_principal->prox_letra;
        }
        atu->lista_principal->prox_letra = novo_no;
    }
    return 1;
}

// Busca um vértice na lista principal do grafo pelo índice
Grafo* buscaVertice(Grafo *g, int i){
  Grafo *atu;
  atu = g;
  int c = 1;

  while((atu != NULL) && (i != c)){
    atu = atu->lista_principal->prox_letra;
    c++;
  }

  if(atu == NULL) return NULL;
  return atu;
}

// Insere um nó na lista de adjacência de outro nó
int insereNoFimAdj(No **n, Grafo **g){
  No *novo_no, *atu;
  novo_no = alocaNo();

  if(novo_no == NULL) return 0;

  novo_no->prox_letra = *g;
  novo_no->lista_adj = NULL;

  if(*n == NULL) *n = novo_no;
  else {
    atu =*n;
    while(atu->lista_adj != NULL)
      atu = atu->lista_adj;
    atu->lista_adj =novo_no;
  }
  return 1;
}

// Constrói um grafo a partir das informações presentes em um arquivo
void criaGrafoDeArquivo(Grafo **g, FILE *arq){
  int i, j = 0;
  char Linha[300];
  Grafo *no_inserido, *no_base;

  no_inserido = inicializaGrafo();
  no_base = inicializaGrafo();

  if(fgets(Linha, 100, arq)) {
    for(i = 0; i < strlen(Linha); i++) {
      if(Linha[i] != ' ') {
        insereListaPrincipal(g, Linha[i]);
      }
    }
  }

  while(!feof(arq)){
    if(fgets(Linha, 100, arq)) {
      for(i = 0; i <= strlen(Linha); i++) {
        if(Linha[i] == '1') {
          no_inserido = buscaVertice(*g, i+1);
          no_base = buscaVertice(*g, j+1);
          if (no_inserido && no_base) {
            insereNoFimAdj(&no_inserido->lista_principal, &no_base);
          }
        }
      }
    j++;
    }
  } 
}


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


// Função para implementar o Algoritmo de Prim para encontrar a árvore geradora mínima de um grafo
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
