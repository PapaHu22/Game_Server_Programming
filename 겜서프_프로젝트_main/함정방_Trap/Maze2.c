#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


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

// �÷��̾��� ���� ��ġ
int playerRow = 8;
int playerCol = 1;

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
    char move;

    do {
        printMaze();
        printf("\n�ⱸ(E)�� ã�� �̷θ� Ż���ϼ���.\n");
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
        default:
            printf("Ű�� �߸� �Է��߽��ϴ�. �ٽ� �Է��ϼ���.");
            Sleep(1000);
            break;
        }

        if (playerRow == 9 && playerCol == 3) {
            printMaze();
            printf("�������� �����߽��ϴ�!\n");
            break;
        }

    } while (move != 'q');

    return 0;
}