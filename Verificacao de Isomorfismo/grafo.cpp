//main de pedrão
#include <stdio.h>
#include <string.h>
#include "listagrafo.h"

int main() {
    FILE *arq;
    
    arq = fopen("D:\Teoria dos Grafos\verificacao de Isomorfismo\adjacencias_01.txt", "rt");

    if (arq == NULL){
        printf("Problemas na CRIACAO do arquivo\n");
        return 1;
    }

  criaListaAdj(arq);
   
    fclose(arq);
    return 0;
}