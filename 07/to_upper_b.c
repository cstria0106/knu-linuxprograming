#include <unistd.h>
#include <fcntl.h>

int main(void) {
    int input_fd, output_fd;
    char c;
    
    input_fd = open("input", O_RDONLY);

    if(input_fd < 0) {
        write(STDERR_FILENO, "No input file.\n", sizeof(char) * 16);
        return 1;
    }

    output_fd = open("output", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if(output_fd < 0) {
        close(input_fd);
        write(STDERR_FILENO, "Error.\n", sizeof(char) * 7);
        return 1;
    }

    while(read(input_fd, &c, sizeof(char))) {
        if(c >= 'a' && c <= 'z') c += 'A' - 'a'; // 소문자라면 대문자로 바꿈
        if(write(output_fd, &c, sizeof(char)) < 0) {
            write(STDERR_FILENO, "Error.\n", sizeof(char) * 7);
            close(input_fd);
            close(output_fd);
            return 1;
        }
    }

    close(input_fd);
    close(output_fd);

    return 0;
}
