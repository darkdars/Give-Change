#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"


#define PROB 0.01 // probabilidade fixa do algoritmo
#define TMAX 100
#define TMIN 5

// Gera um vizinho
// Parametros: solucao actual, vizinho, numero de vertices
//swap two vertices
void gera_vizinho(int a[], int b[], int n)
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

//gera vizinho 1 com +retificacao
void gera_vizinho1(int a[], int b[], int n, float ValorATrocar, float *ValorDasMoedas)
{
    int i, p1, p2, *aux = 0;

    for(i=0; i<n; i++)
        b[i]=a[i];
    
    
    
    p1 = random_l_h(0,n-1);
    p2 = random_l_h(0,n-1);
    
    
 
	// Troca
    b[p1] = a[p2];
    b[p2] = a[p1];
    
    
//implementar a verificaçao
    
    //do{
    //}while(soma!= ValorATrocar);
    
    
    
    
}


// Trepa colinas first-choice
// Parametros: solucao, matriz de adjacencias, numero de vertices e numero de iteracoes
// Devolve o custo da melhor solucao encontrada
int trepa_colinas(int *solucao, float *ValorDasMoedas, int TipoMoedas, float ValorATrocar)  //Solucao, Grafo(onde estao os valores do ficheiro), Tipos de moedas, VALORATROCAR
{
    int *nova_solucao, custo, custo_viz, i;

	nova_solucao = malloc(sizeof(int)*TipoMoedas);
        
    if(nova_solucao == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }
        
	// Avalia solucao inicial
    custo = calcula_fit(solucao, TipoMoedas);
    for(i=0; i<ValorATrocar; i++)
    {
		// Gera vizinho
		gera_vizinho(solucao, nova_solucao, TipoMoedas);
                //gera_vizinho1(sol, nova_solucao, TipoMoedas, ValorATrocar,ValorDasMoedas);
		// Avalia vizinho
		custo_viz = calcula_fit(nova_solucao, TipoMoedas);
		// Aceita vizinho se o custo diminuir (problema de minimizacao)
        if(custo_viz < custo)
        {
			substitui(solucao, nova_solucao, TipoMoedas);
			custo = custo_viz;
        }
    }
    free(nova_solucao);
    return custo;
}

