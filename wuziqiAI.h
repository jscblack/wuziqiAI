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
void board_init();
void game();
void getpos(int& x, int& y);
int win(int** a);