#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int sum; // 최종 합 저장 될 변수
int mul; // 최종 곱 저장 될 변수

void* add(void* param); // 합 스레드 함수 원형
void* multiply(void* param); // 곱 스레드 함수 원형

int main(int argc, char* argv[]) {
    pthread_t add_thread, mul_thread; // 스레드 id
    int n; // 인자로 받은 정수

    if(argc < 2) { // 인자가 잘못되었으면 오류를 출력하고 종료
        printf("Bad arguments.\n");
        exit(EXIT_FAILURE);
    }

    n = strtol(argv[1], NULL, 10); // 인자로 받은 문자열을 정수로 변환하여 저장한다
    pthread_create(&add_thread, NULL, add, &n); // 합 스레드를 생성한다
    pthread_create(&mul_thread, NULL, multiply, &n); // 곱 스레드를 생성한다

    pthread_join(add_thread, NULL); // 합 스레드가 종료되기 까지 기다린 후 해제한다
    pthread_join(mul_thread, NULL); // 곱 스레드가 종료되기 까지 기다린 후 해제한다

    printf("Sum = %d\n", sum); // 최종 합을 출력한다
    printf("Mul = %d\n", mul); // 최종 곱을 출력한다
    exit(EXIT_SUCCESS);
}

void* add(void* param) {
    int i;
    int n = ((int*)param)[0]; // 첫번째 매개변수를 int형으로 받는다(변수 n의 포인터를 받았으므로 이를 참조)

    sum = 0;
    for(i = 1; i <= n; i++) {
        sum += i; // 1부터 n까지 더한다
    }

    pthread_exit(0);
}

void* multiply(void* param) {
    int i;
    int n = *((int*)param); // 첫번째 매개변수를 int형으로 받는다

    mul = 1;
    for(i = 2; i <= n; i++) {
        mul *= i; // 2부터 n까지 곱한다
    }

    pthread_exit(0);
}
