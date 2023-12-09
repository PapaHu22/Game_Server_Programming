#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "game.h"


#define ROWS 10
#define COLS 20

// 미로 배열


// 미로를 출력하는 함수


int maze2() {
    ShMEM* shmem = shm_get();
    char move;

    int playerRow = 8;
    int playerCol = 1;
    char maze[ROWS][COLS] = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', '#', '#', ' ', '#', ' ', '#', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', ' ', '#', '#', '#'},
    {'#', ' ', '#', ' ', ' ', ' ', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#'},
    {'#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', '#', '#', ' ', '#', ' ', ' ', '#'},
    {'#', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', '#', ' ', '#', ' ', '#', ' ', ' ', '#', ' ', '#', '#'},
    {'#', 'P', '#', ' ', '#', ' ', '#', ' ', ' ', '#', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', '#'},
    {'#', '#', '#', 'E', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    };

    signal(SIGALRM, alarmHandler);


    alarm(60);

    do {
        printMaze(&playerRow, &playerCol, maze);
        printf("\n60초 안에 출구(E)를 찾아 미로를 탈출하세요.\n");
        printf("이동하려는 방향을 선택하세요 (w: 위, s: 아래, a: 왼쪽, d: 오른쪽): ");

        move = getchar(); // 키 입력을 받음
        while (getchar() != '\n') {}

        // 목적지에 도달하면 게임 종료
        switch (move)
        {
        case 'w':
            movePlayer(playerRow - 1, playerCol, &playerRow, &playerCol, maze);
            break;
        case 's':
            movePlayer(playerRow + 1, playerCol, &playerRow, &playerCol, maze);
            break;
        case 'a':
            movePlayer(playerRow, playerCol - 1, &playerRow, &playerCol, maze);
            break;
        case 'd':
            movePlayer(playerRow, playerCol + 1, &playerRow, &playerCol, maze);
            break;
        case 'q':
            printf("게임을 종료합니다.\n");
            break;
        default:
            printf("키를 잘못 입력했습니다. 다시 입력하세요.");
            sleep(1);
            break;
        }

        if (playerRow == 9 && playerCol == 3) {
            printMaze(&playerRow, &playerCol, maze);
            shmem->party.Party_Coin += 100;
            printf("목적지에 도착했습니다! 미로에서 보물을 찾았다! 현재 파티 코인 : \n", shmem->party.Party_Coin);
            break;
        }

    } while (move != 'q');

    return 0;
}