#include "combat.h"
#include <stdio.h>

void start_combat(Player* player, Monster* monster) {
    while (monster->Monster_HP > 0 && player->HP > 0) {
        printf("%s\n", MONSTER_ART); // 몬스터 아스키 아트 출력
        printf("당신의 체력: %d, 몬스터 체력: %d\n", player->HP, monster->Monster_HP);
        printf("공격(A), 특수 공격(S),  방어(D): ");
        char choice;
        scanf_s(" %c", &choice, 1);

        switch (choice) {
        case 'A': // 일반 공격
            printf("플레이어 공격!\n");
            monster->Monster_HP -= player->OP;
            break;
        case 'S': // 특수 공격
            printf("특수 공격!\n");
            monster->Monster_HP -= (player->OP * 2);
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
        if (monster->Monster_HP > 0) {
            printf("몬스터의 공격\n");
            player->HP -= monster->Monster_OP;
        }

        // 체력 상태 확인
        if (player->HP <= 0) {
            printf("당신은 패배했습니다\n");
            break;
        }

        if (monster->Monster_HP <= 0) {
            printf("-몬스터를 물리쳤습니다\n");
            break;
        }
    }
}
