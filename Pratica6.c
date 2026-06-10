#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define maxThreads 2

int vetor[100];
int n;

typedef struct {
    int inicio;
    int fim;
    int idThread;
} tipoPack;

void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void *ordenaMetade(void *arg) {
    tipoPack *p = (tipoPack *) arg;

    printf("\nTHREAD %d: Vai ordenar de %d ate %d\n", p->idThread, p->inicio, p->fim);

    for (int i = p->inicio; i < p->fim; i++) {
        int min = i;

        for (int j = i + 1; j <= p->fim; j++) {
            if (vetor[j] < vetor[min]) {
                min = j;
            }
        }

        troca(&vetor[i], &vetor[min]);
    }

    pthread_exit(NULL);
}

void imprimeVetor() {
    for (int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }  }


int main() {
    pthread_t t1, t2;
    tipoPack p1, p2;

    printf("\nDigite o tamanho do vetor: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100) {
        printf("Tamanho invalido!\n(max 100)\n");
        return 1;
    }

    srand(time(NULL));

    printf("\nVetor original:\n");
    for (int i = 0; i < n; i++) {
        vetor[i] = rand() % 100;
        printf("%d ", vetor[i]);
    }
    printf("\n");

    int meio = n / 2;

    p1.inicio = 0;
    p1.fim = meio - 1;
    p1.idThread = 1;

    p2.inicio = meio;
    p2.fim = n - 1;
    p2.idThread = 2;

    pthread_create(&t1, NULL, ordenaMetade, &p1);
    pthread_create(&t2, NULL, ordenaMetade, &p2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("\nVetor ordenado:\n");
    imprimeVetor();

    return 0;
}

