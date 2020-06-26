#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler_a(int sig) {
    printf("Oops! SIGUSR1!\n");
}

void handler_b(int sig) {
    printf("Ooooops! SIGUSR2!\n");
    exit(0);
}

int main(void) {
    signal(SIGUSR1, handler_a);
    signal(SIGUSR2, handler_b);

    while(1);
}
