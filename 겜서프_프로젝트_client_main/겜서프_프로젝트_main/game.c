// game.c

#include <stdio.h>
#include <stdbool.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include "game.h"

//line ���� ����
void draw_line() {
    for (int i = 0; i < MAP_WIDTH; i++) {
        printf("-");
    }
    printf("\n");
}
//�� ������ִ� ��
void draw_map(char map[MAP_HEIGHT][MAP_WIDTH]) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            printf("%c", map[y][x]);
        }
        printf("\n");
    }
}

//������
void draw_move(char input, char map[MAP_HEIGHT][MAP_WIDTH]) {
    ShMEM* shmem = shm_get();
    int new_x = shmem->party.x;
    int new_y = shmem->party.y;

    switch (input) {
    case 'w': new_y--; break;
    case 's': new_y++; break;
    case 'a': new_x--; break;
    case 'd': new_x++; break;
    }

    if (new_x < 0 || new_x >= MAP_WIDTH || new_y < 0 || new_y >= MAP_HEIGHT) {
        return;
    }

    if (new_x == shmem->monster.x && new_y == shmem->monster.y) {
        return;
    }

    map[shmem->party.y][shmem->party.x] = ' '; // ���� �÷��̾� ��ġ �����
    sleep(2);
    map[shmem->party.y][shmem->party.x] = PLAYER_ICON; // �� ��ġ�� �÷��̾� ǥ��
}

void initialize_map(char map[MAP_HEIGHT][MAP_WIDTH]) {
    ShMEM* shmem = shm_get();
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map[y][x] = ' ';
        }
    }
    shmem->party.x = 0;
    shmem->party.y = MAP_HEIGHT / 2;
    map[shmem->party.y][shmem->party.x] = PLAYER_ICON;
}

void alarmHandler(int signo) {
    printf("�ð��ȿ� Ż���� ���Ͽ����ϴ�. ���� ����\n");
    exit(0);
}

void printMaze(int* playerRow, int* playerCol, char maze[ROWS][COLS]) {
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
void movePlayer(int newRow, int newCol, int* playerRow, int* playerCol, char maze[ROWS][COLS]) {
    // �̵��Ϸ��� ��ġ�� ���� �ƴ϶�� �̵�
    if (maze[newRow][newCol] != '#') {
        maze[*playerRow][*playerCol] = ' '; // ���� ��ġ�� ���
        *playerRow = newRow;
        *playerCol = newCol;
        maze[*playerRow][*playerCol] = 'P'; // ���ο� ��ġ�� �÷��̾� ǥ��
    }
}



void ClearLineFromReadBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void field_map(Player* player, int you) {
    ShMEM* shmem = shm_get();
    char map[MAP_HEIGHT][MAP_WIDTH];
    shmem->monster.x = 10; //{ 10, 15, 100, 15, MONSTER_ART }; // ���� �ʱ� ����
    shmem->monster.y = 15;
    shmem->monster.Monster_HP = 100;
    shmem->monster.Monster_OP = 15;
    shmem->monster.ascii_art[0] = MONSTER_ART;
    bool inCombat = false; // ���� ���� �÷���

    initialize_map(map);
    map[shmem->monster.y][shmem->monster.x] = MONSTER_ICON; // ���� ��ġ ǥ��

    while (1) {
        system("clear"); // ȭ�� Ŭ����
        printf("���� ��ġ: �ʵ� ��\n"); // �� �̸� ���
        draw_line();
        draw_map(map); // �� ���
        draw_line();

        if (!inCombat) {
            printf("��Ƽ���� ��Ƽ�� �̵� ���Դϴ�.\n");
        }

        // ���� ���� ����
        bool isNearMonster = abs(shmem->party.x - shmem->monster.x) <= 1 && abs(shmem->party.y - shmem->monster.y) <= 1;

        if (!inCombat && isNearMonster) {
            inCombat = true;
            printf("%s\n", MONSTER_ART); // ���� �ƽ�Ű ��Ʈ ���
            printf("Your Health: %d, Monster's Health: %d\n", player->HP, shmem->monster.Monster_HP);
            start_combat(player, you); // ���� ����
            if (shmem->Host_HP <= 0) {
                break;
            }
            if (player->HP <= 0) {
                break;
            }
            if (shmem->monster.Monster_HP <= 0) {
                map[shmem->monster.x][shmem->monster.y] = ' '; // ���� ��ġ �����
                shmem->monster.y = -1;
                shmem->monster.x = -1;
                inCombat = false; // ���� ���� ����
            }
        }
        else {
            switch (shmem->input) {
            case 'w': // ���� �̵�
            case 'a': // �������� �̵�
            case 's': // �Ʒ��� �̵�
            case 'd': // ���������� �̵�
                draw_move(shmem->input, map);
                break;
            case 'q': // ���� ����
                return 0;
            default:
                printf("���ۺҰ�!\n");
            }
        }
        if (shmem->monster.Monster_HP <= 0) {
            return;
        }
    }
}

void boss_room(Player* player, int you) {
    ShMEM* shmem = shm_get();
    char map[MAP_HEIGHT][MAP_WIDTH];
    shmem->boss_x = 15;
    shmem->boss_y = 15;
    shmem->boss_monster.Monster_OP = 15;
    shmem->boss_monster.Monster_HP = 100;
    shmem->boss_monster2.Monster_OP = 10;
    shmem->boss_monster2.Monster_HP = 100;
    shmem->boss_monster3.Monster_OP = 25;
    shmem->boss_monster3.Monster_HP = 500;

    char input;
    bool inCombat = false; // ���� ���� �÷���

    initialize_map(map);
    map[shmem->boss_y][shmem->boss_x] = MONSTER_ICON; // ���� ��ġ ǥ��

    while (1) {
        system("clear"); // ȭ�� Ŭ����
        printf("���� ��ġ: ���� ��\n"); // �� �̸� ���
        draw_line();
        draw_map(map); // �� ���
        draw_line();

        if (!inCombat) {
            printf("��Ƽ���� ��Ƽ�� �̵� ���Դϴ�.\n");
        }

        // ���� ���� ����
        bool isNearMonster = abs(shmem->party.x - shmem->boss_x) <= 1 && abs(shmem->party.y - shmem->boss_y) <= 1;

        if (!inCombat && isNearMonster) {
            inCombat = true;
            printf("Boss Phase1...\n");
            boss_combat(player, you); // ���� ����
            if (shmem->Host_HP <= 0) {
                break;
            }
            if (shmem->boss_monster.Monster_HP <= 0 && player->HP > 0) {
                printf("Boss Phase2...\n");
                boss_combat2(player, you);
                if (shmem->Host_HP <= 0) {
                    break;
                }
                if (player->HP > 0) {
                    sleep(1);
                    printf("Boss Phase3...\n");
                    boss_combat3(player, you);
                    if (shmem->Host_HP <= 0) {
                        break;
                    }
                    if (shmem->boss_monster3.Monster_HP <= 0 && player->HP > 0) {
                        inCombat = false;
                    }
                }

            }
            if (shmem->boss_monster3.Monster_HP <= 0) {
                map[shmem->boss_x][shmem->boss_y] = ' '; // ���� ��ġ �����
                shmem->boss_x = -1;
                shmem->boss_y = -1;
                inCombat = false; // ���� ���� ����
            }
        }
        else {
            switch (shmem->input) {
            case 'w': // ���� �̵�
            case 'a': // �������� �̵�
            case 's': // �Ʒ��� �̵�
            case 'd': // ���������� �̵�
                draw_move(shmem->input, map);
                break;
            //case 'q': // ���� ����
               // return 0;
            default:
                printf("���ۺҰ�!\n");
            }
        }
        if (shmem->boss_monster3.Monster_HP <= 0) {
            return 0;
        }
    }

    system("clear");

}

ShMEM* shm_get() {
    int shmid;
    key_t key;
    ShMEM* shmem;

    key = ftok("/home/g_202211077/Teamproject", 211);
    shmid = shmget(key, 1024, 0);
    if (shmid == -1) {
        perror("shmget");
        exit(1);

    }
    shmem = (ShMEM*)shmat(shmid, NULL, 0);
    return shmem;

}