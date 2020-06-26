#include <unistd.h>
#include <sys/times.h>
#include <stdio.h>
#include <stdlib.h>

void err_sys(char* p) {
    perror(p);
    exit(-1);
}

// 실행 시간을 형식에 맞게 출력함
void pr_times(clock_t real, struct tms* tmsstart, struct tms* tmsend) {
    static long clktck = 0;

    if(clktck == 0)
        clktck = sysconf(_SC_CLK_TCK);

    // 실제 실행시간
    fprintf(stderr, "   real:   %7.2f\n", real / (double)clktck);

    // 사용자 CPU 점유시간을 체크
    fprintf(stderr, "   user:   %7.2f\n",
            (tmsend->tms_utime - tmsstart->tms_utime) / (double)clktck);
    // 시스템 CPU 점유시간을 체크
    fprintf(stderr, "   sys:    %7.2f\n",
            (tmsend->tms_stime - tmsstart->tms_stime) / (double)clktck);

    // 자식 프로세스의 사용자 CPU 점유시간을 체크
    fprintf(stderr, "   child user:   %7.2f\n",
            (tmsend->tms_cutime - tmsstart->tms_cutime) / (double)clktck);
    // 자식 프로세스의 시스템 CPU 점유시간을 체크
    fprintf(stderr, "   child sys:   %7.2f\n",
            (tmsend->tms_cstime - tmsstart->tms_cstime) / (double)clktck);
}

// 명령어를 실행하고 실행 전과 후의 시간을 검사하여 실행시간을 출력함
void do_cmd(char* cmd) {
    int status;
    clock_t start, end;
    struct tms tmsstart, tmsend;

    fprintf(stderr, "\ncommand: %s\n", cmd);
    if((start = times(&tmsstart)) == -1)      /* starting values */
        err_sys("times error");
    if((status = system(cmd)) < 0)          /* execute command */
        err_sys("system() error");
    if((end = times(&tmsend)) == -1)        /* ending values */
        err_sys("times error");
    pr_times(end - start, &tmsstart, &tmsend);
}

int main(int argc, char* argv[]) {
    int i;
    
    // 인자로 받은 명령어를 각각 실행하고 실행 시간을 체크함
    for(i = 1; i < argc; i++) {
        do_cmd(argv[i]);
    }
    exit(0);
}
