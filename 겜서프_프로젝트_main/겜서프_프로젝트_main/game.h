#ifndef GAME_H
#define GAME_H

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
    int x;
    int y;
    Class class; //����
    int HP; // ü��
    int OP; // ���ݷ�
    int Money; // ��
} Player;

typedef struct Monster {
    int x;
    int y;
    int Monster_HP; // ���� ü��
    int Monster_OP; // ���� ���ݷ�
    char ascii_art[ASCII_ART_SIZE]; // �ƽ�Ű ��Ʈ�� ���� �迭
} Monster;

typedef struct Party {
    int Party_Coin; // ��Ƽ ��
    int Party_OP_buff; // ��Ƽ ���ݷ�
    int Party_HP_buff; // ��Ƽ ü�� ����
}Party;

// �Լ� ������Ÿ�� ����
void draw_line();
void draw_map(char map[MAP_HEIGHT][MAP_WIDTH]);
void draw_move(char input, Player* player, char map[MAP_HEIGHT][MAP_WIDTH], Monster* monster);
void draw_attack(Player* player, Monster* monster);
void initialize_map(char map[MAP_HEIGHT][MAP_WIDTH], Player* player);

#endif
