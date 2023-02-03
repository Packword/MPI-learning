#include <stdio.h>
#include <iostream>
#include <mpi.h>


double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}


int main(int argc, char* argv[]) {
    int procNum, procRank, recvRank;
    MPI_Status Status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    srand(time(NULL) + procRank);
    double num = fRand(0, 100);
    std::cout << "Number in process " << procRank << " : " << num;
    double* result = new double[procNum];
    double t1 = MPI_Wtime();
    MPI_Gather(&num, 1, MPI_DOUBLE, result, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    double t2 = MPI_Wtime();
    if (procRank == 0) {
        std::cout << "\nTime: " << t2 - t1;
        std::cout << "\nGathering completed, result: ";
        for (int i = 0; i < procNum; i++) {
            std::cout << result[i] << (i == (procNum - 1) ? " " : ", ");
        }
    }

    delete[] result;
    MPI_Finalize();

    return 0;
}