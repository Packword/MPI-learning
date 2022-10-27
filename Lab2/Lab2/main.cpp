#include <stdio.h>
#include <string>
#include <iostream>
#include "mpi.h"



bool validationCheck(int* route, int len) {
    bool* test = new bool[len];
    for (int i = 0; i < len; i++) {
        test[i] = false;
    }
    for (int i = 0; i < len; i++) {
        if (test[route[i] - 1] != true) {
            test[route[i] - 1] = true;
        }
        else {
            delete[] test;
            return false;
        }
    }
    for (int i = 0; i < len; i++) {
        if (test[i] != true) {
            delete[] test;
            return false;
        }
    }
}


void updateRoute(int* msg) {
    int tmp = 1;
    int count = 0;
    while (tmp != 0) {
        msg[count] = msg[count + 1];
        count++;
        tmp = msg[count];
    }
}


void printMsg(int* msg, int len) {
    for (int i = 0; i < len; i++) {
        std::cout << msg[i] << " ";
    }
    std::cout << '\n';
}


int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    int procNum, procRank, recvRank;
    MPI_Status Status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);


    int lengthOfInformationSegment = atoi(argv[1]);
    int totalLength = procNum + lengthOfInformationSegment;
    int* route = new int[procNum - 1];
    int* msg = new int[totalLength];
    if (procRank != 0) {
        MPI_Recv(msg, totalLength, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
        updateRoute(msg);
        std::cout << "Recived in " << procRank << " process\n";
        printMsg(msg, totalLength);
        MPI_Send(msg, totalLength, MPI_INT, msg[0], 0, MPI_COMM_WORLD);
    }
    else{
        std::cout << "Insert route without 0:\n";
        for (int i = 0; i < procNum - 1; i++) {
            std::cin >> route[i];
            msg[i] = route[i];
        }
        msg[procNum - 1] = 0;
        double t1 = MPI_Wtime();
        if (!validationCheck(route, procNum - 1)) {
            std::cout << "error";
            delete[] route;
            delete[] msg;
            MPI_Finalize();
            return 0;
        }
        for (int i = procNum; i < totalLength; i++) {
            msg[i] = 42;
        }
        MPI_Send(msg, totalLength, MPI_INT, msg[0], 0, MPI_COMM_WORLD);
        MPI_Recv(msg, totalLength, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
        std::cout << "Route end\n";
        printMsg(msg, totalLength);
        double t2 = MPI_Wtime();
        std::cout << "\nTime: " << t2 - t1 << '\n';
    }

    delete[] route;
    delete[] msg;
    MPI_Finalize();

    return 0;
}
