/*
 * @Author: Gehrychiang
 * @Website: www.yilantingfeng.site
 * @E-mail: gehrychiang@aliyun.com
 */
 //引用库
#include "wuziqiAI.h"
LOGFONT overlay_f;//全局字体

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
int win(int** a)//获胜条件，1黑获胜，2白获胜，3和局
{
	int flag = 1;
	for (int i = 1; i <= 15; i++)
	{
		for (int j = 1; j <= 15; j++)
		{
			if (a[i][j] == 0)//尚有空位
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
	int** boardlay = (int**)calloc(16, sizeof(int**));//1代表黑子 2代表白子
	for (int i = 0; i <= 16; ++i)
	{
		*(boardlay + i) = (int*)calloc(16, sizeof(int));
	}

	int hand = 1;// 黑子先落子 1黑子 0白子
	while (1)
	{
		if (hand == 1)//落黑子
		{
			while (1)
			{
				MOUSEMSG mouse = GetMouseMsg(); // 获取鼠标信息
							//mouse.x
							//mouse.y
				int mx = mouse.x;
				int my = mouse.y;
				if (mx >= 990 && mx <= 1090 && my >= 820 && my <= 895)//
				{
					if (mouse.mkLButton)
					{
						return;
					}
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
		else if (hand == 2)//落白子
		{
			while (1)
			{
				MOUSEMSG mouse = GetMouseMsg(); // 获取鼠标信息
							//mouse.x
							//mouse.y
				int mx = mouse.x;
				int my = mouse.y;
				if (mx >= 990 && mx <= 1090 && my >= 820 && my <= 895)
				{
					if (mouse.mkLButton)
					{
						return;
					}
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
			}
		}
		if (win(boardlay))
		{
			break;
		}
	}
	LOGFONT win_font = overlay_f;
	win_font.lfHeight = 80;
	win_font.lfWidth = 36;
	switch (win(boardlay))
	{
	case 1:
	{
		settextstyle(&win_font);
		outtextxy(1020, 200, _T("黑胜"));
		break;
	}

	case 2:
	{
		settextstyle(&win_font);
		outtextxy(1020, 200, _T("白胜"));
		break;
	}

	case 3:
	{
		settextstyle(&win_font);
		outtextxy(1020, 200, _T("和棋"));
		break;
	}

	}
	free(boardlay);
	Sleep(2000);
	return;
}
void board_init()//绘制原始棋盘
{
	initgraph(1250, 920); // 初始化绘图环境
	setbkcolor(WHITE);
	cleardevice();
	setbkmode(TRANSPARENT); // 设置透明文字输出背景
	setfillcolor(RGB(255, 205, 150));//棋盘颜色
	solidrectangle(55, 55, 895, 895);//棋盘大小
	//文字
	settextstyle(26, 13, _T("Consolas"), 0, 0, 1000, false, false, false);//文字大小
	gettextstyle(&overlay_f);						//获取当前字体
	overlay_f.lfQuality = ANTIALIASED_QUALITY;		// 更改为抗锯齿
	settextstyle(&overlay_f);						// 重载入字体
	settextcolor(BLACK);//文字颜色
	//直线
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 2);
	setlinecolor(BLACK);
	//点
	setfillstyle(BS_SOLID);
	setfillcolor(BLACK);
	for (int i = 1; i <= 15; i++)//置于循环内提高代码复用
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
	overlay_f.lfHeight = 60;
	overlay_f.lfWidth = 24;
	settextstyle(&overlay_f);						// 重载入字体
	outtextxy(1030, 765, _T("读 取"));
	outtextxy(1030, 820, _T("退 出"));
}