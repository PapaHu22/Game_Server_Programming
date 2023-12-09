#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "game.h"

void trap(int you)
{
    ShMEM* shmem = shm_get();
    int pid1, pid2, pid3, pid4;
    int wpid, status;
    switch (shmem->User_num)//플레이어 수만큼 분배
    {
    case 1:
        pid1 = fork(); //자식 프로세스 생성
        if (pid1 == 0)
        {
            switch (getpid() % 4) //pid번호로 함정방 랜덤하게 배치
            {
            case 0:
                execlp("Maze1", "Maze1", NULL);
                break;
            case 1:
                execlp("Maze2", "Maze2", NULL);
                break;
            case 2:
                execlp("Maze3", "Maze3", NULL);
                break;
            case 3:
                execlp("Maze4", "Maze4", NULL);
                break;
            }
            exit(1);
        }
        while ((wpid = wait(&status)) > 0); //자식 프로세의 종료를 기다린다
        break;
    case 2:
        shmem->maze_checkin_1 = false;
        shmem->maze_checkin_2 = false;
        if (you == 1) {
            pid1 = fork();
            if (pid1 == 0)
            {
                switch (getpid() % 4) //pid번호로 함정방 랜덤하게 배치
                {
                case 0:
                    execlp("Maze1", "Maze1", NULL);
                    break;
                case 1:
                    execlp("Maze2", "Maze2", NULL);
                    break;
                case 2:
                    execlp("Maze3", "Maze3", NULL);
                    break;
                case 3:
                    execlp("Maze4", "Maze4", NULL);
                    break;
                }
                exit(1);
            }
            while ((wpid = wait(&status)) > 0); //자식 프로세의 종료를 기다린다
            shmem->maze_checkin_1 = true;
        }
        else if (you == 2) {
            pid2 = fork();
            if (pid2 == 0)
            {
                switch (getpid() % 4) //pid번호로 함정방 랜덤하게 배치
                {
                case 0:
                    execlp("Maze1", "Maze1", NULL);
                    break;
                case 1:
                    execlp("Maze2", "Maze2", NULL);
                    break;
                case 2:
                    execlp("Maze3", "Maze3", NULL);
                    break;
                case 3:
                    execlp("Maze4", "Maze4", NULL);
                    break;
                }
                exit(2);
            }
            while ((wpid = wait(&status)) > 0); //자식 프로세의 종료를 기다린다
            shmem->maze_checkin_2 = true;
        }

        while (1) {
            if (shmem->maze_checkin_1 && shmem->maze_checkin_2) {
                printf("전원 탈출 완료");
                break;
            }
            else {
                cls("clear");
                printf("모든 파티원이 함정방에서 탈출하는걸 대기합니다.\n");
            }
        }

        break;

    case 3:
        shmem->maze_checkin_1 = false;
        shmem->maze_checkin_2 = false;
        shmem->maze_checkin_3 = false;
        if (you == 1) {
            pid1 = fork();
            if (pid1 == 0)
            {
                switch (getpid() % 4) //pid번호로 함정방 랜덤하게 배치
                {
                case 0:
                    execlp("Maze1", "Maze1", NULL);
                    break;
                case 1:
                    execlp("Maze2", "Maze2", NULL);
                    break;
                case 2:
                    execlp("Maze3", "Maze3", NULL);
                    break;
                case 3:
                    execlp("Maze4", "Maze4", NULL);
                    break;
                }
                exit(1);
            }
            while ((wpid = wait(&status)) > 0); //자식 프로세의 종료를 기다린다
            shmem->maze_checkin_1 = true;
        }
        else if (you == 2) {
            pid2 = fork();
            if (pid2 == 0)
            {
                switch (getpid() % 4) //pid번호로 함정방 랜덤하게 배치
                {
                case 0:
                    execlp("Maze1", "Maze1", NULL);
                    break;
                case 1:
                    execlp("Maze2", "Maze2", NULL);
                    break;
                case 2:
                    execlp("Maze3", "Maze3", NULL);
                    break;
                case 3:
                    execlp("Maze4", "Maze4", NULL);
                    break;
                }
                exit(2);
            }
            while ((wpid = wait(&status)) > 0); //자식 프로세의 종료를 기다린다
            shmem->maze_checkin_2 = true;
        }
        else if (you == 3) {
            pid3 = fork();
            if (pid3 == 0)
            {
                switch (getpid() % 4) //pid번호로 함정방 랜덤하게 배치
                {
                case 0:
                    execlp("Maze1", "Maze1", NULL);
                    break;
                case 1:
                    execlp("Maze2", "Maze2", NULL);
                    break;
                case 2:
                    execlp("Maze3", "Maze3", NULL);
                    break;
                case 3:
                    execlp("Maze4", "Maze4", NULL);
                    break;
                }
                exit(3);
            }
            while ((wpid = wait(&status)) > 0); //자식 프로세의 종료를 기다린다
            shmem->maze_checkin_3 = true;
        }
        while (1) {
            if (shmem->maze_checkin_1 && shmem->maze_checkin_2 && shmem->maze_checkin_3) {
                printf("전원 탈출 완료");
                break;
            }
            else {
                cls("clear");
                printf("모든 파티원이 함정방에서 탈출하는걸 대기합니다.\n");
            }
        }

        break;
    case 4:
        shmem->maze_checkin_1 = false;
        shmem->maze_checkin_2 = false;
        shmem->maze_checkin_3 = false;
        shmem->maze_checkin_4 = false;
        if (you == 1) {
            pid1 = fork();
            if (pid1 == 0)
            {
                switch (getpid() % 4) //pid번호로 함정방 랜덤하게 배치
                {
                case 0:
                    execlp("Maze1", "Maze1", NULL);
                    break;
                case 1:
                    execlp("Maze2", "Maze2", NULL);
                    break;
                case 2:
                    execlp("Maze3", "Maze3", NULL);
                    break;
                case 3:
                    execlp("Maze4", "Maze4", NULL);
                    break;
                }
                exit(1);
            }
            while ((wpid = wait(&status)) > 0); //자식 프로세의 종료를 기다린다
            shmem->maze_checkin_1 = true;
        }
        else if (you == 2) {
            pid2 = fork();
            if (pid2 == 0)
            {
                switch (getpid() % 4) //pid번호로 함정방 랜덤하게 배치
                {
                case 0:
                    execlp("Maze1", "Maze1", NULL);
                    break;
                case 1:
                    execlp("Maze2", "Maze2", NULL);
                    break;
                case 2:
                    execlp("Maze3", "Maze3", NULL);
                    break;
                case 3:
                    execlp("Maze4", "Maze4", NULL);
                    break;
                }
                exit(2);
            }
            while ((wpid = wait(&status)) > 0); //자식 프로세의 종료를 기다린다
            shmem->maze_checkin_2 = true;
        }
        else if (you == 3) {
            pid3 = fork();
            if (pid3 == 0)
            {
                switch (getpid() % 4) //pid번호로 함정방 랜덤하게 배치
                {
                case 0:
                    execlp("Maze1", "Maze1", NULL);
                    break;
                case 1:
                    execlp("Maze2", "Maze2", NULL);
                    break;
                case 2:
                    execlp("Maze3", "Maze3", NULL);
                    break;
                case 3:
                    execlp("Maze4", "Maze4", NULL);
                    break;
                }
                exit(3);
            }
            while ((wpid = wait(&status)) > 0); //자식 프로세의 종료를 기다린다
            shmem->maze_checkin_3 = true;
        }
        else if (you == 4) {
            pid4 = fork();
            if (pid4 == 0)
            {
                switch (getpid() % 4) //pid번호로 함정방 랜덤하게 배치
                {
                case 0:
                    execlp("Maze1", "Maze1", NULL);
                    break;
                case 1:
                    execlp("Maze2", "Maze2", NULL);
                    break;
                case 2:
                    execlp("Maze3", "Maze3", NULL);
                    break;
                case 3:
                    execlp("Maze4", "Maze4", NULL);
                    break;
                }
                exit(4);
            }
            while ((wpid = wait(&status)) > 0); //자식 프로세의 종료를 기다린다
            shmem->maze_checkin_4 = true;
        }
        while (1) {
            if (shmem->maze_checkin_1 && shmem->maze_checkin_2 && shmem->maze_checkin_3 && shmem->maze_checkin_4) {
                printf("전원 탈출 완료");
                break;
            }
            else {
                cls("clear");
                printf("모든 파티원이 함정방에서 탈출하는걸 대기합니다.\n");
            }
        }

        break;

    }
    return;
}