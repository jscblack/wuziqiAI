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
	chktb_init();
	//chktb_inited

	system("pause");
	return 0;
}

void chktb_init()//绘制原始棋盘
{
	initgraph(1250, 910); // 初始化绘图环境
	setbkcolor(WHITE);
	cleardevice();
	setbkmode(TRANSPARENT); // 设置透明文字输出背景
	setfillcolor(RGB(255, 205, 150));//棋盘颜色
	solidrectangle(35, 35, 875, 875);//棋盘大小
	//文字
	settextstyle(30, 15, _T("Consolas"), 0, 0, 1000, false, false, false);//文字大小
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
	for (int i = 1; i <= 15; i++)
	{
		//绘制坐标
		if (i >= 10)
		{
			outtextxy(60 * (i - 1) - 8 + 27, 0, char((i + '0') / ('9' + 1) + '0'));
			outtextxy(60 * (i - 1) + 8 + 27, 0, char((i + '0') % ('9' + 1) + '0'));
		}
		else
		{
			outtextxy(60 * (i - 1) + 27, 0, char(i + '0'));
		}
		outtextxy(10, 60 * (i - 1) + 20, char('A' + i - 1));

		//绘制棋盘线
		if (i == 1 || i == 15)
		{
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 4);
		}
		else
		{
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
		}
		line(35, 35 + 60 * (i - 1), 875, 35 + 60 * (i - 1));
		line(35 + 60 * (i - 1), 875, 35 + 60 * (i - 1), 35);
	}
	//填充点
	fillcircle(215, 215, 4);
	fillcircle(215, 695, 4);
	fillcircle(455, 455, 6);
	fillcircle(695, 215, 4);
	fillcircle(695, 695, 4);
}