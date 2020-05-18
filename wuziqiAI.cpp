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
	privacyreq();
	//game started
	game();
	//game ended

	//system("pause");
	return 0;
}
//ai实现
int intpow(int a, int n)
{
	if (n == 0)
	{
		return 1;
	}
	else
	{
		n--;
		while (n--)
		{
			a *= a;
		}
		return a;
	}
}

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
				humsum += intpow(10, cnt != 0 ? cnt : 1);
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
				aisum += intpow(10, cnt != 0 ? cnt : 1);
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
					humsum += intpow(10, cnt);
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
					aisum += intpow(10, cnt);
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
					humsum += intpow(10, cnt);
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
					aisum += intpow(10, cnt);
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
					humsum += intpow(10, cnt);
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
					aisum += intpow(10, cnt);
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
std::string sha1(std::string s)
{
	const char HEX_CHAR[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	const unsigned int K[] = { 0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6 };
	//扩展成K*512位
	unsigned int l;
	l = s.length() * 8;
	unsigned int* data = (unsigned int*)calloc(sizeof(unsigned int), ((l / 512) + 1) * 512);
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

void savegame(int** a, bool click, int hand)
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
			for (int i = 1; i <= 15; i++)
			{
				for (int j = 1; j <= 15; j++)
				{
					fprintf(out, "%d ", a[i][j]);
					chksum += char(a[i][j] + '0');
				}
			}
			std::cout << "存档保存成功" << std::endl;
			fprintf(out, "%d ", hand);	  //手
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
	if (!_access("wuziqi.sav", 0)) //
	{
		printf("\a");
		if (MessageBox(wnd, _T("检测到存档，是否读取？\n"), _T("Warning"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			std::cout << "正在读取存档" << std::endl;
			FILE* in;
			fopen_s(&in, "wuziqi.sav", "r");
			int* tmpsav = (int*)calloc(300, sizeof(int)); //存档读取缓冲
			std::string redchk;
			redchk.resize(40);
			std::string chksum;
			int cntblack = 0;
			int cntwhite = 0;
			for (int i = 0; i < 15 * 15 + 1; i++)
			{
				fscanf_s(in, "%d", tmpsav + i);
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
					chksum += char(*(tmpsav + i) + '0');
				}
			}
			std::cout << "存档读取成功" << std::endl;
			chksum = sha1(chksum);
			fscanf_s(in, "%s", &redchk[0], 50);
			//std::cout << chksum << std::endl;
			//std::cout << redchk << std::endl;
			//std::cout << (chksum == redchk) << std::endl;
			if (chksum != redchk || *(tmpsav + 15 * 15) != cntblack - cntwhite + 1)
			{
				std::cout << "存档校验失败" << std::endl;
				printf("\a");
				MessageBox(wnd, _T("存档文件校验失败\n"), _T("Warning"), MB_OK);
				return 1;
			}
			std::cout << "存档校验成功" << std::endl;
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
			//free(in);
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
		goto game_start;
	}
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