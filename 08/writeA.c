#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096
#define FILE_SIZE   (2 * 1024 * 1024)
#define COUNT       (FILE_SIZE / BUFFER_SIZE)

int main(int argc, char* argv[]) {
    int i, file, do_sync; // 순회용 인덱스, 파일 디스크립터, sync를 수행할지 지정하는 boolean
    char buffer[BUFFER_SIZE]; // 쓸 데이터를 저장해놓을 버퍼

    do_sync = 0; // 기본적으로 sync는 수행하지 않는다.

    // 만약 -s가 인수로 주어진다면 sync를 수행하도록 한다.
    if (argc >= 2 && strcmp(argv[1], "-s") == 0) {
        do_sync = 1;
    }

    // 버퍼를 '.'으로 채워넣음
    memset(buffer, '.', BUFFER_SIZE);
    
    // 파일을 생성
    if ((file = creat("file.write", 0600)) < 0) {
        printf("파일 file.write를 생성할 수 없습니다.");
        exit(EXIT_FAILURE);
    }

    // 파일 사이즈가 FILE_SIZE 바이트만큼 되도록 파일에 버퍼의 내용을 써넣음
    for (i = 0; i < COUNT; i++) {
        write(file, buffer, BUFFER_SIZE);
        if (do_sync) { // 만약 do_sync가 0이 아니라면 sync를 수행한다.
            sync();
        }
    }

    close(file); // 파일을 닫음
    return 0;
}
