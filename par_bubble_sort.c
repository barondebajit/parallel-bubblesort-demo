#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

clock_t begin,end;

void swap(int* a,int* b) {
    *a=*a^*b;
    *b=*a^*b;
    *a=*a^*b;
}

void par_bubblesort(int* arr,int n) {
    int i,j;
    int issorted=0;
    while (1) {
        issorted=1;
        #pragma omp parallel for
        for (i=0;i<n-1;i+=2) {
            if (arr[i]>arr[i+1]) {
                swap(&arr[i],&arr[i+1]);
                issorted=0;
            }
        }
        #pragma omp parallel for
        for (i=1;i<n-1;i+=2) {
            if (arr[i]>arr[i+1]) {
                swap(&arr[i],&arr[i+1]);
                issorted=0;
            }
        }
        if (issorted==1) break;
    }
}

int main() {
    int i,j,k,n=100000;
    while (n<=1000000) {
        int* arr=(int *)malloc(n*sizeof(int));
        FILE* fp=fopen("array.txt","r");
        for (i=0;i<n;i++) {
            fscanf(fp,"%d\t",&arr[i]);
        }
        begin=clock();
        par_bubblesort(arr,n);
        end=clock();
        printf("Time taken for %d data: %.3lf\n",n,(double)(end-begin)/CLOCKS_PER_SEC);
        free(arr);
        n+=100000;
    }
}