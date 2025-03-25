#include <stdio.h>
#include <stdlib.h>

// 함수 원형 선언
void compressMaze(char **miro, int totalRow, int totalCol, char **compressedMaze);

int main() {
    int totalRow, totalCol;
    FILE *fp = fopen("maze1-1.txt", "r");

    fscanf(fp, "%d %d\n", &totalCol, &totalRow);

    // 미로 텍스트 데이터 저장
    char **miro = malloc(sizeof(char*) * totalRow);
    for (int i = 0; i < totalRow + 1; i++) {
        miro[i] = malloc(sizeof(char) * (totalCol + 1));
        fgets(miro[i], totalCol + 2, fp);
    }

    // 압축 미로 저장 공간
    char **compressedMaze = malloc(sizeof(char*) * totalRow/2);
    for (int i = 0; i < totalRow/2; i++) {
        compressedMaze[i] = malloc(sizeof(char) * totalCol/2);
    }

    compressMaze(miro, totalRow, totalCol, compressedMaze);

    // 출력 테스트

    int a,b;
    
    printf("압축 미로:\n");
    for (int i = 0; i < totalRow/2; i++) {
        for (int j = 0; j < totalCol/2; j++) {
            printf("%c", compressedMaze[i][j]);
        }
        printf("\n");
    }

    // 메모리 해제
    for (int i = 0; i < totalRow; i++) {
        free(miro[i]);
    }
    free(miro);

    for (int i = 0; i < totalRow; i++) {
        free(compressedMaze[i]);
    }
    free(compressedMaze);

    fclose(fp);
    return 0;
}


void compressMaze(char **miro, int totalRow, int totalCol, char **compressedMaze) {
    for (int i = 0; i < totalRow/2; i++) {
        for (int j = 0; j < totalCol/2; j++) {
            int down  = (miro[2*i + 2][2*j + 1] == '-');
            int right = (miro[2*i + 1][2*j + 2] == '|');

            if (!down && !right)
                compressedMaze[i][j] = 'a';
            else if (down && !right)
                compressedMaze[i][j] = 'b';
            else if (!down && right)
                compressedMaze[i][j] = 'c';
            else
                compressedMaze[i][j] = 'd';
        }
    }
}