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

	//플레이어 참가
	++shmem->User_num;
	//만약 유저수가 4명을 넘을 경우 참가못하게 하고 종료
	if (shmem->User_num > MAX_USER_NUM) {
		shmem->User_num = 4;
		printf("이미 파티가 꽉찼습니다.");
		return 1;
	}

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

	//화면 초기화
	int game_ready;
	int field_ready;
	printf("던전을 탐험할 준비가 되었습니까?(1번 입력시 시작)"); // 호스트 코드 전용
	scanf("%d", &game_ready);
	if (game_ready == 1) {
		printf("탐험을 시작합니다.");
		shmem->game_ready = true;
	}

	do {
		if (shmem->Cr_room == 1 || shmem->Cr_room == 2) {
			printf("필드방%d 앞입니다. 진입하시겠습니까?(1번 입장시 진입)", shmem->Cr_room);
			scanf("%d", &field_ready);
			if (field_ready == 1) {
				shmem->field_ready = true;
			}
			field_map(player, you);
			if (shmem->Host_HP >= 0) {
				printf("파티장(호스트)이 리타이어됐습니다. 던전 탐험 실패");
			}
			printf("필드맵을 클리어했습니다.");
			shmem->Cr_room++;
		}
		else if (shmem->Cr_room== 3) {
			printf("함정방에 입장하시겠습니까?");
			trap(shmem->User_num);
			printf("함정맵을 클리어했습니다.");
			if (shmem->Host_HP >= 0) {
				printf("파티장(호스트)이 리타이어됐습니다. 던전 탐험 실패");
			}
			shmem->Cr_room++;
		}
		else if(shmem->Cr_room == 4) {
			// 상점맵
			printf("상점맵 이용");
			shmem->Cr_room++;
		}
		else {
			//보스방
			if (shmem->Host_HP >= 0) {
				printf("파티장(호스트)이 리타이어됐습니다. 던전 탐사 실패");
			}
			//화면 초기화?
			printf("보스를 클리어했습니다.");
			shmem->Cr_room++;
		}
	} while (shmem->Cr_room <= 5);

	free(player);
	return 0;
}

