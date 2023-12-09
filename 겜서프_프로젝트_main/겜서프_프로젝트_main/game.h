#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#define MAP_WIDTH 50
#define MAP_HEIGHT 20
#define ASCII_ART_SIZE 256 // �ƽ�Ű ��Ʈ �迭 ũ�� ����

// ���� �� ǥ�ÿ� ���Ǵ� ���ڵ�
#define PLAYER_ICON '#'
#define MONSTER_ICON '&'
#define MONSTER_ART "  /\\_/\\\n ( o.o )\n  > ^ <" //���� �ƽ�Ű ��Ʈ

typedef struct Player_Class {
    int class_HP; // ���� ü��
    int class_OP; // ���� ���ݷ�
}Class; // ����(Ŭ����) ����

// �÷��̾� ��ġ�� �����ϱ� ���� ����ü
typedef struct Player {
    Class class; //����
    int HP; // ü��
    int OP; // ���ݷ�

} Player;

typedef struct Monster {
    int x;
    int y;
    int Monster_HP; // ���� ü��
    int Monster_OP; // ���� ���ݷ�
    char ascii_art[ASCII_ART_SIZE]; // �ƽ�Ű ��Ʈ�� ���� �迭
} Monster;

typedef struct Party {
    int x;
    int y;
    int Party_Coin; // ��Ƽ ��
    int Party_OP_buff; // ��Ƽ ���ݷ�
    int Party_HP_buff; // ��Ƽ ü�� ����
}Party;

typedef struct BossMonster {
    int Monster_HP; // ���� ü��
    int Monster_OP; // ���� ���ݷ�
} BossMonster;

typedef struct ShMEM {
    bool game_ready; //
    bool field_ready;
    bool boss_ready;
    char input;
    struct Monster monster; // ���� ����
    int Host_HP; // ȣ��Ʈ ü��(ȣ��Ʈ ü���� 0�� �Ǹ� ���ӿ���)
    int Cr_room; // ���� �� ��ġ
    int User_num; // ������
    struct Party party; // ��Ƽ ����
    int boss_phase2_HP; // ���� 2������ ü�� 
    int sum_boss_phase2_HP; //��� �����н�  2������ü�� �� 
    bool checkin_1; // �Է� ��� üũ
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
    struct BossMonster boss_monster; // ���� ����
    struct BossMonster boss_monster2; //phase2 boss_monster
    struct BossMonster boss_monster3; //phase3 boss_monster
}ShMEM;

// �Լ� ������Ÿ�� ����
void draw_line();
void field_map(Player* player, int you);
void boss_map(Player* player, int you);
void draw_map(char map[MAP_HEIGHT][MAP_WIDTH]);
void draw_move(char input, char map[MAP_HEIGHT][MAP_WIDTH]);
void draw_attack(Player* player, Monster* monster);
void initialize_map(char map[MAP_HEIGHT][MAP_WIDTH]);
ShMEM* shm_get();
#endif
