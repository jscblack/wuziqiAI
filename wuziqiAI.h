/*
 * @Author: Gehrychiang
 * @Website: www.yilantingfeng.site
 * @E-mail: gehrychiang@aliyun.com
 */
/*
fuction help

void board_init()
Initilize the layout, some variants and required components

void difficultreq()
query difficulty

void privacyreq()
query cloud-service

void game()
main function during the game process

void getpos(int& x, int& y)
get current mouse position

int loadgame(int** a)
load saved game form local save

void savegame(int2* a, bool click, int hand)
save current game to local file and upload to the cloud(optional)

int win(int** a)
query win

void gamesettlement(int** a)
settle the current game

bool quitgame(bool click)
quit game(self kill)

int uploadsav()
upload local save to the cloud

bool chkcloudsav()
check whether there is a save on the cloud server

int downloadsav()
download uploaded save to local

std::string getDiskId()
get the id of harddisk to identify and register user

std::string sha1(std::string s)
encrypt string for safety

int ai_cal(int* chbt, char* chbm, int turn, int depth)
main entrance during the AI calculation

int chess_op(int* chbt, char* chbm, int turn, int rt, int depth, int expect)
main entrance for serching

void chess_add(int x, int y)
add a chess to the backend datebase

try_sol(int* chbt, char* chbm, int posx, int posy, int turn)
try solutions and keep the best

int ser_black(char* chbm, int* chbt, int x, int y)
serch during the round of the black

int ser_white(char* chbm, int* chbt, int x, int y)
serch during the round of the white

int sco_black(char* chbm)
get current score of the black

int sco_white(char* chbm)
get current score of the white
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
int sco_black(char* chbm);
int sco_white(char* chbm);
int chess_op(int* chbt, char* chbm, int turn, int rt, int depth, int expect);
void chess_add(int x, int y);
void try_sol(int* chbt, char* chbm, int posx, int posy, int turn);
int ser_black(char* chbm, int* chbt, int x, int y);
int ser_white(char* chbm, int* chbt, int x, int y);
int ai_cal(int* chbt, char* chbm, int turn, int depth);
LOGFONT cord;//����
LOGFONT opti;//ѡ��
LOGFONT info;//��Ϣ��
std::string DiskId;
std::string ClientFile;
std::string AccessKeyId = "*";
std::string AccessKeySecret = "*";
std::string Endpoint = "*";
std::string BucketName = "*";
std::string ObjectName;
bool cloudsave;
int2 chess_flow[300];//��¼�Ծ�
int difficulty;
int chb[225];
int step;
int steppos[255];
char chbmstep[900];
const int valmapb[31] = { 0, 0, 2, 4, 0, 4, 35, 0, 15, 300, 0, 600, 100000, 200000, 200000, 200000, 0, -1, -2, 0, -2, -15, 0, -10, -100, 0, -200, -1000, -200000, -200000, -200000 };
const int valmapw[31] = { 0, 0, 1, 2, 0, 2, 15, 0, 10, 100, 0, 200, 1000, 200000, 200000, 200000, 0, -2, -4, 0, -4, -35, 0, -15, -300, 0, -600, -100000, -200000, -200000, -200000 };
const int valmapwa[31] = { 0, 0, 2, 4, 0, 8, 70, 0, 45, 900, 0, 24000, 400000, 1000000, 1000000, 1000000, 0, -1, -2, 0, -4, -30, 0, -30, -300, 0, -800, -4000, -1000000, -1000000, -1000000 };
const int valmapba[31] = { 0, 0, 1, 2, 0, 4, 30, 0, 30, 300, 0, 800, 4000, 1000000, 1000000, 1000000, 0, -2, -4, 0, -8, -70, 0, -45, -900, 0, -2400, -400000, -1000000, -1000000, -1000000 };