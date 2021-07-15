#include "Setting.h"
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <time.h>

#define BUFFSIZE 1024


int main(int argc, char* argv[])
{
    ISLAND islandI[4] = {
     {1,13},
     {23,31},
     {43,68},
     {80,90},
    };

    FILE* fp;
    errno_t error;

    char str[20];
    GetPrivateProfileString("section", "fileName1", "fault", str, 20, ".\\Setting.ini");


    int ttime = 0;
    bool pushENTER = false;
    int cntENTER;
    int current_time = 0;
    int past_time = 0;
    char time_display[20];


    // 初期化
    if (initscr() == NULL) {
        return 1;
    }

    curs_set(0);//キー入力後すぐに読み取りを開始する
    cbreak();
    noecho();
    keypad(stdscr, 1);

    ///色の準備
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);//色１は赤
    init_pair(2, COLOR_GREEN, COLOR_BLACK);//色２は緑
    init_pair(3, COLOR_WHITE, COLOR_BLACK);//色３は白
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);//色4は黄色

    bkgd(COLOR_PAIR(3));

    WINDOW* win;
    win = newwin(25, 80, 0, 0);


    while (1) {

        //

        if (judge_flag == true) {
            wattron(win, COLOR_PAIR(2));
            mvwaddstr(win, 12, 5, "GAME START -> PUSH ENTER");
        }



        if (GetKeyState(VK_RETURN) & 0x80) {
            pushENTER = true;
            past_time = clock();
        }


        while (pushENTER && judge_flag) {

            //時間の処理
            current_time = clock();


            sprintf_s(time_display, "%d", (current_time - past_time) / 1000);

            //枠を作る
            wattron(win, COLOR_PAIR(3));
            box(win, '|', '-');
            for (int i = 1; i < 24; i++) {
                mvwaddstr(win, i, 62, "|");
            }

            //キャラクターを動かす
            move_character();

            //島を動かす
            move_land(islandI);

            //島を生成する
            create_land(islandI);

            //ジャンプしてないときの処理
            if (character_state < 2) {
                make_character_state(win);
            }
            judge();

            /*描画の処理ここから*/

                //島の描画
            draw_island(win, land);

            //キャラクターの描画
            draw_character(win);

            //パワーゲージの描画
            if (character_state == 1) {
                draw_power(win, current_time);
            }
            mvwaddstr(win, 2, 66, "POWER GAGE");

            //タイムの描画
            wattron(win, COLOR_PAIR(3));//以下白色
            mvwaddstr(win, 2, 50, "TIME");
            mvwaddstr(win, 2, 55, time_display);



            /*描画の処理ここまで*/


            wrefresh(win);
            wclear(win);

            Sleep(50);
        }

        if (judge_flag == false) {
            wattron(win, COLOR_PAIR(1));
            mvwaddstr(win, 12, 10, "GAME OVER");

            /*ゲーム時間をファイルに出力*/
            if (judge_flag == false) {
                wattron(win, COLOR_PAIR(1));
                mvwaddstr(win, 12, 10, "GAME OVER");

                error = fopen_s(&fp, str, "w");
                if (error != 0) {
                    fprintf_s(stderr, "failed to open");
                }
                else {
                    fputs("Play Time\n", fp);
                    fprintf_s(fp, "%d", current_time);
                    fputs("　秒", fp);
                    fclose(fp);
                }
            }

        }


        wrefresh(win);
        wclear(win);


    }

    /*後処理*/
    wclear(win);
    wrefresh(win);
    endwin();

    return 0;
}