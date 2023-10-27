#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/ipc.h>

#include <sys/msg.h>



struct msg_buffer 

{

    long msg_type;

    int numbers[10];

};



int main() 

{

    key_t key;

    int msg_id;



    key = (key_t)1000;



    msg_id = msgget(key, 0666 | IPC_CREAT);



    if (msg_id == -1) 

    {

        perror("msgget");

        exit(1);

    }



    struct msg_buffer msg;



    msgrcv(msg_id, &msg, sizeof(msg.numbers), 1, 0);



    printf("Data has been received from sender:\n");



    int oddnums = 0;



    printf("Odd numbers: ");

    for (int i = 0; i < 10; i++) 

    {

        if (msg.numbers[i] % 2 != 0) 

        {

            printf("%d ", msg.numbers[i]);

            oddnums++;

        }

    }



    printf("\nTotal odd numbers: %d\n", oddnums);



    msgctl(msg_id, IPC_RMID, NULL);



    return 0;

}