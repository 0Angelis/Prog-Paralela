/* Implementar o desafio da Pratica 04 - k threads calculam a mesma Fatorial de forma conjunta */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *calculaFatorial(void *ptr);

struct tipoPack {
   int tid, inicio, fim;
   unsigned long long parcial;
};

typedef struct tipoPack tipoPack;

void main(void)
{
     int n, k, i;
     int atual, base, resto;
     unsigned long long resultadoFinal = 1;

     printf("\nPrograma Multithreaded de Calculo de uma Fatorial com k Threads\n");

     printf("\nDigite o valor de n > ");
     scanf("%d", &n);

     printf("\nDigite a quantidade de threads (k) > ");
     scanf("%d", &k);

     if (k > n)
         k = n;

     pthread_t thread[k];
     int iret[k];
     tipoPack pack[k];

     base = n / k;
     resto = n % k;
     atual = 1;

     for (i = 0; i < k; i++)
     {
         pack[i].tid = i + 1;
         pack[i].inicio = atual;
         pack[i].fim = atual + base - 1;

         if (resto > 0)
         {
             pack[i].fim++;
             resto--;
         }

         pack[i].parcial = 1;
         atual = pack[i].fim + 1;

         iret[i] = pthread_create(&thread[i], NULL, calculaFatorial, (void*) &pack[i]);
     }

     for (i = 0; i < k; i++)
         pthread_join(thread[i], NULL);

     for (i = 0; i < k; i++)
         resultadoFinal = resultadoFinal * pack[i].parcial;

     printf("\nResultado Final: Fatorial(%d) = %llu\n", n, resultadoFinal);

}

void *calculaFatorial(void *ptr)
{
     int i;
     tipoPack *pack;

     pack = (tipoPack *) ptr;

     printf("\nThread %d: vou calcular de %d ate %d\n", pack->tid, pack->inicio, pack->fim);

     for (i = pack->inicio; i <= pack->fim; i++)
         pack->parcial = pack->parcial * i;

}
