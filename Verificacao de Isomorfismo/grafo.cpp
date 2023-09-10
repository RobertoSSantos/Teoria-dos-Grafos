//main de pedrão
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "listagrafo.h"

int main() {
  FILE *arq;
  char Linha[100];
  char *result;
  int i, a, contlinha=1;
  Vertice *v, *auxv, *aux2;

arq = fopen("Adjacencias_01.txt", "rt");
v=inicializa_vertice();
auxv=inicializa_vertice();
aux2=inicializa_vertice();
  
if (arq == NULL)
{
    printf("Problemas na CRIACAO do arquivo\n");
    return 1;
}

i = 1;
while (!feof(arq)){	// Lê uma linha (inclusive com o '\n')
    result = fgets(Linha, 100, arq);  
    // 'fgets' lê até 99 caracteres ou até o '\n'
    if (result)  // Se foi possível ler
	  //printf("\nLinha %d : %s",i,Linha);
    if (i==1){
      for(a=0; a<=(strlen(Linha)); a++){
      //for pra criar a lista de vertices
        if (a%2==0){
          insere_vertice_no_fim(&v, Linha[a]);
        }
      }
    }else{
      for(a=0; a<=(strlen(Linha)); a++){
          if(Linha[a]=='0'){
            contlinha++;
          }
          if(Linha[a]=='1'){
            auxv=busca_vertice(v, contlinha);
            //printf("%c\n", auxv->vertice);
            aux2=busca_vertice(v, (i-1));
            //printf("vertice adjacente: %c\n", aux2->vertice);
            insere_no(&auxv, &aux2);
            contlinha++;
          }
      }
  }
      contlinha=1;
      i++;
}
  imprime(v);
  fclose(arq);
  return 0;
}

