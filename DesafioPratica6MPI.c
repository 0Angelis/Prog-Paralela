/*
Desafio Prática 6 MPI
Localizar o maior e o menor elemento de um vetor.

Compilar:
mpicc DesafioPratica6MPI.c -o desafio

Executar:
mpirun -np 4 ./desafio
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int id, np, i;
    int faixa, tamVet;
    int *vetor;
    int maiorLocal, menorLocal;
    int maiorGlobal, menorGlobal;
    int tag = 1;

    MPI_Status st;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    printf("Processo %d de %d\n", id, np);

    if(id == 0)
    {
        srand(time(NULL));

        faixa = rand()%20 + 10;
        tamVet = faixa * np;

        vetor = (int*) malloc(tamVet * sizeof(int));

        printf("\nVetor gerado:\n");

        for(i = 0; i < tamVet; i++)
        {
            vetor[i] = rand()%100;
            printf("%d ", vetor[i]);
        }

        printf("\n\nTamanho do vetor = %d\n", tamVet);
        printf("Faixa por processo = %d\n\n", faixa);

        for(i = 1; i < np; i++)
        {
            MPI_Send(&faixa, 1, MPI_INT, i, tag, MPI_COMM_WORLD);
            MPI_Send(&(vetor[i * faixa]), faixa, MPI_INT, i, tag, MPI_COMM_WORLD);
        }

        maiorLocal = vetor[0];
        menorLocal = vetor[0];

        for(i = 1; i < faixa; i++)
        {
            if(vetor[i] > maiorLocal)
                maiorLocal = vetor[i];

            if(vetor[i] < menorLocal)
                menorLocal = vetor[i];
        }

        printf("Processo 0 -> Maior: %d  Menor: %d\n",
               maiorLocal, menorLocal);

        maiorGlobal = maiorLocal;
        menorGlobal = menorLocal;

        for(i = 1; i < np; i++)
        {
            MPI_Recv(&maiorLocal, 1, MPI_INT, i, tag,
                     MPI_COMM_WORLD, &st);

            MPI_Recv(&menorLocal, 1, MPI_INT, i, tag,
                     MPI_COMM_WORLD, &st);

            printf("Recebeu do processo %d -> Maior: %d  Menor: %d\n",
                   i, maiorLocal, menorLocal);

            if(maiorLocal > maiorGlobal)
                maiorGlobal = maiorLocal;

            if(menorLocal < menorGlobal)
                menorGlobal = menorLocal;
        }

        printf("\n================================\n");
        printf("Maior elemento do vetor = %d\n", maiorGlobal);
        printf("Menor elemento do vetor = %d\n", menorGlobal);
        printf("================================\n");
    }
    else
    {
        MPI_Recv(&faixa, 1, MPI_INT, 0, tag,
                 MPI_COMM_WORLD, &st);

        vetor = (int*) malloc(faixa * sizeof(int));

        MPI_Recv(vetor, faixa, MPI_INT, 0, tag,
                 MPI_COMM_WORLD, &st);

        maiorLocal = vetor[0];
        menorLocal = vetor[0];

        for(i = 1; i < faixa; i++)
        {
            if(vetor[i] > maiorLocal)
                maiorLocal = vetor[i];

            if(vetor[i] < menorLocal)
                menorLocal = vetor[i];
        }

        printf("Processo %d -> Maior: %d  Menor: %d\n",
               id, maiorLocal, menorLocal);

        MPI_Send(&maiorLocal, 1, MPI_INT, 0, tag,
                 MPI_COMM_WORLD);

        MPI_Send(&menorLocal, 1, MPI_INT, 0, tag,
                 MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
