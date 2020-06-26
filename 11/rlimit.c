#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// 자식 프로세스가 죽으면 안내문을 출력하고 종료한다
void on_child_dead() {
    printf("Child process' job is complete. Exiting...\n");
    exit(0);
}

int main(int argc, char* argv[]) {
    int n; // 타이머
    char** commands; // 명령어 배열
    int pid; // 생성한 자식 PID

    if(argc != 3) { // 인자가 3개가 아니라면 오류 출력 후 종료
        printf("Invalid arguments!\n");
        exit(1);
    }

    n = strtol(argv[1], NULL, 10); // 첫번째 인자는 정수로 변환 후 타이머로
    commands = &argv[2]; // 두번째 인자의 주소를 명령어 배열로
 
    signal(SIGCHLD, on_child_dead); // SIGCHLD가 발생하면(자식이 죽으면) on_child_dead 함수를 호출하도록 등록
  
    pid = fork(); // 복제한다

    if(pid == 0) {  // Child 
        // 자식이라면 입력한 명령어를 자기자신을 대체하여 실행한다 
        if(execvp(commands[0], commands) == -1){
            perror("Can't execute command!");
        }
    } else {        // Parent
        // 부모라면 n초 쉬고 SIGINT를 보내고 다시 n초 쉬고 SIGKILL을 보낸다
        sleep(n);
        kill(pid, SIGINT);
        sleep(n);
        kill(pid, SIGKILL);
        printf("Time is over. Child process was killed.\n");
    }
}
