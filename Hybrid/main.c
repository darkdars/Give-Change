#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

#define DEFAULT_RUNS	10

int main(int argc, char *argv[])
{
	char        nome_fich[100];
	float       *moedas,ValorATrocar, *grafo,soma = 0;
        int         TipoMoedas,*solucao,*parents, soma_best, soma_bestEver;
	int         gen_actual, r, runs, i, inv, *best_ever, *best_run, xpto;
	float       mbf = 0.0;

        inv = 0;
    // L� os argumentos de entrada
	if (argc == 3)
	{
		runs = atoi(argv[2]);
		strcpy(nome_fich, argv[1]);
	}
	else
        // Se o n�mero de execu��es do processo n�o for colocado nos argumentos de entrada, define-o com um valor por defeito
        if (argc == 2)
        {
            runs = DEFAULT_RUNS;
            strcpy(nome_fich, argv[1]);
        }
        // Se o nome do ficheiro de informa��es n�o for colocado nos argumentos de entrada, pede-o novamente
        else
        {
            runs = DEFAULT_RUNS;
            printf("Nome do Ficheiro: ");
            gets(nome_fich);
        }
    // Se o n�mero de execu��es do processo for menor ou igual a 0, termina o programa
	if (runs <= 0)
		return 0;
    //Inicializa a gera��o dos n�meros aleat�rios
	init_rand();
    // Preenche a matriz com dados dos objectos (peso e valor) e a estrutura EA_param que foram definidos no ficheiro de input
	grafo = init_dados(nome_fich, &TipoMoedas, &ValorATrocar); //Grafo == VALOR DAS MOEDAS
	best_run = malloc(sizeof(int)*TipoMoedas);
        solucao = malloc(sizeof(int)*TipoMoedas);
        if (solucao==NULL || best_run == NULL)
	{
		printf("Erro na alocacao de memoria\n");
		exit(1);
	}
        
          best_ever = malloc(sizeof(int)*TipoMoedas);
        if (best_ever == NULL)
	{
		printf("Erro na alocacao de memoria\n");
		exit(1);
	}
          
          for(xpto = 0; xpto < TipoMoedas;xpto++){
              best_ever[xpto] = 1000;
          }
        
         // Reserva espa�o para os pais da popula��o seguinte
		parents = malloc(sizeof(int)*TipoMoedas);
        // Caso n�o consiga fazer a aloca��o, envia aviso e termina o programa
		if (parents==NULL)
		{
			printf("Erro na alocacao de memoria\n");
			exit(1);
		}
        
        // Faz um ciclo com o n�mero de execu��es definidas
	for (r=0; r<runs; r++)
	{
        // Gera��o da popula��o inicial
		 init_pop(solucao,TipoMoedas,ValorATrocar,grafo); // VALOR DAS MOEDAS
        // Avalia a popula��o inicial
		evaluate(solucao,TipoMoedas);
		gen_actual = 1;
		// Como ainda n�o existe, escolhe-se como melhor solu��o a primeira da popula��o (poderia ser outra qualquer)
                best_run = solucao;
                
        // Encontra-se a melhor solu��o dentro de toda a popula��o
		get_best(TipoMoedas, ValorATrocar, solucao, best_run);
		// Ciclo de optimiza��o
		while (gen_actual <= 10)
		{
            // Torneio bin�rio para encontrar os progenitores (ficam armazenados no vector parents)
			tournament(solucao,parents,TipoMoedas);
            // Aplica os operadores gen�ticos aos pais (os descendentes ficam armazenados na estrutura pop)
			genetic_operators(parents, best_run, TipoMoedas);
            // Avalia a nova popula��o (a dos filhos)
			evaluate(parents,TipoMoedas); // Nao sei se é o parents
            // Actualiza a melhor solu��o encontrada
			get_best(TipoMoedas, ValorATrocar, parents, best_run);
			gen_actual++;
		}
		// Contagem das solu��es inv�lidas
                 soma = 0;
                 soma_best = 0;
                  soma_bestEver = 0;
		for (i=0; i<TipoMoedas; i++){
                    soma += best_run[i] * grafo[i];
                    soma_best += best_run[i];
                    soma_bestEver += best_ever[i];
                }
                    
			if (ValorATrocar != soma)
				inv++;
		// Escreve resultados da repeti��o que terminou
		printf("\nRepeticao %d:", r+1);
		write_best(best_run, TipoMoedas, grafo); // Grafo = valor das moedas
                printf("Moedas Utilizadas: %d\n",soma_best);
                
		mbf += soma_best;
                
                if (soma_best < soma_bestEver){
                    for(xpto = 0; xpto < TipoMoedas; xpto++)
                        best_ever[xpto] = best_run[xpto];
                }
	}
                
              
	// Escreve resultados globais
        printf("\nSolucoes Invalidos: %d\n", inv);
	printf("\n\nMBF: %f\n", mbf/r);
	printf("\nMelhor solucao encontrada");
	write_best(best_ever, TipoMoedas, grafo);
        printf("Moedas Utilizadas: %d\n",soma_bestEver);
        // Liberta a mem�ria usada
		free(parents);
		free(best_run);
                free(best_ever);
	return 0;
}
