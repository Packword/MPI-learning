#include <stdio.h>
#include <iostream>
#include <mpi.h>


int main(int argc, char* argv[]) {
	int procNum, procRank, recvRank;
	MPI_Status Status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &procNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

    if (procRank % 2 == 0) {
        std::cout << "Hello from process " << procRank << '\n';
        for (int i = 1; i < procNum; i++) {
            MPI_Recv(&recvRank, 1, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
            std::cout << "Hello from process " << recvRank << '\n';
        }
    }
    else {
        MPI_Send(&procRank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();

    
	return 0;
}