#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int id;
    int inicio, fim;
} tipoPack;

int fib[1000];

void *calculaFibo(void *arg) {
    tipoPack *p = (tipoPack *)arg;

    for (int i = p->inicio; i <= p->fim; i++) {
        if (i <= 1)
            fib[i] = i;
        else
            fib[i] = fib[i-1] + fib[i-2];
    }

    printf("Thread %d fez de %d ate %d\n", p->id, p->inicio, p->fim);

    pthread_exit(NULL);
}

int main() {
    int n;
    printf("Digite n: ");
    scanf("%d", &n);

    pthread_t thread1, thread2;
    tipoPack p1, p2;

    int meio = n / 2;

   /* Thread 0 calcula até a primeira metade */
    p1.id = 0;
    p1.inicio = 0;
    p1.fim = meio;

    /* Thread 1 calcula segunda metade */
    p2.id = 1;
    p2.inicio = meio + 1;
    p2.fim = n;

    pthread_create(&thread1, NULL, calculaFibo, (void *)&p1);
    pthread_join(thread1, NULL);

    pthread_create(&thread2, NULL, calculaFibo, (void *)&p2);
    pthread_join(thread2, NULL);

    printf("\nFibonacci(%d) = %d\n", n, fib[n]);

    return 0;
}

