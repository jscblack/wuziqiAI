/*
 * @Author: Gehrychiang
 * @Website: www.yilantingfeng.site
 * @E-mail: gehrychiang@aliyun.com
 */
#pragma once
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>
#include <string>
#include <Windows.h>
#include <io.h>
using namespace std;
void board_init();
void game();
void getpos(int& x, int& y);
int win(int** a);
void gamesettlement(int** a);
bool quitgame(bool click);
void savegame(int** a, bool click, int hand);
int loadgame(int** a);
int overall_evaluate(int** boardlay);
void ai(int** boardlay, int& tarx, int& tary);
LOGFONT cord;//坐标
LOGFONT opti;//选项
LOGFONT info;//信息栏
struct node
{
	int five;//100000
	int four;//10000
	int sub_four;//1000
	int three;//1000
	int sub_three;//100
	int two;//100
	int sub_two;//10
	int one;//10
};