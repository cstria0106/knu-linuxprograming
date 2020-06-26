#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    FILE* file;
    int i, count;

    file = fopen("counter.txt", "r+");

    // 인자가 없다면
    if(argc == 1) {
        // counter를 5개 읽어 순서대로 출력한다.
        for(i = 0; i < 5; i++) {
            fread(&count, sizeof(int), 1, file);
            printf("%d", count);
            if(i != 4) {
                printf(", ");
            } else {
                printf("\n");
            }
        }

        return EXIT_SUCCESS;
    }

    // 인자가 있는데 5개가 아니면 오류를 출력한다.
    if(argc != 6) {
        printf("인자 다섯 개가 주어져야합니다.\n");
        exit(EXIT_FAILURE);
    }
 
    // 인자가 5개라면 각각의 인자를 순서대로 파일에 써넣는다.
    for(i = 0; i < 5; i++) {
        count = atoi(argv[i + 1]);
        fwrite(&count, sizeof(int), 1, file);
    }

    return EXIT_SUCCESS;
}
