#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *funcaoImprimeMensagem( void *ptr );

void main(void)
{
    pthread_t thread1, thread2;
    char mensagem1[16] = "\nSou a thread 1";
    char mensagem2[16] = "\nSou a thread 2";
    int  iret1, iret2;


    iret1 = pthread_create(&thread1, NULL, funcaoImprimeMensagem, (void*) mensagem1);

    iret2 = pthread_create(&thread2, NULL, funcaoImprimeMensagem, (void*) mensagem2);

    printf("\nCriacao da thread 1 retornou: %d\n",iret1);
    printf("\nCriacao da thread 2 retornou: %d\n",iret2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("\nAmbas as threads 1 e 2 ja finalizaram e agora eu (o main) finalizarei...\n");
    exit(0);
}

void *funcaoImprimeMensagem(void *ptr )
{
     char *mensagem;
     mensagem = (char *) ptr;
     printf("%s \n", mensagem);
}

