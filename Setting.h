#pragma once
#ifndef _SETTING_H_
#define _SETTING_H_

#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <time.h>

typedef struct _TAG_ISLAND {
    int left;
    int right;
}ISLAND;


typedef struct _TAG_ISLAND {
    int left;
    int right;
}ISLAND;

bool judge_flag = true;

time_t start_time = 0, end_time = 0;
int total_time = 0;

int land[100] = { 0 };

int character_state = 0;

//キャラクターの中心座標
int character_x = 30;
int character_y = 14;

int jump_state = 0;


//キー判定
bool is_key_push = false;



void charactor(WINDOW* win, int x, int y);
void sit_charactor(WINDOW* win, int x, int y);
void jump_charactor(WINDOW* win, int x, int y);
void make_character_state(WINDOW* win);
void draw_island(WINDOW* win, int land[60]);
void move_land(ISLAND islandI[]);
void create_land(ISLAND islandI[]);
void move_character();
void draw_character(WINDOW* win);
void judge();




void charactor(WINDOW* win, int x, int y) {//初期状態は(x,y)=(30,14)
    wattron(win, COLOR_PAIR(3));
    mvwaddstr(win, y, x, "■");
    mvwaddstr(win, y - 1, x - 2, "■");
    mvwaddstr(win, y - 1, x, "■");
    mvwaddstr(win, y - 1, x + 2, "■");
    mvwaddstr(win, y, x - 2, "■");
    mvwaddstr(win, y, x + 2, "■");
    mvwaddstr(win, y + 1, x - 2, "■");
    mvwaddstr(win, y + 1, x, "■");
    mvwaddstr(win, y + 1, x + 2, "■");
    mvwaddstr(win, y + 2, x, "■");
    mvwaddstr(win, y + 3, x, "■");
    mvwaddstr(win, y + 3, x - 2, "■");
    mvwaddstr(win, y + 4, x - 4, "■");
    mvwaddstr(win, y + 3, x + 2, "■");
    mvwaddstr(win, y + 4, x + 4, "■");
    mvwaddstr(win, y + 4, x, "■");
    mvwaddstr(win, y + 5, x, "■");
    mvwaddstr(win, y + 6, x - 2, "■");
    mvwaddstr(win, y + 6, x + 2, "■");
    mvwaddstr(win, y + 7, x - 2, "■");
    mvwaddstr(win, y + 7, x + 2, "■");

}

void sit_charactor(WINDOW* win, int x, int y) {//初期状態は(x,y)=(30,14)
    wattron(win, COLOR_PAIR(3));
    mvwaddstr(win, y + 1, x, "■");
    mvwaddstr(win, y, x - 2, "■");
    mvwaddstr(win, y, x, "■");
    mvwaddstr(win, y, x + 2, "■");
    mvwaddstr(win, y + 1, x - 2, "■");
    mvwaddstr(win, y + 1, x + 2, "■");
    mvwaddstr(win, y + 2, x - 2, "■");
    mvwaddstr(win, y + 2, x, "■");
    mvwaddstr(win, y + 2, x + 2, "■");
    mvwaddstr(win, y + 3, x, "■");
    mvwaddstr(win, y + 4, x, "■");
    mvwaddstr(win, y + 4, x - 2, "■");
    mvwaddstr(win, y + 5, x - 4, "■");
    mvwaddstr(win, y + 4, x + 2, "■");
    mvwaddstr(win, y + 5, x + 4, "■");
    mvwaddstr(win, y + 5, x, "■");
    mvwaddstr(win, y + 6, x - 2, "■");
    mvwaddstr(win, y + 6, x + 2, "■");
    mvwaddstr(win, y + 7, x - 2, "■");
    mvwaddstr(win, y + 7, x + 2, "■");

}

void jump_charactor(WINDOW* win, int x, int y) {//初期状態は(x,y)=(30,14)
    wattron(win, COLOR_PAIR(3));
    mvwaddstr(win, y, x, "■");
    mvwaddstr(win, y - 1, x - 2, "■");
    mvwaddstr(win, y - 1, x, "■");
    mvwaddstr(win, y - 1, x + 2, "■");
    mvwaddstr(win, y, x - 2, "■");
    mvwaddstr(win, y, x + 2, "■");
    mvwaddstr(win, y + 1, x - 2, "■");
    mvwaddstr(win, y + 1, x, "■");
    mvwaddstr(win, y + 1, x + 2, "■");
    mvwaddstr(win, y + 2, x, "■");
    mvwaddstr(win, y + 3, x, "■");
    mvwaddstr(win, y + 3, x - 2, "■");
    mvwaddstr(win, y + 2, x - 4, "■");
    mvwaddstr(win, y + 3, x + 2, "■");
    mvwaddstr(win, y + 2, x + 4, "■");
    mvwaddstr(win, y + 4, x, "■");
    mvwaddstr(win, y + 5, x, "■");
    mvwaddstr(win, y + 6, x - 2, "■");
    mvwaddstr(win, y + 6, x + 2, "■");
    mvwaddstr(win, y + 7, x - 4, "■");
    mvwaddstr(win, y + 7, x + 4, "■");

}

void make_character_state(WINDOW* win) {

    /*キー入力判定*/
    if ((GetKeyState(VK_SPACE) & 0x80)) {//初めてキーを押しているときの処理

        if (is_key_push == false) {//キーを初めて押した時の処理
            is_key_push = true;
            start_time = clock();
        }

        character_state = 1;//しゃがんでいる状態

    }
    else if (!(GetKeyState(VK_SPACE) & 0x80)) {//キーを押してないときの処理

        if (is_key_push == true) {//長押ししていて、離した時の処理

            end_time = clock();

            total_time = end_time - start_time;

            character_state = 2;//ジャンプしている状態

        }

        is_key_push = false;
    }

}


void draw_island(WINDOW* win, int land[60]) {
    wattron(win, COLOR_PAIR(2));
    for (int i = 0; i < 60; i++) {
        if (land[i] == 1) {
            mvwaddstr(win, 22, i, "■");
            mvwaddstr(win, 23, i, "■");
            wrefresh(win);
        }
        else {
            mvwaddstr(win, 22, i, "  ");
            mvwaddstr(win, 23, i, "  ");
            wrefresh(win);
        }
        if (i == 0) {
            mvwaddstr(win, 22, i, "|");
            mvwaddstr(win, 23, i, "|");
            wrefresh(win);
        }
    }
}



void move_land(ISLAND islandI[]) {

    memset(land, 0, 60 * sizeof(land[0]));//0で初期化

    for (int i = 0; i < 4; i++) {//land
        if (islandI[i].left > 0) {
            islandI[i].left--;
        }
        if (islandI[i].right > 0) {
            islandI[i].right--;
        }
        for (int j = islandI[i].left; j < islandI[i].right; j++) {
            land[j] = 1;
        }

    }
}

void create_land(ISLAND islandI[]) {

    for (int i = 0; i < 4; i++) {//land
        if (islandI[i].right <= 0) {
            islandI[i].left = 70;
            islandI[i].right = 80;
        }
    }
}

void move_character() {
    switch (character_state) {

    case 0://初期状態
        character_x--;
        break;
    case 1://しゃがんだ状態
        character_x--;
        break;
    case 2://どれだけ飛ぶかの処理
        jump_state = total_time / 50 + 1;
        character_state = 3;
        break;
    case 3://ジャンプの処理
        if (jump_state > 0) {
            if (jump_state <= 2) {
                character_y = 13;
            }
            else if (jump_state > 2 && jump_state <= 4) {
                character_y = 12;
            }
            else if (jump_state > 4 && jump_state <= 6) {
                character_y = 11;
            }
            else if (jump_state > 6 && jump_state <= 10) {
                character_y = 10;
            }
            else {
                character_y = 9;
            }
            character_x++;
            jump_state--;
        }
        else
        {
            character_y = 14;
            character_state = 0;
        }
        break;
    }
}

void draw_character(WINDOW* win) {
    //キャラクターの描画
    switch (character_state) {

    case 0:
        charactor(win, character_x, character_y);
        break;
    case 1:
        sit_charactor(win, character_x, character_y);
        break;
    case 2:
        jump_charactor(win, character_x, character_y);
        break;
    case 3:
        jump_charactor(win, character_x, character_y);
        break;
    }
}

void judge() {
    if (character_x < 0) {
        judge_flag = false;
    }
    if (character_x > 60) {
        judge_flag = false;
    }
    if (character_state <= 1) {
        if (land[character_x - 3] == 0 && land[character_x + 3] == 0) {
            judge_flag = false;
        }
    }
}



void draw_power(WINDOW* win, int current_time) {

    int power_gage = (current_time - start_time) / 100;

    for (int i = 0; i <= power_gage; i++) {
        if (i >= 0 && i < 3) {
            wattron(win, COLOR_PAIR(3));
        }
        if (i >= 3 && i < 7) {
            wattron(win, COLOR_PAIR(4));
        }
        if (i >= 7) {
            wattron(win, COLOR_PAIR(1));
        }
        mvwaddstr(win, 23 - i, 70, "■");
        mvwaddstr(win, 23 - i, 72, "■");
    }

}


#endif
