#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

struct message {
    long msg_type;
    char msg_text[100];
};

int main() {
    // 1234 is the unique key and 0666 sets permissions
    int msgid = msgget(1234, 0666 | IPC_CREAT);
    struct message msg_send, msg_receive;
    //send
    msg_send.msg_type = 1; 
    strcpy(msg_send.msg_text, "Process X is causing deadlock");
    // msgsnd(id, pointer_to_struct, size_of_text, flags)
    msgsnd(msgid, &msg_send, sizeof(msg_send.msg_text), 0);
    printf("Data Sent: %s\n", msg_send.msg_text);
    // receive
    // msgrcv(id, pointer_to_struct, size_of_text, type, flags)
    msgrcv(msgid, &msg_receive, sizeof(msg_receive.msg_text), 1, 0);
    printf("Data Received: %s\n", msg_receive.msg_text);
    // cleanup
    // Remove the message queue from the system
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}