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

    // 공유 메모리의 연속된 세 값에 각각 2.72를 곱한다.
    shared_memory[0] *= 2.72;
    shared_memory[1] *= 2.72;
    shared_memory[2] *= 2.72;

    exit(EXIT_SUCCESS);
}
