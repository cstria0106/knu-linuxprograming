#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <stdlib.h>
#include "message.h"

#define SEND_KEY 0x19134791
#define RECEIVE_KEY 0x19134792

int main(void) {
    int send_id, receive_id;
    Message message, received;

    message.type = 1;
    
    if((send_id = msgget(SEND_KEY, IPC_CREAT | 0660)) < 0) {
        perror("Send");
        exit(EXIT_FAILURE);
    }

    if((receive_id = msgget(RECEIVE_KEY, IPC_CREAT | 0660)) < 0) {
        perror("Receive");
        exit(EXIT_FAILURE);
    }

    while(1) {
        printf("Message > ");
        fgets(message.content, sizeof(char) * 256, stdin); // 보낼 메세지를 입력받는다.

        if(msgsnd(send_id, &message, sizeof(Message), 0) < 0) { // 메세지를 보낸다.
            perror("Send");
            continue;
        }
         
        if(strcmp(message.content, ".\n") == 0) { // 만약 보낸 메세지가 "." 이었다면 프로그램을 종료한다.
            break;
        }

        if(msgrcv(receive_id, &received, sizeof(Message), 0, 0) < 0) { // 메세지를 대기한다.
            perror("Receive");
            continue;
        }

        printf("Recieved > %s", received.content); // 받은 메세지를 출력한다.
    }

    return EXIT_SUCCESS;
}
