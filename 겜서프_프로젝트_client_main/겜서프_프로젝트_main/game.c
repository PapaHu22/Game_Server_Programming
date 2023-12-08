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
void draw_move(char input, Player* player, char map[MAP_HEIGHT][MAP_WIDTH], Monster* monster) {
    int new_x = player->x;
    int new_y = player->y;

    switch (input) {
    case 'w': new_y--; break;
    case 's': new_y++; break;
    case 'a': new_x--; break;
    case 'd': new_x++; break;
    }

    if (new_x < 0 || new_x >= MAP_WIDTH || new_y < 0 || new_y >= MAP_HEIGHT) {
        return;
    }

    if (new_x == monster->x && new_y == monster->y) {
        return;
    }

    map[player->y][player->x] = ' '; // ���� �÷��̾� ��ġ �����
    player->x = new_x;
    player->y = new_y;
    map[player->y][player->x] = PLAYER_ICON; // �� ��ġ�� �÷��̾� ǥ��
}

void initialize_map(char map[MAP_HEIGHT][MAP_WIDTH], Player* player) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map[y][x] = ' ';
        }
    }
    player->x = 0;
    player->y = MAP_HEIGHT / 2;
    map[player->y][player->x] = PLAYER_ICON;
}





void ClearLineFromReadBuffer(void)
{
	while (getchar() != '\n');
}

void field_map(Player* player) {
	char map[MAP_HEIGHT][MAP_WIDTH];
	Monster monster = { 10, 15, 100, 15, MONSTER_ART }; // ���� �ʱ� ����
	char input;
	bool inCombat = false; // ���� ���� �÷���

	initialize_map(map, player);
	map[monster.y][monster.x] = MONSTER_ICON; // ���� ��ġ ǥ��

	while (1) {
		system("cls"); // ȭ�� Ŭ����
		printf("���� ��ġ: �� �̸�\n"); // �� �̸� ���
		draw_line();
		draw_map(map); // �� ���
		draw_line();

		if (!inCombat) {
			printf("�̵� WASD, Q ����: ");
			scanf_s(" %c", &input, 1);
		}

		// ���� ���� ����
		bool isNearMonster = abs(player->x - monster.x) <= 1 && abs(player->y - monster.y) <= 1;

		if (!inCombat && isNearMonster) {
			inCombat = true;
			printf("%s\n", MONSTER_ART); // ���� �ƽ�Ű ��Ʈ ���
			printf("Your Health: %d, Monster's Health: %d\n", player->HP, monster.Monster_HP);
			start_combat(player, &monster); // ���� ����
			if (monster.Monster_HP <= 0) {
				map[monster.y][monster.x] = ' '; // ���� ��ġ �����
				monster.y = -1;
				monster.x = -1;
				inCombat = false; // ���� ���� ����
			}
		}
		else {
			switch (input) {
			case 'w': // ���� �̵�
			case 'a': // �������� �̵�
			case 's': // �Ʒ��� �̵�
			case 'd': // ���������� �̵�
				draw_move(input, player, map, &monster);
				break;
			case 'q': // ���� ����
				return 0;
			default:
				printf("���ۺҰ�!\n");
			}
		}
	}
}

ShMEM* shm_get() {
    int shmid;
    key_t key;
    ShMEM* shmem;

    key = ftok("/home/g_202211077/Teamproject/Boss", 211);
    shmid = shmget(key, 1024, 0);
    if (shmid == -1) {
        perror("shmget");
        exit(1);

    }
    shmem = (ShMEM*)shmat(shmid, NULL, 0);
    return shmem;

}