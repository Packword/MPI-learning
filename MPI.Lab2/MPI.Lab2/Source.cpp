#include <stdio.h>
#include <iostream>
#include <mpi.h>


int main(int argc, char* argv[]) {
	int procNum, procRank, recvRank;
	MPI_Status Status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &procNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    std::cout << procRank;
    if (procRank % 2 == 0 && procRank != (procNum - 1)) {
        MPI_Send(&procRank, 1, MPI_INT, procRank + 1, 0, MPI_COMM_WORLD);
        std::cout << "Process " << procRank << ": send message to proccess " << procRank + 1;
    }
    else {
        MPI_Recv(&recvRank, 1, MPI_INT, procRank - 1, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
        std::cout << "Process " << procRank << ": recieved message from proccess " << recvRank;
    }
    
    MPI_Finalize();

    
	return 0;
}