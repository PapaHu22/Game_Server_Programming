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

// �÷��̾��� ���� ��ġ
int playerRow = 1;
int playerCol = 1;

void alarmHandler(int signo) {
    printf("�ð��ȿ� Ż���� ���Ͽ����ϴ�. ���� ����\n");
    exit(0);
}

// �̷θ� ����ϴ� �Լ�
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

// �÷��̾� �̵� �Լ�
void movePlayer(int newRow, int newCol) {
    // �̵��Ϸ��� ��ġ�� ���� �ƴ϶�� �̵�
    if (maze[newRow][newCol] != '#') {
        maze[playerRow][playerCol] = ' '; // ���� ��ġ�� ���
        playerRow = newRow;
        playerCol = newCol;
        maze[playerRow][playerCol] = 'P'; // ���ο� ��ġ�� �÷��̾� ǥ��
    }
}

int main() {
    ShMEM* shmem = shm_get();
    char move;

    signal(SIGALRM, alarmHandler);

    alarm(60);

    do {
        printMaze();
        printf("\n60�� �ȿ��ⱸ(E)�� ã�� �̷θ� Ż���ϼ���.\n");
        printf("�̵��Ϸ��� ������ �����ϼ��� (w: ��, s: �Ʒ�, a: ����, d: ������): ");

        move = getchar(); // Ű �Է��� ����
        while (getchar() != '\n') {}

        // �������� �����ϸ� ���� ����
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
                printf("������ �����մϴ�.\n");
                break;
            default :
                printf("Ű�� �߸� �Է��߽��ϴ�. �ٽ� �Է��ϼ���.");
                Sleep(1);
                break;
        }

        if (playerRow == 1 && playerCol == 19) {
            printMaze();
            printf("�������� �����߽��ϴ�!\n");
            shmem->party.Party_Coin += 100;
            break;
        }

    } while (move != 'q');
    printf("��");

    return 0;
}