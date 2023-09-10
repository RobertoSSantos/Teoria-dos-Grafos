#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
  struct Vertice *verticeapontado;
  struct No *proxlista;
} No;

typedef struct Vertice {
  char vertice;
  No *lista;
  int numero;
} Vertice;

Vertice *inicializa_vertice() { // usado
  return NULL;
}

No *inicializa_no() { // usado
  return NULL;
}

int lista_vertice_vazia(Vertice *lista) { // usado
  if (lista == NULL)
    return 1;
  return 0;
}

int lista_no_vazia(No *lista) { // usado
  if (lista == NULL)
    return 1;
  return 0;
}

Vertice *aloca_vertice() { // usado
  Vertice *novo_vertice;
  novo_vertice = (Vertice *)malloc(sizeof(Vertice));
  return novo_vertice;
}

No *aloca_no() { // usado
  No *novo_no;
  novo_no = (No *)malloc(sizeof(No));
  return novo_no;
}

int insere_vertice_no_fim(Vertice **l, char e) { // usado
  Vertice *novo_no, *atu;
  novo_no = aloca_vertice();
  if (novo_no == NULL)
    return 0;
  novo_no->vertice = e;
  novo_no->lista = aloca_no();
  novo_no->numero = 1;
  if (novo_no->lista == NULL)
    return 0;
  if (lista_vertice_vazia(*l)) {
    *l = novo_no;
  } else {
    atu = *l;
    novo_no->numero = (novo_no->numero) + 1;
    while (atu->lista->verticeapontado != NULL) {
      novo_no->numero = (novo_no->numero) + 1;
      atu = atu->lista->verticeapontado;
    }
    atu->lista->verticeapontado = novo_no;
  }
  return 1;
}

void imprimeno(No *lista) { // usado
  No *atu;
  atu = lista;
  while (atu != NULL) {
    if (atu->proxlista == NULL) {
      printf(" %c\n", atu->verticeapontado->vertice);
      atu = atu->proxlista;
    } else {
      printf(" %c ->", atu->verticeapontado->vertice);
      atu = atu->proxlista;
    }
  }
}

void imprime(Vertice *listacompleta) { // usado
  Vertice *atu;
  No *aux;
  atu = listacompleta;
  while (atu->lista->verticeapontado != NULL) {
    printf("%c ->", atu->vertice);
    imprimeno(atu->lista->proxlista);
    atu = atu->lista->verticeapontado;
  }
}

Vertice *busca_vertice(Vertice *lista, int i) { // usado
  Vertice *atu;
  atu = lista;
  while ((atu != NULL) && (atu->numero != i)) {
    atu = atu->lista->verticeapontado;
  }
  if (atu == NULL)
    return NULL;
  return atu;
}

int insere_no_fim(No **l, Vertice **e) { // usado
  No *novo_no, *atu;
  novo_no = aloca_no();
  if (novo_no == NULL)
    return 0;
  novo_no->verticeapontado = *e;
  novo_no->proxlista = NULL;
  if (lista_no_vazia(*l)) {
    *l = novo_no;
  } else {
    atu = *l;
    while (atu->proxlista != NULL) {
      atu = atu->proxlista;
    }
    atu->proxlista = novo_no;
  }
  return 1;
}

int insere_no(Vertice **e, Vertice **listatoda) { // usado
  Vertice *verticeatual, *verticeinserido;
  No *novo_no, *aux;
  verticeatual = *listatoda;
  verticeinserido = *e;
  novo_no = aloca_no();
  aux = aloca_no();
  if (novo_no == NULL)
    return 0;
  if (verticeatual->lista->proxlista == NULL) {
    novo_no->verticeapontado = *e;
    novo_no->proxlista = NULL;
    verticeatual->lista->proxlista = novo_no;
  } else {
    aux = verticeatual->lista;
    insere_no_fim(&aux, &verticeinserido);
    verticeatual->lista = aux;
  }
  return 1;
}