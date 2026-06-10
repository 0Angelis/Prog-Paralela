#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 100
#define maxThreads 50

int vetor[MAX];

void *buscaMinMax(void *ptr);

struct tipoPack {
    int tid;
    int ini;
    int fim;
    int min;
    int max;
};

typedef struct tipoPack tipoPack;

void main(void)
{
    pthread_t thread[maxThreads];
    int i, kThreads;
    int n;
    int faixa, restante, ini, fim;
    int minGlobal, maxGlobal;
    tipoPack pack[maxThreads];

    printf("Programa para buscar o Menor e Maior elemento\n");

    printf("\nDigite o tamanho do vetor => ");
    scanf("%d", &n);

    while (n <= 0 || n > MAX) {
        printf("Valor invalido! Digite novamente => ");
        scanf("%d", &n);
    }

    printf("\nDigite o numero de threads => ");
    scanf("%d", &kThreads);

    while (kThreads <= 0 || kThreads > maxThreads || kThreads > n) {
        printf("Numero invalido! Digite novamente => ");
        scanf("%d", &kThreads);
    }

    for (i = 0; i < n; i++) {
        vetor[i] = rand() % 150;
    }

    printf("\nVetor gerado:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    faixa = n / kThreads;
    restante = n % kThreads;

    ini = 0;
    fim = faixa - 1;

    if (restante > 0) {
        fim++;
        restante--;
    }

    for (i = 0; i < kThreads; i++) {
        pack[i].tid = i + 1;
        pack[i].ini = ini;
        pack[i].fim = fim;

        ini = fim + 1;
        fim = fim + faixa;

        if (restante > 0) {
            fim++;
            restante--;
        }
    }

    for (i = 0; i < kThreads; i++) {
        pthread_create(&(thread[i]), NULL, buscaMinMax, (void*) &pack[i]);
    }

    for (i = 0; i < kThreads; i++) {
        pthread_join(thread[i], NULL);
    }

    minGlobal = pack[0].min;
    maxGlobal = pack[0].max;

    for (i = 1; i < kThreads; i++) {
        if (pack[i].min < minGlobal)
            minGlobal = pack[i].min;

        if (pack[i].max > maxGlobal)
            maxGlobal = pack[i].max;
    }

    printf("\nMenor elemento = %d\n", minGlobal);
    printf("Maior elemento = %d\n", maxGlobal);

    exit(0);
}

void *buscaMinMax(void *ptr)
{
    int i;
    tipoPack *pack;

    pack = (tipoPack *) ptr;

    pack->min = vetor[pack->ini];
    pack->max = vetor[pack->ini];

    printf("\nThread %d: vai analisar de %d ate %d\n", pack->tid, pack->ini, pack->fim);

    for (i = pack->ini; i <= pack->fim; i++) {
        if (vetor[i] < pack->min)
            pack->min = vetor[i];

        if (vetor[i] > pack->max)
            pack->max = vetor[i];
    }

    pthread_exit(NULL);
}
