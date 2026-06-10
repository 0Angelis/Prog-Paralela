#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int vetor[3000];

char mensagem[3][16]={"\nSou a thread 1","\nSou a thread 2","\nSou a thread 3"};


void *funcaoImprimeMensagem( void *ptr );

void main(void)
{
    pthread_t thread0, thread1, thread2, thread3; 

    int  	iret1, iret2, iret3,
					tid1=1, tid2=2, tid3=3, 
					i;


    iret1 = pthread_create(&thread1, NULL, funcaoImprimeMensagem, (void*) &tid1);

    iret2 = pthread_create(&thread2, NULL, funcaoImprimeMensagem, (void*) &tid2);

    iret3 = pthread_create(&thread3, NULL, funcaoImprimeMensagem, (void*) &tid3);

    printf("\nCriacao da thread 1: identificador da thread do sistema = %d\n",thread1);
    printf("\nCriacao da thread 2: identificador da thread do sistema = %d\n",thread2);
    printf("\nCriacao da thread 3: identificador da thread do sistema = %d\n",thread3);

    thread0=pthread_self();

    printf("\nSou a thread Principal (Mae): identificador da thread do sistema  = %d\n",thread0);


    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("\nVetor Preenchido: \n");
    for (i=0; i<3000; i++)
        printf("%d, ",vetor[i]);

    printf("\nAs threads 1, 2 e 3 ja finalizaram e agora a thread principal tambem\n");
    exit(0);
}

void *funcaoImprimeMensagem(void *ptr)
{
     int i, *tid;
     pthread_t nt;

     tid = (int *)ptr;

		 printf("Identificador da Thread do Usuario = %d\n", *tid);

		 nt=pthread_self();

     printf("Identificador da Thread do Sistema = %d\n", nt);


     for (i=0; i<1000; i++)
        printf("%s \n", mensagem[*tid-1]);

     for (i=(*tid-1)*1000; i<1000*(*tid); i++)
        vetor[i]=*tid;
}

