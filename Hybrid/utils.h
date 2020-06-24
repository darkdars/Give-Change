float* init_dados(char *nome, int *TipoMoedas, float *ValorATrocar);

void init_pop(int *solucao,int TipoMoedas,float ValorATrocar,float *ValorDasMoedas);


void get_best(int TipoMoedas,float ValorATrocar, int *solucao, int *best_run);

void write_best(int *solucao, int TipoMoedas, float *ValorDasMoedas);

void init_rand();

int random_l_h(int min, int max);

float rand_01();

int flip();
