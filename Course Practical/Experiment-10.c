-> CODE :

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
struct message {
    long msg_type;
    char msg_text[100];
};
int main()
{
    key_t key = 1234;
    int msgid;
    struct message msg;
    msgid = msgget(key, 0666 | IPC_CREAT);
    msg.msg_type = 1;
    strcpy(msg.msg_text, "Hello Message Queue");
    msgsnd(msgid, &msg, sizeof(msg.msg_text), 0);
    msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0);
    printf("Received Message: %s\n", msg.msg_text);
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}

-> OUTPUT :

Received Message: Hello Message Queue
