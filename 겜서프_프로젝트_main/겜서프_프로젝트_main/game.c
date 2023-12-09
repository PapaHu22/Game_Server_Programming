// game.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include "game.h"
//line 따로 만듬
void draw_line() {
    for (int i = 0; i < MAP_WIDTH; i++) {
        printf("-");
    }
    printf("\n");
}
//맵 만들어주는 거
void draw_map(char map[MAP_HEIGHT][MAP_WIDTH]) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            printf("%c", map[y][x]);
        }
        printf("\n");
    }
}

//움직임
void draw_move(char input, char map[MAP_HEIGHT][MAP_WIDTH]) {
    ShMEM* shmem = shm_get();
    int new_x = shmem->party.x;
    int new_y = shmem->party.y;

    switch (input) {
    case 'w': new_y--; break;
    case 's': new_y++; break;
    case 'a': new_x--; break;
    case 'd': new_x++; break;
    }

    if (new_x < 0 || new_x >= MAP_WIDTH || new_y < 0 || new_y >= MAP_HEIGHT) {
        return;
    }

    if (new_x == shmem->monster.x && new_y == shmem->monster.y) {
        return;
    }

    map[shmem->party.x][shmem->party.x] = ' '; // 이전 플레이어 위치 지우기
	sleep(1);
    shmem->party.x = new_x;
    shmem->party.y = new_y;
    map[shmem->party.x][shmem->party.y] = PLAYER_ICON; // 새 위치에 플레이어 표시
}

void initialize_map(char map[MAP_HEIGHT][MAP_WIDTH]) {
    ShMEM* shmem = shm_get();
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map[y][x] = ' ';
        }
    }
    shmem->party.x = 0;
    shmem->party.y = MAP_HEIGHT / 2;
    map[shmem->party.x][shmem->party.y] = PLAYER_ICON;
}





void ClearLineFromReadBuffer()
{
    int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void field_map(Player* player, int you) {
    ShMEM* shmem = shm_get();
	char map[MAP_HEIGHT][MAP_WIDTH];
    shmem->monster.x = 10; //{ 10, 15, 100, 15, MONSTER_ART }; // 몬스터 초기 설정
    shmem->monster.y = 15;
    shmem->monster.Monster_HP = 100;
    shmem->monster.Monster_OP = 15;
    shmem->monster.ascii_art[0] = MONSTER_ART;
    char input;
	bool inCombat = false; // 전투 상태 플래그

	initialize_map(map);
	map[shmem->monster.y][shmem->monster.x] = MONSTER_ICON; // 몬스터 위치 표시

	while (1) {
        system("clear"); // 화면 클리어
		printf("현재 위치: 필드 방\n"); // 맵 이름 출력
		draw_line();
		draw_map(map); // 맵 출력
		draw_line();

		if (!inCombat) {
			printf("이동 WASD, Q 종료: ");
			scanfs(" %c", &input, 1);
            shmem->input = input;
		}

		// 전투 상태 결정
		bool isNearMonster = abs(shmem->party.x - shmem->monster.x) <= 1 && abs(shmem->party.y - shmem->monster.y) <= 1;

		if (!inCombat && isNearMonster) {
			inCombat = true;
			printf("%s\n", MONSTER_ART); // 몬스터 아스키 아트 출력
			printf("Your Health: %d, Monster's Health: %d\n", player->HP, shmem->monster.Monster_HP);
			start_combat(player, you); // 전투 시작
            if (shmem->Host_HP <= 0) {
                break;
            }
			if (shmem->monster.Monster_HP <= 0) {
				map[shmem->monster.x][shmem->monster.y] = ' '; // 몬스터 위치 지우기
				shmem->monster.y = -1;
				shmem->monster.x = -1;
				inCombat = false; // 전투 상태 종료
			}
		}
		else {
			switch (shmem->input) {
			case 'w': // 위로 이동
			case 'a': // 왼쪽으로 이동
			case 's': // 아래로 이동
			case 'd': // 오른쪽으로 이동
				draw_move(shmem->input, map);
				break;
			case 'q': // 게임 종료
				return 0;
			default:
				printf("조작불가!\n");
			}
		}
	}
}

void boss_room(Player* player, int you) {
	ShMEM* shmem = shm_get();
	char map[MAP_HEIGHT][MAP_WIDTH];
	shmem->boss_x = 15;
	shmem->boss_y = 15;
	shmem->boss_monster.Monster_OP = 15;
	shmem->boss_monster.Monster_HP = 100;
	shmem->boss_monster2.Monster_OP = 10;
	shmem->boss_monster2.Monster_HP = 100;
	shmem->boss_monster3.Monster_OP = 25;
	shmem->boss_monster3.Monster_HP = 2000;

	char input;
	bool inCombat = false; // 전투 상태 플래그

	initialize_map(map);
	map[shmem->boss_x][shmem->boss_y] = MONSTER_ICON; // 몬스터 위치 표시

	while (1) {
		system("clear"); // 화면 클리어
		printf("현재 위치: 보스 방\n"); // 맵 이름 출력
		draw_line();
		draw_map(map); // 맵 출력
		draw_line();

		if (!inCombat) {
			printf("이동 WASD, Q 종료: ");
			scanfs(" %c", &input, 1);
			shmem->input = input;
		}

		// 전투 상태 결정
		bool isNearMonster = abs(shmem->party.x - shmem->monster.x) <= 1 && abs(shmem->party.y - shmem->monster.y) <= 1;

		if (!inCombat && isNearMonster) {
			inCombat = true;
			printf("Boss Phase1...\n");
			boss_combat(player, you); // 전투 시작
			if (shmem->Host_HP <= 0) {
				break;
			}
			if (shmem->boss_monster.Monster_HP <= 0 && player->HP > 0) {
				printf("Boss Phase2...\n");
				boss_combat2(player, you);
				if (shmem->Host_HP <= 0) {
					break;
				}
				if (player->HP > 0) {
					shmem->boss_monster3.Monster_HP -= (100 * shmem->User_num - shmem->sum_boss_phase2_HP);
					printf("Boss Phase3...\n");
					boss_combat3(player, you);
					if (shmem->Host_HP <= 0) {
						break;
					}
					if (shmem->boss_monster3.Monster_HP <= 0 && player->HP > 0) {
						inCombat = false;
					}
				}

			}
			if (shmem->boss_monster3.Monster_HP <= 0) {
				map[shmem->boss_x][shmem->boss_y] = ' '; // 몬스터 위치 지우기
				shmem->boss_x = -1;
				shmem->boss_y = -1;
				inCombat = false; // 전투 상태 종료
			}
		}
		else {
			switch (shmem->input) {
			case 'w': // 위로 이동
			case 'a': // 왼쪽으로 이동
			case 's': // 아래로 이동
			case 'd': // 오른쪽으로 이동
				draw_move(shmem->input, map);
				break;
			case 'q': // 게임 종료
				return 0;
			default:
				printf("조작불가!\n");
			}
		}
	}

	system("clear");
	if (player->HP > 0) {
		printf("\n\n\n\n\n\n      ");

		printf("보스 클리어!");
	}
	else {
		printf("\n\n\n\n\n\n      ");
		printf("GAME OVER...");
	}

}

void shop() {
	ShMEM* shmem = shm_get();
	char input;

	shmem->Potion = 0;
	shmem->OP_UP = 0;
	shmem->MAX_HP_UP = 0;

	while (shmem->party.Party_Coin > 0) {
		printf("포션 구입(파티원 전체 체력 20 회복) <A> [20코인]\n");
		printf("공격력 강화 주문서 구입(파티원 전체 공격력 10 상승) <B> [100코인]\n");
		printf("파티원 전체 최대 체력 상승 구입(파티원 전체 최대 체력 2 배 상승) <C> [200코인]\n");
		scanfs(" %c", &input, 1);

		switch (input) {
		case 'A':
			shmem->Potion++;
			shmem->party.Party_Coin -= 20;
			break;
		case 'B':
			shmem->OP_UP++;
			shmem->party.Party_Coin -= 100;
			break;
		case 'C':
			shmem->MAX_HP_UP++;
			shmem->party.Party_Coin -= 200;
			break;
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