#include <stdio.h>
#include <malloc.h>
#include <string.h>

int main(){
    int a,b,c;
    printf("a? b? c?: ");
    scanf("%d %d %d", &a, &b, &c);

    void ***ptr = malloc(3*sizeof(void **));

    ptr[0] = malloc(a*sizeof(void*)); //ptr[0]은 2차원 포인터터
    for(int i=0; i<a;i++){
        ((int**)ptr[0])[i] = malloc(b*sizeof(int));
    }



    return 0;
}





#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int a, b;
    printf("a(rows)? b(cols)?: ");
    scanf("%d %d", &a, &b);

    void ***ptr = malloc(3 * sizeof(void **));  // [0]=int**, [1]=double**, [2]=char**

    // [0] 정수 배열
    ptr[0] = malloc(a * sizeof(void *));
    for (int i = 0; i < a; i++) {
        ((int **)ptr[0])[i] = malloc(b * sizeof(int));
        for (int j = 0; j < b; j++) {
            ((int **)ptr[0])[i][j] = i * 10 + j;
        }
    }

    // [1] 소수 배열
    ptr[1] = malloc(a * sizeof(void *));
    for (int i = 0; i < a; i++) {
        ((double **)ptr[1])[i] = malloc(b * sizeof(double));
        for (int j = 0; j < b; j++) {
            ((double **)ptr[1])[i][j] = i + j / 10.0;
        }
    }

    // [2] 문자열 배열
    ptr[2] = malloc(a * sizeof(void *));
    for (int i = 0; i < a; i++) {
        ((char **)ptr[2])[i] = malloc((b + 1) * sizeof(char));
        for (int j = 0; j < b; j++) {
            ((char **)ptr[2])[i][j] = 'A' + (j % 26);
        }
        ((char **)ptr[2])[i][b] = '\0';  // 문자열 끝
    }

    // 출력
    printf("\n[정수 배열]\n");
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            printf("%3d ", ((int **)ptr[0])[i][j]);
        }
        printf("\n");
    }

    printf("\n[소수 배열]\n");
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            printf("%4.1f ", ((double **)ptr[1])[i][j]);
        }
        printf("\n");
    }

    printf("\n[문자열 배열]\n");
    for (int i = 0; i < a; i++) {
        printf("%s\n", ((char **)ptr[2])[i]);
    }

    // 해제
    for (int i = 0; i < a; i++) {
        free(((int **)ptr[0])[i]);
        free(((double **)ptr[1])[i]);
        free(((char **)ptr[2])[i]);
    }
    free(ptr[0]);
    free(ptr[1]);
    free(ptr[2]);
    free(ptr);

    return 0;
}
