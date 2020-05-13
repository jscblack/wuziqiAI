/*
 * @Author: Gehrychiang
 * @Website: www.yilantingfeng.site
 * @E-mail: gehrychiang@aliyun.com
 */
 //引用库
#include "wuziqiAI.h"

int main()
{
	//pid started
	board_init();
	//board initilized
	//game started
	game();
	//game ended

	//system("pause");
	return 0;
}
//ai实现
int overall_evaluate(int** boardlay) //对电脑而言的
{
	//获取原棋盘布局，避免产生冲突
	int** bod = (int**)calloc(25, sizeof(int**)); //1代表黑子 2代表白子
	for (int i = 0; i <= 20; ++i)
	{
		*(bod + i) = (int*)calloc(25, sizeof(int));
	}

	for (int i = 1; i <= 15; i++)
	{
		for (int j = 1; j <= 15; j++)
		{
			bod[j][i] = boardlay[i][j]; //逆置很关键
		}
	}
	int aisum = 0;
	int humsum = 0;
	//横
	for (int i = 1; i <= 15; i++)
	{
		for (int j = 1; j <= 15; j++)
		{
			if (bod[i][j] == 1) //黑子
			{
				int cnt = 0;
				for (cnt = 0; cnt <= 16 - j; cnt++)
				{
					if (bod[i][j + cnt] != 1)
					{
						break;
					}
				}
				int pos = cnt;
				if ((j - 1 >= 1 && bod[i][j - 1] == 2) || (j + cnt <= 15 && bod[i][j + cnt] == 2))
				{
					cnt--; //变死的了
				}
				else if (j == 1 || j + cnt == 16)
				{
					cnt--;
				}
				humsum += pow(10, cnt != 0 ? cnt : 1);
				j = j + pos - 1;
			}
			else if (bod[i][j] == 2) //白子
			{
				int cnt = 0;
				for (cnt = 0; cnt <= 16 - j; cnt++)
				{
					if (bod[i][j + cnt] != 2)
					{
						break;
					}
				}
				int pos = cnt;
				if ((j - 1 >= 1 && bod[i][j - 1] == 1) || (j + cnt <= 15 && bod[i][j + cnt] == 1))
				{
					cnt--; //变死的了
				}
				else if (j == 1 || j + cnt == 16)
				{
					cnt--;
				}
				aisum += pow(10, cnt!=0?cnt:1);
				j = j + pos - 1;
			}
		}
	}
	//纵
	for (int j = 1; j <= 15; j++)
	{
		for (int i = 1; i <= 15; i++)
		{
			if (bod[i][j] == 1) //黑子
			{
				int cnt = 0;
				for (cnt = 0; cnt <= 16 - i; cnt++)
				{
					if (bod[i + cnt][j] != 1)
					{
						break;
					}
				}
				int pos = cnt;
				if ((i - 1 >= 1 && bod[i - 1][j] == 2) || (i + cnt <= 15 && bod[i + cnt][j] == 2))
				{
					cnt--; //变死的了
				}
				else if (i == 1 || i + cnt == 16)
				{
					cnt--;
				}
				if (cnt > 1)
					humsum += pow(10, cnt);
				i = i + pos - 1;
			}
			else if (bod[i][j] == 2) //白子
			{
				int cnt = 0;
				for (cnt = 0; cnt <= 16 - i; cnt++)
				{
					if (bod[i + cnt][j] != 2)
					{
						break;
					}
				}
				int pos = cnt;
				if ((i - 1 >= 1 && bod[i - 1][j] == 1) || (i + cnt <= 15 && bod[i + cnt][j] == 1))
				{
					cnt--; //变死的了
				}
				else if (i == 1 || i + cnt == 16)
				{
					cnt--;
				}
				if (cnt > 1)
					aisum += pow(10, cnt);
				i = i + pos - 1;
			}
		}
	}
	//左斜
	for (int i = 1, j = 1, l = 1; i <= 15 && j <= 15; i = min(15, i + 1))
	{
		//起始点为i,j
		for (int k = 0; k < l; k++)
		{
			if (bod[i - k][j + k] == 1) //黑子
			{
				int cnt = 0;
				for (cnt = 0; cnt < l - k; cnt++)
				{
					if (bod[i - k - cnt][j + k + cnt] != 1)
					{
						break;
					}
				}
				int pos = cnt;
				if ((i - k + 1 <= 15 && j + k - 1 >= 1 && bod[i - k + 1][j + k - 1] == 2) || (i - k - cnt >= 1 && j + k + cnt <= 15 && bod[i - k - cnt][j + k + cnt] == 2))
				{
					cnt--; //变死的了
				}
				else if (i - k + 1 == 16 || j + k - 1 == 0 || i - k - cnt == 0 || j + k + cnt == 16)
				{
					cnt--; //变死的了
				}
				if (cnt > 1)
				{
					humsum += pow(10, cnt);
				}
				k = k + pos - 1;
			}
			else if (bod[i - k][j + k] == 2) //白子
			{
				int cnt = 0;
				for (cnt = 0; cnt < l - k; cnt++)
				{
					if (bod[i - k - cnt][j + k + cnt] != 2)
					{
						break;
					}
				}
				int pos = cnt;
				if ((i - k + 1 <= 15 && j + k - 1 >= 1 && bod[i - k + 1][j + k - 1] == 1) || (i - k - cnt >= 1 && j + k + cnt <= 15 && bod[i - k - cnt][j + k + cnt] == 1))
				{
					cnt--; //变死的了
				}
				else if (i - k + 1 == 16 || j + k - 1 == 0 || i - k - cnt == 0 || j + k + cnt == 16)
				{
					cnt--; //变死的了
				}
				if (cnt > 1)
				{
					aisum += pow(10, cnt);
				}
				k = k + pos - 1;
			}
		}
		j = (i == 15 ? j + 1 : 1);
		l = (i == 15 ? l - 1 : l + 1);
	}
	for (int i = 1, j = 15, l = 1; i <= 15 && j >= 1; j = max(1, j - 1))
	{
		//起始点为i,j
		for (int k = 0; k < l; k++)
		{
			if (bod[i + k][j + k] == 1) //黑子
			{
				int cnt = 0;
				for (cnt = 0; cnt < l - k; cnt++)
				{
					if (bod[i + k + cnt][j + k + cnt] != 1)
					{
						break;
					}
				}
				int pos = cnt;
				if ((i + k - 1 <= 15 && j + k - 1 >= 1 && bod[i + k - 1][j + k - 1] == 2) || (i + k + cnt >= 1 && j + k + cnt <= 15 && bod[i + k + cnt][j + k + cnt] == 2))
				{
					cnt--; //变死的了
				}
				else if (i + k - 1 == 16 || j + k - 1 == 0 || i + k + cnt == 0 || j + k + cnt == 16)
				{
					cnt--; //变死的了
				}
				if (cnt > 1)
				{
					humsum += pow(10, cnt);
				}
				k = k + pos - 1;
			}
			else if (bod[i + k][j + k] == 2) //白子
			{
				int cnt = 0;
				for (cnt = 0; cnt < l - k; cnt++)
				{
					if (bod[i + k + cnt][j + k + cnt] != 2)
					{
						break;
					}
				}
				int pos = cnt;
				if ((i + k - 1 <= 15 && j + k - 1 >= 1 && bod[i + k - 1][j + k - 1] == 1) || (i + k + cnt >= 1 && j + k + cnt <= 15 && bod[i + k + cnt][j + k + cnt] == 1))
				{
					cnt--; //变死的了
				}
				else if (i + k - 1 == 16 || j + k - 1 == 0 || i + k + cnt == 0 || j + k + cnt == 16)
				{
					cnt--; //变死的了
				}
				if (cnt > 1)
				{
					aisum += pow(10, cnt);
				}
				k = k + pos - 1;
			}
		}
		i = (j == 1 ? i + 1 : 1);
		l = (j == 1 ? l - 1 : l + 1);
	}
	return aisum - humsum;
}

void ai(int** boardlay, int& tarx, int& tary)
{
	//获取原棋盘布局，避免产生冲突
	int** bod = (int**)calloc(25, sizeof(int**)); //1代表黑子 2代表白子
	for (int i = 0; i <= 20; ++i)
	{
		*(bod + i) = (int*)calloc(25, sizeof(int));
	}

	for (int i = 1; i <= 15; i++)
	{
		for (int j = 1; j <= 15; j++)
		{
			bod[i][j] = boardlay[i][j];
		}
	}
}

//gui和逻辑已经构建完成2020.5.9
//bug基本修复
int uploadsav()
{
	using namespace AlibabaCloud::OSS;
	/* 初始化OSS账号信息 */
	std::string AccessKeyId = "LTAI4G9vzd4PdQJwV8tQRsKG";
	std::string AccessKeySecret = "N53YmQiN0I09wmKJt230vxinKjeOd8";
	std::string Endpoint = "oss-cn-beijing.aliyuncs.com";
	std::string BucketName = "wuziqi-sav";
	/* yourObjectName表示上传文件到OSS时需要指定包含文件后缀在内的完整路径，例如abc/efg/123.jpg */
	std::string ObjectName = "test/sav.dat";

	/* 初始化网络等资源 */
	std::cout << "正在连接服务器" << "\n";
	InitializeSdk();
	
	std::cout << "连接服务器成功" << "\n";
	//GetModuleFileName()
	ClientConfiguration conf;
	OssClient client(Endpoint, AccessKeyId, AccessKeySecret, conf);

	/* 上传文件 */
	/* yourLocalFilename由本地文件路径加文件名包括后缀组成，例如/users/local/myfile.txt */
	std::cout << "正在上传存档" << "\n";
	auto outcome = client.PutObject(BucketName, ObjectName, "E:/DxDiag.txt");
	
	if (!outcome.isSuccess()) {
		/* 异常处理 */
		std::cout << "PutObject fail" <<
			",code:" << outcome.error().Code() <<
			",message:" << outcome.error().Message() <<
			",requestId:" << outcome.error().RequestId() << std::endl;
		ShutdownSdk();
		return -1;
	}
	/* 释放网络等资源 */
	ShutdownSdk();
	std::cout << "存档上传成功" << "\n";
	return 0;
}
void gamesettlement(int** a)
{
	LOGFONT win_font = cord;
	win_font.lfHeight = 90;
	win_font.lfWidth = 41;
	settextstyle(&win_font);
	switch (win(a))
	{
	case 1:
	{
		setfillstyle(BS_SOLID);
		setfillcolor(BLACK);
		fillrectangle(990, 55, 1190, 745);
		settextcolor(WHITE);
		outtextxy(1007, 350, _T("黑胜"));
		break;
	}

	case 2:
	{
		setfillstyle(BS_SOLID);
		setfillcolor(BLACK);
		fillrectangle(990, 55, 1190, 745);
		settextcolor(WHITE);
		outtextxy(1007, 350, _T("白胜"));
		break;
	}

	case 3:
	{
		outtextxy(1007, 350, _T("和棋"));
		break;
	}
	}
	printf("\a");
	HWND wnd = GetHWnd();
	MessageBox(wnd, _T("游戏结束\n程序将自动退出"), _T("Warning"), MB_OK);
	return;
}

bool quitgame(bool click)
{
	if (click)
	{
		HWND wnd = GetHWnd();
		printf("\a");
		if (MessageBox(wnd, _T("确定退出吗。\n"), _T("Warning"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

void savegame(int** a, bool click, int hand)
{
	if (click)
	{
		HWND wnd = GetHWnd();
		if (MessageBox(wnd, _T("确定存档吗。\n"), _T("Warning"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			FILE* out;
			out = fopen("wuziqi.sav", "w");
			long long chksum = 20001122;
			for (int i = 1; i <= 15; i++)
			{
				for (int j = 1; j <= 15; j++)
				{
					fprintf(out, "%d ", a[i][j]);
					chksum = (chksum ^ a[i][j]);
				}
			}
			fprintf(out, "%d ", hand);	//手
			fprintf(out, "%lld", chksum); //校验码
			fclose(out);
			free(out);
				printf("\a");
			MessageBox(wnd, _T("保存成功\n"), _T("Warning"), MB_OK);
			if (uploadsav() == 0)
			{
				printf("\a");
				MessageBox(wnd, _T("上传成功\n"), _T("Warning"), MB_OK);
			}
			else
			{
				printf("\a");
				MessageBox(wnd, _T("上传失败\n"), _T("Warning"), MB_OK);
			}


			
		}
	}
	return;
}

int loadgame(int** a)
{

	HWND wnd = GetHWnd();
	if (!access("wuziqi.sav", 0)) //
	{
		printf("\a");
		if (MessageBox(wnd, _T("检测到存档，是否读取？\n"), _T("Warning"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			FILE* in;
			in = fopen("wuziqi.sav", "r");
			int* tmpsav = (int*)calloc(300, sizeof(int)); //存档读取缓冲
			int chksum = 20001122;
			int cntblack = 0;
			int cntwhite = 0;
			for (int i = 0; i < 15 * 15 + 2; i++)
			{
				fscanf(in, "%d", tmpsav + i);

				if (i < 15 * 15)
				{
					if (*(tmpsav + i) == 1)
					{
						cntblack++;
					}
					else if (*(tmpsav + i) == 2)
					{
						cntwhite++;
					}
					chksum = (chksum ^ *(tmpsav + i));
				}
			}
			if (chksum != *(tmpsav + 15 * 15 + 1) || *(tmpsav + 15 * 15) != cntblack - cntwhite + 1)
			{
				printf("\a");
				MessageBox(wnd, _T("存档文件校验失败\n"), _T("Warning"), MB_OK);
				return 1;
			}
			int p = 0;
			setlinecolor(BLACK);
			setfillstyle(BS_SOLID);
			for (int i = 1; i <= 15; i++)
			{
				for (int j = 1; j <= 15; j++)
				{
					a[i][j] = *(tmpsav + p);

					if (a[i][j] == 1)
					{
						setfillcolor(BLACK);
						fillcircle((i - 1) * 60 + 55, (j - 1) * 60 + 55, 20);
					}
					else if (a[i][j] == 2)
					{
						setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
						setfillcolor(WHITE);
						fillcircle((i - 1) * 60 + 55, (j - 1) * 60 + 55, 20);
					}
					p++;
				}
			}
			printf("\a");
			MessageBox(wnd, _T("存档文件读取成功\n"), _T("Warning"), MB_OK);
			fclose(in);
			free(in);
			return *(tmpsav + 15 * 15);
		}
	}
	return 1;
}

void getpos(int& x, int& y)
{
	for (int i = 0; i < 15; i++)
	{
		if (abs(i * 60 + 55 - x) < 30)
		{
			for (int j = 0; j < 15; j++)
			{
				if (abs(j * 60 + 55 - y) < 30)
				{
					x = i + 1;
					y = j + 1;
					return;
				}
			}
		}
	}
}

int win(int** a) //获胜条件，1黑获胜，2白获胜，3和局
{
	int flag = 1;
	for (int i = 1; i <= 15; i++)
	{
		for (int j = 1; j <= 15; j++)
		{
			if (a[i][j] == 0) //尚有空位
			{
				flag = 0;
			}
			if (a[i][j] == 1)
			{
				if (i + 4 <= 15 && a[i + 1][j] == 1 && a[i + 2][j] == 1 && a[i + 3][j] == 1 && a[i + 4][j] == 1)
				{
					return 1;
				}
				if (j + 4 <= 15 && a[i][j + 1] == 1 && a[i][j + 2] == 1 && a[i][j + 3] == 1 && a[i][j + 4] == 1)
				{
					return 1;
				}
				if (i + 4 <= 15 && j + 4 <= 15 && a[i + 1][j + 1] == 1 && a[i + 2][j + 2] == 1 && a[i + 3][j + 3] == 1 && a[i + 4][j + 4] == 1)
				{
					return 1;
				}
				if (i + 4 <= 15 && j - 4 >= 0 && a[i + 1][j - 1] == 1 && a[i + 2][j - 2] == 1 && a[i + 3][j - 3] == 1 && a[i + 4][j - 4] == 1)
				{
					return 1;
				}
			}
			else if (a[i][j] == 2)
			{
				if (i + 4 <= 15 && a[i + 1][j] == 2 && a[i + 2][j] == 2 && a[i + 3][j] == 2 && a[i + 4][j] == 2)
				{
					return 2;
				}
				if (j + 4 <= 15 && a[i][j + 1] == 2 && a[i][j + 2] == 2 && a[i][j + 3] == 2 && a[i][j + 4] == 2)
				{
					return 2;
				}
				if (i + 4 <= 15 && j + 4 <= 15 && a[i + 1][j + 1] == 2 && a[i + 2][j + 2] == 2 && a[i + 3][j + 3] == 2 && a[i + 4][j + 4] == 2)
				{
					return 2;
				}
				if (i + 4 <= 15 && j - 4 >= 0 && a[i + 1][j - 1] == 2 && a[i + 2][j - 2] == 2 && a[i + 3][j - 3] == 2 && a[i + 4][j - 4] == 2)
				{
					return 2;
				}
			}
		}
	}
	if (flag)
	{
		return 3;
	}
	else
	{
		return 0;
	}
}

void game()
{
	//申请棋盘空间
	int** boardlay = (int**)calloc(25, sizeof(int**)); //1代表黑子 2代表白子
	for (int i = 0; i <= 20; ++i)
	{
		*(boardlay + i) = (int*)calloc(25, sizeof(int));
	}
	//读档

	int hand = loadgame(boardlay); // 黑子先落子 1黑子 2白子
	while (1)
	{
		if (hand == 1) //落黑子
		{
			while (1)
			{
				MOUSEMSG mouse = GetMouseMsg(); // 获取鼠标信息
												//mouse.x
												//mouse.y
				int mx = mouse.x;
				int my = mouse.y;
				if (mx >= 990 && mx <= 1190 && my >= 820 && my <= 895) //退出按钮
				{
					if (quitgame(mouse.mkLButton))
					{
						return;
					}
				}
				if (mx >= 990 && mx <= 1190 && my >= 765 && my <= 820) //存档按钮
				{
					savegame(boardlay, mouse.mkLButton, 1);
				}
				getpos(mx, my);
				if (mx >= 1 && mx <= 15 && my >= 1 && my <= 15 && boardlay[mx][my] == 0)
				{
					//绘制标识区域
					if (mouse.mkLButton)
					{
						boardlay[mx][my] = 1;
						//绘制棋子
						setlinecolor(BLACK);
						setfillstyle(BS_SOLID);
						setfillcolor(BLACK);
						fillcircle((mx - 1) * 60 + 55, (my - 1) * 60 + 55, 20);
						hand = 2;
						break;
					}
				}
			}
		}
		else if (hand == 2) //落白子
		{
			while (1)
			{
				MOUSEMSG mouse = GetMouseMsg(); // 获取鼠标信息
												//mouse.x
												//mouse.y
				int mx = mouse.x;
				int my = mouse.y;
				if (mx >= 990 && mx <= 1190 && my >= 820 && my <= 895)
				{
					if (quitgame(mouse.mkLButton))
					{
						return;
					}
				}
				if (mx >= 990 && mx <= 1190 && my >= 765 && my <= 820) //存档按钮
				{
					savegame(boardlay, mouse.mkLButton, 2);
				}
				getpos(mx, my);
				if (mx >= 1 && mx <= 15 && my >= 1 && my <= 15 && boardlay[mx][my] == 0)
				{
					//绘制标识区域
					if (mouse.mkLButton)
					{
						boardlay[mx][my] = 2;
						//绘制棋子
						setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
						setfillstyle(BS_SOLID);
						setfillcolor(WHITE);
						fillcircle((mx - 1) * 60 + 55, (my - 1) * 60 + 55, 20);
						hand = 1;
						break;
					}
				}
			} //玩家
		}
		printf("%d\n", overall_evaluate(boardlay));
		if (win(boardlay)) //判断胜负关系
		{
			break; //跳出
		}
	}
	gamesettlement(boardlay);
	free(boardlay);
	return;
}

void board_init() //绘制原始棋盘
{
	initgraph(1250, 920, SHOWCONSOLE); // 初始化绘图环境
	setbkcolor(WHITE);
	cleardevice();
	setbkmode(TRANSPARENT);			  // 设置透明文字输出背景
	setfillcolor(RGB(255, 205, 150)); //棋盘颜色
	solidrectangle(55, 55, 895, 895); //棋盘大小
	//文字
	settextstyle(26, 13, _T("Consolas"), 0, 0, 1000, false, false, false); //文字大小
	gettextstyle(&cord);												   //获取当前字体
	cord.lfQuality = ANTIALIASED_QUALITY;								   // 更改为抗锯齿
	settextstyle(&cord);												   // 重载入字体
	settextcolor(BLACK);												   //文字颜色
	//直线
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 2);
	setlinecolor(BLACK);
	//点
	setfillstyle(BS_SOLID);
	setfillcolor(BLACK);
	for (int i = 1; i <= 15; i++) //置于循环内提高代码复用
	{
		//绘制坐标
		if (i >= 10)
		{
			outtextxy(60 * (i - 1) - 6 + 47, 2, char((i + '0') / ('9' + 1) + '0'));
			outtextxy(60 * (i - 1) + 6 + 47, 2, char((i + '0') % ('9' + 1) + '0'));
		}
		else
		{
			outtextxy(60 * (i - 1) + 47, 2, char(i + '0'));
		}
		outtextxy(9, 60 * (i - 1) + 43, char('A' + i - 1));

		//绘制棋盘线
		if (i == 1 || i == 15)
		{
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 4);
		}
		else
		{
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
		}
		line(55, 55 + 60 * (i - 1), 895, 55 + 60 * (i - 1));
		line(55 + 60 * (i - 1), 895, 55 + 60 * (i - 1), 55);
	}
	//填充点
	fillcircle(235, 235, 4);
	fillcircle(235, 715, 4);
	fillcircle(475, 475, 6);
	fillcircle(715, 235, 4);
	fillcircle(715, 715, 4);
	//退出按钮
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 2);
	setlinecolor(BLACK);
	setfillstyle(BS_SOLID);
	setfillcolor(WHITE);
	fillrectangle(990, 55, 1190, 745);
	fillrectangle(990, 765, 1190, 820);
	fillrectangle(990, 820, 1190, 875);
	opti = cord;
	opti.lfHeight = 60;
	opti.lfWidth = 24;
	settextstyle(&opti); // 重载入字体
	outtextxy(1030, 765, _T("存 档"));
	outtextxy(1030, 820, _T("退 出"));
	info = cord;
	info.lfHeight = 30;
	info.lfWidth = 11;
}