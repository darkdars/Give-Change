#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "utils.h"

// Preenche uma estrutura com os progenitores da pr�xima gera��o, de acordo com o resultados do torneio binario (tamanho de torneio: 2)
// Par�metros de entrada: popula��o actual (pop), estrutura com par�metros (d) e popula��o de pais a encher
void tournament(int a[], int b[], int n)
{
    int i, p1, p2, *aux = 0;

    for(i=0; i<n; i++)
        b[i]=a[i];
    
    
    
    p1 = random_l_h(0,n-1);
    p2 = random_l_h(0,n-1);
    
    
 
	// Troca
    b[p1] = a[p2];
    b[p2] = a[p1];
    
}

// Operadores geneticos a usar na gera��o dos filhos
// Par�metros de entrada: estrutura com os pais (parents), estrutura com par�metros (d), estrutura que guardar� os descendentes (offspring)
void genetic_operators(int *parents, int *best_run, int TipoMoedas)
{
    // Recombina��o com um ponto de corte
	crossover(parents, best_run, TipoMoedas);
	// Muta��o bin�ria
	mutation(parents, TipoMoedas);
}

// Preenche o vector descendentes com o resultado das opera��es de recombina��o
// Par�metros de entrada: estrutura com os pais (parents), estrutura com par�metros (d), estrutura que guardar� os descendentes (offspring)
void crossover(int *parents,int *best_run, int TipoMoedas)
{
      
    /*   int i, p1, p2, *aux = 0;
    
    p1 = random_l_h(0,TipoMoedas-1);
    p2 = random_l_h(0,TipoMoedas-1);
    
    
 
	// Troca
    parents[p1] = best_run[p2];
    */
    float pr = 0.10;
    int i, j, point;

	for (i=0; i<TipoMoedas; i++)
	{
		if (rand_01() < pr)
		{
			point = random_l_h(0, TipoMoedas-1);
			for (j=0; j<point; j++)
			{
				parents[j] = best_run[j];
			}
			for (j=point; j<TipoMoedas; j++)
			{
				parents[j] = best_run[j];
			}
		}
		else
		{
			parents[i] = best_run[i];
		}
	}
    
    
    
	
}

// Muta��o bin�ria com v�rios pontos de muta��o
// Par�metros de entrada: estrutura com os descendentes (offspring) e estrutura com par�metros (d)
void mutation(int *parents, int TipoMoedas)
{
     /*
   int i, p1, p2, *aux;

   aux = malloc(sizeof(int) * TipoMoedas);
   if(aux == NULL){
       printf("ERRO A ALOCAR MEMORIA!\n");
       exit(1);
   }
   
    for(i=0; i<TipoMoedas; i++)
       aux[i] = parents[i];
    
    
    
    p1 = random_l_h(0,TipoMoedas-1);
    p2 = random_l_h(0,TipoMoedas-1);
    
    
 
	// Troca
    parents[p1] = aux[p2];
    parents[p2] = aux[p1];
    */
    
    	int i, j,pos1,pos2,aux;
        float pm = 0.10;

	for (i=0; i<TipoMoedas; i++){
            if(rand_01() < pm){
                do
                    pos1 = random_l_h(0,TipoMoedas-1);
                while(parents[pos1] == 0);
                aux = parents[pos1];
                parents[pos1] = parents[i];
                parents[i] = aux;
            }
        }
    
    
    
}
