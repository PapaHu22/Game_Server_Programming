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
	Monster monster = { 10, 15, 100, 15, MONSTER_ART }; // 몬스터 초기 설정
	char input;
	bool inCombat = false; // 전투 상태 플래그

	initialize_map(map, player);
	map[monster.y][monster.x] = MONSTER_ICON; // 몬스터 위치 표시

	while (1) {
		system("cls"); // 화면 클리어
		printf("현재 위치: 맵 이름\n"); // 맵 이름 출력
		draw_line(); 
		draw_map(map); // 맵 출력
		draw_line();

		if (!inCombat) {
			printf("이동 WASD, Q 종료: ");
			scanf_s(" %c", &input, 1);
		}

		// 전투 상태 결정
		bool isNearMonster = abs(player->x - monster.x) <= 1 && abs(player->y - monster.y) <= 1;

		if (!inCombat && isNearMonster) {
			inCombat = true;
			printf("%s\n", MONSTER_ART); // 몬스터 아스키 아트 출력
			printf("Your Health: %d, Monster's Health: %d\n", player->HP, monster.Monster_HP);
			start_combat(player, &monster); // 전투 시작
			if (monster.Monster_HP <= 0) {
				map[monster.y][monster.x] = ' '; // 몬스터 위치 지우기
				monster.y = -1;
				monster.x = -1;
				inCombat = false; // 전투 상태 종료
			}
		}
		else {
			switch (input) {
			case 'w': // 위로 이동
			case 'a': // 왼쪽으로 이동
			case 's': // 아래로 이동
			case 'd': // 오른쪽으로 이동
				draw_move(input, player, map, &monster);
				break;
			case 'q': // 게임 종료
				return 0;
			default:
				printf("조작불가!\n");
			}
		}
	}
}


int main() 
{
	int shmid;
	key_t key;
	ShMEM* shmem; //공유메모리 요소(유저수, 현재 방 위치, 파티, 보스2페이즈 체력)
	
	key = ftok("/home/g_202010951/project_space", 1);
	shmid = shmget(key, 1024, 0);
	if (shmid == -1) {
		perror("shmget");
		exit(1);
	}

	shmem = (ShMEM*)shmat(shmid, NULL, 0);

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


	shmem->User_num = 3;
	int you; // 당사자
	
	// 유저수가 
	if (shmem->User_num != 1 && shmem->User_num != 2 && shmem->User_num != 3 && shmem->User_num != 4) {
		shmem->User_num = 0;
	}

	//플레이어 참가
	++shmem->User_num;
	//만약 유저수가 4명을 넘을 경우 참가못하게 하고 종료
	if (shmem->User_num > MAX_USER_NUM) {
		shmem->User_num = 4;
		printf("이미 파티가 꽉찼습니다.");
		return 1;
	}

	Player* player = (Player*)malloc(sizeof(Player));
	player->x = 0;
	player->y = MAP_HEIGHT;

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

	system("cls");

	shmem->Cr_room++;
	do {
		if (shmem->Cr_room == 1 || shmem->Cr_room == 2) {
			field_map(player);
			printf("필드맵을 클리어했습니다.");
			shmem->Cr_room++;
		}
		else if (shmem->Cr_room== 3) {
			trap(shmem->User_num);
			printf("함정맵을 클리어했습니다.");
			shmem->Cr_room++;
		}
		else if(shmem->Cr_room == 4) {
			// 상점맵
			printf("상점맵 이용");
			shmem->Cr_room++;
		}
		else {
			//보스방
			printf("보스를 클리어했습니다.");
			shmem->Cr_room++;
		}
	} while (player->HP > 0 && shmem->Cr_room <= 5);

	free(player);
	return 0;
}

