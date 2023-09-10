#include <stdio.h>
#include <string.h>
#include "listagrafo.h"

Vertice *criaListaAdj(FILE *arq) {
  char Linha[100];
  char *result;
  int i = 1;
  int a, contlinha = 1;
  Vertice *v, *auxv, *aux2;

  v = inicializa_vertice();
  auxv = inicializa_vertice();
  aux2 = inicializa_vertice();

  while (!feof(arq)) { 
    result = fgets(Linha, 100, arq);
    if (result) {
      printf("\nLinha %d : %s\n", i, Linha);
    } // Se foi possível ler
    if (i == 1) {
      for (a = 0; a <= (strlen(Linha)); a++) {
        // for pra criar a lista de vertices
        if (a % 2 == 0) {
          insere_vertice_no_fim(&v, Linha[a]);
        }
      }
    } else {
      for (a = 0; a <= (strlen(Linha)); a++) {
        if (Linha[a] == '0') {
          contlinha++;
        }
        if (Linha[a] == '1') {
          auxv = busca_vertice(v, contlinha);
          aux2 = busca_vertice(v, (i - 1));
          insere_no(&auxv, &aux2);
          contlinha++;
        }
      }
    }
    contlinha = 1;
    i++;
  }
  imprime(v);
  return v;
}

int contVert(FILE *arq) {
  char Linha[100];
  char *result;
  int i = 1;

  while (!feof(arq)) { // Lê uma linha (inclusive com o '\n')
    result = fgets(Linha, 100, arq);
    i++;
  }
  i = i - 2;
  return i;
}

bool sameNumVert(int numVert1, int numVert2){
  return (numVert1 == numVert2);
}

bool sameNumArest(int numArest1, int numArest2){
  return (numArest1 == numArest2);
}