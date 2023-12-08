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
    ShMEM* shmem = shm_get();//���� ���� �ƽ�Ű��Ʈ �κ� ����
    int random = 0;
    while (shmem->Monster_HP > 0 && player->health > 0) {
        //printf("%s\n", monster1->boss_ascii_art); // ���� �ƽ�Ű >    ��Ʈ ���

        printf("����� HP: %d, �������� HP: %d\n", player->health, s    hmem->Monster_HP);
        printf("Attack (A), Special Attack (S),  Defend (D): ");
        char choice;
        scanf(" %c", &choice, 1);

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



void start_combat2(Player* player) {
    ShMEM* shmem = shm_get();
    int random = 0;
    //printf("�ڽ� ���μ����÷��̾� %d ȭ��\n", process_num);

    while (shmem->Monster_HP > 0 && player->health > 0) {
        //printf("�ڽ� ���μ��� �÷��̾� %d ȭ��\n",process_num);
            //printf("%s\n", monster2->boss_ascii_art); // ���� �ƽ�Ű >    ��Ʈ ���

        printf("����� HP: %d, ���������� HP: %d\n", player->health, shmem->Monster_HP);
        printf("Attack (A), Special Attack (S),  Defend (D): ");
        char choice;
        scanf(" %c", &choice, 1);

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

        // ������ �ݰ�
        if (shmem->Monster_HP > 0) {
            random = rand() % 3 + 1;
            if (random == 1) {
                printf("�������Ͱ� ����� �����մϴ�!\n");
                player->health -= shmem->Monster_OP;

            }
            else if (random == 2) {
                printf("�������ʹ� ��� �����Դϴ�.\n");


            }


        }

        // ü�� ���� Ȯ��
        if (player->health <= 0) {
            printf("�й�\n");
            break;

        }

        if (shmem->Monster_HP <= 0) {
            printf("Phase2 �¸�\n\n\n");
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
        //printf("%s\n", monster3->boss_ascii_art); // ���� �ƽ�Ű >    ��Ʈ ���

        printf("����� HP: %d, ���������� HP: %d\n", player->health, shmem->Monster_HP);
        printf("Attack (A), Special Attack (S),  Defend (D): ");
        char choice;
        scanf(" %c", &choice, 1);

        switch (choice) {
        case 'A': // �Ϲ� ����
            printf("����� ���͸� �����߽��ϴ�!!\n");
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
                printf("�������Ͱ� ��� �����Դϴ�!\n");


            }

        }


    }

}
