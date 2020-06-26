#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <utime.h>

int main(int argc, char* argv[]) {
    char* path; // 파일의 경로를 저장할 문자열 포인터
    time_t current_time; // 현재 시각을 저장할 구조체
    struct utimbuf time_buffer; // 파일의 접근/수정 시각을 지정할 구조체

    // 인수가 하나가 아니라면 오류 발생
    if(argc != 2) {
        printf("파일 이름으로 인수가 하나만 주어져야 합니다.\n");
        exit(EXIT_FAILURE);
    }

    // 현재 시각을 알아낸다.
    current_time = time(NULL);

    // 접근/수정 시각을 1년 뒤로 설정한다.
    time_buffer.actime = current_time + 31536000;
    time_buffer.modtime = current_time + 31536000;
    
    // 파일의 경로를 첫 번째 인수로 설정
    path = argv[1];
    
    // 파일의 접근/수정 시각을 수정한다.
    // 실패하면 에러 발생
    if(utime(path, &time_buffer) < 0) {
        printf("파일의 접근/수정 시간을 변경할 수 없습니다.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
