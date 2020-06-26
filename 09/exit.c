#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int count;

// 첫번째 콜백 함수
void callback_a() {
    printf("%d\n", count % 2020);
}

// 두번째 콜백 함수
void callback_b() {
    printf("%d\n", time(NULL));
}

int main(void) {
    // 각 콜백을 등록함
    if (atexit(callback_a) != 0) {
        printf("callback_a를 등록할 수 없습니다.");
    }
    if (atexit(callback_b) != 0) {
        printf("callback_b를 등록할 수 없습니다.");
    }
    
    // for문을 돌면서 최종적으로  count를 10000으로 설정
    for(count = 0; count < 10000; count++);

    return 0;
}
