#include <stdio.h>
#include <malloc.h>
#include <string.h>

int main(){
    int a,b,c;
    printf("a? b? c?: ");
    scanf("%d %d %d", &a, &b, &c);

    void ***ptr = malloc(3*sizeof(void **));

    
    ptr[0] = malloc(a*sizeof(void*));
    for(int i=0; i<a; i++){
        ptr[0][i] = malloc(b*sizeof(int));
    }

    int *num = malloc(b*sizeof(int));
    printf("정수를 입력하세요: ");

    for(int j=0; j<a; j++){
        for(int k=0; k<b; k++){
            scanf("%d", &((int **)ptr[0])[j][k]);
        }
    }

    for(int j=0; j<a; j++){
        for(int k=0; k<b; k++){
             printf("%d ", ((int **)ptr[0])[j][k]);
        }
        printf("\n");
    }




    ptr[1] = malloc(b*sizeof(void*));
    for(int i=0; i<b; i++){
        ptr[1][i] = malloc(c*sizeof(float));
    }

    float *flNum = malloc(c*sizeof(float));
    printf("소수를 입력하세요: ");

    for(int j=0; j<b; j++){
        for(int k=0; k<c; k++){
            scanf("%f", &((float **)ptr[1])[j][k]);
        }
    }

    //float array 출력
    for(int j=0; j<b; j++){
        for(int k=0; k<c; k++){
             printf("%f ", ((float **)ptr[1])[j][k]);
        }
        printf("\n");
    }





    ptr[2] = malloc(c*sizeof(void*));
    
    for(int i=0; i<c; i++){
        ptr[2][i] = (char**)malloc(a*sizeof(char*));
    }

    char *str = malloc(a*sizeof(char));
    for (int j = 0; j < c; j++) {
        for (int k = 0; k < a; k++) {
            ((char **)ptr[2][j])[k] = malloc(5 * sizeof(char));  
        }
    }
    printf("문자열을 입력하세요: ");

    for(int j=0; j<c; j++){
        for(int k=0; k<a; k++){
            scanf("%4s", ((char **)ptr[2][j])[k]);
        }
    }

    //string array 출력
    for(int j=0; j<c; j++){
        for(int k=0; k<a; k++){
             printf("%s ", ((char **)ptr[2][j])[k]);
        }
        printf("\n");
    }



    free(ptr);
    return 0;
}