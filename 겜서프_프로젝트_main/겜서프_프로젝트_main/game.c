// game.c

#include <stdio.h>
#include "game.h"
//line 따로 만듬
void draw_line() {
    for (int i = 0; i < MAP_WIDTH; i++) {
        printf("-");
    }
    printf("\n");
}
//맵 만들어주는 거
void draw_map(char map[MAP_HEIGHT][MAP_WIDTH]) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            printf("%c", map[y][x]);
        }
        printf("\n");
    }
}

//움직임
void draw_move(char input, Player* player, char map[MAP_HEIGHT][MAP_WIDTH], Monster* monster) {
    int new_x = player->x;
    int new_y = player->y;

    switch (input) {
    case 'w': new_y--; break;
    case 's': new_y++; break;
    case 'a': new_x--; break;
    case 'd': new_x++; break;
    }

    if (new_x < 0 || new_x >= MAP_WIDTH || new_y < 0 || new_y >= MAP_HEIGHT) {
        return;
    }

    if (new_x == monster->x && new_y == monster->y) {
        return;
    }

    map[player->y][player->x] = ' '; // 이전 플레이어 위치 지우기
    player->x = new_x;
    player->y = new_y;
    map[player->y][player->x] = PLAYER_ICON; // 새 위치에 플레이어 표시
}

void initialize_map(char map[MAP_HEIGHT][MAP_WIDTH], Player* player) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map[y][x] = ' ';
        }
    }
    player->x = 0;
    player->y = MAP_HEIGHT / 2;
    map[player->y][player->x] = PLAYER_ICON;
}