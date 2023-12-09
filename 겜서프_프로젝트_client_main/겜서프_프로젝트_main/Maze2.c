#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "game.h"


#define ROWS 10
#define COLS 20

// �̷� �迭


// �̷θ� ����ϴ� �Լ�


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
        printf("\n60�� �ȿ� �ⱸ(E)�� ã�� �̷θ� Ż���ϼ���.\n");
        printf("�̵��Ϸ��� ������ �����ϼ��� (w: ��, s: �Ʒ�, a: ����, d: ������): ");

        move = getchar(); // Ű �Է��� ����
        while (getchar() != '\n') {}

        // �������� �����ϸ� ���� ����
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
            printf("������ �����մϴ�.\n");
            break;
        default:
            printf("Ű�� �߸� �Է��߽��ϴ�. �ٽ� �Է��ϼ���.");
            sleep(1);
            break;
        }

        if (playerRow == 9 && playerCol == 3) {
            printMaze(&playerRow, &playerCol, maze);
            printf("�������� �����߽��ϴ�!\n");
            shmem->party.Party_Coin += 100;
            break;
        }

    } while (move != 'q');

    return 0;
}