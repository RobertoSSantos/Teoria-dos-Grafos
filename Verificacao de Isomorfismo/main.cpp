// Isomorfismo
#include "grafo.h"
#include <stdio.h>
#include <string.h>

int contAresta(FILE *arq) {
  char Linha[100];
  char *result;
  int contaresta = 0;
  int i =1;


  while (!feof(arq)) { // Lê uma linha (inclusive com o '\n')
    result = fgets(Linha, 100, arq);

    if (i==1){
      for (int a = 0; a <= (strlen(Linha)); a++) {
      printf("%c", Linha[a]);
        if (Linha[a] == '1') {
          printf("criciuma");
          contaresta++;
        }
      }
    } 
  }
  return contaresta;
}

int main() {
  FILE *arq1, *arq2;
  bool valid;

  arq1 = fopen("isomorfos/isomorfismo_1.txt", "rt");
  arq2 = fopen("isomorfos/isomorfismo_2.txt", "rt");

  if (arq1 == NULL || arq2 == NULL) {
    printf("Problemas na CRIACAO do arquivo\n");
    return 1;
  }

  Vertice *adj1 = criaListaAdj(arq1);
  // criaListaAdj(arq2);

  int arest = contVert(arq1);
  printf("\nTotal de Vertices %d\n", arest);

  int vert = contAresta(arq1);
  printf("\nTotal de Aresta %d\n", vert);

  int arest2 = contVert(arq2);
  printf("\nTotal de Vertices %d\n", arest2);

  int vert2 = contAresta(arq2);
  printf("\nTotal de Aresta %d\n", vert2);
  
  fclose(arq1);
  fclose(arq2);
  return 0;
}