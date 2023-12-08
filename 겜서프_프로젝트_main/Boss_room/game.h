#ifndef GAME_H
#define GAME_H

#define MAP_WIDTH 50
#define MAP_HEIGHT 20
#define ASCII_ART_SIZE 256 // 아스키 아트 배열 크기 정의

// 게임 맵 표시에 사용되는 문자들
#define PLAYER_ICON '#'
#define BOSSMONSTER_ICON '&'
#define BOSSMONSTER_ART1 "  /\\_/\\\n ( T.T )\n  [ ^ ]"
#define BOSSMONSTER_ART2 "  /\\_/\\\n ( ^.^ )\n  < ^ >"
#define BOSSMONSTER_ART3 "  /\\_/\\\n ( poq )\n *< ^ >*" 

// 플레이어 위치를 저장하기 위한 구조체
typedef struct {
    int x;
    int y;
    int health;
    int attack;
    int defense;
} Player;

typedef struct BossMonster {
    int x;
    int y;
    int Monster_HP; // 몬스터 체력
    int Monster_OP; // 몬스터 공격력
    char boss_ascii_art[ASCII_ART_SIZE]; // 아스키 아트를 위한 배열
} BossMonster;

typedef struct Party {
    int x;
    int y;
    int Party_Coin; // 파티 돈
    int Party_OP_buff; // 파티 공격력
    int Party_HP_buff; // 파티 체력 버프
} Party;

typedef struct ShMEM {
    struct BossMonster boss_monster; // 몬스터 정보
    struct BossMonster boss_monster2; //phase2 boss_monster
    struct BossMonster boss_monster3; //phase3 boss_monster
    int Host_HP; // 호스트 체력(호스트 체력이 0이 되면 게임오버)
    int Cr_room; // 현재 방 위치
    int x;
    int y;
    int Monster_HP; // 몬스터 체력
    int Monster_OP; // 몬스터 공격력
    char boss_ascii_art[ASCII_ART_SIZE];
    int User_num; // 유저수
    struct Party party; // 파티 정보
    int boss_phase2_HP; // 보스 2페이즈 체력
    int sum_boss_phase2_HP; //모든 보스분신  2페이즈체력 합 
} ShMEM;

// 함수 프로토타입 선언
void draw_line();
void draw_map(char map[MAP_HEIGHT][MAP_WIDTH]);
void draw_move(char input, Player* player, char map[MAP_HEIGHT][MAP_WIDTH], BossMonster* monster);
void draw_attack(Player* player, BossMonster* monster);
void initialize_map(char map[MAP_HEIGHT][MAP_WIDTH], Player* player);

#endif
