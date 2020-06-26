#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <stdlib.h>
#include "message.h"

#define SEND_KEY 0x19134792
#define RECEIVE_KEY 0x19134791

int main(void) {
    int send_id, receive_id;
    Message message, received;
    char* c;

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
        if(msgrcv(receive_id, &received, sizeof(Message), 0, 0) < 0) { // 메세지를 대기한다.
            perror("Receive");
            continue;
        }

        if(strcmp(received.content, ".\n") == 0) { // 받은 메세지가 "." 이라면 프로그램을 종료한다.
            break;
        }

        printf("Recieved > %s", received.content); // 받은 메세지를 출력해본다.

        // 받은 메세지를 저장한 버퍼를 순회하면서 대문자는 소문자로 소문자는 대문자로 변경한다.
        c = received.content;

        while(*c != '\0') {
            if(islower(*c)) {
                *c = toupper(*c);
            }
            else {
                *c = tolower(*c);
            }

            c++;
        }

        printf("To send > %s", received.content); // 변경된 메세지를 출력해본다.
        strcpy(message.content, received.content); // 변경된 메세지를 보낼 메세지 버퍼에 복사한다.
        
        if(msgsnd(send_id, &message, sizeof(Message), 0) < 0) { // 메세지를 전송한다.
            perror("Send");
            continue;
        }
    }

    return EXIT_SUCCESS;
}
