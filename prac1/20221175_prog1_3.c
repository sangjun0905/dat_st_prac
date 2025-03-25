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

    printf("미로를 칸으로 표현, 칸의 형태에 따라 알파벳 타입 설정:\n");
    for (int i=0;i<boxRow;i++) {
        for (int j=0;j<boxCol;j++) {
            printf("%c", simpledMaze[i][j]);
        }
        printf("\n");
    }
    

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
            int y = 2 * i;
            int x = 2 * j;

            char tempBox = simpledMaze[i][j];

            // 모퉁이 부분
            reDrawnMaze[y][x] = '+';
            reDrawnMaze[y][x+2] = '+';
            reDrawnMaze[y+2][x] = '+';
            reDrawnMaze[y+2][x+2] = '+';

            // 길
            reDrawnMaze[y+1][x+1] = ' ';

            // 왼쪽 벽: 첫 줄이거나 왼쪽 칸의 오른쪽 벽이 막혀 있는 경우
            if (j==0 || simpledMaze[i][j-1]=='c' || simpledMaze[i][j-1]=='d') {
                reDrawnMaze[y+1][x] = '|';
            }

            // 위쪽 벽: 첫 줄이거나 위쪽 칸의 아래쪽 벽이 막혀 있는 경우
            if (i==0|| simpledMaze[i-1][j]=='b' || simpledMaze[i-1][j]=='d') {
                reDrawnMaze[y][x+1] = '-';
            }

            // 오른쪽 벽 (현재 칸 기준)
            if (tempBox=='c' || tempBox=='d') {
                reDrawnMaze[y+1][x+2] = '|';
            }

            // 아래쪽 벽 (현재 칸칸 기준)
            if (tempBox=='b' || tempBox=='d') {
                reDrawnMaze[y+2][x+1] = '-';
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
