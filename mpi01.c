#include <stdio.h>
#include <mpi.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int meurank;
    char msg[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meurank);

    printf("Meu pid é %d e meu rank é %d\n", getpid(), meurank);

    if(meurank != 0) {
        // Estou no slave
        sprintf(msg, "I'm alive!");
        MPI_Send(msg, strlen(msg), MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        MPI_Finalize();
    } else {
        // Estou no master
        MPI_Recv(msg, 100, MPI_CHAR, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Master recebendo mensagem do slave => %s", msg);
        MPI_Finalize();
    }

    return 0;
}