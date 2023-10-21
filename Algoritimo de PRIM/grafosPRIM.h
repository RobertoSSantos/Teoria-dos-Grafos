#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define INF INT_MAX

typedef struct No {
    struct Grafo *prox_letra;
    struct No *lista_adj;
    int peso;  // Peso da aresta
} No;

typedef struct Grafo {
    char rotulo;
    No *lista_principal;
    bool visitado;  // Para verificar se o vértice foi visitado no Algoritmo de Prim
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
