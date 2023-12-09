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


// phase2���� �� �����н� ü���� ������ŭ ��ü �н�ü���� ��´�. �׸��� phase3 ������ ü�µ� �� ��´�. �˶� ����� �־ phase2���� ���� �ð��ȿ� ��>�� �н��� �� ��ġ��� ü���� ���� ��ŭ�� phase3����ü�¿� ������ �ش�.




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
    map[shmem->y][shmem->x] = BOSSMONSTER_ICON; // ���� ��ġ ǥ��

    while (1) {

        system("clear"); // ȭ�� Ŭ����
        printf("���� ��ġ: ������\n");
        draw_line();
        draw_map(map);
        draw_line();

        // ���� ���� ����
        bool isNearMonster = abs(player.x - shmem->x) <= 1 && abs(player.y - shmem->y) <= 1;

        if (!inCombat && isNearMonster) {
            inCombat = true;

            printf("Boss Phase1...\n");
            start_combat(&player, you); // ���� ����


            if (shmem->Monster_HP <= 0 && player.health > 0) {


                printf("Boss Phase2...\n");

                start_combat2(&player, you);


                if (player.health > 0) {

                    shmem->Monster3_HP -= (100 * shmem->User_num - shmem->sum_boss_phase2_HP);
                    printf("Boss Phase3...\n");
                    start_combat3(&player, you);
                    if (shmem->Monster3_HP <= 0 && player.health > 0) {

                        inCombat = false; // ���� ���� ����

                    }
                }
            }
            break;
        }
        else {
            printf("�̵� WASD, press E ��������, Q ����: ");
            scanf(" %c", &input, 1);
            switch (input) {
            case 'w': // ���� �̵�
            case 'a': // �������� �̵�
            case 's': // �Ʒ��� �̵�
            case 'd': // ���������� �̵�
                draw_move(input, &player, map, &monster1);
                break;
            case 'q': // ���� ����
                return 0;
            default:
                printf("���ۺҰ�!\n");
            }
        }
        /*_getch();*/
    }//while
    system("clear");
    if (player.health > 0) {
        printf("\n\n\n\n\n\n      ");

        printf("���� Ŭ����!");
    }

    else {
        printf("\n\n\n\n\n\n      ");
        printf("GAME OVER...");
    }


    return 0;
}

