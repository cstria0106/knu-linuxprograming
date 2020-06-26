/* myprog2.c */
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char *av[]) {
    int i, p, l;

    if(ac < 2) {
        printf("Usage: %s number\n", av[0]);
        exit(-1);
    }

    l = strtol(av[1], 0, 0);
    // 1부터 첫번째 인자 숫자까지 곱해 출력(팩토리얼)
    for(p = i = 1; i <= l; i++) p *= i;
    printf("p = %d\n", p);
}
