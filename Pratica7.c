#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#define maxThreads 50
#define maxElem 100

void *buscaMaiorMenor(void *ptr);
void geraVetor(int n);
void buscaSequencial(int n, int *posMaior, int *posMenor);

int vet[maxElem];

struct tipoPack {
   int tid, ini, fim, posMaior, posMenor;
};

typedef struct tipoPack tipoPack;

int main(void)
{
     pthread_t thread[maxThreads];

     int  i, j, iret[maxThreads], kThreads;
     int ini, fim, faixa, restante, nElem, posMaior, posMenor;
     int posMaiorSeq, posMenorSeq;
     int nTestes;
     int erro = 0;

     tipoPack pack[maxThreads];

     srand(time(NULL));

     printf("Programa Multithread para Buscar Maior e Menor Elementos\n");

     nElem=0;
     while ((nElem<1) || (nElem>maxElem)) {
        printf("\nEntre com numero de elementos do vetor => ");
        scanf("%d", &nElem);
     }

     kThreads=0;
     while ((kThreads<1)||(kThreads>nElem)) {
        printf("\nO numero de threads => ");
        scanf("%d", &kThreads);
     }

     nTestes=0;
     while (nTestes<1) {
        printf("\nEntre com quantas vezes quer executar a verificacao => ");
        scanf("%d", &nTestes);
     }

     for (j=1; j<=nTestes; j++) {

         printf("\n\n================ EXECUCAO %d ================\n", j);

         geraVetor(nElem);

         /* busca sequencial */
         buscaSequencial(nElem, &posMaiorSeq, &posMenorSeq);

         faixa = nElem/kThreads;
         restante = nElem % kThreads;

         ini = 0;
         fim = faixa-1;

         if (restante>0)
         {
             fim++;
             restante--;
         }

         for (i=0; i<kThreads; i++)
         {
                pack[i].tid=i+1;
                pack[i].ini = ini;
                pack[i].fim = fim;
                pack[i].posMaior=ini;
                pack[i].posMenor=ini;

                ini=fim+1;
                fim=ini+faixa-1;

                if (restante>0)
                {
                    fim++;
                    restante--;
                }
         }

         for (i=0; i<kThreads; i++)
            iret[i] = pthread_create(&(thread[i]), NULL, buscaMaiorMenor, (void*) &pack[i]);

         for (i=0; i<kThreads; i++)
            pthread_join(thread[i], NULL);

         posMaior=pack[0].posMaior;
         posMenor=pack[0].posMenor;

         for (i=1; i<kThreads; i++)
         {
             if (vet[posMaior] < vet[pack[i].posMaior])
                 posMaior=pack[i].posMaior;

             if (vet[posMenor] > vet[pack[i].posMenor])
                 posMenor=pack[i].posMenor;
         }

         printf("\nSequencial: Maior = %d e Menor = %d\n", vet[posMaiorSeq], vet[posMenorSeq]);
         printf("Paralela:   Maior = %d e Menor = %d\n", vet[posMaior], vet[posMenor]);

         if ((vet[posMaiorSeq] != vet[posMaior]) || (vet[posMenorSeq] != vet[posMenor])) {
             printf("\nERRO ENCONTRADO NA EXECUCAO %d\n", j);

             printf("\nVetor:\n");
             for (i=0; i<nElem; i++) {
                 printf("%d ", vet[i]);
             }
             printf("\n");

             erro = 1;
             break;
         }
         else {
             printf("Resultado correto.\n");
         }
     }

     if (erro == 0) {
         printf("\n\nTodas as execucoes deram certo.\n");
     }

     return 0;
}

void *buscaMaiorMenor(void *ptr)
{
     int i;

     tipoPack *pack;

     pack= (tipoPack *) ptr;

     for (i=pack->ini+1; i<=(pack->fim); i++){
         if (vet[pack->posMaior]<vet[i])
             pack->posMaior=i;

         if (vet[pack->posMenor]>vet[i])
             pack->posMenor=i;
     }

     pthread_exit(NULL);
}

void buscaSequencial(int n, int *posMaior, int *posMenor)
{
     int i;

     *posMaior = 0;
     *posMenor = 0;

     for (i=1; i<n; i++) {
         if (vet[*posMaior] < vet[i])
             *posMaior = i;

         if (vet[*posMenor] > vet[i])
             *posMenor = i;
     }
}

void geraVetor(int n)
{
    int i;

    printf("\nGeracao do Vetor:\n");

    for (i=0; i<n-1; i++){
        vet[i]=rand()%1000;
        printf("%d, ",vet[i]);
    }
    vet[i]=rand()%1000;
    printf("%d\n",vet[i]);
}
