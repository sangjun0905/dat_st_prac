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

    //미로 원본을 저장하기 위한 메모리 할당
    for (int i=0;i<totalRow;i++) {
        miro[i] = malloc(sizeof(char) * (totalCol+2));  
        fgets(miro[i], totalCol+3, fp); 

    }
    
    int boxRow = totalRow / 2; //세로 칸의 개수 = (totalRow - 1) / 2
    int boxCol = totalCol / 2; //가로로 칸의 개수 = (totalCol - 1) / 2

    char **simpledMaze = malloc(sizeof(char*) * boxRow);

    for(int i=0;i<boxRow;i++){
        simpledMaze[i] = malloc(sizeof(char) * boxCol);
    }

    simpleMaze(miro, totalRow, totalCol, simpledMaze);

    // printf("미로를 칸으로 표현, 칸의 형태에 따라 알파벳 타입 설정:\n");
    // for (int i=0;i<boxRow;i++) {
    //     for (int j=0;j<boxCol;j++) {
    //         printf("%c", simpledMaze[i][j]);
    //     }
    //     printf("\n");
    // }
    

    drawMaze(simpledMaze, boxRow, boxCol);

    for (int i=0;i<totalRow;i++) {
        free(miro[i]);
    }
    free(miro);

    for (int i=0;i<boxRow;i++) {
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
            int down  = (miro[2*i+2][2*j+1] == '-');
            int right = (miro[2*i+1][2*j+2] == '|');
            
            // 1. 아래와 오른쪽 모두 뚫린 모양 = ‘a’ 로 저장
            // 2. 아래만 막히고 오른쪽은 뚫린 모양 = ‘b’ 로 저장
            // 3. 오른쪽이 막힌 모양 = ‘c’ 로 저장
            // 4. 아래와 오른쪽 모두 막힌 모양 = ‘d’ 로 저장

            if (!down && !right){
                simpledMaze[i][j] = 'a';
            } else if (down && !right){
                simpledMaze[i][j] = 'b';
            } else if (!down && right){
                simpledMaze[i][j] = 'c';
            } else{
                simpledMaze[i][j] = 'd';
            }
        }
    }

}

void drawMaze(char **simpledMaze, int boxRow, int boxCol) {
    int newRow = 2 * boxRow + 1;
    int newCol = 2 * boxCol + 1;

    char **reDrawnMaze = malloc(sizeof(char*) * newRow);
    for (int i=0;i<newRow;i++) {
        reDrawnMaze[i] = malloc(sizeof(char) * (newCol+1));
        for (int j=0; j<newCol;j++) {
            reDrawnMaze[i][j] = ' ';
        }
        reDrawnMaze[i][newCol] = '\0';
    }

    for (int i=0;i<boxRow;i++) {
        for (int j=0;j<boxCol;j++) {

            char tempBox = simpledMaze[i][j];

            // 모퉁이 부분
            reDrawnMaze[2*i][2*j] = '-';
            reDrawnMaze[2*i+1][2*j+1] = '-';
            

            // 길
            reDrawnMaze[2*i+1][2*j+1] = ' ';


            
            // 왼쪽 벽: 첫 줄이거나 왼쪽 칸의 오른쪽 벽이 막혀 있는 경우
            if (j==0 || simpledMaze[i][j-1]=='c' || simpledMaze[i][j-1]=='d') {
                reDrawnMaze[2*i+1][2*j] = '|';
            }

            // 위쪽 벽: 첫 줄이거나 위쪽 칸의 아래쪽 벽이 막혀 있는 경우
            if (i==0|| simpledMaze[i-1][j]=='b' || simpledMaze[i-1][j]=='d') {
                reDrawnMaze[2*i][2*j+1] = '-';
            }

            // 오른쪽 벽 (현재 칸 기준)
            if (tempBox=='c' || tempBox=='d') {
                reDrawnMaze[2*i+1][2*j+2] = '|';
            }

            // 아래쪽 벽 (현재 칸칸 기준)
            if (tempBox=='b' || tempBox=='d') {
                reDrawnMaze[2*i+2][2*j+1] = '-';
            }


            // 마지막 행과 마지막 열 구현현
            if (j==boxCol-1){
                reDrawnMaze[2*i][2*j+2] = '|';
            }
            if (i==boxRow-1){
                reDrawnMaze[2*i+2][2*j] = '-';
            }

            for (int i = 0; i < newRow; i += 2) {
                for (int j = 0; j < newCol; j += 2) {
            
                    if (((j + 1 < newCol && reDrawnMaze[i][j + 1] == '-') ||
                         (j - 1 >= 0     && reDrawnMaze[i][j - 1] == '-')) &&
                        ((i + 1 < newRow && reDrawnMaze[i + 1][j] == '|') ||
                         (i - 1 >= 0     && reDrawnMaze[i - 1][j] == '|'))) {
            
                        reDrawnMaze[i][j] = '+';  // 양쪽 다 있으면 +
            
                    } else if ((j + 1 < newCol && reDrawnMaze[i][j + 1] == '-') ||
                               (j - 1 >= 0     && reDrawnMaze[i][j - 1] == '-')) {
            
                        reDrawnMaze[i][j] = '-';  // 가로 벽만 있으면 -
            
                    } else if ((i + 1 < newRow && reDrawnMaze[i + 1][j] == '|') ||
                               (i - 1 >= 0     && reDrawnMaze[i - 1][j] == '|')) {
            
                        reDrawnMaze[i][j] = '|';  // 세로 벽만 있으면 |
            
                    } else {
                        reDrawnMaze[i][j] = ' ';  // 아무것도 없으면 공백
                    }
                }
            }
            
            for (int i = 0; i < newRow; i += 2) {
                for (int j = 0; j < newCol; j += 2) {
                    int wallCount = 0;
            
                    if (j + 1 < newCol && reDrawnMaze[i][j + 1] == '-') wallCount++;  // 오른쪽
                    if (j - 1 >= 0     && reDrawnMaze[i][j - 1] == '-') wallCount++;  // 왼쪽
                    if (i + 1 < newRow && reDrawnMaze[i + 1][j] == '|') wallCount++;  // 아래
                    if (i - 1 >= 0     && reDrawnMaze[i - 1][j] == '|') wallCount++;  // 위
            
                    if (wallCount == 1) {
                        reDrawnMaze[i][j] = '+';  // 오직 하나의 벽만 있을 때 +
                    }
                }
            }

            
        }
    }


    printf("\n저장한 미로 재출력:\n");
    for (int i=0;i<newRow;i++) {
        printf("%s\n", reDrawnMaze[i]);
    }



    for(int i=0;i<newRow;i++){
        free(reDrawnMaze[i]);
    }
    free(reDrawnMaze);
    
    return 0;
}
