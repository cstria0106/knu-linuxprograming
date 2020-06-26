#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    char* str;  // 할당받을 문자열 포인터
    int count;  // 문자열의 길이로 입력받은 인자
    int i;      // 배열 순회용 변수

    // 인자를 하나만 받아야 함
    if (argc != 2) {
        printf("인자 하나를 문자열의 길이로 받아야 합니다.\n");
        exit(EXIT_FAILURE);
    }

    // 인자를 정수로 변환
    count = atoi(argv[1]);

    // count + 1 길이의 문자열을 동적 할당
    str = malloc(sizeof(char) * (count + 1));

    // 오류 처리
    if (str == NULL) {
        printf("문자열을 할당할 수 없습니다.\n");
        exit(EXIT_FAILURE);
    }

    // count 길이의 문자열을 채움
    for (i = 0; i < count; i++) {
        str[i] = (char)(count + 0x40);    
    }

    // count + 11 길이의 문자열로 기존의 문자열을 복사하여 다시 할당
    str = realloc(str, sizeof(char) * (count + 11));

    // 오류 처리
    if (str == NULL) {
        printf("문자열을 할당할 수 없습니다.\n");
        exit(EXIT_FAILURE);
    }

    // 뒤에 이어붙여서 10개의 문자로 채움
    for (i = count; i < count + 10; i++) {
        str[i] = (char)(count + 0x60);
    }

    // 마지막을 널 문자로 설정
    str[count + 10] = '\0';
    
    // 출력
    printf("%s\n", str);    
    
    // 할당 해제
    free(str);

    return 0;
}
