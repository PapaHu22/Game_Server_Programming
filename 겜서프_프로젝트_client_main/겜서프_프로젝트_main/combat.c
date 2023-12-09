#include "combat.h"
#include "game.h"
#include <stdio.h>


void start_combat(Player* player, int you) {
    ShMEM* shmem = shm_get();
    shmem->checkin_1 = false;
    shmem->checkin_2 = false;
    shmem->checkin_3 = false;
    shmem->checkin_4 = false;
    while (shmem->monster.Monster_HP > 0 && player->HP > 0) {
        printf("%s\n", MONSTER_ART); // 몬스터 아스키 아트 출력
        printf("당신의 체력: %d, 몬스터 체력: %d\n", player->HP, shmem->monster.Monster_HP);
        printf("공격(A), 특수 공격(S),  방어(D): ");
        char choice;

     
        switch (shmem->User_num) {
        case 1:
            scanf_s(" %c", &choice, 1);
            break;
        case 2:
            while (true) {
                if (you == 1 && !shmem->checkin_1) {
                    scanf_s(" %c", &choice, 1);
                    shmem->checkin_1 = true;
                }
                else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                    scanf_s(" %c", &choice, 1);
                    shmem->checkin_2 = true;
                }

                if (shmem->checkin_1 && shmem->checkin_2) {
                    shmem->checkin_1 = false;
                    shmem->checkin_2 = false;
                    break;
                }
            }
            break;
        case 3:
            while (true) {
                if (you == 1 && !shmem->checkin_1) {
                    scanf_s(" %c", &choice, 1);
                    shmem->checkin_1 = true;
                }
                else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                    scanf_s(" %c", &choice, 1);
                    shmem->checkin_2 = true;
                }
                else if (you == 3 && shmem->checkin_2 && !shmem->checkin_3)
                {
                    scanf_s(" %c", &choice, 1);
                    shmem->checkin_3 = true;
                }

                if (shmem->checkin_1 && shmem->checkin_2 && shmem->checkin_3) {
                    shmem->checkin_1 = false;
                    shmem->checkin_2 = false;
                    shmem->checkin_3 = false;
                    break;
                }
            }
            break;
        case 4:
            while (true) {
                if (you == 1 && !shmem->checkin_1) {
                    scanf_s(" %c", &choice, 1);
                    shmem->checkin_1 = true;
                }
                else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                    scanf_s(" %c", &choice, 1);
                    shmem->checkin_2 = true;
                }
                else if (you == 3 && shmem->checkin_2 && !shmem->checkin_3)
                {
                    scanf_s(" %c", &choice, 1);
                    shmem->checkin_3 = true;
                }
                else if (you == 4 && shmem->checkin_3 && !shmem->checkin_4) {
                    scanf_s(" %c", &choice, 1);
                    shmem->checkin_4 = true;
                }

                if (shmem->checkin_1 && shmem->checkin_2 && shmem->checkin_3 && shmem->checkin_4) {
                    shmem->checkin_1 = false;
                    shmem->checkin_2 = false;
                    shmem->checkin_3 = false;
                    shmem->checkin_4 = false;
                    break;
                }
            }
            break;
        }


        switch (choice) {
        case 'A': // 일반 공격
            printf("플레이어 공격!\n");
            shmem->monster.Monster_HP -= player->OP;
            break;
        case 'S': // 특수 공격
            printf("특수 공격!\n");
            shmem->monster.Monster_HP -= (player->OP * 2);
            break;
        case 'D': // 방어
            printf("방어!\n");
            //player->HP += player->defense;
            break;
        default:
            printf("조작불가!\n");
            continue;
        }

        // 몬스터의 반격
        if (shmem->monster.Monster_HP > 0) {
            printf("몬스터의 공격\n");
            player->HP -= shmem->monster.Monster_OP;
        }

        // 호스트 다운
        if (shmem->Host_HP <= 0) {
            break;
        }


        //  체력 상태 확인
        if (player->HP <= 0) {
            printf("당신은 패배했습니다\n");
            break;
        }

        if (shmem->monster.Monster_HP <= 0) {
            printf("-몬스터를 물리쳤습니다\n");
            shmem->party.Party_Coin += 100;
            break;
        }
    }
}
