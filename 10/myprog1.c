/* myprog1.c */
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char *av[]) {
    int i, s, l;

    if(ac < 2) {
        printf("Usage: %s number\n", av[0]);
        exit(-1);
    }

    l = strtol(av[1], 0, 0);
    // 1부터 첫번째 인자 숫자까지 더하여 출력
    for(s = 0, i = 1; i <= l; i++) s += i;
    printf("s = %d\n", s);
}
