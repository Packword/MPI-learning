#include <stdio.h>
#include <string>
#include <iostream>
#include "mpi.h"


int main(int argc, char* argv[]) {
    int procNum, procRank, recvRank;
    MPI_Status Status;
    MPI_Init(&argc, &argv);
    int len = atoi(argv[1]);
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    long double* msg = new long double[len];

    if (procRank != 0) {
        MPI_Recv(msg, len, MPI_LONG_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
        MPI_Send(&procRank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else {
        double t1 = MPI_Wtime();
        for (int i = 1; i < procNum; i++) {
            MPI_Send(msg, len, MPI_LONG_DOUBLE, i, 0, MPI_COMM_WORLD);
            MPI_Recv(&recvRank, 1, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
            std::cout << "hello from process " << recvRank << '\n';
        }
        double t2 = MPI_Wtime();
        std::cout << "Время: " << t2 - t1;
    }

    delete[] msg;
    MPI_Finalize();

    return 0;
}