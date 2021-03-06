#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

// 문자 c를 count번 파일에 쓰고 에러 처리
int write_many(int fd, char c, int count) {
    int i;
    for(i = 0; i < count; i++) {
        if(write(fd, &c, sizeof(char)) < 0) {
            perror(NULL);
            exit(1);
        }
    }
    return 0;
}

int main(void) {
    int size;
    int fd;
    int i, j;

    printf("Size: ");
    scanf("%d", &size);

    fd = open("output", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if(fd < 0) {
        perror(NULL);
        return 1;
    }

    // 잎(삼각형 모양) 가운데 정렬하여 출력
    for(i = 0; i < size; i++) {
        write_many(fd, ' ', size - i - 1);
        write_many(fd, '$', (i + 1) * 2);
        write_many(fd, '\n', 1);
    }

    // 가지(네모 모양) 가운데 정렬하여 출력
    for(i = 0; i < 2; i++) {
        write_many(fd, ' ', size - 1);
        write_many(fd, '$', 2);
        write_many(fd, '\n', 1);
    }

    close(fd);

    return 0;
}
