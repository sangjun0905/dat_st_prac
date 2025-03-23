#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>




// 포인터 배열    -> 2차원
// 포인터 배열
// 배열 포인터    -> // int (*ptr)[5] = malloc(sizeof(int[5]));

int main(){
    int a,b,c;
    printf("a? b? c?: ");
    scanf("%d %d %d", &a, &b, &c);

    
    void ***ptr = malloc(3*sizeof(void**));    //void **ptr[3]; //ptr[1], ptr[2], ptr[3]
    
    int i = 0; // i는 만드는 자료형별 배열의 넘버링 i=0 : 정수 배열, i=1: 소수 배열, i=2 : 문자열 
    
    for(int j=0; j<a; j++){
        ptr[i] = malloc(a*sizeof(int*));
        ptr[i][j] = malloc(b * sizeof(int));
        int *n = malloc(b*sizeof(int));
        
        for(int k=0;k<b;k++){
            
            ptr[i][j][k] = n[k];
        }
    }

   
    return 0;
}