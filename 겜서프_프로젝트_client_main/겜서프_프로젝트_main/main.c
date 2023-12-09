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
	shmid = shmget(key, 1024, 0);
	if (shmid == -1) {
		perror("shmget");
		exit(1);
	}

	shmem = (ShMEM*)shmat(shmid, NULL, 0);

	if (shmem->game_ready) {
		printf("�̹� �� ��Ƽ�� ���� Ž�縦 �����߽��ϴ�.");
		return 2;
	}

	shmem->User_num++;
	if (shmem->User_num >= 5) {
		printf("��Ƽ�� ��á���ϴ�.\n");
		shmem->User_num = 4;
		return 1;
	}

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


	int you = shmem->User_num; // ������ȣ �ο�
	

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

	while (true) {
		printf("��Ƽ���� ������ ��ٸ��� �ֽ��ϴ�.");
		cls("clear");
		if (shmem->game_ready) {
			printf("��Ƽ���� �����Ͽ����ϴ�.");
			break;
		}
	}


	do {
		if (shmem->Cr_room == 1 || shmem->Cr_room == 2) {
			printf("�� �տ� �ֽ��ϴ�. ��Ƽ���� ������ ����մϴ�.\n", shmem->Cr_room);
			while (1) {
				if (shmem->field_ready) {
					break;
				}
			}
			field_map(player);
			sleep(1);
			if (shmem->Host_HP >= 0) {
				printf("��Ƽ��(ȣ��Ʈ)�� ��Ÿ�̾�ƽ��ϴ�. ���� Ž�� ����");
				break;
			}
			printf("�ʵ���� Ŭ�����߽��ϴ�.");
		}
		else if (shmem->Cr_room== 3) {
			printf("�� �տ� �ֽ��ϴ�. ��Ƽ���� ������ ����մϴ�.\n", shmem->Cr_room);
			while (1) {
				if (shmem->field_ready) {
					break;
				}
			}
			trap(shmem->User_num);
			sleep(1);
			if (shmem->Host_HP >= 0) {
				printf("��Ƽ��(ȣ��Ʈ)�� ��Ÿ�̾�ƽ��ϴ�. ���� Ž�� ����");
				break;
			}
			printf("�������� Ŭ�����߽��ϴ�.");
		}
		else if(shmem->Cr_room == 4) {
			// ������
			printf("������ �̿�");
		}
		else {
			//������
			if (shmem->Host_HP >= 0) {
				printf("��Ƽ��(ȣ��Ʈ)�� ��Ÿ�̾�ƽ��ϴ�. ���� Ž�� ����");
				break;
			}
			cls("clear");
			printf("������ Ŭ�����߽��ϴ�.");
			sleep(1);
		}

		if (player->HP <= 0) {
			printf("����� Ż���߽��ϴ�.\n");
			shmem->User_num--;
			break;
		}
	} while (shmem->Cr_room <= 5);

	free(player);
	return 0;
}

