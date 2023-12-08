// game.c

#include <stdio.h>
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
void draw_move(char input, Player* player, char map[MAP_HEIGHT][MAP_WIDTH], Monster* monster) {
    int new_x = player->x;
    int new_y = player->y;

    switch (input) {
    case 'w': new_y--; break;
    case 's': new_y++; break;
    case 'a': new_x--; break;
    case 'd': new_x++; break;
    }

    if (new_x < 0 || new_x >= MAP_WIDTH || new_y < 0 || new_y >= MAP_HEIGHT) {
        return;
    }

    if (new_x == monster->x && new_y == monster->y) {
        return;
    }

    map[player->y][player->x] = ' '; // 이전 플레이어 위치 지우기
    player->x = new_x;
    player->y = new_y;
    map[player->y][player->x] = PLAYER_ICON; // 새 위치에 플레이어 표시
}

void initialize_map(char map[MAP_HEIGHT][MAP_WIDTH], Player* player) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map[y][x] = ' ';
        }
    }
    player->x = 0;
    player->y = MAP_HEIGHT / 2;
    map[player->y][player->x] = PLAYER_ICON;
}





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