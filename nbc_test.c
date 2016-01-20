#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char * argv[]) {
   
	int rank, i;
	int arr[100];

	for(i=0;i<=100;i++) {
		srand(time(NULL) * i);
		arr[i] = rand() % 100;
	}

	MPI_Request req; 
   	MPI_Status status;
	
	MPI_Init(&argc, &argv);
    
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	

	MPI_Ibcast(arr, 100, MPI_INT, 0, MPI_COMM_WORLD, &req);

	MPI_Wait(&req, &status); 
	

	if(rank == 0) {
		printf("Hello from r00t\r\n");
    	} else {
		printf("My Rank is %d and I drew %d \r\n", rank, arr[rank]);
	}
    
    	
	MPI_Finalize();
    
    	return 0;

}
