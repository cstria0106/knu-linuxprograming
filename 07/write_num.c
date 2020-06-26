#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int i;
    double numerator, denominator, n; // 분자, 분모, 생성한 수
    int fd;

    fd = open("201913479.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd < 0) {
        perror(NULL);
        return 1;
    }

    // 시드 설정
    srand((unsigned int)time(NULL));

    for(i = 0; i < 20; i++) {
        numerator = (double)rand();
        
        // 분모가 0이 아닐 때까지 반복하여 생성
        do {
            denominator = (double)rand();
        } while(denominator == 0);
        
        n = numerator / denominator; // 분자와 분모를 통해 수를 생성

        if(write(fd, &n, sizeof(double)) < 0) { // 생성한 수를 파일에 써넣음
            perror(NULL);
            return 1;
        }
    }

    close(fd);

    return 0;
}
