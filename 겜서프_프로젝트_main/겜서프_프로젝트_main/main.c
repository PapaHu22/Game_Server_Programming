#include <stdio.h>
#include "combat.h"
#include "game.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#pragma warning(disable:4996)


#define MAX_USER_NUM 4




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


int main() 
{
	int shmid;
	key_t key;
	ShMEM* shmem; //�����޸� ���(������, ���� �� ��ġ, ��Ƽ, ����2������ ü��)
	
	key = ftok("/home/g_202010951/project_space", 1);
	shmid = shmget(key, 1024, 0);
	if (shmid == -1) {
		perror("shmget");
		exit(1);
	}

	shmem = (ShMEM*)shmat(shmid, NULL, 0);

	Class Warrior; //����, ��
	Class SwordsMan; //�˻�, �ٵ�
	Class Priest; //������, ����
	Class Archer; // �ü�, ����

	Warrior.class_HP = 500;
	Warrior.class_OP = 50;
	
	SwordsMan.class_HP = 250;
	SwordsMan.class_OP = 70;

	Priest.class_HP = 200;
	Priest.class_OP = 30;

	Archer.class_HP = 150;
	Archer.class_OP = 100;


	shmem->User_num = 3;
	int you; // �����
	
	// �������� 
	if (shmem->User_num != 1 && shmem->User_num != 2 && shmem->User_num != 3 && shmem->User_num != 4) {
		shmem->User_num = 0;
	}

	//�÷��̾� ����
	++shmem->User_num;
	//���� �������� 4���� ���� ��� �������ϰ� �ϰ� ����
	if (shmem->User_num > MAX_USER_NUM) {
		shmem->User_num = 4;
		printf("�̹� ��Ƽ�� ��á���ϴ�.");
		return 1;
	}

	Player* player = (Player*)malloc(sizeof(Player));
	player->x = 0;
	player->y = MAP_HEIGHT;

	int select_class;

	//��������
	printf("������ �����ϼ���.\n");
	while (true) {
		printf("����(1), �ϻ���(2), ������(3), �ü�(4)\n");
		scanf("%d", &select_class);
		switch (select_class) {
		case 1:
			player->class = Warrior;
			player->HP = Warrior.class_HP;
			player->OP = Warrior.class_OP;
			break;
		case 2:
			player->class = SwordsMan;
			player->HP = SwordsMan.class_HP;
			player->OP = SwordsMan.class_OP;
			break;
		case 3:
			player->class = Priest;
			player->HP = Priest.class_HP;
			player->OP = Priest.class_OP;
			break;
		case 4:
			player->class = Archer;
			player->HP = Archer.class_HP;
			player->OP = Archer.class_OP;
			break;
		default:
			printf("�߸��� �Է��Դϴ�.");
		}
		ClearLineFromReadBuffer();
		if (select_class == 1 || select_class == 2 || select_class == 3 || select_class == 4) {
			break;
		}
	}

	system("cls");

	shmem->Cr_room++;
	do {
		if (shmem->Cr_room == 1 || shmem->Cr_room == 2) {
			field_map(player);
			printf("�ʵ���� Ŭ�����߽��ϴ�.");
			shmem->Cr_room++;
		}
		else if (shmem->Cr_room== 3) {
			trap(shmem->User_num);
			printf("�������� Ŭ�����߽��ϴ�.");
			shmem->Cr_room++;
		}
		else if(shmem->Cr_room == 4) {
			// ������
			printf("������ �̿�");
			shmem->Cr_room++;
		}
		else {
			//������
			printf("������ Ŭ�����߽��ϴ�.");
			shmem->Cr_room++;
		}
	} while (player->HP > 0 && shmem->Cr_room <= 5);

	free(player);
	return 0;
}

