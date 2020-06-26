#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    char* path;
    struct stat file_stat; // 파일의 정보를 저장할 구조체

    // 인수가 적으면 오류 발생
    if(argc != 2) {
        printf("파일 이름으로 한 개의 인수가 필요합니다.\n");
        exit(EXIT_FAILURE);
    }

    // 경로를 첫 번째 인수로 설정
    path = argv[1];

    // 파일의 정보를 알아냄
    stat(path, &file_stat);

    // 기존 권한에 그룹 실행 권한과 setgid 비트를 추가하여 권한을 변경
    if(chmod(path, file_stat.st_mode | S_IXGRP | S_ISGID) < 0) {
        printf("파일의 권한을 변경할 수 없습니다.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
