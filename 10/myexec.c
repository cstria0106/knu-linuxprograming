#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    // 인자가 부족하면 오류를 발생
    if(argc < 2) {
        printf("Usage: myexec [a|b]\n");
        exit(-1);
    }

    // 첫 번째 인자의 첫 글자가
    switch(argv[1][0]) {
        case 'a': // 'a'라면
            // myprog1을 execl로 실행
            execl("./myprog1", "myprog1", "15", NULL);
            break;

        case 'b': // 'b'라면
            // myprog2를 execlp로 실행
            execlp("myprog2", "myprog2", "15", NULL);
            break;

        default: // 둘 다 아니라면
            // 오류 발생 후 종료
            printf("Usage: myexec [a|b]\n");
            exit(-1);
            break;
    }

    // exec가 정상적으로 실행되면 실행하면 아래 코드는 실행되지 않는다
    printf("정상적으로 실행되지 않았습니다.\n");
    exit(-1);
}
