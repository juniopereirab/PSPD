#include <stdio.h>
#include <mpi.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int meurank, nprocs;
    int voriginal = 10, venvio, vrecebido;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meurank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    printf("Meu pid é %d e meu rank é %d\n", getpid(), meurank);

    if(meurank == 0) {
        // Estou no master
        for (int i = 1; i < nprocs; i++) {
            venvio = voriginal * i;
            MPI_Send(&venvio, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            printf("Master enviando!\n");
        }
    } else {
        // Estou no slave
        MPI_Recv(&vrecebido, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Escravo[%d] recebeu %d\n", meurank, vrecebido);
    }

    return 0;
}