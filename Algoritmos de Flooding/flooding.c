// Carlos Henrique Racobaldo Luz Montes, Joseph Samuel Neiva, Roberto Santana Santos

#include "grafosListasAdj.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Abre o arquivo contendo a representação do grafo.
    FILE* arquivo = fopen("arq1.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    // Cria o grafo a partir do arquivo e fecha o arquivo.
    Grafo* g = inicializaGrafo();
    criaGrafoDeArquivo(&g, arquivo);
    fclose(arquivo);

    // Calcula e imprime o número de componentes conexas.
    printf("O numero de componentes conexos e: %d\n", numeroComponentesConexos(g));

    return 0;
}
