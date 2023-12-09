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
	
	key = ftok("/home/g_202211077/Teamproject", 211);
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
	shmem->boss_ready = false;
	shmem->shoping_wait = false;

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
	
	int you = shmem->User_num; // 당사자

	

	Player* player = (Player*)malloc(sizeof(Player));

	shmem->party.x = 0;
	shmem->party.y = MAP_HEIGHT;

	shmem->Cr_room = 1;

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

	shmem->Host_HP = player->HP;

	system("clear");
	int game_ready;
	int field_ready;
	int boss_ready;
	printf("던전을 탐험할 준비가 되었습니까?(1번 입력시 시작)"); // 호스트 코드 전용
	scanf("%d", &game_ready);
	if (game_ready == 1) {
		printf("탐험을 시작합니다.");
		fflush(stdout);
		shmem->game_ready = true;
	}

	do {
		if (shmem->Cr_room == 1 || shmem->Cr_room == 2) {
			printf("앞에 문이 있습니다. 진입하시겠습니까?(1번 입력시 진입)");
			fflush(stdout);
			while (1) {
				scanf("%d", &field_ready);
				if (field_ready == 1) {
					shmem->field_ready = true;
					break;
				}
				else {
					printf("잘못된 입력\n");
				}
			}
			field_map(player, you);
			shmem->field_ready = false;
			if (shmem->Host_HP <= 0) {
				printf("파티장(호스트)이 리타이어됐습니다. 던전 탐험 실패");
				fflush(stdout);
				break;
			}

			printf("필드맵을 클리어했습니다.");
			fflush(stdout);
			shmem->Cr_room++;
		}
		else if (shmem->Cr_room== 3) {
			printf("앞에 문이 있습니다. 진입하시겠습니까?(1번 입력시 진입)");
			fflush(stdout);
			while (1) {
				scanf("%d", &field_ready);
				if (field_ready == 1) {
					shmem->field_ready = true;
					break;
				}
				else {
					printf("잘못된 입력\n");
				}
			}
			trap(you);
			shmem->field_ready = false;
			if (shmem->Host_HP <= 0) {
				printf("파티장(호스트)이 리타이어됐습니다. 던전 탐험 실패");
				fflush(stdout);
				break;
			}
			printf("함정맵을 클리어했습니다.");
			fflush(stdout);
			shmem->Cr_room++;
		}
		else if(shmem->Cr_room == 4) {
			system("clear");
			// 상점맵
			shop();
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
			shmem->Host_HP = player->HP;
			shmem->shoping_wait = true;
			printf("던전 상점 이용 끝");
			fflush(stdout);
			sleep(2);
			shmem->Cr_room++;
		}
		else {
			printf("보스방 앞에 있습니다.진입하시겠습니까 ? (1번 입력시 진입)");
			fflush(stdout);
			while (1) {
				scanf("%d", &boss_ready);
				if (boss_ready == 1) {
					shmem->boss_ready = true;
					break;
				}
				else {
					printf("잘못된 입력\n");
				}
			}
			//보스방
			boss_room(player, you);
			if (shmem->Host_HP <= 0) {
				printf("파티장(호스트)이 리타이어됐습니다. 던전 탐사 실패");
				fflush(stdout);
				break;
			}
			system("clear");
			printf("보스를 클리어했습니다.");
			fflush(stdout);
			shmem->Cr_room++;
		}
	} while (shmem->Cr_room <= 5);

	free(player);
	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}

