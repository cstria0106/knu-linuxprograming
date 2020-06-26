#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

int main(int argc, char* argv[]) {
    DIR* directory;         // 연 디렉터리
    struct dirent* entry;  // 디렉터리의 엔트리

    // 인자를 하나만 받아야 함
    if(argc != 2) {
        printf("인수 하나가 디렉터리 위치로 주어져야 합니다.\n");
        exit(EXIT_FAILURE);
    }

    // 디렉터리를 연다
    directory = opendir(argv[1]);

    // 열 수 없으면 오류 출력 후 종료
    if(directory == NULL) {
        printf("디렉터리를 열 수 없습니다.\n");
        exit(EXIT_FAILURE);
    }

    // 디렉터리의 엔트리를 하나씩 찾아서 이름을 출력
    while((entry = readdir(directory)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    return 0;
}
