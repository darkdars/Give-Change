#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

// Leitura do ficheiro de input
// Recebe: nome do ficheiro, numero de vertices (ptr), numero de iteracoes (ptr)
// Devolve a matriz de adjacencias
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
	p = malloc(sizeof(float)*(*TipoMoedas));
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

// Gera a solucao inicial
// Parametros: solucao, numero de vertices
void gera_sol_inicial(int *solucao, int TipoMoedas,float ValorATrocar, float *ValorDasMoedas)  //receber valor a trocar
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

// Escreve solucao
// Parametros: solucao e TipoMoedas
void escreve_sol(int *solucao, int TipoMoedas, float *ValorDasMoedas)
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

// copia vector b para a (tamanho n)
void substitui(int a[], int b[], int n)
{
    int i;
    for(i=0; i<n; i++)
        a[i]=b[i];
}

// Inicializa o gerador de numeros aleatorios
void init_rand()
{
	srand((unsigned)time(NULL));
}

// Devolve valor inteiro aleatorio entre min e max
int random_l_h(int min, int max)
{
	return min + rand() % (max-min+1);
}

// Devolve um valor real aleatorio do intervalo [0, 1]
float rand_01()
{
	return ((float)rand())/RAND_MAX;
}

