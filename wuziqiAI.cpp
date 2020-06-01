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
	printf_s("Gomoku V1.1\n");
	printf_s("Author:gehrychiang\n");
	//board initilized
	difficultreq();
	privacyreq();
	//game started
	game();
	//game ended

	//system("pause");
	return 0;
}

//ai实现2020.6.1
//ai主入口
int ai_cal(int* chbt, char* chbm, int turn, int depth)
{
	int* pval, i, j, k, ** pord, * pt, v, vt, p;
	char* tchbm;
	int zero;
	if (step == 0)
	{
		step = 1;
		return 112;
	}
	if (step == 1)
	{
		return 112;
	}
	if (turn == 1)
	{
		zero = -10000000;
	}
	else
	{
		zero = 10000000;
	}
	tchbm = (char*)malloc(900);
	pval = (int*)malloc(900);
	pord = (int**)malloc(225 * sizeof(int*));
	for (i = 0; i < 225; i++)
	{
		if (!chbt[i])
		{
			if (turn == 1)
			{
				pval[i] = gvaldivb(chbm, chbt, i / 15, i % 15) - 0.01 * gvaldivw(chbm, chbt, i / 15, i % 15);
			}
			else
			{
				pval[i] = gvaldivw(chbm, chbt, i / 15, i % 15) - 0.01 * gvaldivb(chbm, chbt, i / 15, i % 15);
			}
			pord[i] = pval + i;
		}
		else
		{
			pord[i] = &zero;
		}
	}
	if (turn == 1)
	{
		for (i = 0; i < 50 + step / 5; i++)
		{
			for (j = i + 1; j < 225; j++)
			{
				if (*pord[i] < *pord[j])
				{
					pt = pord[i];
					pord[i] = pord[j];
					pord[j] = pt;
				}
			}
		}
	}
	else
	{
		for (i = 0; i < 50 + step / 5; i++)
		{
			for (j = i + 1; j < 225; j++)
			{
				if (*pord[i] > * pord[j])
				{
					pt = pord[i];
					pord[i] = pord[j];
					pord[j] = pt;
				}
			}
		}
	}
	i = 0;
	k = 0;
	if (*pord[k] > 600000 || *pord[k] < -600000)
	{
		p = pord[k] - pval;
		free(tchbm);
		free(pval);
		free(pord);
		return p;
	}
	j = pord[k] - pval;
	p = j;
	memcpy(tchbm, chbm, 900);
	uchbm(chbt, tchbm, j / 15, j % 15, turn);
	chbt[j] = turn;
	v = cho(chbt, tchbm, 3 - turn, turn, depth - 1, zero);
	chbt[j] = 0;
	for (k = 1; i < 20 + step / 10 && k < 50 + step / 5; k++)
	{
		if (*pord[k] != *pord[k - 1])
		{
			i++;
		}
		if (*pord[k] == zero)
		{
			break;
		}
		j = pord[k] - pval;
		memcpy(tchbm, chbm, 900);
		uchbm(chbt, tchbm, j / 15, j % 15, turn);
		chbt[j] = turn;
		vt = cho(chbt, tchbm, 3 - turn, turn, depth - 1, v);
		chbt[j] = 0;
		if (turn == 1)
		{
			if (vt > v)
			{
				v = vt;
				p = j;
			}
		}
		else
		{
			if (vt < v)
			{
				v = vt;
				p = j;
			}
		}
	}
	free(tchbm);
	free(pval);
	free(pord);
	return p;
}
//主搜索函数
int cho(int* chbt, char* chbm, int turn, int rt, int depth, int expect)
{
	int* pval, i, j, k, ** pord, * pt, v, vt;
	char* tchbm;
	int zero;
	zero = (turn == 1) ? -10000000 : 10000000;
	tchbm = (char*)malloc(900);
	pval = (int*)malloc(900);
	pord = (int**)malloc(225 * sizeof(int*));
	if (depth < 0)
	{
		for (i = 0; i < 225; i++)
		{
			if (!chbt[i])
			{
				if (turn == 1)
				{
					pval[i] = gvaldivb(chbm, chbt, i / 15, i % 15);
				}
				else
				{
					pval[i] = gvaldivw(chbm, chbt, i / 15, i % 15);
				}
				pord[i] = pval + i;
			}
			else
			{
				pord[i] = &zero;
			}
		}
		if (turn == 1)
		{
			i = 0;
			for (j = i + 1; j < 225; j++)
			{
				if (*pord[i] < *pord[j])
				{
					pt = pord[i];
					pord[i] = pord[j];
					pord[j] = pt;
				}
			}
		}
		else
		{
			i = 0;
			for (j = i + 1; j < 225; j++)
			{
				if (*pord[i] > * pord[j])
				{
					pt = pord[i];
					pord[i] = pord[j];
					pord[j] = pt;
				}
			}
		}
		j = pord[0] - pval;
		memcpy(tchbm, chbm, 900);
		if (**pord != zero)
			uchbm(chbt, tchbm, j / 15, j % 15, turn);
		v = (turn == 1) ? gvaw(tchbm) : gvab(tchbm);
		free(tchbm);
		free(pval);
		free(pord);
		return v;
	}
	for (i = 0; i < 225; i++)
	{
		if (!chbt[i])
		{
			if (turn == 1)
			{
				pval[i] = gvaldivb(chbm, chbt, i / 15, i % 15) - 0.02 * gvaldivw(chbm, chbt, i / 15, i % 15);
				;
			}
			else
			{
				pval[i] = gvaldivw(chbm, chbt, i / 15, i % 15) - 0.02 * gvaldivb(chbm, chbt, i / 15, i % 15);
			}
			pord[i] = pval + i;
		}
		else
		{
			pord[i] = &zero;
		}
	}
	if (turn == 1)
	{
		for (i = 0; i < 20 + step / 5; i++)
		{
			for (j = i + 1; j < 225; j++)
			{
				if (*pord[i] < *pord[j])
				{
					pt = pord[i];
					pord[i] = pord[j];
					pord[j] = pt;
				}
			}
		}
	}
	else
	{
		for (i = 0; i < 20 + step / 5; i++)
		{
			for (j = i + 1; j < 225; j++)
			{
				if (*pord[i] > * pord[j])
				{
					pt = pord[i];
					pord[i] = pord[j];
					pord[j] = pt;
				}
			}
		}
	}
	i = 0;
	k = 0;
	if (*pord[0] > 600000 || *pord[0] < -600000)
	{
		j = pord[0] - pval;
		memcpy(tchbm, chbm, 900);
		if (**pord != zero)
			uchbm(chbt, tchbm, j / 15, j % 15, turn);
		v = (turn == 1) ? gvaw(tchbm) : gvab(tchbm);
		free(tchbm);
		free(pval);
		free(pord);
		return v;
	}
	j = pord[k] - pval;
	memcpy(tchbm, chbm, 900);
	if (**pord != zero)
		uchbm(chbt, tchbm, j / 15, j % 15, turn);
	chbt[j] = turn;
	v = cho(chbt, tchbm, 3 - turn, rt, depth - 1, zero);
	chbt[j] = 0;
	for (k = 1; i < 10 + step / 16 && k < 20 + step / 8; k++)
	{
		if (*pord[k] != *pord[k - 1])
		{
			i++;
		}
		if (*pord[k] == zero)
		{
			break;
		}
		j = pord[k] - pval;
		memcpy(tchbm, chbm, 900);
		uchbm(chbt, tchbm, j / 15, j % 15, turn);
		chbt[j] = turn;
		vt = cho(chbt, tchbm, 3 - turn, rt, depth - 1, v);
		chbt[j] = 0;
		if (turn == 1)
		{
			v = max(v, vt);
			if (v >= expect)
			{
				free(tchbm);
				free(pval);
				free(pord);
				return v;
			}
		}
		else
		{
			v = min(v, vt);
			if (v <= expect)
			{
				free(tchbm);
				free(pval);
				free(pord);
				return v;
			}
		}
	}
	free(tchbm);
	free(pval);
	free(pord);
	return v;
}
//棋子加入，更新棋盘布局
void chess_add(int x, int y)
{
	if (x > -1 && y > -1 && x < 15 && y < 15 && (!chb[y + x * 15]))
	{
		uchbm(chb, chbmstep, x, y, (step - 1) % 2 + 1);
		chb[y + x * 15] = (step - 1) % 2 + 1;
		step++;
	}
}
//尝试当前解
void uchbm(int* chbt, char* chbm, int posx, int posy, int turn)
{
	int i, j, x, y;
	if (turn == 1)
	{
		i = 0;
		j = 3;
		x = posx + 1;
		y = posy + 0;
		while (x < 15 && chbt[x * 15 + y] == 2)
		{
			chbm[x * 60 + y * 4 + 0]--;
			x += 1;
			y += 0;
		}
		x = posx - 1;
		y = posy - 0;
		while (x > -1 && chbt[x * 15 + y] == 2)
		{
			chbm[x * 60 + y * 4 + 0]--;
			x -= 1;
			y -= 0;
		}
		x = posx + 1;
		y = posy + 0;
		while (x < 15 && chbt[x * 15 + y] == 1)
		{
			i++;
			x += 1;
			y += 0;
		}
		if (x == 15 || chbt[x * 15 + y] == 2)
		{
			j--;
		}
		x = posx - 1;
		y = posy - 0;
		while (x > -1 && chbt[x * 15 + y] == 1)
		{
			i++;
			x -= 1;
			y -= 0;
		}
		if (x == -1 || chbt[x * 15 + y] == 2)
		{
			j--;
		}
		i = min(i, 4) * 3 + j;
		x = posx + 1;
		y = posy + 0;
		while (x < 15 && chbt[x * 15 + y] == 1)
		{
			chbm[x * 60 + y * 4 + 0] = i;
			x += 1;
			y += 0;
		}
		x = posx - 1;
		y = posy - 0;
		while (x > 0 && chbt[x * 15 + y] == 1)
		{
			chbm[x * 60 + y * 4 + 0] = i;
			x -= 1;
			y -= 0;
		}
		chbm[posx * 60 + posy * 4 + 0] = i;
		i = 0;
		j = 3;
		x = posx + 1;
		y = posy + -1;
		while (x < 15 && y > -1 && chbt[x * 15 + y] == 2)
		{
			chbm[x * 60 + y * 4 + 1]--;
			x += 1;
			y += -1;
		}
		x = posx - 1;
		y = posy - -1;
		while (x > -1 && y < 15 && chbt[x * 15 + y] == 2)
		{
			chbm[x * 60 + y * 4 + 1]--;
			x -= 1;
			y -= -1;
		}
		x = posx + 1;
		y = posy + -1;
		while (x < 15 && y > -1 && chbt[x * 15 + y] == 1)
		{
			i++;
			x += 1;
			y += -1;
		}
		if (x == 15 || y == -1 || chbt[x * 15 + y] == 2)
		{
			j--;
		}
		x = posx - 1;
		y = posy - -1;
		while (x > -1 && y < 15 && chbt[x * 15 + y] == 1)
		{
			i++;
			x -= 1;
			y -= -1;
		}
		if (x == -1 || y == 15 || chbt[x * 15 + y] == 2)
		{
			j--;
		}
		i = min(i, 4) * 3 + j;
		x = posx + 1;
		y = posy + -1;
		while (x < 15 && y > -1 && chbt[x * 15 + y] == 1)
		{
			chbm[x * 60 + y * 4 + 1] = i;
			x += 1;
			y += -1;
		}
		x = posx - 1;
		y = posy - -1;
		while (x > -1 && y < 15 && chbt[x * 15 + y] == 1)
		{
			chbm[x * 60 + y * 4 + 1] = i;
			x -= 1;
			y -= -1;
		}
		chbm[posx * 60 + posy * 4 + 1] = i;
		i = 0;
		j = 3;
		x = posx + 0;
		y = posy + -1;
		while (y > -1 && chbt[x * 15 + y] == 2)
		{
			chbm[x * 60 + y * 4 + 2]--;
			x += 0;
			y += -1;
		}
		x = posx - 0;
		y = posy - -1;
		while (y < 15 && chbt[x * 15 + y] == 2)
		{
			chbm[x * 60 + y * 4 + 2]--;
			x -= 0;
			y -= -1;
		}
		x = posx + 0;
		y = posy + -1;
		while (y > -1 && chbt[x * 15 + y] == 1)
		{
			i++;
			x += 0;
			y += -1;
		}
		if (y == -1 || chbt[x * 15 + y] == 2)
		{
			j--;
		}
		x = posx - 0;
		y = posy - -1;
		while (y < 15 && chbt[x * 15 + y] == 1)
		{
			i++;
			x -= 0;
			y -= -1;
		}
		if (y == 15 || chbt[x * 15 + y] == 2)
		{
			j--;
		}
		i = min(i, 4) * 3 + j;
		x = posx + 0;
		y = posy + -1;
		while (y > -1 && chbt[x * 15 + y] == 1)
		{
			chbm[x * 60 + y * 4 + 2] = i;
			x += 0;
			y += -1;
		}
		x = posx - 0;
		y = posy - -1;
		while (y < 15 && chbt[x * 15 + y] == 1)
		{
			chbm[x * 60 + y * 4 + 2] = i;
			x -= 0;
			y -= -1;
		}
		chbm[posx * 60 + posy * 4 + 2] = i;
		i = 0;
		j = 3;
		x = posx + -1;
		y = posy + -1;
		while (x > -1 && y > -1 && chbt[x * 15 + y] == 2)
		{
			chbm[x * 60 + y * 4 + 3]--;
			x += -1;
			y += -1;
		}
		x = posx - -1;
		y = posy - -1;
		while (x < 15 && y < 15 && chbt[x * 15 + y] == 2)
		{
			chbm[x * 60 + y * 4 + 3]--;
			x -= -1;
			y -= -1;
		}
		x = posx + -1;
		y = posy + -1;
		while (x > -1 && y > -1 && chbt[x * 15 + y] == 1)
		{
			i++;
			x += -1;
			y += -1;
		}
		if (x == -1 || y == -1 || chbt[x * 15 + y] == 2)
		{
			j--;
		}
		x = posx - -1;
		y = posy - -1;
		while (x < 15 && y < 15 && x < 15 && y < 15 && chbt[x * 15 + y] == 1)
		{
			i++;
			x -= -1;
			y -= -1;
		}
		if (x == 15 || y == 15 || chbt[x * 15 + y] == 2)
		{
			j--;
		}
		i = min(i, 4) * 3 + j;
		x = posx + -1;
		y = posy + -1;
		while (x > -1 && y > -1 && chbt[x * 15 + y] == 1)
		{
			chbm[x * 60 + y * 4 + 3] = i;
			x += -1;
			y += -1;
		}
		x = posx - -1;
		y = posy - -1;
		while (x < 15 && y < 15 && chbt[x * 15 + y] == 1)
		{
			chbm[x * 60 + y * 4 + 3] = i;
			x -= -1;
			y -= -1;
		}
		chbm[posx * 60 + posy * 4 + 3] = i;
	}
	else
	{
		i = 0;
		j = 18;
		x = posx + 1;
		y = posy + 0;
		while (x < 15 && chbt[x * 15 + y] == 1)
		{
			chbm[x * 60 + y * 4 + 0]--;
			x += 1;
			y += 0;
		}
		x = posx - 1;
		y = posy - 0;
		while (x > -1 && chbt[x * 15 + y] == 1)
		{
			chbm[x * 60 + y * 4 + 0]--;
			x -= 1;
			y -= 0;
		}
		x = posx + 1;
		y = posy + 0;
		while (x < 15 && chbt[x * 15 + y] == 2)
		{
			i++;
			x += 1;
			y += 0;
		}
		if (x == 15 || chbt[x * 15 + y] == 1)
		{
			j--;
		}
		x = posx - 1;
		y = posy - 0;
		while (x > -1 && chbt[x * 15 + y] == 2)
		{
			i++;
			x -= 1;
			y -= 0;
		}
		if (x == -1 || chbt[x * 15 + y] == 1)
		{
			j--;
		}
		i = min(i, 4) * 3 + j;
		x = posx + 1;
		y = posy + 0;
		while (x < 15 && chbt[x * 15 + y] == 2)
		{
			chbm[x * 60 + y * 4 + 0] = i;
			x += 1;
			y += 0;
		}
		x = posx - 1;
		y = posy - 0;
		while (x > -1 && chbt[x * 15 + y] == 2)
		{
			chbm[x * 60 + y * 4 + 0] = i;
			x -= 1;
			y -= 0;
		}
		chbm[posx * 60 + posy * 4 + 0] = i;
		i = 0;
		j = 18;
		x = posx + 1;
		y = posy + -1;
		while (x < 15 && y > -1 && chbt[x * 15 + y] == 1)
		{
			chbm[x * 60 + y * 4 + 1]--;
			x += 1;
			y += -1;
		}
		x = posx - 1;
		y = posy - -1;
		while (x > -1 && y < 15 && chbt[x * 15 + y] == 1)
		{
			chbm[x * 60 + y * 4 + 1]--;
			x -= 1;
			y -= -1;
		}
		x = posx + 1;
		y = posy + -1;
		while (x < 15 && y > -1 && chbt[x * 15 + y] == 2)
		{
			i++;
			x += 1;
			y += -1;
		}
		if (x == 15 || y == -1 || chbt[x * 15 + y] == 1)
		{
			j--;
		}
		x = posx - 1;
		y = posy - -1;
		while (x > -1 && y < 15 && chbt[x * 15 + y] == 2)
		{
			i++;
			x -= 1;
			y -= -1;
		}
		if (x == -1 || y == 15 || chbt[x * 15 + y] == 1)
		{
			j--;
		}
		i = min(i, 4) * 3 + j;
		x = posx + 1;
		y = posy + -1;
		while (x < 15 && y > -1 && chbt[x * 15 + y] == 2)
		{
			chbm[x * 60 + y * 4 + 1] = i;
			x += 1;
			y += -1;
		}
		x = posx - 1;
		y = posy - -1;
		while (x > -1 && y < 15 && chbt[x * 15 + y] == 2)
		{
			chbm[x * 60 + y * 4 + 1] = i;
			x -= 1;
			y -= -1;
		}
		chbm[posx * 60 + posy * 4 + 1] = i;
		i = 0;
		j = 18;
		x = posx + 0;
		y = posy + -1;
		while (y > -1 && chbt[x * 15 + y] == 1)
		{
			chbm[x * 60 + y * 4 + 2]--;
			x += 0;
			y += -1;
		}
		x = posx - 0;
		y = posy - -1;
		while (y < 15 && chbt[x * 15 + y] == 1)
		{
			chbm[x * 60 + y * 4 + 2]--;
			x -= 0;
			y -= -1;
		}
		x = posx + 0;
		y = posy + -1;
		while (y > -1 && chbt[x * 15 + y] == 2)
		{
			i++;
			x += 0;
			y += -1;
		}
		if (y == -1 || chbt[x * 15 + y] == 1)
		{
			j--;
		}
		x = posx - 0;
		y = posy - -1;
		while (y < 15 && chbt[x * 15 + y] == 2)
		{
			i++;
			x -= 0;
			y -= -1;
		}
		if (y == 15 || chbt[x * 15 + y] == 1)
		{
			j--;
		}
		i = min(i, 4) * 3 + j;
		x = posx + 0;
		y = posy + -1;
		while (y > -1 && chbt[x * 15 + y] == 2)
		{
			chbm[x * 60 + y * 4 + 2] = i;
			x += 0;
			y += -1;
		}
		x = posx - 0;
		y = posy - -1;
		while (y < 15 && chbt[x * 15 + y] == 2)
		{
			chbm[x * 60 + y * 4 + 2] = i;
			x -= 0;
			y -= -1;
		}
		chbm[posx * 60 + posy * 4 + 2] = i;
		i = 0;
		j = 18;
		x = posx + -1;
		y = posy + -1;
		while (x > -1 && y > -1 && chbt[x * 15 + y] == 1)
		{
			chbm[x * 60 + y * 4 + 3]--;
			x += -1;
			y += -1;
		}
		x = posx - -1;
		y = posy - -1;
		while (x < 15 && y < 15 && chbt[x * 15 + y] == 1)
		{
			chbm[x * 60 + y * 4 + 3]--;
			x -= -1;
			y -= -1;
		}
		x = posx + -1;
		y = posy + -1;
		while (x > -1 && y > -1 && chbt[x * 15 + y] == 2)
		{
			i++;
			x += -1;
			y += -1;
		}
		if (x == -1 || y == -1 || chbt[x * 15 + y] == 1)
		{
			j--;
		}
		x = posx - -1;
		y = posy - -1;
		while (x < 15 && y < 15 && chbt[x * 15 + y] == 2)
		{
			i++;
			x -= -1;
			y -= -1;
		}
		if (x == 15 || y == 15 || chbt[x * 15 + y] == 1)
		{
			j--;
		}
		i = min(i, 4) * 3 + j;
		x = posx + -1;
		y = posy + -1;
		while (x > -1 && y > -1 && chbt[x * 15 + y] == 2)
		{
			chbm[x * 60 + y * 4 + 3] = i;
			x += -1;
			y += -1;
		}
		x = posx - -1;
		y = posy - -1;
		while (x < 15 && y < 15 && chbt[x * 15 + y] == 2)
		{
			chbm[x * 60 + y * 4 + 3] = i;
			x -= -1;
			y -= -1;
		}
		chbm[posx * 60 + posy * 4 + 3] = i;
	}
}
//黑子层搜索
int gvaldivb(char* chbm, int* chbt, int x, int y)
{
	int v, p, mod1, mod2, mod3, mod4;
	v = 0;
	p = 15 * x + y;
	mod1 = 3;
	mod2 = 3;
	mod3 = 3;
	mod4 = 3;
	if (x < 14)
	{
		if (chbt[p + 15] == 2)
		{
			v += valmapba[chbm[p * 4 + 60] - 1] - valmapba[chbm[p * 4 + 60]];
			mod1--;
		}
		if (chbt[p + 15] == 1)
		{
			v -= valmapba[chbm[p * 4 + 60]];
			mod1 += chbm[p * 4 + 60];
		}
		if (y < 14)
		{
			if (chbt[p + 16] == 2)
			{
				v += valmapba[chbm[p * 4 + 67] - 1] - valmapba[chbm[p * 4 + 67]];
				mod4--;
			}
			if (chbt[p + 16] == 1)
			{
				v -= valmapba[chbm[p * 4 + 67]];
				mod4 += chbm[p * 4 + 67];
			}
		}
		else
		{
			mod4--;
		}
		if (y > 0)
		{
			if (chbt[p + 14] == 2)
			{
				v += valmapba[chbm[p * 4 + 57] - 1] - valmapba[chbm[p * 4 + 57]];
				mod2--;
			}
			if (chbt[p + 14] == 1)
			{
				v -= valmapba[chbm[p * 4 + 57]];
				mod2 += chbm[p * 4 + 57];
			}
		}
		else
		{
			mod2--;
		}
	}
	else
	{
		mod1--;
		mod2--;
		mod4--;
	}
	if (x > 0)
	{
		if (chbt[p - 15] == 2)
		{
			v += valmapba[chbm[p * 4 - 60] - 1] - valmapba[chbm[p * 4 - 60]];
			mod1--;
		}
		if (chbt[p - 15] == 1)
		{
			v -= valmapba[chbm[p * 4 - 60]];
			mod1 += chbm[p * 4 - 60];
		}
		if (y > 0)
		{
			if (chbt[p - 16] == 2)
			{
				v += valmapba[chbm[p * 4 - 61] - 1] - valmapba[chbm[p * 4 - 61]];
				mod4--;
			}
			if (chbt[p - 16] == 1)
			{
				v -= valmapba[chbm[p * 4 - 61]];
				mod4 += chbm[p * 4 - 61];
			}
		}
		else
		{
			mod4--;
		}
		if (y < 14)
		{
			if (chbt[p - 14] == 2)
			{
				v += valmapba[chbm[p * 4 - 55] - 1] - valmapba[chbm[p * 4 - 55]];
				mod2--;
			}
			if (chbt[p - 14] == 1)
			{
				v -= valmapba[chbm[p * 4 - 55]];
				mod2 += chbm[p * 4 - 55];
			}
		}
		else
		{
			mod2--;
		}
	}
	else
	{
		mod1--;
		mod2--;
		mod4--;
	}
	if (y > 0)
	{
		if (chbt[p - 1] == 2)
		{
			v += valmapba[chbm[p * 4 - 2] - 1] - valmapba[chbm[p * 4 - 2]];
			mod3--;
		}
		if (chbt[p - 1] == 1)
		{
			v -= valmapba[chbm[p * 4 - 2]];
			mod3 += chbm[p * 4 - 2];
		}
	}
	else
	{
		mod3--;
	}
	if (y < 14)
	{
		if (chbt[p + 1] == 2)
		{
			v += valmapba[chbm[p * 4 + 6] - 1] - valmapba[chbm[p * 4 + 6]];
			mod3--;
		}
		if (chbt[p + 1] == 1)
		{
			v -= valmapba[chbm[p * 4 + 6]];
			mod3 += chbm[p * 4 + 6];
		}
	}
	else
	{
		mod3--;
	}
	while (mod1 > 15)
		mod1 -= 3;
	while (mod2 > 15)
		mod2 -= 3;
	while (mod3 > 15)
		mod3 -= 3;
	while (mod4 > 15)
		mod4 -= 3;
	v += valmapba[mod1] + valmapba[mod2] + valmapba[mod3] + valmapba[mod4];
	return v;
}
//白子层搜索
int gvaldivw(char* chbm, int* chbt, int x, int y)
{
	int v, p, mod1, mod2, mod3, mod4;
	v = 0;
	p = 15 * x + y;
	mod1 = 18;
	mod2 = 18;
	mod3 = 18;
	mod4 = 18;
	if (x < 14)
	{
		if (chbt[p + 15] == 1)
		{
			v += valmapwa[chbm[p * 4 + 60] - 1] - valmapwa[chbm[p * 4 + 60]];
			mod1--;
		}
		if (chbt[p + 15] == 2)
		{
			v -= valmapwa[chbm[p * 4 + 60]];
			mod1 += chbm[p * 4 + 60] - 15;
		}
		if (y < 14)
		{
			if (chbt[p + 16] == 1)
			{
				v += valmapwa[chbm[p * 4 + 67] - 1] - valmapwa[chbm[p * 4 + 67]];
				mod4--;
			}
			if (chbt[p + 16] == 2)
			{
				v -= valmapwa[chbm[p * 4 + 67]];
				mod4 += chbm[p * 4 + 67] - 15;
			}
		}
		else
		{
			mod4--;
		}
		if (y > 0)
		{
			if (chbt[p + 14] == 1)
			{
				v += valmapwa[chbm[p * 4 + 57] - 1] - valmapwa[chbm[p * 4 + 57]];
				mod2--;
			}
			if (chbt[p + 14] == 2)
			{
				v -= valmapwa[chbm[p * 4 + 57]];
				mod2 += chbm[p * 4 + 57] - 15;
			}
		}
		else
		{
			mod2--;
		}
	}
	else
	{
		mod1--;
		mod2--;
		mod4--;
	}
	if (x > 0)
	{
		if (chbt[p - 15] == 1)
		{
			v += valmapwa[chbm[p * 4 - 60] - 1] - valmapwa[chbm[p * 4 - 60]];
			mod1--;
		}
		if (chbt[p - 15] == 2)
		{
			v -= valmapwa[chbm[p * 4 - 60]];
			mod1 += chbm[p * 4 - 60] - 15;
		}
		if (y > 0)
		{
			if (chbt[p - 16] == 1)
			{
				v += valmapwa[chbm[p * 4 - 61] - 1] - valmapwa[chbm[p * 4 - 61]];
				mod4--;
			}
			if (chbt[p - 16] == 2)
			{
				v -= valmapwa[chbm[p * 4 - 61]];
				mod4 += chbm[p * 4 - 61] - 15;
			}
		}
		else
		{
			mod4--;
		}
		if (y < 14)
		{
			if (chbt[p - 14] == 1)
			{
				v += valmapwa[chbm[p * 4 - 55] - 1] - valmapwa[chbm[p * 4 - 55]];
				mod2--;
			}
			if (chbt[p - 14] == 2)
			{
				v -= valmapwa[chbm[p * 4 - 55]];
				mod2 += chbm[p * 4 - 55] - 15;
			}
		}
		else
		{
			mod2--;
		}
	}
	else
	{
		mod1--;
		mod2--;
		mod4--;
	}
	if (y > 0)
	{
		if (chbt[p - 1] == 1)
		{
			v += valmapwa[chbm[p * 4 - 2] - 1] - valmapwa[chbm[p * 4 - 2]];
			mod3--;
		}
		if (chbt[p - 1] == 2)
		{
			v -= valmapwa[chbm[p * 4 - 2]];
			mod3 += chbm[p * 4 - 2] - 15;
		}
	}
	else
	{
		mod3--;
	}
	if (y < 14)
	{
		if (chbt[p + 1] == 1)
		{
			v += valmapwa[chbm[p * 4 + 6] - 1] - valmapwa[chbm[p * 4 + 6]];
			mod3--;
		}
		if (chbt[p + 1] == 2)
		{
			v -= valmapwa[chbm[p * 4 + 6]];
			mod3 += chbm[p * 4 + 6] - 15;
		}
	}
	else
	{
		mod3--;
	}
	while (mod1 > 30)
		mod1 -= 3;
	while (mod2 > 30)
		mod2 -= 3;
	while (mod3 > 30)
		mod3 -= 3;
	while (mod4 > 30)
		mod4 -= 3;
	v += valmapwa[mod1] + valmapwa[mod2] + valmapwa[mod3] + valmapwa[mod4];
	return v;
}
//黑分数统计
int gvab(char* chbm)
{
	int i, j;
	j = 0;
	for (i = 0; i < 900; i++)
	{
		j += valmapb[chbm[i]];
	}
	return j;
}
//白分数统计
int gvaw(char* chbm)
{
	int i, j;
	j = 0;
	for (i = 0; i < 900; i++)
	{
		j += valmapw[chbm[i]];
	}
	return j;
}
//

//gui和逻辑已经构建完成2020.5.9
//弹框实现
LRESULT CALLBACK CBHookProcA(int nCode, WPARAM wParam, LPARAM lParam)
{
	HWND hwnd = (HWND)wParam;
	if (nCode == HCBT_ACTIVATE)
	{
		SetDlgItemText(hwnd, IDYES, L"易");
		SetDlgItemText(hwnd, IDNO, L"难");
	}
	return 0;
}
LRESULT CALLBACK CBHookProcB(int nCode, WPARAM wParam, LPARAM lParam)
{
	HWND hwnd = (HWND)wParam;
	if (nCode == HCBT_ACTIVATE)
	{
		SetDlgItemText(hwnd, IDYES, L"智障版");
		SetDlgItemText(hwnd, IDNO, L"易");
	}
	return 0;
}
int MyMessageBoxA(HWND hwnd, const TCHAR* szText, const TCHAR* szCaption, UINT uType)
{
	int ret;
	HHOOK hHook = SetWindowsHookEx(WH_CBT, CBHookProcA, nullptr, GetCurrentThreadId());
	ret = MessageBoxEx(hwnd, szText, szCaption, uType, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
	UnhookWindowsHookEx(hHook);
	return ret;
}
int MyMessageBoxB(HWND hwnd, const TCHAR* szText, const TCHAR* szCaption, UINT uType)
{
	int ret;
	HHOOK hHook = SetWindowsHookEx(WH_CBT, CBHookProcB, nullptr, GetCurrentThreadId());
	ret = MessageBoxEx(hwnd, szText, szCaption, uType, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
	UnhookWindowsHookEx(hHook);
	return ret;
}
//

//存档加密实现
std::string sha1(std::string s)
{
	const char HEX_CHAR[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	const unsigned int K[] = { 0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6 };
	//扩展成K*512位
	unsigned int l;
	l = (unsigned int)s.length() * 8;
	unsigned int* data = (unsigned int*)calloc(sizeof(unsigned int), ((l / 512U) + 1U) * 512U);
	for (unsigned int i = 0; i < s.length(); ++i)
	{
		data[i / 4] |= (s[i] << (unsigned int)8 * (3 - (i % 4)));
	}
	data[s.length() / 4] |= (128 << (unsigned int)8 * (3 - (s.length() % 4)));
	data[((l / 512) + 1) * 512 / 32 - 1] = l;
	l = (l / 512) + 1;
	//开始计算
	unsigned int H[5], G[5];
	H[0] = G[0] = 0x67452301;
	H[1] = G[1] = 0xEFCDAB89;
	H[2] = G[2] = 0x98BADCFE;
	H[3] = G[3] = 0x10325476;
	H[4] = G[4] = 0xC3D2E1F0;
	for (unsigned int i = 0; i < l; ++i)
	{
		unsigned int W[80];
		int t;
		for (t = 0; t < 16; ++t)
			W[t] = data[i * 16 + t];
		for (t = 16; t < 80; ++t)
		{
			unsigned int tmp = W[t - 3] ^ W[t - 8] ^ W[t - 14] ^ W[t - 16];
			W[t] = (tmp << 1) | (tmp >> 31);
		}
		unsigned int tmp;
		for (t = 0; t < 5; ++t)
			H[t] = G[t];
		for (t = 0; t < 20; ++t)
		{
			tmp = ((H[0] << 5) | (H[0] >> 27)) + ((H[1] & H[2]) | (~H[1] & H[3])) + H[4] + W[t] + K[0];
			H[4] = H[3];
			H[3] = H[2];
			H[2] = (H[1] << 30) | (H[1] >> 2);
			H[1] = H[0];
			H[0] = tmp;
		}
		for (t = 20; t < 40; ++t)
		{
			tmp = ((H[0] << 5) | (H[0] >> 27)) + (H[1] ^ H[2] ^ H[3]) + H[4] + W[t] + K[1];
			H[4] = H[3];
			H[3] = H[2];
			H[2] = (H[1] << 30) | (H[1] >> 2);
			H[1] = H[0];
			H[0] = tmp;
		}
		for (t = 40; t < 60; ++t)
		{
			tmp = ((H[0] << 5) | (H[0] >> 27)) + ((H[1] & H[2]) | (H[2] & H[3]) | (H[1] & H[3])) + H[4] + W[t] + K[2];
			H[4] = H[3];
			H[3] = H[2];
			H[2] = (H[1] << 30) | (H[1] >> 2);
			H[1] = H[0];
			H[0] = tmp;
		}
		for (t = 60; t < 80; ++t)
		{
			tmp = ((H[0] << 5) | (H[0] >> 27)) + (H[1] ^ H[2] ^ H[3]) + H[4] + W[t] + K[3];
			H[4] = H[3];
			H[3] = H[2];
			H[2] = (H[1] << 30) | (H[1] >> 2);
			H[1] = H[0];
			H[0] = tmp;
		}
		for (t = 0; t < 5; ++t)
			G[t] += H[t];
	}
	free(data);
	std::string buf;
	for (int i = 0; i < 40; ++i)
	{
		buf += HEX_CHAR[(G[i / 8] >> (4 * (7 - (i % 8)))) & 0xf];
	}
	return buf;
}
//

//唯一标识存档实现
std::string exe_cmd(const char* cmd)
{
	char buffer[128] = { 0 };
	std::string result;
	FILE* pipe = _popen(cmd, "r");
	if (!pipe)
		throw std::runtime_error("_popen() failed!");
	while (!feof(pipe))
	{
		if (fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}
	_pclose(pipe);
	result.erase(std::remove(result.begin(), result.end(), '\r'), result.end());
	result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());
	result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
	result = result.erase(0, 12);
	return result;
}
std::string getDiskId()
{
	std::string disc = exe_cmd("wmic BaseBoard get serialnumber");
	disc = sha1(disc);
	return disc;
}
//

//云存档实现
void ProgressCallback(size_t increment, int64_t transfered, int64_t total, void* userData)
{
	std::cout << "ProgressCallback[" << userData << "] => " << increment << " ," << transfered << "," << total << std::endl;
}
int uploadsav()
{
	using namespace AlibabaCloud::OSS;
	/* 初始化OSS账号信息 */
	//std::string AccessKeyId = "LTAI4G9vzd4PdQJwV8tQRsKG";
	//std::string AccessKeySecret = "N53YmQiN0I09wmKJt230vxinKjeOd8";
	//std::string Endpoint = "oss-cn-beijing.aliyuncs.com";
	//std::string BucketName = "wuziqi-sav";
	/* yourObjectName表示上传文件到OSS时需要指定包含文件后缀在内的完整路径，例如abc/efg/123.jpg */

	/* 初始化网络等资源 */
	std::cout << "正在连接服务器"
		<< "\n";
	InitializeSdk();

	std::cout << "连接服务器成功"
		<< "\n";
	//GetModuleFileName()
	ClientConfiguration conf;
	OssClient client(Endpoint, AccessKeyId, AccessKeySecret, conf);

	/* 上传文件 */
	/* yourLocalFilename由本地文件路径加文件名包括后缀组成，例如/users/local/myfile.txt */
	std::cout << "正在上传存档"
		<< "\n";
	//auto outcome = client.PutObject(BucketName, ObjectName, "E:/DxDiag.txt");
	std::shared_ptr<std::iostream> content = std::make_shared<std::fstream>(ClientFile, std::ios::in | std::ios::binary);
	PutObjectRequest request(BucketName, ObjectName, content);
	TransferProgress progressCallback = { ProgressCallback, nullptr };
	request.setTransferProgress(progressCallback);
	auto outcome = client.PutObject(request);
	if (!outcome.isSuccess())
	{

		/* 异常处理 */
		std::cout << "PutObject fail"
			<< ",code:" << outcome.error().Code() << ",message:" << outcome.error().Message() << ",requestId:" << outcome.error().RequestId() << std::endl;
		ShutdownSdk();
		return -1;
	}
	/* 释放网络等资源 */
	ShutdownSdk();
	std::cout << "存档上传成功"
		<< "\n";
	return 0;
}
bool chkcloudsav()
{
	using namespace AlibabaCloud::OSS;
	/* 初始化OSS账号信息 */

	/* 初始化网络等资源 */
	std::cout << "正在连接服务器"
		<< "\n";
	InitializeSdk();

	std::cout << "连接服务器成功"
		<< "\n";

	ClientConfiguration conf;
	OssClient client(Endpoint, AccessKeyId, AccessKeySecret, conf);

	/* 判断文件是否存在 */
	std::cout << "正在检测云存档"
		<< "\n";
	auto outcome = client.DoesObjectExist(BucketName, ObjectName);

	if (outcome) {
		std::cout << "发现云存档"
			<< "\n";
		return true;
	}
	else {
		std::cout << "未发现云存档"
			<< "\n";
		return false;
	}

	/* 释放网络等资源 */
	ShutdownSdk();
	return 0;
}
int downloadsav()
{
	using namespace AlibabaCloud::OSS;
	/* 初始化OSS账号信息 */
	std::string FileNametoSave = "wuziqi.sav";
	/* 初始化网络等资源 */
	std::cout << "正在连接服务器"
		<< "\n";
	InitializeSdk();

	std::cout << "连接服务器成功"
		<< "\n";

	ClientConfiguration conf;
	OssClient client(Endpoint, AccessKeyId, AccessKeySecret, conf);

	/* 获取文件 */
	std::cout << "正在下载存档"
		<< "\n";
	DownloadObjectRequest request(BucketName, ObjectName, ClientFile);
	TransferProgress progressCallback = { ProgressCallback, nullptr };
	request.setTransferProgress(progressCallback);
	auto outcome = client.ResumableDownloadObject(request);
	//auto outcome = oss_client->ResumableDownloadObject(request);
	if (!outcome.isSuccess()) {
		/* 异常处理 */
		std::cout << "getObject fail" <<
			",code:" << outcome.error().Code() <<
			",message:" << outcome.error().Message() <<
			",requestId:" << outcome.error().RequestId() << std::endl;
		ShutdownSdk();
		return -1;
	}

	/* 释放网络等资源 */
	ShutdownSdk();
	std::cout << "存档下载成功"
		<< "\n";
	return 0;
}
//

//对局核心函数
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
	MessageBox(wnd, _T("游戏结束\n"), _T("Warning"), MB_OK);
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
void savegame(int2* a, bool click, int hand)
{
	if (click)
	{
		HWND wnd = GetHWnd();
		if (MessageBox(wnd, _T("确定存档吗。\n"), _T("Warning"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			std::cout << "正在保存存档" << std::endl;
			FILE* out;
			fopen_s(&out, "wuziqi.sav", "w");
			std::string chksum;
			fprintf(out, "%d ", step);
			for (int i = 0; i < step - 1; i++)
			{
				fprintf(out, "%d %d ", a[i].x, a[i].y);
				chksum += std::to_string(a[i].x);
				chksum += std::to_string(a[i].y);
			}
			std::cout << "对局写入成功" << std::endl;
			fprintf(out, "%d ", hand);	  //手
			std::cout << chksum << std::endl;
			chksum = sha1(chksum);
			fprintf(out, "%s", chksum.c_str()); //校验码
			std::cout << "校验码写入成功" << std::endl;
			fclose(out);
			//free(out);
			printf("\a");
			MessageBox(wnd, _T("保存成功\n"), _T("Warning"), MB_OK);
			if (cloudsave)
			{
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
	}
	return;
}
int loadgame(int** a)
{
	HWND wnd = GetHWnd();
	if (!_access("wuziqi.sav", 0))
	{
		printf("\a");
		if (MessageBox(wnd, _T("检测到存档，是否读取？\n"), _T("Warning"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			std::cout << "正在读取存档" << std::endl;
			FILE* in;
			fopen_s(&in, "wuziqi.sav", "r");
			std::string redchk;
			redchk.resize(40);
			std::string chksum;
			int len = 0;
			int uio;
			fscanf_s(in, "%d", &len);
			for (int i = 0; i < len - 1; i++)
			{
				fscanf_s(in, "%d %d", &chess_flow[i].x, &chess_flow[i].y);
				printf("%d %d\n", chess_flow[i].x, chess_flow[i].y);
				chksum += std::to_string(chess_flow[i].x);
				chksum += std::to_string(chess_flow[i].y);
			}

			fscanf_s(in, "%d", &uio);
			std::cout << "存档读取成功" << std::endl;
			chksum = sha1(chksum);
			fscanf_s(in, "%s", &redchk[0], 50);
			std::cout << chksum << std::endl;
			std::cout << redchk << std::endl;
			std::cout << (chksum == redchk) << std::endl;
			if (chksum != redchk)
			{
				std::cout << "存档校验失败" << std::endl;
				printf("\a");
				MessageBox(wnd, _T("存档文件校验失败\n"), _T("Warning"), MB_OK);
				for (int i = 0; i < 300; i++)
				{
					chess_flow[i].x = 0;
					chess_flow[i].y = 0;
				}
				for (int i = 1; i <= 15; i++)
				{
					for (int j = 1; j <= 15; j++)
					{
						a[i][j] = 0;
					}
				}
				for (int i = 0; i < 225; i++)
				{
					chb[i] = 0;
				}
				for (int i = 0; i < 900; i++)
				{
					chbmstep[i] = 0;
				}
				step = 1;
				fclose(in);
				return 1;
			}
			std::cout << "存档校验成功" << std::endl;
			for (int i = 0; i < len - 1; i++)
			{
				chess_add(chess_flow[i].x, chess_flow[i].y);
				a[chess_flow[i].y + 1][chess_flow[i].x + 1] = i % 2 + 1;
			}
			printf("debug:%d %d\n", step, len);
			int p = 0;
			setlinecolor(BLACK);
			setfillstyle(BS_SOLID);
			for (int i = 1; i <= 15; i++)
			{
				for (int j = 1; j <= 15; j++)
				{
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
			//free(in);
			return uio;
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

game_start:
	FlushMouseMsgBuffer();

	while (1)
	{
		if (hand == 1) //落黑子
		{
			//while (1)//(human)
			//{
			//	MOUSEMSG mouse = GetMouseMsg(); // 获取鼠标信息
			//									//mouse.x
			//									//mouse.y
			//	int mx = mouse.x;
			//	int my = mouse.y;
			//	if (mx >= 990 && mx <= 1190 && my >= 820 && my <= 895) //退出按钮
			//	{
			//		if (quitgame(mouse.mkLButton))
			//		{
			//			return;
			//		}
			//	}
			//	if (mx >= 990 && mx <= 1190 && my >= 765 && my <= 820) //存档按钮
			//	{
			//		savegame(boardlay, mouse.mkLButton, 1);
			//	}
			//	getpos(mx, my);
				//if (mx >= 1 && mx <= 15 && my >= 1 && my <= 15 && boardlay[mx][my] == 0)
				//{
				//	//绘制标识区域
				//	if (mouse.mkLButton)
				//	{
				//		boardlay[mx][my] = 1;
				//		//绘制棋子
				//		setlinecolor(BLACK);
				//		setfillstyle(BS_SOLID);
				//		setfillcolor(BLACK);
				//		fillcircle((mx - 1) * 60 + 55, (my - 1) * 60 + 55, 20);
				//		hand = 2;
				//		break;
				//	}
				//}
			//}
			clock_t st_time = clock();
			printf("开始计算......");
			int ans = ai_cal(chb, chbmstep, hand, difficulty);
			clock_t en_time = clock();
			printf("          本次计算耗时%lf\n", (double)en_time - (double)st_time);
			int2 pos;
			pos.x = ans / 15;
			pos.y = ans % 15;
			//putjson(pos);
			chess_flow[step - 1] = pos;
			chess_add(pos.x, pos.y);//自己的
			int mx = pos.y + 1;
			int my = pos.x + 1;
			boardlay[mx][my] = 1;

			//绘制棋子
			setlinecolor(BLACK);
			setfillstyle(BS_SOLID);
			setfillcolor(BLACK);
			setfillcolor(BLACK);
			fillcircle((mx - 1) * 60 + 55, (my - 1) * 60 + 55, 20);
			hand = 2;
		}
		else if (hand == 2) //落白子
		{
			while (1)
			{
				MOUSEMSG mouse = GetMouseMsg(); // 获取鼠标信息
				int mx = mouse.x;//mouse.x
				int my = mouse.y;//mouse.y
				if (mx >= 990 && mx <= 1190 && my >= 820 && my <= 895)
				{
					if (quitgame(mouse.mkLButton))
					{
						return;
					}
				}
				if (mx >= 990 && mx <= 1190 && my >= 765 && my <= 820) //存档按钮
				{
					savegame(chess_flow, mouse.mkLButton, 2);
				}
				getpos(mx, my);
				if (mx >= 1 && mx <= 15 && my >= 1 && my <= 15 && boardlay[mx][my] == 0)
				{
					//绘制标识区域
					if (mouse.mkLButton)
					{
						chess_flow[step - 1] = { my - 1,mx - 1 };
						chess_add(my - 1, mx - 1);//人类下
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
		//printf("%d\n", overall_evaluate(boardlay));
		if (win(boardlay)) //判断胜负关系
		{
			break; //跳出
		}
	}
	gamesettlement(boardlay);
	HWND wnd = GetHWnd();
	if (MessageBox(wnd, _T("再来一局？\n"), _T("Warning"), MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		cleardevice();
		closegraph();
		board_init();
		hand = 1;
		for (int i = 1; i <= 15; i++)
		{
			for (int j = 1; j <= 15; j++)
			{
				boardlay[i][j] = 0;
			}
		}
		for (int i = 0; i < 225; i++)
		{
			chb[i] = 0;
		}
		for (int i = 0; i < 900; i++)
		{
			chbmstep[i] = 0;
		}
		step = 1;
		goto game_start;
	}
	free(boardlay);
	return;
}
//

//初始化函数
void privacyreq()
{
	printf("\a");
	HWND wnd = GetHWnd();
	if (MessageBox(wnd, _T("是否开启云存档功能？\n本功能会自动获取您的序列号，并经过严格的SHA加密后用作主机身份识别。请放心使用"), _T("Warning"), MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		cloudsave = true;
		DiskId = getDiskId();
		std::cout << "您的唯一识别码为:" << DiskId << std::endl;
		char buff[1000];
		_getcwd(buff, 1000);
		for (int i = 0; i < strlen(buff); i++)
		{
			if (buff[i] == '\\')
			{
				buff[i] = '/';
			}
		}
		ObjectName = "sav/";
		ObjectName += DiskId;
		ObjectName += ".sav";
		ClientFile = buff;
		ClientFile += "/wuziqi.sav";
		std::cout << "当前路径是：" << ClientFile << std::endl;
		if (chkcloudsav())
		{
			printf("\a");
			if (MessageBox(wnd, _T("检测到您存在云存档，是否下载并覆盖本地存档？\n"), _T("Warning"), MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				if (downloadsav() == 0)
				{
					printf("\a");
					MessageBox(wnd, _T("下载成功\n"), _T("Warning"), MB_OK);
				}
				else
				{
					printf("\a");
					MessageBox(wnd, _T("下载失败\n"), _T("Warning"), MB_OK);
				}
			}
		}
	}
	else
	{
		cloudsave = false;
	}
	return;
}
void difficultreq()
{
	printf("\a");
	HWND wnd = GetHWnd();
	if (MyMessageBoxA(wnd, _T("请选择您需要的难度"), _T("Warning"), MB_YESNO) == IDYES)
	{
		if (MyMessageBoxB(wnd, _T("不是吧，这都嫌难？"), _T("Warning"), MB_YESNO) == IDYES)
		{
			difficulty = 3;
		}
		else
		{
			difficulty = 4;
		}

	}
	else
	{
		difficulty = 5;
	}
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
	for (int i = 0; i < 225; i++)
	{
		chb[i] = 0;
	}
	for (int i = 0; i < 900; i++)
	{
		chbmstep[i] = 0;
	}
	step = 1;
}
//
