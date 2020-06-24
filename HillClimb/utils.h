float* init_dados(char *nome, int *TipoMoedas, float *ValorATrocar);
void gera_sol_inicial(int *solucao, int TipoMoedas,float ValorATrocar, float *ValorDasMoedas);
void escreve_sol(int *solucao, int TipoMoedas, float *ValorDasMoedas);
void substitui(int a[], int b[], int n);
void init_rand();
int random_l_h(int min, int max);
float rand_01();
