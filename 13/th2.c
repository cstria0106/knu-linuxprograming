#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* print_method(void* param); // 출력 스레드 함수 원형

int main(void) {
    pthread_t threads[10]; // 스레드 id 배열
    int i;
    int params[10]; // 스레드 매개변수 배열
    
    // 별을 40개 찍는다
    for(i = 0; i < 40; i++) {
        printf("*");
    }
    printf("\n");

    // 10번 반복하여 출력 스레드를 생성한다
    for(i = 0; i < 10; i++) {
        params[i] = i; // 인자 배열의 값을 설정한다
        pthread_create(threads + i, NULL, print_method, params + i);
    }

    // 각 스레드가 종료되기 까지 기다리고 해제한다
    for(i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // 모든 스레드가 종료되었으므로 별을 40개 출력하고 종료한다
    for(i = 0; i < 40; i++) {
        printf("*");
    }
    printf("\n");

    exit(EXIT_SUCCESS);
}


void* print_method(void* param) {
    int i;
    int tid = ((int*)param)[0]; // 매개변수의 첫번째 값을 스레드 번호로서 정수형으로 받는다

    for(i = 0; i < (tid + 1) * 3; i++) { // (스레드 번호 + 1) * 3 번 #을 찍는다 
        printf("#");
    }
    printf("\n");
    pthread_exit(0);
}

