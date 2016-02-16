// persist.c
// Bradley Morgan
// 01.26.2015
//
// A simple demonstration of
// OpenMPI persistent requests.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

int main(int argc, char * argv[]) {

	// initialize MPI

	int i, rank, size, rec;
	int arr[100];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// populate a sample array,
	// i.e. simulated input

	if(rank == 0) {

		printf("\r\n\r\nHello from r00t. Starting\r\n\r\n");

	} else {

		int i;

		for(i=0;i<=100;i++) {
			srand(time(NULL) * rank * i);
			arr[i] = rand() % 100;
		}

	}

	MPI_Request sreq, rreq;
	MPI_Status status;

	if(rank > 0) {

		int source, dest;

		if(rank == 1) { source = size - 1; } else { source = rank - 1; }
		if(rank == size - 1) { dest = 1; } else { dest = rank + 1; }

		// create a persistent send and a persistent recieve request
		MPI_Send_init(&arr[rank], 1, MPI_INT, dest, NULL, MPI_COMM_WORLD, &sreq);
		MPI_Recv_init(&rec, 1, MPI_INT, source, NULL, MPI_COMM_WORLD, &rreq);

		// once created we can use them over and over again...

		for(i=0; i<100; i++) {

			MPI_Start(&rreq);
			MPI_Start(&sreq);

			MPI_Wait(&rreq, &status);

			printf("My rank is %d and I received %d from %d\n", rank, rec, source);

			MPI_Wait(&sreq, &status);


		}

		MPI_Cancel(&rreq);
		MPI_Cancel(&sreq);

	}

}
