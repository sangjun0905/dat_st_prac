#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

void simpleMaze(char **miro, int totalRow, int totalCol, char **simpledMaze);
void drawMaze(char **simpledMaze, int boxRow, int boxCol);

int main(){
    int totalRow, totalCol;
    FILE *fp = fopen("maze1-1.txt", "r");

    fscanf(fp, "%d %d\n", &totalCol, &totalRow);


    char **miro = malloc(sizeof(char*) * totalRow);

    //미로 원본을 저장하기 위한 메모리 할당당
    for (int i = 0; i < totalRow; i++) {
        miro[i] = malloc(sizeof(char) * (totalCol + 2));  
        fgets(miro[i], totalCol + 3, fp); 

    }
    
    int boxRow = totalRow / 2; //세로 칸의 개수 = (totalRow - 1) / 2
    int boxCol = totalCol / 2; //가로로 칸의 개수 = (totalCol - 1) / 2

    char **simpledMaze = malloc(sizeof(char*) * boxRow);

    for(int i=0;i<boxRow;i++){
        simpledMaze[i] = malloc(sizeof(char) * boxCol);
    }

    simpleMaze(miro, totalRow, totalCol, simpledMaze);

    printf("압축 미로:\n");
    for (int i = 0; i < boxRow; i++) {
        for (int j = 0; j < boxCol; j++) {
            printf("%c", simpledMaze[i][j]);
        }
        printf("\n");
    }
    

    drawMaze(simpledMaze, boxRow, boxCol);

    for (int i = 0; i < totalRow; i++) {
        free(miro[i]);
    }
    free(miro);

    for (int i = 0; i < boxRow; i++) {
        free(simpledMaze[i]);
    }
    free(simpledMaze);

    fclose(fp);
    return 0;


}

void simpleMaze(char **miro, int totalRow, int totalCol, char **simpledMaze) {
    int boxRow = totalRow / 2;
    int boxCol = totalCol / 2;

    for (int i = 0; i < boxRow; i++) {
        for (int j = 0; j < boxCol; j++) {
            int down  = (miro[2*i + 2][2*j + 1] == '-');
            int right = (miro[2*i + 1][2*j + 2] == '|');

            if (!down && !right)
                simpledMaze[i][j] = 'a';
            else if (down && !right)
                simpledMaze[i][j] = 'b';
            else if (!down && right)
                simpledMaze[i][j] = 'c';
            else
                simpledMaze[i][j] = 'd';
        }
    }

}

void drawMaze(char **simpledMaze, int boxRow, int boxCol) {
    int outRow = 2 * boxRow + 1;
    int outCol = 2 * boxCol + 1;

    char **output = malloc(sizeof(char*) * outRow);
    for (int i = 0; i < outRow; i++) {
        output[i] = malloc(sizeof(char) * (outCol + 1));
        for (int j = 0; j < outCol; j++) {
            output[i][j] = ' ';
        }
        output[i][outCol] = '\0';
    }

    for (int i = 0; i < boxRow; i++) {
        for (int j = 0; j < boxCol; j++) {
            int y = 2 * i;
            int x = 2 * j;

            char cell = simpledMaze[i][j];

            // 꼭짓점
            output[y][x] = '+';
            output[y][x+2] = '+';
            output[y+2][x] = '+';
            output[y+2][x+2] = '+';

            // 내부 공간
            output[y+1][x+1] = ' ';

            // 왼쪽 벽 (첫 열이거나 왼쪽 셀의 오른쪽 벽이 막혀 있으면)
            if (j == 0 || simpledMaze[i][j-1] == 'c' || simpledMaze[i][j-1] == 'd') {
                output[y+1][x] = '|';
            }

            // 위쪽 벽 (첫 행이거나 윗 셀의 아래쪽 벽이 막혀 있으면)
            if (i == 0 || simpledMaze[i-1][j] == 'b' || simpledMaze[i-1][j] == 'd') {
                output[y][x+1] = '-';
            }

            // 오른쪽 벽 (현재 셀 기준)
            if (cell == 'c' || cell == 'd') {
                output[y+1][x+2] = '|';
            }

            // 아래쪽 벽 (현재 셀 기준)
            if (cell == 'b' || cell == 'd') {
                output[y+2][x+1] = '-';
            }
        }
    }

    // 출력
    printf("\n복원된 미로:\n");
    for (int i = 0; i < outRow; i++) {
        printf("%s\n", output[i]);
        free(output[i]);
    }
    free(output);
}
