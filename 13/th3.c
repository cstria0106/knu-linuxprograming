#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct param {
    int n; // 스레드 번호
    char** messages; // 메세지 배열
} Param; // 매개변수 구조체

void* print_method(void* param); // 출력 스레드 함수 원형

int main(int argc, char* argv[]) {
    int i;
    Param params[5]; // 매개변수 구조체 배열
    pthread_t threads[5]; // 스레드 id 배열
    char* messages[] = {"First", "Second", "Third", "Fourth", "Fifth"}; // 출력할 메세지 배열

    // 5개의 출력 스레드를 만든다
    for(i = 0; i < 5; i++) {
        params[i].n = i; // 배개변수의 n값을 설정한다
        params[i].messages = messages; // 매개변수의 메세지 배열 값을 설정한다
        pthread_create(threads + i, NULL, print_method, params + i); // 스레드를 생성한다
    }
   
    // 각 스레드가 종료되는 것을 기다리고 해제한다
    for(i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    exit(EXIT_SUCCESS);
}

void* print_method(void* param) {
    int i;
    
    // 매개변수의 첫번째 값을 구조체로서 받는다
    // (매개변수 구조체의 포인터를 받았으므로 이를 참조)
    Param param_value = ((Param*)param)[0];

    printf("[Thread #%d]\n", param_value.n); // 스레드 번호를 출력한다
    for(i = 0; i <= param_value.n; i++) { // 0번째 메세지부터 스레드 번호까지의 메세지까지 출력
        printf("%s", param_value.messages[i]); 
        if(i != param_value.n) printf(", ");
    }
    printf("\n");

    pthread_exit(0);
}
