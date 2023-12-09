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
	system("clear");

	while (true) {
		printf("��Ƽ���� ������ ��ٸ��� �ֽ��ϴ�.");
		system("clear");
		if (shmem->game_ready) {
			printf("��Ƽ���� �����Ͽ����ϴ�.");
			fflush(stdout);
			break;
		}
	}


	do {
		if (shmem->Cr_room == 1 || shmem->Cr_room == 2) {
			printf("�� �տ� �ֽ��ϴ�. ��Ƽ���� ������ ����մϴ�.\n");
			fflush(stdout);
			while (1) {
				if (shmem->field_ready) {
					break;
				}
			}
			field_map(player, you);
			sleep(1);
			if (shmem->Host_HP >= 0) {
				printf("��Ƽ��(ȣ��Ʈ)�� ��Ÿ�̾�ƽ��ϴ�. ���� Ž�� ����");
				fflush(stdout);
				break;
			}
			if (player->HP <= 0) {
				printf("GAME OVER.\n");
				shmem->User_num--;
				break;
			}
			printf("�ʵ���� Ŭ�����߽��ϴ�.");
			fflush(stdout);
		}
		else if (shmem->Cr_room== 3) {
			printf("�� �տ� �ֽ��ϴ�. ��Ƽ���� ������ ����մϴ�.\n");
			fflush(stdout);
			while (1) {
				if (shmem->field_ready) {
					break;
				}
			}
			trap();
			sleep(1);
			if (shmem->Host_HP >= 0) {
				printf("��Ƽ��(ȣ��Ʈ)�� ��Ÿ�̾�ƽ��ϴ�. ���� Ž�� ����");
				fflush(stdout);
				break;
			}
			if (player->HP <= 0) {
				printf("GAME OVER.\n");
				fflush(stdout);
				shmem->User_num--;
				break;
			}
			printf("�������� Ŭ�����߽��ϴ�.");
			fflush(stdout);
		}
		else if(shmem->Cr_room == 4) {
			system("clear");
			while (1) {
				if (shmem->shoping_wait) {
					break;
				}
				else {
					system("clear");
					printf("��Ƽ���� ���� ���Դϴ�. �����ϰ� ��ٸ�����");
					fflush(stdout);
					sleep(1);
				}
			}
			player->OP += (10 * shmem->OP_UP);
			for (int i = 0; i < shmem->MAX_HP_UP; i++) {
				player->class.class_HP = player->class.class_HP * 2;
			}
			for (int i = 0; i < shmem->Potion; i++) {
				player->HP += 20;
				if (player->HP > player->class.class_HP) {
					player->HP = player->class.class_HP;
				}
			}
			printf("���� ���� �̿� ��");
			fflush(stdout);
			sleep(2);
		}
		else {
			printf("������ �տ� �ֽ��ϴ�. ��Ƽ���� ������ ����մϴ�.\n");
			fflush(stdout);
			while (1) {
				if (shmem->boss_ready) {
					break;
				}
			}
			sleep(1);
			//������
			boss_room(player, you);
			if (shmem->Host_HP >= 0) {
				printf("��Ƽ��(ȣ��Ʈ)�� ��Ÿ�̾�ƽ��ϴ�. ���� Ž�� ����");
				fflush(stdout);
				break;
			}
			if (player->HP <= 0) {
				printf("GAME OVER.\n");
				shmem->User_num--;
				break;
			}
			system("clear");
			printf("������ Ŭ�����߽��ϴ�.");
			fflush(stdout);
			shmem->Cr_room++;
		}
	} while (shmem->Cr_room <= 5);

	free(player);
	return 0;
}

