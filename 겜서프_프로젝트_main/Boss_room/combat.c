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
void start_combat(Player* player, int you) {
    ShMEM* shmem = shm_get();//���� ���� �ƽ�Ű��Ʈ �κ� ����
    int random = 0;

    while (shmem->Monster_HP > 0 && player->health > 0) {
        printf("  /\\_/\\\n ( T.T )\n  [ ^ ]\n");
        fflush(stdout);
        //"  /\\_/\\\n ( ^.^ )\n  < ^ >"        
        //"  /\\_/\\\n ( poq )\n *< ^ >*"

        ClearLineFromReadBuffer();
        sleep(3);
        shmem->checkin_1 = false;
        shmem->checkin_2 = false;



        printf("����� HP: %d, �������� HP: %d\n", player->health, shmem->Monster_HP);
        fflush(stdout);

        printf("Attack (A), Special Attack (S),  Defend (D): ");
        fflush(stdout);




        sleep(5);
        char choice;

        switch (shmem->User_num) {
        case 1:
            scanf(" %c", &choice, 1);
            break;
        case 2:
            while (true) {
                if (you == 1 && !shmem->checkin_1) {
                    scanf(" %c", &choice, 1);
                    shmem->checkin_1 = true;
                }
                else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                    scanf(" %c", &choice, 1);
                    shmem->checkin_2 = true;
                }
                else {
                    printf("����� HP: %d, �������� HP: %d\n", player->health, shmem->Monster_HP);
                    fflush(stdout);
                    printf("�Է� ��� �����Դϴ�.\n");
                    fflush(stdout);
                    sleep(1);
                    system("clear");
                }
                if (shmem->checkin_1 && shmem->checkin_2) {
                    printf("��� �Է��Ͽ����ϴ�.");
                    fflush(stdout);


                    break;
                }
            }


            break;
        }

        switch (choice) {
        case 'A': // �Ϲ� ����
            printf("����� �������͸� �����߽��ϴ�!\n");
             while (true) {
                    if (you == 1 && !shmem->checkin_1) {
                        scanf(" %c", &choice, 1);
                        shmem->checkin_1 = true;
                    }
                    else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                        scanf(" %c", &choice, 1);
                        shmem->checkin_2 = true;
                }
                else{
                printf("����� HP: %d, �������� HP: %d\n", player->health, shmem->Monster_HP);
                fflush(stdout);
                printf("�Է� ��� �����Դϴ�.\n");
                fflush(stdout);
                sleep(1);
                system("clear");
                }
                    if (shmem->checkin_1 && shmem->checkin_2) {
                        printf("��� �Է��Ͽ����ϴ�.");
                        fflush(stdout);


                        break;
                    }
                }


            break;
        }

        switch (choice) {
        case 'A': // �Ϲ� ����
            printf("����� �������͸� �����߽��ϴ�!\n");
            shmem->Monster_HP -= player->attack;

            break;
        case 'S': // Ư�� ����
            printf("������ ������ �߽��ϴ�!\n");
            shmem->Monster_HP -= (player->attack * 2);
            break;
        case 'D': // ���
            printf("��� �����Դϴ�!\n");
            //player->health += player->defense;
            break;
        default:
            printf("�߸��� �����Դϴ�!\n");
            continue;
        }

        sleep(3);
        // ������ �ݰ�
        if (shmem->Monster_HP > 0) {

            random = rand() % 3 + 1;
            if (random == 1) {
                printf("�������Ͱ� ����� �����մϴ�!\n");
                player->health -= shmem->Monster_OP;
            }
            else if (random == 2) {
                printf("�������Ͱ� ������ ������ �մϴ�!\n");
                player->health -= (shmem->Monster_OP * 2);
            }
            else {
                printf("�������ʹ� ��� �����Դϴ�!\n");
                //monster->health += monster->defense;
            }
        }


        }

        // ü�� ���� Ȯ��
        if (player->health <= 0) {
            printf("�й�\n");
            break;
        }

        if (shmem->Monster_HP <= 0) {
            printf("Phase1 �¸�\n\n\n");
            shmem->x = -1;
            shmem->y = -1;
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



void start_combat2(Player* player, int you) {
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

    while (shmem->Monster_HP <= 0 && player->health > 0 && t) {
        printf("  /\\_/\\\n ( ^.^ )\n  < ^ >\n");
        fflush(stdout);
        //printf("���� �ð� 10�� ���� ���� ������ �н��� ������ �� �ֽ��ϴ�. ������ �н��� �����߸��°� ���� �̴ϴ�.");
    //sleep(1);
    //printf("%d�� ��� \n", ++sec);

        printf("����� HP: %d, �������� �н��� HP: %d\n", player->health, monster2.Monster_HP);
        printf("Attack (A), Special Attack (S),  Defend (D): ");

        shmem->sum_boss_phase2_HP = (400 - (100 - monster2.Monster_HP));
        char choice;
        scanf(" %c", &choice, 1);

        if (t != 0) {
            switch (choice) {
            case 'A': // �Ϲ� ����
                printf("����� ���������� �н��� �����߽��ϴ�!\n");
                monster2.Monster_HP -= player->attack;
                break;
            case 'S': // Ư�� ����
                printf("������ ������ �߽��ϴ�!\n");
                monster2.Monster_HP -= (player->attack * 2);
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
                    player->health -= monster2.Monster_HP;
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
        // ü�� ���� Ȯ��
        if (player->health <= 0) {
            printf("�й�\n");
            alarm(0);
            break;
        }

        if (monster2.Monster_HP <= 0) {
            printf("Phase2 �¸�\n\n\n");
            shmem->x = -1;
            shmem->y = -1;
            alarm(0);
            break;
        }

    }

}


void start_combat3(Player* player, int you) {
    ShMEM* shmem = shm_get();
    int random = 0;
    while (shmem->Monster3_HP > 0 && player->health > 0) {
        //      "  /\\_/\\\n ( ^.^ )\n  < ^ >"      
        printf("  /\\_/\\\n ( poq )\n *< ^ >*\n");
        fflush(stdout);
        ClearLineFromReadBuffer();
        sleep(3);
        shmem->checkin_1 = false;
        shmem->checkin_2 = false;



        printf("����� HP: %d, �������� HP: %d\n", player->health, shmem->Monster3_HP);
        fflush(stdout);
        printf("Attack (A), Special Attack (S),  Defend (D): ");
        fflush(stdout);




        sleep(5);
        char choice;

        switch (shmem->User_num) {
        case 1:
            scanf(" %c", &choice, 1);
            break;
        case 2:
            while (true) {
                if (you == 1 && !shmem->checkin_1) {
                    scanf(" %c", &choice, 1);
                    shmem->checkin_1 = true;
                }
                else if (you == 2 && shmem->checkin_1 && !shmem->checkin_2) {
                    scanf(" %c", &choice, 1);
                    shmem->checkin_2 = true;
                }
                else {
                    printf("����� HP: %d, �������� HP: %d\n", player->health, shmem->Monster3_HP);
                    fflush(stdout);
                    printf("�Է� ��� �����Դϴ�.\n");
                    fflush(stdout);
                    sleep(1);
                    system("clear");
                }
                if (shmem->checkin_1 && shmem->checkin_2) {
                    printf("��� �Է��Ͽ����ϴ�.");
                    fflush(stdout);


                    break;
                }
            }


            break;
        }

        switch (choice) {
        case 'A': // �Ϲ� ����
            printf("����� ���͸� �����߽��ϴ�!!\n");
            shmem->Monster3_HP -= player->attack;
            break;
        case 'S': // Ư�� ����
            printf("������ ������ �߽��ϴ�!\n");
            shmem->Monster3_HP -= (player->attack * 2);
            break;
        case 'D': // ���
            printf("��� �����Դϴ�!\n");
            //player->health += player->defense;
            break;
        default:
            printf("�߸��� �����Դϴ�!\n");
            continue;
        }

        sleep(3);
        // ������ �ݰ�
        if (shmem->Monster3_HP > 0) {
            random = rand() % 3 + 1;
            if (random == 1) {
                printf("�������Ͱ� ����� �����մϴ�!\n");
                player->health -= shmem->Monster3_OP;
            }
            else if (random == 2) {
                printf("�������Ͱ� ������ ������ �մϴ�!\n");
                player->health -= (shmem->Monster3_OP * 2);
            }
            else {
                printf("�������Ͱ� ��� �����Դϴ�!\n");
                //monster->health += monster->defense;
            }
        }

    }
}
