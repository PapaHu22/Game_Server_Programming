#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "game.h"


#define ROWS 10
#define COLS 20

// �̷� �迭
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



void alarmHandler(int signo) {
    printf("�ð��ȿ� Ż���� ���Ͽ����ϴ�. ���� ����\n");
    exit(0);
}

// �̷θ� ����ϴ� �Լ�
void printMaze(int* playerRow, int* playerCol) {
    system("clear");
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

// �÷��̾� �̵� �Լ�
void movePlayer(int newRow, int newCol, int* playerRow, int* playerCol) {
    // �̵��Ϸ��� ��ġ�� ���� �ƴ϶�� �̵�
    if (maze[newRow][newCol] != '#') {
        maze[*playerRow][*playerCol] = ' '; // ���� ��ġ�� ���
        *playerRow = newRow;
        *playerCol = newCol;
        maze[*playerRow][*playerCol] = 'P'; // ���ο� ��ġ�� �÷��̾� ǥ��
    }
}

int main() {
    ShMEM* shmem = shm_get();
    char move;

    int playerRow = 8;
    int playerCol = 1;

    signal(SIGALRM, alarmHandler);

    alarm(60);

    do {
        printMaze(&playerRow, &playerCol);
        printf("\n60�� �ȿ� �ⱸ(E)�� ã�� �̷θ� Ż���ϼ���.\n");
        printf("�̵��Ϸ��� ������ �����ϼ��� (w: ��, s: �Ʒ�, a: ����, d: ������): ");

        move = getchar(); // Ű �Է��� ����
        while (getchar() != '\n') {}

        // �������� �����ϸ� ���� ����
        switch (move)
        {
        case 'w':
            movePlayer(playerRow - 1, playerCol, &playerRow, &playerCol);
            break;
        case 's':
            movePlayer(playerRow + 1, playerCol, &playerRow, &playerCol);
            break;
        case 'a':
            movePlayer(playerRow, playerCol - 1, &playerRow, &playerCol);
            break;
        case 'd':
            movePlayer(playerRow, playerCol + 1, &playerRow, &playerCol);
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
            printMaze(&playerRow, &playerCol);
            printf("�������� �����߽��ϴ�!\n");
            shmem->party.Party_Coin += 100;
            break;
        }

    } while (move != 'q');

    return 0;
}