#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *funcaoImprimeMensagem(void *ptr);
int vetor[3000];

void main(void)
{
    pthread_t thread1, thread2, thread3;
    char mensagem1[16] = "\nSou a thread 1";
    char mensagem2[16] = "\nSou a thread 2";
    char mensagem3[16] = "\nSou a thread 3";
    int  iret1, iret2, iret3;
    int  id1, id2, id3;
    id1 = 1;
    id2 = 2;
    id3 = 3;


    iret1 = pthread_create(&thread1, NULL, funcaoImprimeMensagem, (void*) &id1);

    iret2 = pthread_create(&thread2, NULL, funcaoImprimeMensagem, (void*) &id2);

    iret3 = pthread_create(&thread3, NULL, funcaoImprimeMensagem, (void*) &id3);

    printf("\nCriacao da thread 1 retornou: %d\n",iret1);
    printf("\nCriacao da thread 2 retornou: %d\n",iret2);
    printf("\nCriacao da thread 3 retornou: %d\n",iret3);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("\nImpressao do vetor: \n");
    int idx;
    for (idx = 0; idx < 3000; idx++) {
        printf("%i \n", vetor[idx]);
    }

    printf("\nAs threads finalizaram e agora eu (o main) finalizarei...\n");
    exit(0);
}

void *funcaoImprimeMensagem(void *ptr)
{
    int i;
    int *idThread = (int *) ptr;

    for (i = 0; i < 1000; i++) {
        printf("Sou a thread %d\n", *idThread);
    }

    if (*idThread == 1) {
        for (i = 0; i < 1000; i++) {
            vetor[i] = *idThread;
        }
    } else if (*idThread == 2) {
        for (i = 1000; i < 2000; i++) {
            vetor[i] = *idThread;
        }
    } else if (*idThread == 3) {
        for (i = 2000; i < 3000; i++) {
            vetor[i] = *idThread;
        }
    }

    return NULL;
}

