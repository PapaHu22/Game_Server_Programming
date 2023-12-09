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
        printf("%s\n", MONSTER_ART); // ���� �ƽ�Ű ��Ʈ ���
        printf("����� ü��: %d, ���� ü��: %d\n", player->HP, shmem->monster.Monster_HP);
        printf("����(A), Ư�� ����(S),  ���(D): ");
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
        case 'A': // �Ϲ� ����
            printf("�÷��̾� ����!\n");
            shmem->monster.Monster_HP -= player->OP;
            break;
        case 'S': // Ư�� ����
            printf("Ư�� ����!\n");
            shmem->monster.Monster_HP -= (player->OP * 2);
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
        if (shmem->monster.Monster_HP > 0) {
            printf("������ ����\n");
            player->HP -= shmem->monster.Monster_OP;
        }

        // ȣ��Ʈ �ٿ�
        if (shmem->Host_HP <= 0) {
            break;
        }


        //  ü�� ���� Ȯ��
        if (player->HP <= 0) {
            printf("����� �й��߽��ϴ�\n");
            break;
        }

        if (shmem->monster.Monster_HP <= 0) {
            printf("-���͸� �����ƽ��ϴ�\n");
            shmem->party.Party_Coin += 100;
            break;
        }
    }
}
