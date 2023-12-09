#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#define MAP_WIDTH 50
#define MAP_HEIGHT 20
#define ASCII_ART_SIZE 256 // 아스키 아트 배열 크기 정의

// 게임 맵 표시에 사용되는 문자들
#define PLAYER_ICON '#'
#define MONSTER_ICON '&'
#define MONSTER_ART "  /\\_/\\\n ( o.o )\n  > ^ <" //몬스터 아스키 아트

typedef struct Player_Class {
    int class_HP; // 직업 체력
    int class_OP; // 직업 공격력
}Class; // 직업(클래스) 정보

// 플레이어 위치를 저장하기 위한 구조체
typedef struct Player {
    Class class; //직업
    int HP; // 체력
    int OP; // 공격력

} Player;

typedef struct Monster {
    int x;
    int y;
    int Monster_HP; // 몬스터 체력
    int Monster_OP; // 몬스터 공격력
    char ascii_art[ASCII_ART_SIZE]; // 아스키 아트를 위한 배열
} Monster;

typedef struct Party {
    int x;
    int y;
    int Party_Coin; // 파티 돈
    int Party_OP_buff; // 파티 공격력
    int Party_HP_buff; // 파티 체력 버프
}Party;

typedef struct BossMonster {
    int Monster_HP; // 몬스터 체력
    int Monster_OP; // 몬스터 공격력
} BossMonster;

typedef struct ShMEM {
    bool game_ready; //
    bool field_ready;
    bool boss_ready;
    char input;
    struct Monster monster; // 몬스터 정보
    int Host_HP; // 호스트 체력(호스트 체력이 0이 되면 게임오버)
    int Cr_room; // 현재 방 위치
    int User_num; // 유저수
    struct Party party; // 파티 정보
    int boss_phase2_HP; // 보스 2페이즈 체력 
    int sum_boss_phase2_HP; //모든 보스분신  2페이즈체력 합 
    bool checkin_1; // 입력 대기 체크
    bool checkin_2;
    bool checkin_3;
    bool checkin_4;
    bool maze_checkin_1;
    bool maze_checkin_2;
    bool maze_checkin_3;
    bool maze_checkin_4;
    bool shoping_wait;
    int Potion;
    int OP_UP;
    int MAX_HP_UP;
    int boss_x;
    int boss_y;
    struct BossMonster boss_monster; // 몬스터 정보
    struct BossMonster boss_monster2; //phase2 boss_monster
    struct BossMonster boss_monster3; //phase3 boss_monster
}ShMEM;

// 함수 프로토타입 선언
void draw_line();
void field_map(Player* player, int you);
void boss_map(Player* player, int you);
void draw_map(char map[MAP_HEIGHT][MAP_WIDTH]);
void draw_move(char input, char map[MAP_HEIGHT][MAP_WIDTH]);
void draw_attack(Player* player, Monster* monster);
void initialize_map(char map[MAP_HEIGHT][MAP_WIDTH]);
ShMEM* shm_get();
#endif
