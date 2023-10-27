#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/ipc.h>

#include <sys/msg.h>



struct msg_buffer 

{

    long msg_type;

    int nums[10];

};



int main()

{

    key_t key;

    int msg_id;



    key = (key_t)1000;



    msg_id = msgget(key, 0666 | IPC_CREAT);



    

    struct msg_buffer message;

    message.msg_type = 1;

    printf("Enter at least 10 nums:\n");

    for (int i = 0; i < 10; i++)

        scanf("%d", &message.nums[i]);

    if (msg_id == -1) 

        exit(1);

    msgsnd(msg_id, &message, sizeof(message.nums), 0);

    printf("Data has been sent to receiver\n");

    return 0;

}