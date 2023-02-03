#include <stdio.h>
#include <iostream>
#include <mpi.h>


int main(int argc, char* argv[]) {
    int procNum, procRank, result = 0;
    MPI_Status Status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    srand(time(NULL) + procRank);
    
    int randNum = rand() % 100;
    std::cout << "Process " << procRank << " generate " << randNum << '\n';
    MPI_Comm CubeComm;
    int ndims = 3;
    int dims[3] = { 2, 2, procNum / 4 };
    int periods[3] = { 0, 0, 0 };
    int reorder = 0;

    MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, reorder, &CubeComm);

    MPI_Comm SquareComm;
    int subdims[3] = { 1, 1, 0 };
    MPI_Cart_sub(CubeComm, subdims, &SquareComm);

    MPI_Allreduce(&randNum, &result, 1, MPI_INT, MPI_SUM, SquareComm);
    std::cout << "Result on process " << procRank << " is " << result << '\n';
    
    
    MPI_Finalize();

    return 0;
}