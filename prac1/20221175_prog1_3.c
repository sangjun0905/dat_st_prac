#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("maze1-1.txt", "r");

    int totalRow, totalCol; 
    fscanf(fp, "%d %d\n", &totalCol, &totalRow);  
    

    char **miro = malloc(sizeof(char*) * (2*totalRow));
    for (int i = 0; i < 2*totalRow; i++) {
        miro[i] = malloc(sizeof(char) * (totalCol + 1));
        fgets(miro[i], totalCol + 2, fp); 
    }

    // 출력 테스트
    printf("미로 크기: %d행 %d열\n", totalRow, totalCol);
    for (int i = 0; i < 2*totalRow; i++) {
        printf("%s", miro[i]);
    }

    // 메모리 해제
    for (int i = 0; i < 2*totalRow; i++) {
        free(miro[i]);
    }
    free(miro);

    fclose(fp);

    ("%d", totalRow);
    return 0;
}