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
        printf("%s\n", MONSTER_ART); // ���� �ƽ�Ű ��Ʈ ���
        fflush(stdout);
        printf("����� ü��: %d, ���� ü��: %d\n", player->HP, shmem->monster.Monster_HP);
        fflush(stdout);
        char choice;

     
        switch (shmem->User_num) {
        case 1:
            printf("����(A), Ư�� ����(S),  ���(D): ");
            scanf(" %c", &choice, 1);
            break;
        case 2:
            while (true) {
                if (you == 1 && !shmem->checkin_1) {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_1 = true;
                }
                else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_2 = true;
                }
                else {
                    system("clear");
                    printf("����� ü��: %d, ���� ü��: %d\n", player->HP, shmem->monster.Monster_HP);
                    fflush(stdout);
                    printf("�Է´������Դϴ�.\n");
                    fflush(stdout);
                    sleep(1);
                }

                if (shmem->checkin_1 && shmem->checkin_2) {
                    printf("��� �Է��Ͽ����ϴ�.\n");
                    fflush(stdout);
                    break;
                }
            }
            break;
        case 3:
            while (true) {
                if (you == 1 && !shmem->checkin_1) {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_1 = true;
                }
                else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_2 = true;
                }
                else if (you == 3 && shmem->checkin_2 && !shmem->checkin_3)
                {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_3 = true;
                }
                else {
                    system("clear");
                    printf("����� ü��: %d, ���� ü��: %d\n", player->HP, shmem->monster.Monster_HP);
                    fflush(stdout);
                    printf("�Է´������Դϴ�.\n");
                    fflush(stdout);
                    sleep(1);
                }

                if (shmem->checkin_1 && shmem->checkin_2 && shmem->checkin_3) {
                    printf("��� �Է��Ͽ����ϴ�.\n");
                    fflush(stdout);
                    break;
                }
            }
            break;
        case 4:
            while (true) {
                if (you == 1 && !shmem->checkin_1) {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_1 = true;
                }
                else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_2 = true;
                }
                else if (you == 3 && shmem->checkin_2 && !shmem->checkin_3)
                {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_3 = true;
                }
                else if (you == 4 && shmem->checkin_3 && !shmem->checkin_4) {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_4 = true;
                }
                else {
                    system("clear");
                    printf("����� ü��: %d, ���� ü��: %d\n", player->HP, shmem->monster.Monster_HP);
                    fflush(stdout);
                    printf("�Է´������Դϴ�.\n");
                    fflush(stdout);
                    sleep(1);
                }

                if (shmem->checkin_1 && shmem->checkin_2 && shmem->checkin_3 && shmem->checkin_4) {
                    printf("��� �Է��Ͽ����ϴ�.\n");
                    fflush(stdout);
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

        sleep(2);

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

void boss_combat(Player* player, int you) {
    ShMEM* shmem = shm_get();//���� ���� �ƽ�Ű��Ʈ �κ� ����
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


        printf("����� HP: %d, �������� HP: %d\n", player->HP, shmem->boss_monster.Monster_HP);
        fflush(stdout);

        char choice;


        switch (shmem->User_num) {
        case 1:
            printf("����(A), Ư�� ����(S),  ���(D): ");
            scanf(" %c", &choice, 1);
            break;
        case 2:
            while (true) {
                if (you == 1 && !shmem->checkin_1) {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_1 = true;
                }
                else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_2 = true;
                }
                else {
                    system("clear");
                    printf("����� HP: %d, �������� HP: %d\n", player->HP, shmem->boss_monster.Monster_HP);
                    fflush(stdout);
                    printf("�Է´������Դϴ�.\n");
                    fflush(stdout);
                    sleep(1);
                }

                if (shmem->checkin_1 && shmem->checkin_2) {
                    printf("��� �Է��Ͽ����ϴ�.\n");
                    fflush(stdout);
                    break;
                }
            }
            break;
        case 3:
            while (true) {
                if (you == 1 && !shmem->checkin_1) {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_1 = true;
                }
                else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_2 = true;
                }
                else if (you == 3 && shmem->checkin_2 && !shmem->checkin_3)
                {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_3 = true;
                }
                else {
                    system("clear");
                    printf("����� HP: %d, �������� HP: %d\n", player->HP, shmem->boss_monster.Monster_HP);
                    fflush(stdout);
                    printf("�Է´������Դϴ�.\n");
                    fflush(stdout);
                    sleep(1);
                }

                if (shmem->checkin_1 && shmem->checkin_2 && shmem->checkin_3) {
                    printf("��� �Է��Ͽ����ϴ�.\n");
                    fflush(stdout);
                    break;
                }
            }
            break;
        case 4:
            while (true) {
                if (you == 1 && !shmem->checkin_1) {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_1 = true;
                }
                else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_2 = true;
                }
                else if (you == 3 && shmem->checkin_2 && !shmem->checkin_3)
                {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_3 = true;
                }
                else if (you == 4 && shmem->checkin_3 && !shmem->checkin_4) {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_4 = true;
                }
                else {
                    system("clear");
                    printf("����� HP: %d, �������� HP: %d\n", player->HP, shmem->boss_monster.Monster_HP);
                    fflush(stdout);
                    printf("�Է´������Դϴ�.\n");
                    fflush(stdout);
                    sleep(1);
                }

                if (shmem->checkin_1 && shmem->checkin_2 && shmem->checkin_3 && shmem->checkin_4) {
                    printf("��� �Է��Ͽ����ϴ�.\n");
                    fflush(stdout);
                    break;
                }
            }
            break;
        }



        switch (choice) {
        case 'A': // �Ϲ� ����
            printf("����� �������͸� �����߽��ϴ�!\n");
            shmem->boss_monster.Monster_HP -= player->OP;

            break;
        case 'S': // Ư�� ����
            printf("������ ������ �߽��ϴ�!\n");
            shmem->boss_monster.Monster_HP -= (player->OP * 2);
            break;
        case 'D': // ���
            printf("��� �����Դϴ�!\n");
            //player->health += player->defense;
            break;
        default:
            printf("�߸��� �����Դϴ�!\n");
            continue;
        }

        sleep(2);
        // ������ �ݰ�
        if (shmem->boss_monster.Monster_HP > 0) {

            random = rand() % 3 + 1;
            if (random == 1) {
                printf("�������Ͱ� ����� �����մϴ�!\n");
                player->HP -= shmem->boss_monster.Monster_OP;
            }
            else if (random == 2) {
                printf("�������Ͱ� ������ ������ �մϴ�!\n");
                player->HP -= (shmem->boss_monster.Monster_OP * 2);
            }
            else {
                printf("�������ʹ� ��� �����Դϴ�!\n");
                //monster->health += monster->defense;
            }
        }

        sleep(2);

        if (shmem->Host_HP <= 0) {
            break;
        }

        // ü�� ���� Ȯ��
        if (player->HP <= 0) {
            printf("�й�\n");
            break;
        }

        if (shmem->boss_monster.Monster_HP <= 0) {
            printf("Phase1 �¸�\n\n\n");
            shmem->boss_x = -1;
            shmem->boss_y = -1;
            break;
        }
    }
}

int t = 1;

void handler(int signo) {
    t = 0;

    printf("10�� ��!!!\n");
    printf("�ƹ� Ű�� �Է��Ͻø� phase3�� �Ѿ�ϴ�.\n");
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
    printf("���� �ð� 10�� ���� ���� ������ �н��� ������ �� �ֽ��ϴ�. ������ �н��� �����߸��°� �����ϴ�.\n");
    fflush(stdout);

    while (monster2.Monster_HP >= 0 && player->HP > 0 && t) {
        printf("  /\\_/\\\n ( ^.^ )\n  < ^ >\n");
        fflush(stdout);
        //printf("���� �ð� 10�� ���� ���� ������ �н��� ������ �� �ֽ��ϴ�. ������ �н��� �����߸��°� ���� �̴ϴ�.");
    //sleep(1);
    //printf("%d�� ��� \n", ++sec);

        printf("����� HP: %d, �������� �н��� HP: %d\n", player->HP, monster2.Monster_HP);
        printf("Attack (A), Special Attack (S),  Defend (D): ");

        shmem->sum_boss_phase2_HP = (100 * shmem->User_num - (100 - monster2.Monster_HP));
        char choice;
        scanf(" %c", &choice, 1);

        if (t != 0) {
            switch (choice) {
            case 'A': // �Ϲ� ����
                printf("����� ���������� �н��� �����߽��ϴ�!\n");
                monster2.Monster_HP -= player->OP;
                break;
            case 'S': // Ư�� ����
                printf("������ ������ �߽��ϴ�!\n");
                monster2.Monster_HP -= (player->OP * 2);
                break;
            case 'D': // ���
                printf("��� �����Դϴ�!\n");
                //player->health += player->defense;
                break;
            default:
                printf("�߸��� �����Դϴ�!\n");
                continue;
            }

            // ������ �ݰ�
            if (monster2.Monster_HP > 0) {
                random = rand() % 3 + 1;
                if (random == 1) {
                    printf("�������Ͱ� ����� �����մϴ�!\n");
                    player->HP -= monster2.Monster_HP;
                }
                else if (random == 2) {
                    printf("�������ʹ� ��� �����Դϴ�.\n");
                    //monster->health += monster->defense;
                }
                /*else {
                    printf("���������� ���\n");
                    monster->health += monster->defense;
                }*/
            }
        }

        if (shmem->Host_HP <= 0) {
            break;
        }


        // ü�� ���� Ȯ��
        if (player->HP <= 0) {
            printf("�й�\n");
            alarm(0);
            break;
        }

        if (monster2.Monster_HP <= 0) {
            printf("Phase2 �¸�\n\n\n");
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



        printf("����� HP: %d, �������� HP: %d\n", player->HP, shmem->boss_monster3.Monster_HP);
        fflush(stdout);


        char choice;

        switch (shmem->User_num) {
        case 1:
            printf("����(A), Ư�� ����(S),  ���(D): ");
            scanf(" %c", &choice, 1);
            break;
        case 2:
            while (true) {
                if (you == 1 && !shmem->checkin_1) {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_1 = true;
                }
                else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_2 = true;
                }
                else {
                    system("clear");
                    printf("����� HP: %d, �������� HP: %d\n", player->HP, shmem->boss_monster3.Monster_HP);
                    fflush(stdout);
                    printf("�Է´������Դϴ�.\n");
                    fflush(stdout);
                    sleep(1);
                }

                if (shmem->checkin_1 && shmem->checkin_2) {
                    printf("��� �Է��Ͽ����ϴ�.\n");
                    fflush(stdout);
                    break;
                }
            }
            break;
        case 3:
            while (true) {
                if (you == 1 && !shmem->checkin_1) {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_1 = true;
                }
                else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_2 = true;
                }
                else if (you == 3 && shmem->checkin_2 && !shmem->checkin_3)
                {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_3 = true;
                }
                else {
                    system("clear");
                    printf("����� HP: %d, �������� HP: %d\n", player->HP, shmem->boss_monster3.Monster_HP);
                    fflush(stdout);
                    printf("�Է´������Դϴ�.\n");
                    fflush(stdout);
                    sleep(1);
                }

                if (shmem->checkin_1 && shmem->checkin_2 && shmem->checkin_3) {
                    printf("��� �Է��Ͽ����ϴ�.\n");
                    fflush(stdout);
                    break;
                }
            }
            break;
        case 4:
            while (true) {
                if (you == 1 && !shmem->checkin_1) {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_1 = true;
                }
                else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_2 = true;
                }
                else if (you == 3 && shmem->checkin_2 && !shmem->checkin_3)
                {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_3 = true;
                }
                else if (you == 4 && shmem->checkin_3 && !shmem->checkin_4) {
                    printf("����(A), Ư�� ����(S),  ���(D): ");
                    fflush(stdout);
                    scanf(" %c", &choice, 1);
                    shmem->checkin_4 = true;
                }
                else {
                    system("clear");
                    printf("����� HP: %d, �������� HP: %d\n", player->HP, shmem->boss_monster3.Monster_HP);
                    fflush(stdout);
                    printf("�Է´������Դϴ�.\n");
                    fflush(stdout);
                    sleep(1);
                }

                if (shmem->checkin_1 && shmem->checkin_2 && shmem->checkin_3 && shmem->checkin_4) {
                    printf("��� �Է��Ͽ����ϴ�.\n");
                    fflush(stdout);
                    break;
                }
            }
            break;
        }

        switch (choice) {
        case 'A': // �Ϲ� ����
            printf("����� ���͸� �����߽��ϴ�!!\n");
            fflush(stdout);
            shmem->boss_monster3.Monster_HP -= player->OP;
            break;
        case 'S': // Ư�� ����
            printf("������ ������ �߽��ϴ�!\n");
            fflush(stdout);
            shmem->boss_monster3.Monster_HP -= (player->OP * 2);
            break;
        case 'D': // ���
            printf("��� �����Դϴ�!\n");
            fflush(stdout);
            //player->health += player->defense;
            break;
        default:
            printf("�߸��� �����Դϴ�!\n");
            continue;
        }

        sleep(2);
        // ������ �ݰ�
        if (shmem->boss_monster3.Monster_HP > 0) {
            random = rand() % 3 + 1;
            if (random == 1) {
                printf("�������Ͱ� ����� �����մϴ�!\n");
                fflush(stdout);
                player->HP -= shmem->boss_monster3.Monster_OP;
            }
            else if (random == 2) {
                printf("�������Ͱ� ������ ������ �մϴ�!\n");
                fflush(stdout);
                player->HP -= (shmem->boss_monster3.Monster_OP * 2);
            }
            else {
                printf("�������Ͱ� ��� �����Դϴ�!\n");
                fflush(stdout);
                //monster->health += monster->defense;
            }
        }

        sleep(2);

        if (shmem->Host_HP <= 0) {
            break;
        }

        // ü�� ���� Ȯ��
        if (player->HP <= 0) {
            printf("�й�\n");
            break;
        }

        if (shmem->boss_monster3.Monster_HP <= 0) {
            printf("Phase3 �¸�\n\n\n");
            shmem->boss_x = -1;
            shmem->boss_y = -1;
            break;
        }

    }
}