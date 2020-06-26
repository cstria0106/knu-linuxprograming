#include <stdio.h>
#include <stdlib.h>

/* 
 * n번째 피보나치 수를 구함 
 * 같은 연산을 여러번 반복하기에 실행시간이 길다
 */
int fibonacci(int n) {
    if(n == 1 || n == 2) {
        return n - 1;
    }
    return fibonacci(n - 2) + fibonacci(n - 1);
}

int main(void) {
    printf("%d\n", fibonacci(42)); 
    return 0;
}
