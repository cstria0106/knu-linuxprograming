#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int fd;
    double n; // 읽은 double 값을 저장할 변수
    int i;

    fd = open("201913479.bin", O_RDONLY);
    
    for(i = 0; i < 20; i++) {
        read(fd, &n, sizeof(double)); // 파일에서 double 값 하나를 읽어 n에 저장
        printf("%10.4f", n);    // 오른쪽으로 넓이 10으로 정렬하여 출력
    }
    printf("\n");

    close(fd);

    return 0;
}
