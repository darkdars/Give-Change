#include "funcao.h"

// Calcula a qualidade de uma solu��o
// Recebe:  A solu��o, a, a matriz de adjac�ncias, mat, e o n�mero de v�rtices, vert
// Devolve: O custo que � o n�mero de liga��es que existem na solu��o
int calcula_fit(int *solucao,int TipoMoedas)
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



