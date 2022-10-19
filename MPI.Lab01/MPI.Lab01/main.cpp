#include <stdio.h>
#include <string>
#include <iostream>
#include "mpi.h"


int main(int argc, char* argv[]) {
    int procNum, procRank;
    MPI_Status Status;
    MPI_Init(&argc, &argv);
    int len = atoi(argv[1]);
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    long double* msg = new long double[len];

    if (procRank % 2 == 0 ) {
        if (procRank != procNum - 1) {
            double t1 = MPI_Wtime();
            MPI_Send(msg, len, MPI_LONG_DOUBLE, procRank + 1, 0, MPI_COMM_WORLD);
            double t2 = MPI_Wtime();
            std::cout << "Process " << procRank << ": send message to proccess " << procRank + 1 << " len " << len << " time for send = " << t2 - t1;
        }
    }
    else {
        MPI_Recv(msg, len, MPI_LONG_DOUBLE, procRank - 1, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
        std::cout << "Process " << procRank << ": recieved message from proccess " << procRank - 1 << " with len " << len;
    }

    delete[] msg;
    MPI_Finalize();

    return 0;
}