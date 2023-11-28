#include "combat.h"
#include <stdio.h>

void start_combat(Player* player, Monster* monster) {
    while (monster->Monster_HP > 0 && player->HP > 0) {
        printf("%s\n", MONSTER_ART); // ���� �ƽ�Ű ��Ʈ ���
        printf("����� ü��: %d, ���� ü��: %d\n", player->HP, monster->Monster_HP);
        printf("����(A), Ư�� ����(S),  ���(D): ");
        char choice;
        scanf_s(" %c", &choice, 1);

        switch (choice) {
        case 'A': // �Ϲ� ����
            printf("�÷��̾� ����!\n");
            monster->Monster_HP -= player->OP;
            break;
        case 'S': // Ư�� ����
            printf("Ư�� ����!\n");
            monster->Monster_HP -= (player->OP * 2);
            break;
        case 'D': // ���
            printf("���!\n");
            //player->HP += player->defense;
            break;
        default:
            printf("���ۺҰ�!\n");
            continue;
        }

        // ������ �ݰ�
        if (monster->Monster_HP > 0) {
            printf("������ ����\n");
            player->HP -= monster->Monster_OP;
        }

        // ü�� ���� Ȯ��
        if (player->HP <= 0) {
            printf("����� �й��߽��ϴ�\n");
            break;
        }

        if (monster->Monster_HP <= 0) {
            printf("-���͸� �����ƽ��ϴ�\n");
            break;
        }
    }
}
