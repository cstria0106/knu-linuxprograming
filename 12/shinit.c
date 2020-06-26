#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void throw(char* message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int main(void) {
    int shared_memory_id;
    double* shared_memory = NULL;
 
    shared_memory_id = shmget(0x19134793, sizeof(double) * 3, IPC_CREAT | 0660);
    if(shared_memory_id < 0) throw("공유 메모리를 얻을 수 없습니다.");

    shared_memory = shmat(shared_memory_id, 0, 0);

    if(shared_memory < 0) throw("공유 메모리의 위치를 읽을 수 없습니다.");

    // 공유 메모리의 값을 1.414, 3.142, 1.771로 초기화한다.
    shared_memory[0] = 1.414;
    shared_memory[1] = 3.142;
    shared_memory[2] = 1.771;

    exit(EXIT_SUCCESS);
}
