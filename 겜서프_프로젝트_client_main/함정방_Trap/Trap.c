#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void trap(int player)
{
    int pid1, pid2, pid3, pid4;
    int wpid, status;
    switch(player)//플레이어 수만큼 분배
    {
        case 1:
            pid1 = fork(); //자식 프로세스 생성
            if(pid1 == 0)
            {
                switch (getpid() % 4) //pid번호로 함정방 랜덤하게 배치
                {
                    case 0 :
                        execlp("Maze1", "Maze1", NULL);
                        break;
                    case 1 :
                        execlp("Maze2", "Maze2", NULL);
                        break;
                    case 2 :
                        execlp("Maze3", "Maze3", NULL);
                        break;
                    case 3 :
                        execlp("Maze4", "Maze4", NULL);
                            break;
                }
                exit(1);
            }
            while ((wpid = wait(&status)) > 0); //자식 프로세의 종료를 기다린다
        case 2:
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
        case 3:
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
        case 4:
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
    }
    return;
}