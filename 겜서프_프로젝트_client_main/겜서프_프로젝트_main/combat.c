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
#include <signal.h>
#include "game.h"


void start_combat(Player* player, int you) {
    ShMEM* shmem = shm_get();

    while (shmem->monster.Monster_HP > 0 && player->HP > 0) {
        ClearLineFromReadBuffer();
        sleep(2);
        shmem->checkin_1 = false;
        shmem->checkin_2 = false;
        shmem->checkin_3 = false;
        shmem->checkin_4 = false;
        printf("%s\n", MONSTER_ART); // 몬스터 아스키 아트 출력
        fflush(stdout);
        printf("당신의 체력: %d, 몬스터 체력: %d\n", player->HP, shmem->monster.Monster_HP);
        fflush(stdout);
        char choice;

     
        switch (shmem->User_num) {
        case 1:
            printf("공격(A), 특수 공격(S),  방어(D): ");
            scanf(" %c", &choice, 1);
            break;
        case 2:
            while (true) {
                if (you == 1 && !shmem->checkin_1) {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_1 = true;
                }
                else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_2 = true;
                }
                else {
                    system("clear");
                    printf("당신의 체력: %d, 몬스터 체력: %d\n", player->HP, shmem->monster.Monster_HP);
                    fflush(stdout);
                    printf("입력대기상태입니다.\n");
                    fflush(stdout);
                    sleep(1);
                }

                if (shmem->checkin_1 && shmem->checkin_2) {
                    printf("모두 입력하였습니다.\n");
                    fflush(stdout);
                    break;
                }
            }
            break;
        case 3:
            while (true) {
                if (you == 1 && !shmem->checkin_1) {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_1 = true;
                }
                else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_2 = true;
                }
                else if (you == 3 && shmem->checkin_2 && !shmem->checkin_3)
                {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_3 = true;
                }
                else {
                    system("clear");
                    printf("당신의 체력: %d, 몬스터 체력: %d\n", player->HP, shmem->monster.Monster_HP);
                    fflush(stdout);
                    printf("입력대기상태입니다.\n");
                    fflush(stdout);
                    sleep(1);
                }

                if (shmem->checkin_1 && shmem->checkin_2 && shmem->checkin_3) {
                    printf("모두 입력하였습니다.\n");
                    fflush(stdout);
                    break;
                }
            }
            break;
        case 4:
            while (true) {
                if (you == 1 && !shmem->checkin_1) {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_1 = true;
                }
                else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_2 = true;
                }
                else if (you == 3 && shmem->checkin_2 && !shmem->checkin_3)
                {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_3 = true;
                }
                else if (you == 4 && shmem->checkin_3 && !shmem->checkin_4) {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_4 = true;
                }
                else {
                    system("clear");
                    printf("당신의 체력: %d, 몬스터 체력: %d\n", player->HP, shmem->monster.Monster_HP);
                    fflush(stdout);
                    printf("입력대기상태입니다.\n");
                    fflush(stdout);
                    sleep(1);
                }

                if (shmem->checkin_1 && shmem->checkin_2 && shmem->checkin_3 && shmem->checkin_4) {
                    printf("모두 입력하였습니다.\n");
                    fflush(stdout);
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

        sleep(2);

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

void boss_combat(Player* player, int you) {
    ShMEM* shmem = shm_get();//보스 몬스터 아스키아트 부분 수정
    int random = 0;

    while (shmem->boss_monster.Monster_HP > 0 && player->HP > 0) {
        printf("  /\\_/\\\n ( T.T )\n  [ ^ ]\n");
        fflush(stdout);
        //"  /\\_/\\\n ( ^.^ )\n  < ^ >"        
        //"  /\\_/\\\n ( poq )\n *< ^ >*"

        ClearLineFromReadBuffer();
        sleep(3);
        shmem->checkin_1 = false;
        shmem->checkin_2 = false;
        shmem->checkin_3 = false;
        shmem->checkin_4 = false;


        printf("당신의 HP: %d, 보스몬스터 HP: %d\n", player->HP, shmem->boss_monster.Monster_HP);
        fflush(stdout);

        char choice;


        switch (shmem->User_num) {
        case 1:
            printf("공격(A), 특수 공격(S),  방어(D): ");
            scanf(" %c", &choice, 1);
            break;
        case 2:
            while (true) {
                if (you == 1 && !shmem->checkin_1) {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_1 = true;
                }
                else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_2 = true;
                }
                else {
                    system("clear");
                    printf("당신의 HP: %d, 보스몬스터 HP: %d\n", player->HP, shmem->boss_monster.Monster_HP);
                    fflush(stdout);
                    printf("입력대기상태입니다.\n");
                    fflush(stdout);
                    sleep(1);
                }

                if (shmem->checkin_1 && shmem->checkin_2) {
                    printf("모두 입력하였습니다.\n");
                    fflush(stdout);
                    break;
                }
            }
            break;
        case 3:
            while (true) {
                if (you == 1 && !shmem->checkin_1) {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_1 = true;
                }
                else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_2 = true;
                }
                else if (you == 3 && shmem->checkin_2 && !shmem->checkin_3)
                {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_3 = true;
                }
                else {
                    system("clear");
                    printf("당신의 HP: %d, 보스몬스터 HP: %d\n", player->HP, shmem->boss_monster.Monster_HP);
                    fflush(stdout);
                    printf("입력대기상태입니다.\n");
                    fflush(stdout);
                    sleep(1);
                }

                if (shmem->checkin_1 && shmem->checkin_2 && shmem->checkin_3) {
                    printf("모두 입력하였습니다.\n");
                    fflush(stdout);
                    break;
                }
            }
            break;
        case 4:
            while (true) {
                if (you == 1 && !shmem->checkin_1) {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_1 = true;
                }
                else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_2 = true;
                }
                else if (you == 3 && shmem->checkin_2 && !shmem->checkin_3)
                {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_3 = true;
                }
                else if (you == 4 && shmem->checkin_3 && !shmem->checkin_4) {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_4 = true;
                }
                else {
                    system("clear");
                    printf("당신의 HP: %d, 보스몬스터 HP: %d\n", player->HP, shmem->boss_monster.Monster_HP);
                    fflush(stdout);
                    printf("입력대기상태입니다.\n");
                    fflush(stdout);
                    sleep(1);
                }

                if (shmem->checkin_1 && shmem->checkin_2 && shmem->checkin_3 && shmem->checkin_4) {
                    printf("모두 입력하였습니다.\n");
                    fflush(stdout);
                    break;
                }
            }
            break;
        }



        switch (choice) {
        case 'A': // 일반 공격
            printf("당신은 보스몬스터를 공격했습니다!\n");
            shmem->boss_monster.Monster_HP -= player->OP;

            break;
        case 'S': // 특수 공격
            printf("강력한 공격을 했습니다!\n");
            shmem->boss_monster.Monster_HP -= (player->OP * 2);
            break;
        case 'D': // 방어
            printf("방어 상태입니다!\n");
            //player->health += player->defense;
            break;
        default:
            printf("잘못된 선택입니다!\n");
            continue;
        }

        sleep(2);
        // 몬스터의 반격
        if (shmem->boss_monster.Monster_HP > 0) {

            random = rand() % 3 + 1;
            if (random == 1) {
                printf("보스몬스터가 당신을 공격합니다!\n");
                player->HP -= shmem->boss_monster.Monster_OP;
            }
            else if (random == 2) {
                printf("보스몬스터가 강력한 공격을 합니다!\n");
                player->HP -= (shmem->boss_monster.Monster_OP * 2);
            }
            else {
                printf("보스몬스터는 방어 상태입니다!\n");
                //monster->health += monster->defense;
            }
        }

        sleep(2);

        if (shmem->Host_HP <= 0) {
            break;
        }

        // 체력 상태 확인
        if (player->HP <= 0) {
            printf("패배\n");
            break;
        }

        if (shmem->boss_monster.Monster_HP <= 0) {
            printf("Phase1 승리\n\n\n");
            shmem->boss_x = -1;
            shmem->boss_y = -1;
            break;
        }
    }
}

int t = 1;

void handler(int signo) {
    t = 0;

    printf("10초 끝!!!\n");
    printf("아무 키나 입력하시면 phase3로 넘어갑니다.\n");
}




void boss_combat2(Player* player, int you) {
    ShMEM* shmem = shm_get();
    int random = 0;
    int sec = 0;
    //int t = 1;
    BossMonster monster2;
    monster2.Monster_HP = 100;
    monster2.Monster_OP = 10;
    //"  /\\_/\\\n ( ^.^ )\n  < ^ >"        
        //"  /\\_/\\\n ( poq )\n *< ^ >*"


    signal(SIGALRM, handler);
    alarm(10);
    printf("제한 시간 10초 동안 보스 몬스터의 분신을 공격할 수 있습니다. 가능한 분신을 쓰러뜨리는게 좋습니다.\n");
    fflush(stdout);

    while (monster2.Monster_HP >= 0 && player->HP > 0 && t) {
        printf("  /\\_/\\\n ( ^.^ )\n  < ^ >\n");
        fflush(stdout);
        //printf("제한 시간 10초 동안 보스 몬스터의 분신을 공격할 수 있습니다. 가능한 분신을 쓰러뜨리는게 좋을 겁니다.");
    //sleep(1);
    //printf("%d초 경과 \n", ++sec);

        printf("당신의 HP: %d, 보스몬스터 분신의 HP: %d\n", player->HP, monster2.Monster_HP);
        printf("Attack (A), Special Attack (S),  Defend (D): ");

        shmem->sum_boss_phase2_HP = (100 * shmem->User_num - (100 - monster2.Monster_HP));
        char choice;
        scanf(" %c", &choice, 1);

        if (t != 0) {
            switch (choice) {
            case 'A': // 일반 공격
                printf("당신은 보스몬스터의 분신을 공격했습니다!\n");
                monster2.Monster_HP -= player->OP;
                break;
            case 'S': // 특수 공격
                printf("강력한 공격을 했습니다!\n");
                monster2.Monster_HP -= (player->OP * 2);
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
            if (monster2.Monster_HP > 0) {
                random = rand() % 3 + 1;
                if (random == 1) {
                    printf("보스몬스터가 당신을 공격합니다!\n");
                    player->HP -= monster2.Monster_HP;
                }
                else if (random == 2) {
                    printf("보스몬스터는 방어 상태입니다.\n");
                    //monster->health += monster->defense;
                }
                /*else {
                    printf("보스몬스터의 방어\n");
                    monster->health += monster->defense;
                }*/
            }
        }

        if (shmem->Host_HP <= 0) {
            break;
        }


        // 체력 상태 확인
        if (player->HP <= 0) {
            printf("패배\n");
            alarm(0);
            break;
        }

        if (monster2.Monster_HP <= 0) {
            printf("Phase2 승리\n\n\n");
            shmem->boss_x = -1;
            shmem->boss_y = -1;
            alarm(0);
            break;
        }

    }


}

void boss_combat3(Player* player, int you) {
    ShMEM* shmem = shm_get();
    int random = 0;
    while (shmem->boss_monster3.Monster_HP > 0 && player->HP > 0) {
        //      "  /\\_/\\\n ( ^.^ )\n  < ^ >"      
        printf("  /\\_/\\\n ( poq )\n *< ^ >*\n");
        fflush(stdout);
        ClearLineFromReadBuffer();
        sleep(2);
        shmem->checkin_1 = false;
        shmem->checkin_2 = false;



        printf("당신의 HP: %d, 보스몬스터 HP: %d\n", player->HP, shmem->boss_monster3.Monster_HP);
        fflush(stdout);


        char choice;

        switch (shmem->User_num) {
        case 1:
            printf("공격(A), 특수 공격(S),  방어(D): ");
            scanf(" %c", &choice, 1);
            break;
        case 2:
            while (true) {
                if (you == 1 && !shmem->checkin_1) {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_1 = true;
                }
                else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_2 = true;
                }
                else {
                    system("clear");
                    printf("당신의 HP: %d, 보스몬스터 HP: %d\n", player->HP, shmem->boss_monster3.Monster_HP);
                    fflush(stdout);
                    printf("입력대기상태입니다.\n");
                    fflush(stdout);
                    sleep(1);
                }

                if (shmem->checkin_1 && shmem->checkin_2) {
                    printf("모두 입력하였습니다.\n");
                    fflush(stdout);
                    break;
                }
            }
            break;
        case 3:
            while (true) {
                if (you == 1 && !shmem->checkin_1) {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_1 = true;
                }
                else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_2 = true;
                }
                else if (you == 3 && shmem->checkin_2 && !shmem->checkin_3)
                {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_3 = true;
                }
                else {
                    system("clear");
                    printf("당신의 HP: %d, 보스몬스터 HP: %d\n", player->HP, shmem->boss_monster3.Monster_HP);
                    fflush(stdout);
                    printf("입력대기상태입니다.\n");
                    fflush(stdout);
                    sleep(1);
                }

                if (shmem->checkin_1 && shmem->checkin_2 && shmem->checkin_3) {
                    printf("모두 입력하였습니다.\n");
                    fflush(stdout);
                    break;
                }
            }
            break;
        case 4:
            while (true) {
                if (you == 1 && !shmem->checkin_1) {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_1 = true;
                }
                else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_2 = true;
                }
                else if (you == 3 && shmem->checkin_2 && !shmem->checkin_3)
                {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_3 = true;
                }
                else if (you == 4 && shmem->checkin_3 && !shmem->checkin_4) {
                    printf("공격(A), 특수 공격(S),  방어(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_4 = true;
                }
                else {
                    system("clear");
                    printf("당신의 HP: %d, 보스몬스터 HP: %d\n", player->HP, shmem->boss_monster3.Monster_HP);
                    fflush(stdout);
                    printf("입력대기상태입니다.\n");
                    fflush(stdout);
                    sleep(1);
                }

                if (shmem->checkin_1 && shmem->checkin_2 && shmem->checkin_3 && shmem->checkin_4) {
                    printf("모두 입력하였습니다.\n");
                    fflush(stdout);
                    break;
                }
            }
            break;
        }

        switch (choice) {
        case 'A': // 일반 공격
            printf("당신은 몬스터를 공격했습니다!!\n");
            fflush(stdout);
            shmem->boss_monster3.Monster_HP -= player->OP;
            break;
        case 'S': // 특수 공격
            printf("강력한 공격을 했습니다!\n");
            fflush(stdout);
            shmem->boss_monster3.Monster_HP -= (player->OP * 2);
            break;
        case 'D': // 방어
            printf("방어 상태입니다!\n");
            fflush(stdout);
            //player->health += player->defense;
            break;
        default:
            printf("잘못된 선택입니다!\n");
            continue;
        }

        sleep(2);
        // 몬스터의 반격
        if (shmem->boss_monster3.Monster_HP > 0) {
            random = rand() % 3 + 1;
            if (random == 1) {
                printf("보스몬스터가 당신을 공격합니다!\n");
                fflush(stdout);
                player->HP -= shmem->boss_monster3.Monster_OP;
            }
            else if (random == 2) {
                printf("보스몬스터가 강력한 공격을 합니다!\n");
                fflush(stdout);
                player->HP -= (shmem->boss_monster3.Monster_OP * 2);
            }
            else {
                printf("보스몬스터가 방어 상태입니다!\n");
                fflush(stdout);
                //monster->health += monster->defense;
            }
        }

        sleep(2);

        if (shmem->Host_HP <= 0) {
            break;
        }

        // 체력 상태 확인
        if (player->HP <= 0) {
            printf("패배\n");
            break;
        }

        if (shmem->boss_monster3.Monster_HP <= 0) {
            printf("Phase3 승리\n\n\n");
            shmem->boss_x = -1;
            shmem->boss_y = -1;
            break;
        }

    }
}