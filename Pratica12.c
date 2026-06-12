#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define maxDim 100

typedef int tipoMatriz[maxDim][maxDim];

tipoMatriz A, B, C;

int m, n, p;

typedef struct
{
    int linha;
    int coluna;
} dadosThread;

void *produtoEscalar(void *arg)
{
    int i, soma = 0;

    dadosThread *dados = (dadosThread *)arg;

    int lin = dados->linha;
    int col = dados->coluna;

    for(i = 0; i < n; i++)
    {
        soma = soma + A[lin][i] * B[i][col];
    }

    C[lin][col] = soma;

    pthread_exit(NULL);
}

void geraMatriz(tipoMatriz M, int nLins, int nCols)
{
    int l, c;

    for(l = 0; l < nLins; l++)
    {
        for(c = 0; c < nCols; c++)
        {
            M[l][c] = rand() % 10;
        }
    }
}

void mostraMatriz(char *nome, tipoMatriz M, int nLins, int nCols)
{
    int l, c;

    printf("\n%s:\n", nome);

    for(l = 0; l < nLins; l++)
    {
        for(c = 0; c < nCols; c++)
        {
            printf("%3d ", M[l][c]);
        }

        printf("\n");
    }
}

void multiplicaMatriz()
{
    int l, c;

    pthread_t threads[maxDim][maxDim];
    dadosThread dados[maxDim][maxDim];

    for(l = 0; l < m; l++)
    {
        for(c = 0; c < p; c++)
        {
            dados[l][c].linha = l;
            dados[l][c].coluna = c;

            pthread_create(&threads[l][c], NULL, produtoEscalar, &dados[l][c]);
        }
    }

    for(l = 0; l < m; l++)
    {
        for(c = 0; c < p; c++)
        {
            pthread_join(threads[l][c], NULL);
        }
    }
}

int main(void)
{
    int opcao;

    srand(time(NULL));

    do
    {
        system("cls || clear");

        printf("*** Programa para Multiplicacao Matricial Paralela ***\n");

        printf("\nQuantas linhas na matriz A? => ");
        scanf("%d", &m);

        printf("\nQuantas colunas na matriz A? => ");
        scanf("%d", &n);

        printf("\nQuantas colunas na matriz B? => ");
        scanf("%d", &p);

        geraMatriz(A, m, n);
        mostraMatriz("Matriz A", A, m, n);

        geraMatriz(B, n, p);
        mostraMatriz("Matriz B", B, n, p);

        multiplicaMatriz();

        mostraMatriz("Matriz C (Resultante)", C, m, p);

        printf("\nDeseja nova execucao <1>Sim ou <2>Nao? > ");
        scanf("%d", &opcao);

    } while(opcao == 1);

    return 0;
}
