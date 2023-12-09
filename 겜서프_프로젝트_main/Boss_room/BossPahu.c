#include "game.h"
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


// phase2에서 각 보스분신 체력을 깎은만큼 전체 분신체력을 깎는다. 그리고 phase3 보스에 체력도 또 깎는다. 알람 기능을 넣어서 phase2에서 제한 시간안에 보>스 분신을 못 해치우면 체력을 깎은 만큼만 phase3보스체력에 영향을 준다.




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
    shmem->Monster2_HP = 100;
    shmem->Monster2_OP = 10;
    shmem->Monster3_HP = 2000;
    shmem->Monster3_OP = 25;
    shmem->User_num = 2;

    shmem->sum_boss_phase2_HP = 100 * shmem->User_num;

    shmem->checkin_1 = false;
    shmem->checkin_2 = false;
    shmem->checkin_3 = false;
    shmem->checkin_4 = false;
    int you = 1;

    int i;
    char map[MAP_HEIGHT][MAP_WIDTH];
    Player player = { 0, MAP_HEIGHT / 2, 200, 30, 10 };
    BossMonster monster1 = { 10, 15, 200, 25, BOSSMONSTER_ART1 };
    //BossMonster monster3 = { 10, 15, 200, 25, BOSSMONSTER_ART3 };

    char input;
    bool inCombat = false;

    initialize_map(map, &player);
    map[shmem->y][shmem->x] = BOSSMONSTER_ICON; // 몬스터 위치 표시

    while (1) {

        system("clear"); // 화면 클리어
        printf("현재 위치: 보스방\n");
        draw_line();
        draw_map(map);
        draw_line();

        // 전투 상태 결정
        bool isNearMonster = abs(player.x - shmem->x) <= 1 && abs(player.y - shmem->y) <= 1;

        if (!inCombat && isNearMonster) {
            inCombat = true;

            printf("Boss Phase1...\n");
            start_combat(&player, you); // 전투 시작


            if (shmem->Monster_HP <= 0 && player.health > 0) {


                printf("Boss Phase2...\n");

                start_combat2(&player, you);


                if (player.health > 0) {

                    shmem->Monster3_HP -= (100 * shmem->User_num - shmem->sum_boss_phase2_HP);
                    printf("Boss Phase3...\n");
                    start_combat3(&player, you);
                    if (shmem->Monster3_HP <= 0 && player.health > 0) {

                        inCombat = false; // 전투 상태 종료

                    }
                }
            }
            break;
        }
        else {
            printf("이동 WASD, press E 전투시작, Q 종료: ");
            scanf(" %c", &input, 1);
            switch (input) {
            case 'w': // 위로 이동
            case 'a': // 왼쪽으로 이동
            case 's': // 아래로 이동
            case 'd': // 오른쪽으로 이동
                draw_move(input, &player, map, &monster1);
                break;
            case 'q': // 게임 종료
                return 0;
            default:
                printf("조작불가!\n");
            }
        }
        /*_getch();*/
    }//while
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

