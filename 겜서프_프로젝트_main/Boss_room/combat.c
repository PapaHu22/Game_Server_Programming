#define CRT_SECURE_NO_WARNINGS_
#include "combat.h"
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

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

void start_combat(Player* player) {
    ShMEM* shmem = shm_get();//보스 몬스터 아스키아트 부분 수정
    int random = 0;
    while (shmem->Monster_HP > 0 && player->health > 0) {
        //printf("%s\n", monster1->boss_ascii_art); // 몬스터 아스키 >    아트 출력

        printf("당신의 HP: %d, 보스몬스터 HP: %d\n", player->health, s    hmem->Monster_HP);
        printf("Attack (A), Special Attack (S),  Defend (D): ");
        char choice;
        scanf(" %c", &choice, 1);

        switch (choice) {
        case 'A': // 일반 공격
            printf("당신은 보스몬스터를 공격했습니다!\n");
            shmem->Monster_HP -= player->attack;
            break;
        case 'S': // 특수 공격
            printf("강력한 공격을 했습니다!\n");
            shmem->Monster_HP -= (player->attack * 2);
            break;
        case 'D': // 방어
            printf("방어 상태입니다!\n");
            //player->health += player->defense;
            break;
        default:
            printf("잘못된 선택입니다!\n");
            continue;

        }

        // 몬스터의 반격
        if (shmem->Monster_HP > 0) {
            random = rand() % 3 + 1;
            if (random == 1) {
                printf("보스몬스터가 당신을 공격합니다!\n");
                player->health -= shmem->Monster_OP;

            }
            else if (random == 2) {
                printf("보스몬스터가 강력한 공격을 합니다!\n");
                player->health -= (shmem->Monster_OP * 2);

            }
            else {
                printf("보스몬스터는 방어 상태입니다!\n");
                //monster->health += monster->defense;

            }



        }

        // 체력 상태 확인
        if (player->health <= 0) {
            printf("패배\n");
            break;

        }

        if (shmem->Monster_HP <= 0) {
            printf("Phase1 승리\n\n\n");
            shmem->x = -1;
            shmem->y = -1;
            break;

        }

    }

}



void start_combat2(Player* player) {
    ShMEM* shmem = shm_get();
    int random = 0;
    //printf("자식 프로세스플레이어 %d 화면\n", process_num);

    while (shmem->Monster_HP > 0 && player->health > 0) {
        //printf("자식 프로세스 플레이어 %d 화면\n",process_num);
            //printf("%s\n", monster2->boss_ascii_art); // 몬스터 아스키 >    아트 출력

        printf("당신의 HP: %d, 보스몬스터의 HP: %d\n", player->health, shmem->Monster_HP);
        printf("Attack (A), Special Attack (S),  Defend (D): ");
        char choice;
        scanf(" %c", &choice, 1);

        switch (choice) {
        case 'A': // 일반 공격
            printf("당신은 보스몬스터를 공격했습니다!\n");
            shmem->Monster_HP -= player->attack;
            break;
        case 'S': // 특수 공격
            printf("강력한 공격을 했습니다!\n");
            shmem->Monster_HP -= (player->attack * 2);
            break;
        case 'D': // 방어
            printf("방어 상태입니다!\n");
            //player->health += player->defense;
            break;
        default:
            printf("잘못된 선택입니다!\n");
            continue;

        }

        // 몬스터의 반격
        if (shmem->Monster_HP > 0) {
            random = rand() % 3 + 1;
            if (random == 1) {
                printf("보스몬스터가 당신을 공격합니다!\n");
                player->health -= shmem->Monster_OP;

            }
            else if (random == 2) {
                printf("보스몬스터는 방어 상태입니다.\n");


            }


        }

        // 체력 상태 확인
        if (player->health <= 0) {
            printf("패배\n");
            break;

        }

        if (shmem->Monster_HP <= 0) {
            printf("Phase2 승리\n\n\n");
            shmem->x = -1;
            shmem->y = -1;
            break;

        }

    }

}


void start_combat3(Player* player) {
    ShMEM* shmem = shm_get();
    int random = 0;
    while (shmem->Monster_HP > 0 && player->health > 0) {
        //printf("%s\n", monster3->boss_ascii_art); // 몬스터 아스키 >    아트 출력

        printf("당신의 HP: %d, 보스몬스터의 HP: %d\n", player->health, shmem->Monster_HP);
        printf("Attack (A), Special Attack (S),  Defend (D): ");
        char choice;
        scanf(" %c", &choice, 1);

        switch (choice) {
        case 'A': // 일반 공격
            printf("당신은 몬스터를 공격했습니다!!\n");
            shmem->Monster_HP -= player->attack;
            break;
        case 'S': // 특수 공격
            printf("강력한 공격을 했습니다!\n");
            shmem->Monster_HP -= (player->attack * 2);
            break;
        case 'D': // 방어
            printf("방어 상태입니다!\n");
            //player->health += player->defense;
            break;
        default:
            printf("잘못된 선택입니다!\n");
            continue;

        }


        if (shmem->Monster_HP > 0) {
            random = rand() % 3 + 1;
            if (random == 1) {
                printf("보스몬스터가 당신을 공격합니다!\n");
                player->health -= shmem->Monster_OP;
            }
            else if (random == 2) {
                printf("보스몬스터가 강력한 공격을 합니다!\n");
                player->health -= (shmem->Monster_OP * 2);

            }
            else {
                printf("보스몬스터가 방어 상태입니다!\n");


            }

        }


    }

}
