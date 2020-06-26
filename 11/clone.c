#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#define PROCESS_NUMBER 7

int uid = 0;

int pid_array[PROCESS_NUMBER];

// SIGINT가 오면 적절한 메세지를 출력하고 종료
void on_sigint() {
    if(uid != 0) printf("I'm %dth child. Now I'm dead.\n", uid); // uid가 0이 아니면(자식 프로세스면)
    else printf("I'm parent. My all children is dead. Exiting...\n"); // 0이면(부모 프로세스면)
    exit(0);
}

// 프로세스를 n번 복제하여 만약 자식 프로세스라면 false를 부모 프로세스라면 true를 반환한다
int clone(int n) {
    int pid;
 
    if(n == 0) return 1; // n이 0이라면 이는 부모 프로세스이며 true를 반환한다
    pid = fork(); // 프로세스 복제
    
    if(pid == 0) {  // Child
        uid = PROCESS_NUMBER - n + 1; // 이 자식 프로세스에게 uid를 매긴다
        printf("Hello! I'm %dth child.\n", uid);
        return 0; // 자식 프로세스이기 때문에 false를 반환한다
    }
    else {
        pid_array[n - 1] = pid; // 부모 프로세스라면 생성한 자식 프로세스의 pid를 배열에 집어넣는다
        clone(n - 1); // 반복 횟수 n에 대해 n - 1로 재귀적으로 호출한다
    }
}

int main(void) {
    int i;
    int is_parent;
    
    signal(SIGINT, on_sigint); // SIGINT를 받으면 on_sigint를 실행한다

    is_parent = clone(PROCESS_NUMBER); // PROCESS_NUMBER개의 자식 프로세스를 생성한다

    if(!is_parent) pause(); // 만약 자식 프로세스라면 대기한다
 
    // 부모 프로세스라면
    for(i = 0; i < PROCESS_NUMBER; i++) { // 생성한 프로세스에게 역순으로 SIGINT를 보낸다
        sleep(1);
        kill(pid_array[i], SIGINT);
    }

    sleep(1);
    raise(SIGINT); // 마지막에는 자기 자신한테 SIGINT를 보낸다
}
