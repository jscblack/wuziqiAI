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
void privacyreq();
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