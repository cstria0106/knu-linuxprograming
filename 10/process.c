#include <unistd.h>
#include <stdio.h>

int main(void) {
    pid_t child;
    pid_t grandchild;

    // I am parent 출력하고 fork를 수행하여 child process를 생성
    printf("I am parent(%d, %d)!\n", getpid(), getppid());
    child = fork();
    
    // child process라면
    if(child == 0) {
        // I am a child 출력하고 fork를 수행하여 grandchild process를 생성
        printf("I am a child(%d, %d)!\n", getpid(), getppid());
        grandchild = fork();
        
        // grandchild process라면
        if(grandchild == 0) {
            // I am grandchild 출력
            printf("I am grandchild(%d, %d)!\n", getpid(), getppid());
            return 0; // 종료
        }
    }

    return 0; // 종료
}
