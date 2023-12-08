#include <stdio.h>
#include "combat.h"
#include "game.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>
#pragma warning(disable:4996)


#define MAX_USER_NUM 4


int main() 
{
	int shmid;
	key_t key;
	ShMEM* shmem; //�����޸� ���(������, ���� �� ��ġ, ��Ƽ, ����2������ ü��)
	
	key = ftok("/home/g_202211077/Teamproject/Boss", 211);
	shmid = shmget(key, 1024, IPC_CREAT | 0666);
	if (shmid == -1) {
		perror("shmget");
		exit(1);
	}

	shmem = (ShMEM*)shmat(shmid, NULL, 0);

	shmem->User_num = 1;

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

	shmem->Host_HP = player->HP;

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

