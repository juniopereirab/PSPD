/* 
 AUTOR: DÂMASO JÚNIO PEREIRA BRASILEO
 MATRICULA: 17/0031438

 EXERCÍCIO PARA SOMA DE ARRAYS

 Possível executar com 4 processos filhos, sendo 5 processos no máximo. O MASTER e os 4 SLAVES.
*/

#include <stdio.h>
#include <mpi.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#define SIZE_OF_ARRAY 16

int main(int argc, char *argv[]) {
    int meurank, nprocs;
    int venvio[4], venvio2[4], vrecebido[4], vrecebido2[4];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meurank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    if(meurank == 0) {
        int v1[SIZE_OF_ARRAY];
        for(int i = 0; i < SIZE_OF_ARRAY; i++) {
            v1[i] = i;
        }
        int v2[SIZE_OF_ARRAY];
        for(int i = 0; i < SIZE_OF_ARRAY; i++) {
            v2[i] = i;
        }
        int resultado[SIZE_OF_ARRAY];
        int inicio, fim, index;
        
        // Estou no master
        for (int i = 1; i < nprocs; i++) {
            inicio = (i-1) * 4;
            fim = i * 4;
            index = 0;
            for (int j = inicio; j < fim; j++) {
                venvio[index] = v1[j];
                venvio2[index] = v2[j];
                index++;
            }
            MPI_Send(&venvio, 4, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&venvio2, 4, MPI_INT, i, 0, MPI_COMM_WORLD);
            printf("Master enviando!\n");
        }
        for (int i = 1; i < nprocs; i++) {
            MPI_Recv(&vrecebido, 4, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            inicio = (i-1) * 4;
            fim = i * 4;
            index = 0;
            for (int j = inicio; j < fim; j++) {
                resultado[j] = vrecebido[index];
                index++;
            }
        }
        printf("Master recebeu array alterado\n");
        for (int j = 0; j < 16; j++) {
            if (j == 0) {
                printf("{ %d,", resultado[j]);
            } else if (j == 15) {
                printf(" %d }\n", resultado[j]);
            } else {
                printf(" %d,", resultado[j]);
            }
        }
    } else {
        int resultado[4];
        // Estou no slave
        MPI_Recv(&vrecebido, 4, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&vrecebido2, 4, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = 0; i < 4; i++) {
            resultado[i] = vrecebido[i] + vrecebido2[i];
        }

        MPI_Send(&resultado, 4, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    return 0;
}