#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("maze1-1.txt", "r");
    if (file == NULL) {
        perror("파일 열기 실패");
        return 1;
    }

    int rows, cols;
    fscanf(file, "%d %d\n", &rows, &cols);  // 첫 줄: 규격 정보

    // 미로 저장용 이차원 배열 (문자열 저장)
    char **maze = malloc(sizeof(char*) * rows);
    for (int i = 0; i < rows; i++) {
        maze[i] = malloc(sizeof(char) * (cols + 2)); // '\n' + '\0' 대비
        fgets(maze[i], cols + 2, file); // 한 줄씩 읽기
    }

    // 출력 테스트
    printf("미로 크기: %d행 %d열\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        printf("%s", maze[i]);
    }

    // 메모리 해제
    for (int i = 0; i < rows; i++) {
        free(maze[i]);
    }
    free(maze);

    fclose(file);
    return 0;
}