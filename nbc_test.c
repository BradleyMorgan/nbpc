// nbc_test.c
// Bradley Morgan
// 12.15.2015
//
// A very simple demonstration of 
// nonblocking collectives (libnbc) 
// in MPI.
//
// This is basically used to confirm
// that libnbc has been built and
// can be instantiated as expected
//

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char * argv[]) {

	// initialize MPI 

	int rank;
	int arr[100];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// populate a sample array, 
	// i.e. simulated input
	        
	if(rank == 0) {
		
		printf("\r\n\r\nHello from r00t. Starting\r\n\r\n");
	
		int i; 

		for(i=0;i<=100;i++) {
			srand(time(NULL) * i);
			arr[i] = rand() % 100;
		}

	}

	MPI_Request req; 
   	MPI_Status status;
	
        // send our populated array to each process 
        // using a simple nonblocking collective ...
        
	MPI_Ibcast(arr, 100, MPI_INT, 0, MPI_COMM_WORLD, &req);
	
	// compare to ...
	// MPI_Bcast(arr, 100, MPI_INT, 0, MPI_COMM_WORLD);

	// here we can do work that is independent of our
	// MPI computations...

	printf("*working*\r\n");
	
	// since we are sending asynchronous requests
	// a wait is issued to synchronize each process
	// before we can evaluate our results
	
	MPI_Wait(&req, &status); 
	
	if(rank > 0) {
		        
	        printf("My Rank is %d and I drew %d \r\n", rank, arr[rank]);
        
	}
    	
	MPI_Finalize();
        
	if(rank == 0) { 
		printf("\r\n\r\nDone\r\n\r\n");  
	}
 
    	return 0;

}
