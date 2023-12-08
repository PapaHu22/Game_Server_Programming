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
	shmem->Cr_room = 1;
	shmem->game_ready = false;
	shmem->field_ready = false;
	shmem->boos_ready = false;

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
	
	int you = shmem->User_num; // �����

	//�÷��̾� ����
	++shmem->User_num;
	//���� �������� 4���� ���� ��� �������ϰ� �ϰ� ����
	if (shmem->User_num > MAX_USER_NUM) {
		shmem->User_num = 4;
		printf("�̹� ��Ƽ�� ��á���ϴ�.");
		return 1;
	}

	Player* player = (Player*)malloc(sizeof(Player));

	shmem->party.x = 0;
	shmem->party.y = MAP_HEIGHT;

	shmem->Cr_room = 1;

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

	//ȭ�� �ʱ�ȭ
	int game_ready;
	int field_ready;
	printf("������ Ž���� �غ� �Ǿ����ϱ�?(1�� �Է½� ����)"); // ȣ��Ʈ �ڵ� ����
	scanf("%d", &game_ready);
	if (game_ready == 1) {
		printf("Ž���� �����մϴ�.");
		shmem->game_ready = true;
	}

	do {
		if (shmem->Cr_room == 1 || shmem->Cr_room == 2) {
			printf("�ʵ��%d ���Դϴ�. �����Ͻðڽ��ϱ�?(1�� ����� ����)", shmem->Cr_room);
			scanf("%d", &field_ready);
			if (field_ready == 1) {
				shmem->field_ready = true;
			}
			field_map(player, you);
			if (shmem->Host_HP >= 0) {
				printf("��Ƽ��(ȣ��Ʈ)�� ��Ÿ�̾�ƽ��ϴ�. ���� Ž�� ����");
			}
			printf("�ʵ���� Ŭ�����߽��ϴ�.");
			shmem->Cr_room++;
		}
		else if (shmem->Cr_room== 3) {
			printf("�����濡 �����Ͻðڽ��ϱ�?");
			trap(shmem->User_num);
			printf("�������� Ŭ�����߽��ϴ�.");
			if (shmem->Host_HP >= 0) {
				printf("��Ƽ��(ȣ��Ʈ)�� ��Ÿ�̾�ƽ��ϴ�. ���� Ž�� ����");
			}
			shmem->Cr_room++;
		}
		else if(shmem->Cr_room == 4) {
			// ������
			printf("������ �̿�");
			shmem->Cr_room++;
		}
		else {
			//������
			if (shmem->Host_HP >= 0) {
				printf("��Ƽ��(ȣ��Ʈ)�� ��Ÿ�̾�ƽ��ϴ�. ���� Ž�� ����");
			}
			//ȭ�� �ʱ�ȭ?
			printf("������ Ŭ�����߽��ϴ�.");
			shmem->Cr_room++;
		}
	} while (shmem->Cr_room <= 5);

	free(player);
	return 0;
}

