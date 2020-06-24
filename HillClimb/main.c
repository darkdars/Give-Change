#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "utils.h"

#define DEFAULT_RUNS 10

/*
 * -> Vizinhanca ( por exemplo: o que consegue prececionar)
 * -> Funcao Avaliacao (por exemplo: distancia)
 * -> Solucao Inicial
 * -> Ciclo
 * 
    x<-Estado Inicial(ou solucao inicial)
    y-> FIM
 *  fazer enquanto ( x != y)
 * 
 * 
 * 
 
 */

int main(int argc, char *argv[])
{
    char    nome_fich[100];
    int     TipoMoedas, k, runs, custo, best_custo,i;
    int     *solucao, *best;
    float   mbf = 0.0,ValorATrocar, *grafo;

	if(argc == 3)
	{
		runs = atoi(argv[2]); //Runs é um inteiro
		strcpy(nome_fich, argv[1]);
	}
	else
        if(argc == 2)
        {
            runs = DEFAULT_RUNS; // 10 por default
            strcpy(nome_fich, argv[1]);
        }
        else
        {
            runs = DEFAULT_RUNS;
            printf("Nome do Ficheiro: ");
            gets(nome_fich);
        }
	if(runs <= 0)
		return 0;
	init_rand(); //Limpar a semente, ou seja, nao gerar sempre os mesmos valores
        // Preenche matriz de adjacencias
        grafo = init_dados(nome_fich, &TipoMoedas, &ValorATrocar); // VALORES ESTAO GRAVADOS NO GRAFO(TIPO MOEDAS EXISTENTES)
        
        printf("\n%s - %d\n",nome_fich,TipoMoedas);
        for(i=0;i<TipoMoedas;i++){
            printf("%.2f ",grafo[i]);
        }
        printf("\n");
        
        
	solucao = malloc(sizeof(int)*TipoMoedas);
	best = malloc(sizeof(int)*TipoMoedas);
	if(solucao == NULL || best == NULL)
	{
		printf("Erro na alocacao de memoria");
		exit(1);
	}
	for(k=0; k<runs; k++)
	{
		// Gerar solucao inicial
		gera_sol_inicial(solucao, TipoMoedas, ValorATrocar, grafo);
		escreve_sol(solucao, TipoMoedas,grafo); //ESCREVER NO ECRA
		// Trepa colinas
		custo = trepa_colinas(solucao, grafo, TipoMoedas, ValorATrocar);
		// Escreve resultados da repeticao k
		printf("\nRepeticao %d:", k);
		escreve_sol(solucao, TipoMoedas,grafo);
		printf("Custo final: %2d\n", custo);
		mbf += custo;
		if(k==0 || best_custo > custo)
		{
			best_custo = custo;
			substitui(best, solucao, TipoMoedas);
		}
    }
	// Escreve eresultados globais
	printf("\n\nMBF: %f\n", mbf/k);
	printf("\nMelhor solucao encontrada");
	escreve_sol(best, TipoMoedas,grafo);
	printf("Custo final: %2d\n", best_custo);
	free(grafo);
        free(solucao);
	free(best);
    return 0;
}
