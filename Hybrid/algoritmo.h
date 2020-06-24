#define MAX_OBJ 1000		// Numero maximo de objectos


void tournament(int a[], int b[], int n);

void genetic_operators(int *parents, int *best_run, int TipoMoedas);

void crossover(int *parents,int *best_run, int TipoMoedas);

void mutation(int *parents, int TipoMoedas);
