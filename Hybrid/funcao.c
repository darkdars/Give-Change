#define _CRT_SECURE_NO_WARNINGS 1
#include "algoritmo.h"
#include "funcao.h"

// Avaliacao da popula��o
// Par�metros de entrada: populacao (pop), estrutura com parametros (d) e matriz com dados do problema (mat)
// Par�metros de sa�da: Preenche pop com os valores de fitness e de validade para cada solu��o
int evaluate(int *solucao,int TipoMoedas)
{
        int total=0;
	int i, j;

	for(i=0; i<TipoMoedas; i++){
              if(*(solucao+i) != 0){
                total += *(solucao+i);
            }
        }
          
        
	return total;
}
