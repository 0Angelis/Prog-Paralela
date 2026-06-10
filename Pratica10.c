#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define maxVet 10000
#define maxNumero 10000

typedef int tipoVetor[maxVet];

tipoVetor A;
int tamA;
int limite;

typedef struct {
    int ini;
    int fim;
} Param;

int leTam(void)
{
    int tam;
    do {
        printf("\nDigite o tamanho do Vetor = ");
        scanf("%d", &tam);
    } while ((tam<1)||(tam>maxVet));
    return tam;
}

void geraVetor(tipoVetor V, int tam)
{
    int i, sinal;
    printf("\nGeracao Aleatoria do Vetor\n");

    for (i=0; i<tam; i++)
    {
        V[i]=rand()%maxNumero;
        sinal=(rand()%2)*2-1;
        V[i]=sinal*V[i];
    }
}

void mostraVetor(char *id, tipoVetor V, int tam)
{
    int i;
    printf("\nElementos do Vetor %s:\n", id);
    printf("%d",V[0]);
    for (i=1; i<tam; i++)
        printf(", %d",V[i]);
    printf("\n");
}

/* ================= MERGE ================= */

void mergeMetades(tipoVetor V, int ini, int meio, int fim)
{
    tipoVetor auxV1, auxV2;
    int tam1=0, tam2=0, maior, i, i1, i2;

    for (i=ini; i<=meio; i++)
        auxV1[tam1++] = V[i];

    for (i=meio+1; i<=fim; i++)
        auxV2[tam2++] = V[i];

    if (auxV1[tam1-1] > auxV2[tam2-1])
        maior = auxV1[tam1-1] + 1;
    else
        maior = auxV2[tam2-1] + 1;

    auxV1[tam1] = maior;
    auxV2[tam2] = maior;

    i1 = 0;
    i2 = 0;

    for (i=ini; i<=fim; i++)
    {
        if (auxV1[i1] < auxV2[i2])
            V[i] = auxV1[i1++];
        else
            V[i] = auxV2[i2++];
    }
}

/* ================= MERGESORT THREAD ================= */

void* mergeSortThread(void *arg)
{
    Param *p = (Param*) arg;
    int ini = p->ini;
    int fim = p->fim;

    if (ini < fim)
    {
        int meio = (ini + fim)/2;

        if ((fim - ini) > limite)
        {
            pthread_t t1, t2;

            Param p1 = {ini, meio};
            Param p2 = {meio+1, fim};

            pthread_create(&t1, NULL, mergeSortThread, &p1);
            pthread_create(&t2, NULL, mergeSortThread, &p2);

            pthread_join(t1, NULL);
            pthread_join(t2, NULL);
        }
        else
        {
            Param p1 = {ini, meio};
            Param p2 = {meio+1, fim};

            mergeSortThread(&p1);
            mergeSortThread(&p2);
        }

        mergeMetades(A, ini, meio, fim);
    }

    return NULL;
}

int main()
{
    srand(time(NULL));

    tamA = leTam();

    printf("Digite o limite = ");
    scanf("%d", &limite);

    geraVetor(A, tamA);
    mostraVetor("A antes", A, tamA);

    Param p = {0, tamA-1};
    mergeSortThread(&p);

    mostraVetor("A ordenado", A, tamA);

    return 0;
}
