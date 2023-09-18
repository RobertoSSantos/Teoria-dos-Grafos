#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Definindo a estrutura de um Nó
typedef struct No {
    struct Grafo *prox_letra;  // Aponta para o próximo vértice na lista principal do grafo
    struct No *lista_adj;      // Aponta para o próximo nó na lista de adjacência
} No;

// Definindo a estrutura de um Grafo
typedef struct Grafo {
    char rotulo;                // Representa o rótulo do vértice (uma letra)
    No *lista_principal;       // Aponta para a lista de adjacência deste vértice
} Grafo;

// Inicializa o grafo retornando um ponteiro nulo
Grafo* inicializaGrafo() {
    return NULL;
}

// Verifica se o grafo está vazio
int grafoVazio(Grafo *lista){
    return lista == NULL;
}

// Verifica se a lista de adjacência de um nó está vazia
int listaNoVazia(No *lista){
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

  if(listaNoVazia(*n)) *n = novo_no;
  else {
    atu =*n;
    while(atu->lista_adj != NULL)
      atu = atu->lista_adj;
    atu->lista_adj =novo_no;
  }
  return 1;
}
// Imprime a lista de adjacência de um nó
void imprimeNo(No *lista){
  No *atu;
  atu = lista;

  while(atu != NULL){
    if(atu->lista_adj == NULL){
      printf("%c ->", atu->prox_letra->rotulo);
      atu = atu->lista_adj;
    } else {
      printf("%c ->", atu->prox_letra->rotulo);
      atu = atu->lista_adj;
    }
  }
}
// Imprime a representação do grafo
void imprimeGrafo(Grafo *g){
  Grafo *atu;
  No *aux;

  atu = g;
  while(atu->lista_principal->prox_letra != NULL){
    if( atu->rotulo != ' ') printf("%c ->", atu->rotulo);
    imprimeNo(atu->lista_principal->lista_adj);
    atu = atu->lista_principal->prox_letra;
    printf("\n");
  }
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


// Definição da estrutura para uma fila que armazenará vértices.
typedef struct Fila {
    No* vertice;          // Ponteiro para o nó (vértice) da fila.
    struct Fila* prox;    // Ponteiro para o próximo elemento da fila.
} Fila;



// Função para adicionar (enfileirar) um vértice à fila.
void enfileira(Fila** f, No* v) {
    Fila* novo = (Fila*)malloc(sizeof(Fila));
    novo->vertice = v;
    novo->prox = NULL;

    if (*f==NULL) {
        *f = novo;
    } else {
        Fila* temp = *f;
        while (temp->prox) {
            temp = temp->prox;
        }
        temp->prox = novo;
    }
}

// Função para remover (desenfileirar) um vértice da fila.
No* desenfileira(Fila** f) {
    if (*f==NULL) {
        return NULL;
    }
    Fila* temp = *f;
    No* ret = temp->vertice;
    *f = (*f)->prox;
    free(temp);
    return ret;
}

// Função de busca em largura para explorar o grafo.
void BFS(Grafo* g, No* start, bool* visited) {
    Fila* fila = NULL;
    enfileira(&fila, start);

    while (fila!=NULL) {
        No* atual = desenfileira(&fila);
        int index = atual->prox_letra->rotulo - 'A';
        if (index >= 0 && index < 26 && !visited[index]) {
            visited[index] = true;

            No* vizinho = atual->lista_adj;
            while (vizinho) {
                int vIndex = vizinho->prox_letra->rotulo - 'A';
                if (vIndex >= 0 && vIndex < 26 && !visited[vIndex]) {
                    enfileira(&fila, vizinho);
                }
                vizinho = vizinho->lista_adj;
            }
        }
    }
}

// Função para calcular o número de componentes conexas no grafo.
int numeroComponentesConexos(Grafo* g) {
    int count = 0;
    bool visited[26] = {false};

    Grafo* atual = g;
    while (atual) {
        int index = atual->rotulo - 'A';
        if (index >= 0 && index < 26 && !visited[index]) {
            BFS(g, atual->lista_principal, visited);
            count++;
        }
        atual = atual->lista_principal->prox_letra;
    }
    return count;
}
