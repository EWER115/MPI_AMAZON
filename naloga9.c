#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
	int myid, size;
	
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//int buff_size = 2*size+2;
	int buff_size = 1024;
	char buffer[buff_size];

	if(myid==0)
	{		
		sprintf(buffer,"%d",myid);
		MPI_Send(buffer,strlen(buffer)+1, MPI_CHAR,1,myid,MPI_COMM_WORLD);
		MPI_Recv(buffer, buff_size, MPI_CHAR, size-1, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		// Konec, izpisem buffer
		sprintf(buffer,"%s-%d",buffer,myid);
		printf("%s\n",buffer);	
	}
	else
	{
		MPI_Recv(buffer, buff_size, MPI_CHAR, myid-1, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		sprintf(buffer,"%s-%d",buffer,myid);
		
		if(myid == (size-1))		
			MPI_Send(buffer, strlen(buffer)+1, MPI_CHAR,0,myid,MPI_COMM_WORLD);
		else
			MPI_Send(buffer, strlen(buffer)+1, MPI_CHAR,myid+1,myid,MPI_COMM_WORLD);
	}

	MPI_Finalize();
	
	

	return 0;
}
