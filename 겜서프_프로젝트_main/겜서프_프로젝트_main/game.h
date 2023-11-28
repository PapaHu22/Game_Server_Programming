#ifndef GAME_H
#define GAME_H

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
    int x;
    int y;
    Class class; //직업
    int HP; // 체력
    int OP; // 공격력
    int Money; // 돈
} Player;

typedef struct Monster {
    int x;
    int y;
    int Monster_HP; // 몬스터 체력
    int Monster_OP; // 몬스터 공격력
    char ascii_art[ASCII_ART_SIZE]; // 아스키 아트를 위한 배열
} Monster;

typedef struct Party {
    int Party_Coin; // 파티 돈
    int Party_OP_buff; // 파티 공격력
    int Party_HP_buff; // 파티 체력 버프
}Party;

// 함수 프로토타입 선언
void draw_line();
void draw_map(char map[MAP_HEIGHT][MAP_WIDTH]);
void draw_move(char input, Player* player, char map[MAP_HEIGHT][MAP_WIDTH], Monster* monster);
void draw_attack(Player* player, Monster* monster);
void initialize_map(char map[MAP_HEIGHT][MAP_WIDTH], Player* player);

#endif
