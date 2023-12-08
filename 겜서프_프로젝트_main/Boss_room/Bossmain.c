#include "game.h"
#include "test.h"
#include "combat.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

Players players[MAX_PLAYERS];

int main() {

    int shmid;
    key_t key;
    ShMEM* shmem;

    key = ftok("/home/g_202211077/Teamproject/Boss", 211);

    shmid = shmget(key, 1024, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    shmem = (ShMEM*)shmat(shmid, NULL, 0);

    shmem->x = 10;
    shmem->y = 15;
    shmem->Monster_HP = 100;
    shmem->Monster_OP = 15;

    int i;
    char map[MAP_HEIGHT][MAP_WIDTH];
    Player player = { 0, MAP_HEIGHT / 2, 200, 30, 10 };
    Player heal = { 0, MAP_HEIGHT / 2, 200, 30, 10 };
    Player taeng = { 0, MAP_HEIGHT / 2, 500, 50, 10 };
    Player shadow = { 0, MAP_HEIGHT / 2, 250, 70, 10 };
    Player ad = { 0, MAP_HEIGHT / 2, 150, 100, 10 };

    BossMonster monster1 = { 10, 15, 100, 15, BOSSMONSTER_ART1 };

    char input;
    bool inCombat = false;

    initialize_map(map, &player);
    map[shmem->y][shmem->x] = BOSSMONSTER_ICON;

    while (1) {
        system("clear");
        printf("현재 위치: 보스방\n");
        draw_line();
        draw_map(map);
        draw_line();

        bool isNearMonster = abs(player.x - shmem->x) <= 1 && abs(player.y - shmem->y) <= 1;

        if (!inCombat && isNearMonster) {
            inCombat = true;

            printf("Boss Phase1...\n");
            start_combat(&player);

            if (shmem->Monster_HP <= 0 && player.health > 0) {
                printf("Boss Phase2...\n");
                start_combat2(&player);

                if (shmem->Monster_HP <= 0 && player.health > 0) {
                    printf("Boss Phase3...\n");
                    start_combat3(&player);

                    if (shmem->Monster_HP <= 0 && player.health > 0) {
                        inCombat = false;
                    }
                }
            }
            break;
        }
        else {
            printf("이동 WASD, press E 전투시작, Q 종료: ");
            scanf(" %c", &input, 1);
            switch (input) {
            case 'w':
            case 'a':
            case 's':
            case 'd':
                draw_move(input, &player, map, &monster1);
                break;
            case 'q':
                return 0;
            default:
                printf("조작불가!\n");
            }
        }
    }

    system("clear");
    if (player.health > 0) {
        printf("\n\n\n\n\n\n      ");
        printf("보스 클리어!");
    }
    else {
        printf("\n\n\n\n\n\n      ");
        printf("GAME OVER...");
    }

    return 0;
}
