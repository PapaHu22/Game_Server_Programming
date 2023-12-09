#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "game.h"

#define ROWS 10
#define COLS 20

// 미로 배열
char maze[ROWS][COLS] = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', 'P', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', 'E'},
    {'#', ' ', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#'},
    {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
    {'#', '#', '#', ' ', '#', '#', '#', '#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#'},
    {'#', ' ', '#', ' ', ' ', ' ', '#', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', ' ', '#', ' ', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#'},
    {'#', ' ', '#', ' ', '#', ' ', '#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', '#', ' ', '#', '#'},
    {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

// 플레이어의 현재 위치
int playerRow = 1;
int playerCol = 1;

void alarmHandler(int signo) {
    printf("시간안에 탈출을 못하였습니다. 강제 전이\n");
    exit(0);
}

// 미로를 출력하는 함수
void printMaze() {
    system("cls");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (i >= playerRow - 1 && i <= playerRow + 1 && j >= playerCol - 1 && j <= playerCol + 1)
            {
                printf("%c ", maze[i][j]);
            }
            else
            {
                printf("  ");
            }
        }
        printf("\n");
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
}

// 플레이어 이동 함수
void movePlayer(int newRow, int newCol) {
    // 이동하려는 위치가 벽이 아니라면 이동
    if (maze[newRow][newCol] != '#') {
        maze[playerRow][playerCol] = ' '; // 이전 위치를 비움
        playerRow = newRow;
        playerCol = newCol;
        maze[playerRow][playerCol] = 'P'; // 새로운 위치에 플레이어 표시
    }
}

int main() {
    ShMEM* shmem = shm_get();
    char move;

    signal(SIGALRM, alarmHandler);

    alarm(60);

    do {
        printMaze();
        printf("\n60초 안에출구(E)를 찾아 미로를 탈출하세요.\n");
        printf("이동하려는 방향을 선택하세요 (w: 위, s: 아래, a: 왼쪽, d: 오른쪽): ");

        move = getchar(); // 키 입력을 받음
        while (getchar() != '\n') {}

        // 목적지에 도달하면 게임 종료
        switch (move) 
        {
            case 'w':
                movePlayer(playerRow - 1, playerCol);
                break;
            case 's':
                movePlayer(playerRow + 1, playerCol);
                break;
            case 'a':
                movePlayer(playerRow, playerCol - 1);
                break;
            case 'd':
                movePlayer(playerRow, playerCol + 1);
                break;
            case 'q':
                printf("게임을 종료합니다.\n");
                break;
            default :
                printf("키를 잘못 입력했습니다. 다시 입력하세요.");
                Sleep(1);
                break;
        }

        if (playerRow == 1 && playerCol == 19) {
            printMaze();
            printf("목적지에 도착했습니다!\n");
            shmem->party.Party_Coin += 100;
            break;
        }

    } while (move != 'q');
    printf("끝");

    return 0;
}