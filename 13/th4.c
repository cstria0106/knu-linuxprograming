#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

void* sin_method(void* param); // 사인 값 계산 스레드 함수 원형
void* cos_method(void* param); // 코사인 값 계산 스레드 함수 원형
void* log_method(void* param); // 로그 값 계산 스레드 함수 원형
void* exp_method(void* param); // 지수 값 계산 스레드 함수 원형

long double sin_sum = 0; // 사인 합
long double cos_sum = 0; // 코사인 합
long double log_sum = 0; // 로그 합
long double exp_sum = 0; // 지수 합

int main(void) {
    int i;
    int params[4]; // 매개변수 배열
    pthread_t threads[4]; // 스레드 id 배열
    void* (*functions[4])(void*) = {sin_method, cos_method, log_method, exp_method}; // 각각 스레드에 대한 함수 원형 포인터 배열

    // 4개의 계산 스레드를 생성한다
    for(i = 0; i < 4; i++) {
        params[i] = i; // 매개변수의 값을 설정한다
        pthread_create(threads + i, NULL, functions[i], params + i); // i번째 함수를 원형으로 하는 스레드 생성
    }

    // 각 스레드가 종료되는 것을 기다리고 해제한다
    for(i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    // 최종 계산 값을 출력한다
    printf("Sin = %Lf\n", sin_sum);
    printf("Cos = %Lf\n", cos_sum);
    printf("Log = %Lf\n", log_sum);
    printf("Exp = %Lf\n", exp_sum);

    exit(EXIT_SUCCESS);
}


void* sin_method(void* param) {
    int i;
    int n = ((int*)param)[0];

    printf("[Thread #%d start]\n", n);

    for(i = 0; i < 500000; i++) {
        sin_sum += sin((double)i / 1000000);
    }

    printf("[Thread #%d complete]\n", n);

    pthread_exit(0);
}

void* cos_method(void* param) {
    int i;
    int n = ((int*)param)[0];

    printf("[Thread #%d start]\n", n);

    for(i = 0; i < 500000; i++) {
        cos_sum += cos((double)i / 1000000);
    }

    printf("[Thread #%d complete]\n", n);

    pthread_exit(0);
}

void* log_method(void* param) {
    int i;
    int n = ((int*)param)[0];

    printf("[Thread #%d start]\n", n);

    for(i = 0; i < 500000; i++) {
        log_sum += log10((double)(i + 1) / 1000000);
    }

    printf("[Thread #%d complete]\n", n);

    pthread_exit(0);
}

void* exp_method(void* param) {
    int i;
    int n = ((int*)param)[0];

    printf("[Thread #%d start]\n", n);

    for(i = 0; i < 500000; i++) {
        exp_sum += exp((double)i / 1000000);
    }
    
    printf("[Thread #%d complete]\n", n);

    pthread_exit(0);
}
