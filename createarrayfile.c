#include <stdio.h>
#include <stdlib.h>

#define N 1000000

int main() {
    int i;
    FILE* fp=fopen("array.txt","w");
    for (i=0;i<N;i++) {
        fprintf(fp,"%d\t",1+rand()%1000000);
    }
    return 0;
}