#include <unistd.h>
#include <fcntl.h>
#define SIZE 10000000


int main(void) {
    int file;
    int i;

    file = open("output.txt", O_CREAT | O_TRUNC);

    // 0부터 SIZE - 1까지 반복하며 파일에 바이너리로 써넣음
    for(i = 0; i < SIZE; i++) {
        write(file, &i, sizeof(int));
        // 파일을 저장장치에 동기화한다.
        // 이를 SIZE번 수행하기 때문에 실행시간이 길다.
        fsync(file);
    }

    close(file);

    return 0;
}
