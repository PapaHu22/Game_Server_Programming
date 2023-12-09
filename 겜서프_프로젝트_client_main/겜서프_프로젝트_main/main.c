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
	ShMEM* shmem; //공유메모리 요소(유저수, 현재 방 위치, 파티, 보스2페이즈 체력)
	
	key = ftok("/home/g_202211077/Teamproject/Boss", 211);
	shmid = shmget(key, 1024, 0);
	if (shmid == -1) {
		perror("shmget");
		exit(1);
	}

	shmem = (ShMEM*)shmat(shmid, NULL, 0);

	if (shmem->game_ready) {
		printf("이미 이 파티는 던전 탐사를 시작했습니다.");
		return 2;
	}

	shmem->User_num++;
	if (shmem->User_num >= 5) {
		printf("파티가 꽉찼습니다.\n");
		shmem->User_num = 4;
		return 1;
	}

	Class Warrior; //전사, 탱
	Class SwordsMan; //검사, 근딜
	Class Priest; //성직자, 힐러
	Class Archer; // 궁수, 원딜

	Warrior.class_HP = 500;
	Warrior.class_OP = 50;
	
	SwordsMan.class_HP = 250;
	SwordsMan.class_OP = 70;

	Priest.class_HP = 200;
	Priest.class_OP = 30;

	Archer.class_HP = 150;
	Archer.class_OP = 100;


	int you = shmem->User_num; // 유저번호 부여
	

	Player* player = (Player*)malloc(sizeof(Player));

	int select_class;

	//직업선택
	printf("직업을 선택하세요.\n");
	while (true) {
		printf("전사(1), 암살자(2), 성직자(3), 궁수(4)\n");
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
			printf("잘못된 입력입니다.");
		}
		ClearLineFromReadBuffer();
		if (select_class == 1 || select_class == 2 || select_class == 3 || select_class == 4) {
			break;
		}
	}
	system("clear");

	while (true) {
		printf("파티장의 시작을 기다리고 있습니다.");
		system("clear");
		if (shmem->game_ready) {
			printf("파티장이 시작하였습니다.");
			fflush(stdout);
			break;
		}
	}


	do {
		if (shmem->Cr_room == 1 || shmem->Cr_room == 2) {
			printf("문 앞에 있습니다. 파티장의 시작을 대기합니다.\n");
			fflush(stdout);
			while (1) {
				if (shmem->field_ready) {
					break;
				}
			}
			field_map(player, you);
			sleep(1);
			if (shmem->Host_HP >= 0) {
				printf("파티장(호스트)이 리타이어됐습니다. 던전 탐험 실패");
				fflush(stdout);
				break;
			}
			if (player->HP <= 0) {
				printf("GAME OVER.\n");
				shmem->User_num--;
				break;
			}
			printf("필드맵을 클리어했습니다.");
			fflush(stdout);
		}
		else if (shmem->Cr_room== 3) {
			printf("문 앞에 있습니다. 파티장의 시작을 대기합니다.\n");
			fflush(stdout);
			while (1) {
				if (shmem->field_ready) {
					break;
				}
			}
			trap();
			sleep(1);
			if (shmem->Host_HP >= 0) {
				printf("파티장(호스트)이 리타이어됐습니다. 던전 탐험 실패");
				fflush(stdout);
				break;
			}
			if (player->HP <= 0) {
				printf("GAME OVER.\n");
				fflush(stdout);
				shmem->User_num--;
				break;
			}
			printf("함정맵을 클리어했습니다.");
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
					printf("파티장이 쇼핑 중입니다. 느긋하게 기다리세요");
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
			printf("던전 상점 이용 끝");
			fflush(stdout);
			sleep(2);
		}
		else {
			printf("보스방 앞에 있습니다. 파티장의 시작을 대기합니다.\n");
			fflush(stdout);
			while (1) {
				if (shmem->boss_ready) {
					break;
				}
			}
			sleep(1);
			//보스방
			boss_room(player, you);
			if (shmem->Host_HP >= 0) {
				printf("파티장(호스트)이 리타이어됐습니다. 던전 탐험 실패");
				fflush(stdout);
				break;
			}
			if (player->HP <= 0) {
				printf("GAME OVER.\n");
				shmem->User_num--;
				break;
			}
			system("clear");
			printf("보스를 클리어했습니다.");
			fflush(stdout);
			shmem->Cr_room++;
		}
	} while (shmem->Cr_room <= 5);

	free(player);
	return 0;
}

