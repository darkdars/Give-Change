#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algoritmo.h"
#include "utils.h"

// Inicializa��o do gerador de n�meros aleat�rios
void init_rand()
{
	srand((unsigned)time(NULL));
}

// Leitura dos par�metros e dos dados do problema
// Par�metros de entrada: Nome do ficheiro e matriz a preencher com os dados dos objectos (peso e valor)
// Par�metros de sa�da: Devolve a estrutura com os par�metros
float* init_dados(char *nome, int *TipoMoedas, float *ValorATrocar)
{
	FILE *f;
	float *p, *q;
	int i;
        
	f=fopen(nome, "r");
	if(!f)
	{
		printf("Erro no acesso ao ficheiro dos dados\n");
		exit(1);
	}
        
	// Numero de MOEDAS
	fscanf(f, "%d", TipoMoedas);
        
	// Valor a Trocar
	fscanf(f, " %f", ValorATrocar);
	// Alocacao dinamica da matriz
	p = malloc(sizeof(int)*(*TipoMoedas));
	if(!p)
	{
	    printf("Erro na alocacao de memoria\n");
	    exit(1);
	}
	q=p;
	// Preenchimento da matriz
	for(i=0; i<*TipoMoedas; i++){
             fscanf(f, " %f", q++);
        }
     
	fclose(f);
	return p;
}


// Simula o lan�amento de uma moeda, retornando o valor 0 ou 1
int flip()
{
	if ((((float)rand()) / RAND_MAX) < 0.5)
		return 0;
	else
		return 1;
}

// Criacao da populacao inicial. O vector e alocado dinamicamente
// Par�metro de entrada: Estrutura com par�metros do problema
// Par�metro de sa�da: Preenche da estrutura da popula��o apenas o vector bin�rio com os elementos que est�o dentro ou fora da mochila
void init_pop(int *solucao,int TipoMoedas,float ValorATrocar, float *ValorDasMoedas)
{
	int i, x = 0;
        float soma = 0, max_moedas = 0, moeda_pequena = 0;
         //Por valores a 0
	for(i=0; i<TipoMoedas; i++)
        solucao[i]=0;     
        
        //Encontrar a moeda mais pequena, no valor das moedas
        moeda_pequena = *(ValorDasMoedas);
        for(i = 0;i<TipoMoedas;i++){
            if(moeda_pequena > *(ValorDasMoedas+i)){
                moeda_pequena = *(ValorDasMoedas+i);
            }
        }
        
        //Ver qual é o maximo de moedas para a solucao
        max_moedas = ValorATrocar / moeda_pequena;

	for(i=0; i<TipoMoedas; i++)
    {
        *(solucao+i) = random_l_h(0,max_moedas);
    }
        
        do{
            x = 0;
            if(soma > ValorATrocar){
                
                do{
                 x = random_l_h(0,TipoMoedas);
                }while((*(solucao+x)) == 0);
                
                (*(solucao+x))--;
            }else{
                x = random_l_h(0,TipoMoedas);
                (*(solucao+x))++;
            }
            
         soma = 0;
        for(i = 0;i<TipoMoedas;i++){
           soma += *(solucao+i) * *(ValorDasMoedas+i); 
        }
         
        }while(soma != ValorATrocar);
        
       

}

// Actualiza a melhor solu��o encontrada
// Par�metro de entrada: populacao actual (pop), estrutura com par�metros (d) e a melhor solucao encontrada at� a gera��oo imediatamente anterior (best)
// Par�metro de sa�da: a melhor solucao encontrada at� a gera��o actual
void get_best(int TipoMoedas,float ValorATrocar, int *solucao, int *best_run)
{
	int i,soma_best = 0, soma = 0,j;

	for (i=0; i<TipoMoedas; i++)
	{
            soma += solucao[i];
            soma_best += best_run[i];
	}
        
        if(soma <= soma_best){
            for(j = 0; j < TipoMoedas; j++){
                best_run[i] = solucao[j];
            }
            
        }
	
}

// Devolve um valor inteiro distribuido uniformemente entre min e max
int random_l_h(int min, int max)
{
	return min + rand() % (max-min+1);
}

// Devolve um valor real distribuido uniformemente entre 0 e 1
float rand_01()
{
	return ((float)rand())/RAND_MAX;
}

// Escreve uma solu��o na consola
// Par�metro de entrada: populacao actual (pop) e estrutura com par�metros (d)
void write_best(int *solucao, int TipoMoedas, float *ValorDasMoedas)
{
	int i;
        float soma = 0;

        for(i = 0;i<TipoMoedas;i++){
            if((*solucao+i)!= 0){
                printf(" %d moedas de %.2f",*(solucao+i),*(ValorDasMoedas+i));
                soma += (*(solucao+i) * (ValorDasMoedas[i]));
            }
        }
        
	printf("(Valor = %.2f)\n",soma);
}
