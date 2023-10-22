//Carlos Henrique Racobaldo, Joseph Samuel Neiva, Roberto Santana Santos
#include "grafosPRIM.h" 


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