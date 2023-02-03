#include <stdio.h>
#include <iostream>
#include <mpi.h>


int main(int argc, char* argv[]) {
    int procNum, procRank, recvRank, result = 0;
    MPI_Status Status;
    MPI_Comm customComm;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    srand(time(NULL) + procRank);
    double t1, t2;
    int* ranks = new int[procNum];
    int n = rand() % 2;
    if (procRank == 0)
        t1 = MPI_Wtime();
    if (n == 1 || procRank == 0) {
        ranks[procRank] = 1;
        MPI_Comm_split(MPI_COMM_WORLD, n, procRank, &customComm);
    }
    else {
        ranks[procRank] = 0;
        MPI_Comm_split(MPI_COMM_WORLD, MPI_UNDEFINED, procRank, &customComm);
    }
    
    if (ranks[procRank] == 1) {
        int num = rand() % 100;
        std::cout << "\nProcess " << procRank << " generate " << num << " number and send it";
        MPI_Allreduce(&num, &result, 1, MPI_INT, MPI_SUM, customComm);
    }
    if (procRank == 0) {
        t2 = MPI_Wtime();
        std::cout << "\nProcess " << procRank << " have " << result << " in result. TIME: " << t2 - t1;
    }
    else {
        std::cout << "\nProcess " << procRank << " have " << result << " in result.";
    }

    delete[] ranks;
    MPI_Finalize();

    return 0;
}