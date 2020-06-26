#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define KEY 0x19134794

union semun {
    int val;
    struct semid_ds* buf;
    unsigned short int* array;
};

static int semid;

int main(int argc, char* argv[]) {
    FILE* file; // counter.txt 파일 포인터
    int count[5]; // 카운터 배열
    int i;

    union semun sem_union;
    struct sembuf mysem_open = {0, -1, SEM_UNDO};
    struct sembuf mysem_close = {0, 1, SEM_UNDO};
    int sem_num;

    sem_num = argc > 1 ? 1 : 0;
    
    // 세마포 id를 얻는다.
    semid = semget((key_t)KEY, sem_num, 0660 | IPC_CREAT);
    if(semid < 0) {
        perror("세마포를 얻을 수 없습니다.");
        exit(EXIT_FAILURE);
    }

    // 인자가 있었다면 세마포를 초기화한다.
    if(sem_num == 1) {
        sem_union.val = 1;
        if(semctl(semid, 0, SETVAL, sem_union) < 0) {
            perror("세마포의 값을 초기화할 수 없습니다.");
            exit(EXIT_FAILURE);
        }
    }

    // 세마포를 연다. (내 차례가 올 때 까지 기다린다.)
    if(semop(semid, &mysem_open, 1) < 0) {
        perror("세마포를 열 수 없습니다.");
        exit(EXIT_FAILURE);
    }

    // 파일을 열어 카운터를 5개 읽고 각각 1을 더한다..
    if((file = fopen("counter.txt", "r+")) == NULL) {
        perror("counter.txt 파일을 열 수 없습니다.");
        exit(EXIT_FAILURE);
    }

    fread(count, sizeof(int), 5, file);

    for(i = 0; i < 5; i++) {
        count[i]++;
    }

    // 5초 기다린다.
    sleep(5);

    // 1씩 더했던 값을 파일에 써넣는다.
    rewind(file);
    fwrite(count, sizeof(int), 5, file);
    
    // 파일을 닫는다.
    fclose(file);

    // 세마포를 반환한다.
    semop(semid, &mysem_close, 1);

    return EXIT_SUCCESS;
}
