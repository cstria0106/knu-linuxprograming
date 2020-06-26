#include <stdio.h>

int main(void) {
    FILE* input_file;
    FILE* output_file;
    char line[1024];
    int line_num = 0; // 읽어들인 줄의 수를 저장할 변수
    
    input_file = fopen("input", "r");
    output_file = fopen("output", "w");

    if(input_file == NULL) {
        printf("File not found.");
        return 1;
    }
    
    while(fgets(line, sizeof(char) * 1024, input_file)) { // 한줄 한줄 읽음
        if(++line_num % 2 == 0) continue; // 읽은 줄의 수가 짝수라면 넘어감
        fputs(line, output_file); // 홀수 줄만 써넣음
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}
