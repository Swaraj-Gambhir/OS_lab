//CS21B2024
//Swaraj P Gambhir
#include <stdio.h>

#include <stdlib.h>

#include <fcntl.h>

#include <unistd.h>

#include <sys/stat.h>

#include <sys/types.h>



int main() {

    // Create the FIFO (Named Pipe) if it doesn't exist

    const char *fifoName = "myfifo";

    mkfifo(fifoName, 0666);



    printf("Receiver: FIFO created.\n");



    // Open the FIFO for reading

    int fifo_fd = open(fifoName, O_RDONLY);



    if (fifo_fd == -1) {

        perror("Receiver: Error opening FIFO for reading");

        exit(EXIT_FAILURE);

    }



    // Read an integer value (A) from the FIFO

    int A;

    read(fifo_fd, &A, sizeof(A));

    printf("Receiver: Read A = %d from FIFO.\n", A);



    // Calculate the one's complement (B1)

    int i=0;

    int B1[10] ;

    while(i<10)

    {

    	B1[i]=A%2;

    	A=A/2;

    	i++;

    	if(A==0)

    	break;

    }

    for (int j=0;j<i;j++)

    {

    	if(B1[j]==0)

    	B1[j]=1;

    	else

    	B1[j]=0;

    	printf("%d",B1[j]);

    	

    }

    int mult=1;

    int sum=0;

    for (int j=0;j<i;j++)

    {

    	sum=sum+mult*B1[j];

    	mult=mult*2;

    	

    }

    

    printf("Receiver: Calculated B1 = %d.\n", sum);



    // Close the FIFO for reading

    close(fifo_fd);



    // Reopen the FIFO for writing

    fifo_fd = open(fifoName, O_WRONLY);



    if (fifo_fd == -1) {

        perror("Receiver: Error opening FIFO for writing");

        exit(EXIT_FAILURE);

    }



    // Write the one's complement (B1) back to the FIFO

    printf("Receiver: Writing B1 = %d to FIFO.\n", sum);

    write(fifo_fd, &sum, sizeof(sum));



    // Close the FIFO for writing

    close(fifo_fd);



    printf("Receiver: Done.\n");



    return 0;

}