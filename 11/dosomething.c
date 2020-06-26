#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void print_warning() {
    printf("Warning!\n");
}

// 문자열을 뒤집어 반환한다
char* reversed() {
    static char buffer[100];
    
    len = strlen(str);

    for(i = 0; i < len; i++) {
        buffer[i] = str[len - i - 1];
    }

    return buffer;
}

int main(void) {
    char str[100];
    int i, len;

    // SIGINT가 오면 경고를 출력한다
    signal(SIGINT, print_warning);

    scanf("%s", str); 
    printf("Reversed: %s\n", reversed(str));
}
