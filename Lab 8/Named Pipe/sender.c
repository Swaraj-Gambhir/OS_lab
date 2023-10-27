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



    printf("Sender: FIFO created.\n");



    // Open the FIFO for writing

    int fifo_fd = open(fifoName, O_WRONLY);



    if (fifo_fd == -1) {

        perror("Sender: Error opening FIFO for writing");

        exit(EXIT_FAILURE);

    }



    // Write an integer value (A) to the FIFO

    int A ;

    scanf("%d",&A);

    printf("Sender: Writing A = %d to FIFO.\n", A);

    write(fifo_fd, &A, sizeof(A));



    // Close the FIFO

    close(fifo_fd);

    

    



    printf("Sender: Done.\n");

    

    

    printf("Receiver(Sender ): FIFO created.\n");



    // Open the FIFO for reading

    int fifo_fd1 = open(fifoName, O_RDONLY);



    if (fifo_fd == -1) {

        perror("Receiver: Error opening FIFO for reading");

        exit(EXIT_FAILURE);

    }



    // Read an integer value (A) from the FIFO

    int B1;

    read(fifo_fd1, &B1, sizeof(A));

    printf("Receiver: Read B1 = %d from FIFO.\n", B1);



    return 0;

}


