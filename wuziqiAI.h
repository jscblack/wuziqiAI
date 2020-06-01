/*
 * @Author: Gehrychiang
 * @Website: www.yilantingfeng.site
 * @E-mail: gehrychiang@aliyun.com
 */
#pragma once
#include "resource.h"
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
#include <alibabacloud/oss/OssClient.h>
#include <string>
#include <Ntddstor.h>
#include <fstream>
#include <direct.h>
struct int2
{
	int x, y;
};
void board_init();
void difficultreq();
void game();
void getpos(int& x, int& y);
int win(int** a);
void gamesettlement(int** a);
bool quitgame(bool click);
void savegame(int2* a, bool click, int hand);
int loadgame(int** a);
void privacyreq();
int gvab(char* chbm);
int gvaw(char* chbm);
int cho(int* chbt, char* chbm, int turn, int rt, int depth, int expect);
void chess_add(int x, int y);
void uchbm(int* chbt, char* chbm, int posx, int posy, int turn);
int gvaldivb(char* chbm, int* chbt, int x, int y);
int gvaldivw(char* chbm, int* chbt, int x, int y);
int ai_cal(int* chbt, char* chbm, int turn, int depth);
LOGFONT cord;//坐标
LOGFONT opti;//选项
LOGFONT info;//信息栏
std::string DiskId;
std::string ClientFile;
std::string AccessKeyId = "LTAI4G9vzd4PdQJwV8tQRsKG";
std::string AccessKeySecret = "N53YmQiN0I09wmKJt230vxinKjeOd8";
std::string Endpoint = "oss-cn-beijing.aliyuncs.com";
std::string BucketName = "wuziqi-sav";
std::string ObjectName;
bool cloudsave;
int2 chess_flow[300];//记录对局
int difficulty;
int chb[225];
int step;
int steppos[255];
char chbmstep[900];
const int valmapb[31] = { 0, 0, 2, 4, 0, 4, 35, 0, 15, 300, 0, 600, 100000, 200000, 200000, 200000, 0, -1, -2, 0, -2, -15, 0, -10, -100, 0, -200, -1000, -200000, -200000, -200000 };
const int valmapw[31] = { 0, 0, 1, 2, 0, 2, 15, 0, 10, 100, 0, 200, 1000, 200000, 200000, 200000, 0, -2, -4, 0, -4, -35, 0, -15, -300, 0, -600, -100000, -200000, -200000, -200000 };
const int valmapwa[31] = { 0, 0, 2, 4, 0, 8, 70, 0, 45, 900, 0, 24000, 400000, 1000000, 1000000, 1000000, 0, -1, -2, 0, -4, -30, 0, -30, -300, 0, -800, -4000, -1000000, -1000000, -1000000 };
const int valmapba[31] = { 0, 0, 1, 2, 0, 4, 30, 0, 30, 300, 0, 800, 4000, 1000000, 1000000, 1000000, 0, -2, -4, 0, -8, -70, 0, -45, -900, 0, -2400, -400000, -1000000, -1000000, -1000000 };