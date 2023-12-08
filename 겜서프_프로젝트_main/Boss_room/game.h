#ifndef GAME_H
#define GAME_H

#define MAP_WIDTH 50
#define MAP_HEIGHT 20
#define ASCII_ART_SIZE 256 // �ƽ�Ű ��Ʈ �迭 ũ�� ����

// ���� �� ǥ�ÿ� ���Ǵ� ���ڵ�
#define PLAYER_ICON '#'
#define BOSSMONSTER_ICON '&'
#define BOSSMONSTER_ART1 "  /\\_/\\\n ( T.T )\n  [ ^ ]"
#define BOSSMONSTER_ART2 "  /\\_/\\\n ( ^.^ )\n  < ^ >"
#define BOSSMONSTER_ART3 "  /\\_/\\\n ( poq )\n *< ^ >*" 

// �÷��̾� ��ġ�� �����ϱ� ���� ����ü
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
    int Monster_HP; // ���� ü��
    int Monster_OP; // ���� ���ݷ�
    char boss_ascii_art[ASCII_ART_SIZE]; // �ƽ�Ű ��Ʈ�� ���� �迭
} BossMonster;

typedef struct Party {
    int x;
    int y;
    int Party_Coin; // ��Ƽ ��
    int Party_OP_buff; // ��Ƽ ���ݷ�
    int Party_HP_buff; // ��Ƽ ü�� ����
} Party;

typedef struct ShMEM {
    struct BossMonster boss_monster; // ���� ����
    struct BossMonster boss_monster2; //phase2 boss_monster
    struct BossMonster boss_monster3; //phase3 boss_monster
    int Host_HP; // ȣ��Ʈ ü��(ȣ��Ʈ ü���� 0�� �Ǹ� ���ӿ���)
    int Cr_room; // ���� �� ��ġ
    int x;
    int y;
    int Monster_HP; // ���� ü��
    int Monster_OP; // ���� ���ݷ�
    char boss_ascii_art[ASCII_ART_SIZE];
    int User_num; // ������
    struct Party party; // ��Ƽ ����
    int boss_phase2_HP; // ���� 2������ ü��
    int sum_boss_phase2_HP; //��� �����н�  2������ü�� �� 
} ShMEM;

// �Լ� ������Ÿ�� ����
void draw_line();
void draw_map(char map[MAP_HEIGHT][MAP_WIDTH]);
void draw_move(char input, Player* player, char map[MAP_HEIGHT][MAP_WIDTH], BossMonster* monster);
void draw_attack(Player* player, BossMonster* monster);
void initialize_map(char map[MAP_HEIGHT][MAP_WIDTH], Player* player);

#endif
