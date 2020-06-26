#include <stdio.h>

int main(void) {
    FILE* input_file;
    FILE* output_file;
    char c;
    
    input_file = fopen("input", "r");

    if(input_file == NULL) {
        perror(NULL);
        return 1;
    }

    output_file = fopen("output", "w");

    if(output_file == NULL) {
        fclose(output_file);
        perror(NULL);
        return 1;
    }

    while(1) {
        c = fgetc(input_file);
        
        if(feof(input_file)) {
            break;
        }

        if(c >= 'a' && c <= 'z') c += 'A' - 'a'; // 소문자라면 대문자로 바꿈
        fputc(c, output_file);
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}
