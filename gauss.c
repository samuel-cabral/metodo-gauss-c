#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#define EPSILON 0.000001

double **alocaMatriz(int l, int c){
	/*Se houver memoria disponivel, aloca 
	uma matriz de double com l linhas e c 
	colunas e devolve um ponteiro para a matriz.
	Caso contrario, devolve o ponteiro NULL.*/
	double **m;
	int i, j;
	m = malloc(sizeof(double *)*l);
	if (m == NULL) return NULL; /*falta de memória*/
	for (i=0; i<l; i++){
		m[i] = malloc(sizeof(double)*c);
		if(m[i] == NULL){ /*falta de memória*/
			for(j=0; j<i; j++){
				free(m[j]); }
			free(m);
			return NULL;
		}
	}
	return m;
} /*Fim alocaMatriz()*/

void leMatriz(double **m, int l, int c){
	/*Lê valores para uma matriz de double, 
	alocada dinamicamente, com l linhas e c colunas. */
	int i, j;
	for(i=0; i<l; i++){
		for(j=0; j<c; j++){
			printf("M[%d][%d] = ", i+1, j+1);
			scanf("%lf", &m[i][j]);
		}
	}
}/*fim leMatriz()*/

void imprimeMatriz(double **m, int l, int c){
	/*Imprime o conteudo de uma matriz de double, 
	alocada dinamicamente, com l linhas e c colunas. */
	int i, j;
	for(i=0; i<l; i++){
		for(j=0; j<c; j++){
			printf("%10.3lf ", m[i][j]);
		}
		printf("\n");
	}
}/*fim imprimeMatriz()*/

int sretro(double **m, int n, double x[]){
	/* Algoritmo de substituição retroativa.
	Recebe m, a matriz aumentada de um SL TS com n variaveis.
	Se o sistema linear for determinado, armazena em x a solução
	no SL e devolve 0.
	Se for indeterminado, armazena em x uma solução do SL e 
	devolve 1. */
	int i,j, tipo=0;
	double soma;
	for(i=n-1; i>=0; i--){
		soma=0;
		for(j=i+1; j<n; j++){
			soma += m[i][j] * x[j];
		}
		if(m[i][i] == 0){
			if(fabs(m[i][n] - soma) < EPSILON){
				x[i]=0;	/*variavel livre*/
				tipo = 1;
			}else{
				return 2; /*SL incompativel*/
			}
		}else{
			x[i] = (m[i][n] - soma)/m[i][i];
			}	
	}
	return tipo;
} /*Fim sretro()*/

void Gauss(double **m, int n){
	/*Recebe M, a matriz aumentada de um SL com n 
	variáveis, e transforma M na matriz aumentada 
	de um SL TS equivalente. */
	int i, j, k;
	double mult, *aux;
	for(i=0; i<n-1; i++){
		if(m[i][i] == 0){
			j = i+1;
			while(j < n && m[j][i] == 0){
				j++;
			}
			if(j < n){ /* Trocando as linhas i e j. */
				aux = m[i];
				m[i] = m[j];
				m[j] = aux;
			}
		}
		if(m[i][i] != 0){
			for(j=i+1; j<n; j++){
				mult = -m[j][i]/m[i][i];
				m[j][i] = 0;
				for(k=i+1; k<=n; k++){
					m[j][k] += mult * m[i][k];
				}
			}
		}
	}
} /* fim Gauss() */

int main(){
	int i, n, tipo;
	double **m, *x;
	printf("METODO DE GAUSS!\n\n");
	printf("QUANTIDADE DE VARIAVEIS: ");
	scanf("%d", &n);
	m = alocaMatriz(n, n+1);
	x = malloc(sizeof(double)*n);
	if(m == NULL || x == NULL) {/*Falta de memória*/
		printf("Deu pau!\nFalta de memoria!\n");
		return 1;
	}
	leMatriz(m, n, n+1);
	imprimeMatriz(m, n, n+1);
	Gauss(m, n);
	printf("\nMatriz triangularizada - método de Gauss \n");
	imprimeMatriz(m, n, n+1);
	tipo = sretro(m, n, x);
	if(tipo == 2){
		printf("SL imcompativel!\n");
	}else{
		printf("SL %sdeterminado\n", tipo?"In":"");
		for(i=0; i<n; i++){
			printf("x[%d] = %10.3lf\n", i+1, x[i]);
		}
	}
	return 0;
}/*fim main()*/