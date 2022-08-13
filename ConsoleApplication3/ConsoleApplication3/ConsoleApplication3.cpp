#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<easyx.h>
#include<corecrt_wstdlib.h>
#include<string>
#include<mmsystem.h>//多媒体
#pragma comment(lib,"winmm.lib")
#include<time.h>
#include<corecrt_wstdio.h>
#define PI 3.14159
const int N = 15;
int p[N][N] = { 0 };
void zhixing();
IMAGE img, img1, img2;
void playlastBGM();
struct 
{
	int x;
	int y;

}point;
int r;
void biao() {
	int center_x, center_y;        //中心点坐标，钟表中心
	center_x = 915;
	center_y = 165;
	int secondLength = 100;         //秒针长度
	int minuteLength = 85;          //分针长度
	int hourLength = 70;           //时针长度

	int secondEnd_x, secondEnd_y;         //秒针重点
	int minuteEnd_x, minuteEnd_y;          //分针终点
	int hourEnd_x, hourEnd_y;              //时针终点
	float secondAngle;                    //秒针对应角度
	float minuteAngle;                    //分针对应角度
	float hourAngle;                      //时针对应角度

	SYSTEMTIME ti;                        //定义系统时间变量

	BeginBatchDraw();
	while (1)
	{
		//绘制表盘
		setlinestyle(PS_SOLID, 1);
		setcolor(WHITE);
		circle(center_x, center_y,150);

		//画刻度
		int x, y, i;
		for (i = 0; i < 60; i++)
		{
			x = center_x + int(150/ 4.3 * sin(PI * 2 * i / 60));
			y = center_y + int(150 / 4.3 * cos(PI * 2 * i / 60));

			if (i % 15 == 0)
				bar(x - 5, y - 5, x + 5, y + 5);
			else if (i % 5 == 0)
				circle(x, y, 3);
			else
				putpixel(x, y, WHITE);
		}

		//outtextxy(center_x - 25, center_y +70, _T("xian"));
		GetLocalTime(&ti);                    //获取当前时间
		//秒针角度的变化
		secondAngle = ti.wSecond * 2 * PI / 60;
		//分针角度变化
		minuteAngle = ti.wMinute * 2 * PI / 60 + secondAngle / 60;
		//时针角度变化
		hourAngle = ti.wHour * 2 * PI / 12 + minuteAngle / 12;
		//由角度决定的秒针短点坐标
		secondEnd_x = center_x + secondLength * sin(secondAngle);
		secondEnd_y = center_y - secondLength * cos(secondAngle);
		//由角度决定分针端点坐标
		minuteEnd_x = center_x + minuteLength * sin(minuteAngle);
		minuteEnd_y = center_y - minuteLength * cos(minuteAngle);
		//由角度决定的时针端点坐标
		hourEnd_x = center_x + hourLength * sin(hourAngle);
		hourEnd_y = center_y - hourLength * cos(hourAngle);

		setlinestyle(PS_SOLID, 2);
		setcolor(YELLOW);
		line(center_x, center_y, secondEnd_x, secondEnd_y);       //画秒针
		setlinestyle(PS_SOLID, 4);
		setcolor(BLUE);
		line(center_x, center_y, minuteEnd_x, minuteEnd_y);       //画分针
		setlinestyle(PS_SOLID, 6);
		setcolor(RED);
		line(center_x, center_y, hourEnd_x, hourEnd_y);           //画时针

		FlushBatchDraw();
		Sleep(10);

		setcolor(BLACK);
		setlinestyle(PS_SOLID, 3);
		line(center_x, center_y, secondEnd_x, secondEnd_y);
		setlinestyle(PS_SOLID, 5);
		line(center_x, center_y, minuteEnd_x, minuteEnd_y);
		setlinestyle(PS_SOLID, 10);
		line(center_x, center_y, hourEnd_x, hourEnd_y);
	}
	EndBatchDraw();
	_getch();                   //按任意键继续
	closegraph();
}

void Playbgm() //播放背景音乐
{
	mciSendString("open normnal.wav", NULL, 0, NULL);
	mciSendString("play normnal.wav", NULL, 0, NULL);
	Sleep(2000);
	mciSendString("close normnal.wav", NULL, 0, NULL);
	
		
		
}
void playlastBGM() {
	mciSendString("open a.aac", NULL, 0, NULL);
	mciSendString("play a.aac", NULL, 0, NULL);
	Sleep(1000);
	mciSendString("close a.aac", NULL, 0, NULL);
}
void white() {
	loadimage(&img1, _T("pic/2(1).jpg"));
	putimage(750, 330, &img1);
}
void black() {
	loadimage(&img2, _T("pic/3(1).jpg"));
	putimage(750, 330, &img2);
}
void wenzi() 
//使用前面文字
{
	char str1[] = { "欢迎使用瓜大小辉五子棋" };
	char str2[] = { "按任意键继续___" };
	char str3[] = {"使用鼠标左键点击可以下棋"};
	
		setbkmode(OPAQUE);
		settextcolor(GREEN);
		settextstyle(0, 30, "楷体");
		outtextxy(0, 20, str1);
		settextstyle(20, 20, "楷体");
		outtextxy(0, 100, str2);
		outtextxy(0, 200, str3);
		
		_getch();
		cleardevice();
	
}


void bg() {
	initgraph(1080, 750);

}

int num = 1;
void draw_line() {
	setlinecolor(BLACK);
	for (int x = 25; x < 750; x += 50)
		line(x, 25, x, 725);
	for (int y = 25; y < 750; y += 50)
		line(25, y, 725, y);
}
//int change_piece(int x, int y) {
//	if (p[x][y] != 0)
//		return 0;
//	else
//		p[x][y] = num;
//	return 1;
//}
void rightimage(int a) {
	if (a == -1) {
		white();
	}
	if (a == 1) {
		black();
	}
	return;
}

void draw_piece(int m, int n) {
	if (num == -1)
		setfillcolor(WHITE);
	else if (num == 1)
		setfillcolor(BLACK);
	int x, y;
	x = m / 50;
	y = n / 50;
	p[x][y] = num;//白为-1，黑为1
	/*if (change_piece(x, y) == 0)
		return;*/
	fillcircle(m - (m % 50) + 25, n - (n % 50) + 25, 15);
	rightimage(num);
	num *= -1;
	
	

}

void draw_point() {
	setlinecolor(BLACK);
	fillcircle(4 * 50 - 25, 4 * 50 - 25, 3);
	fillcircle(4 * 50 - 25, 12 * 50 - 25, 3);
	fillcircle(8 * 50 - 25, 8 * 50 - 25, 3);
	fillcircle(12 * 50 - 25, 4 * 50 - 25, 3);
	fillcircle(12 * 50 - 25, 12 * 50 - 25, 3);
}


int check_5(int x, int y) {
	if (x < 2 || y < 2 || x>12 || y>12)
		return 0;//0代表无结果
	if(p[x][y] == p[x - 1][y] && p[x][y] == p[x - 2][y] && p[x][y] == p[x + 1][y] && p[x][y] == p[x + 2][y]){
		if (p[x][y] == -1)
			return -1;
		else return 1;
  }   if (p[x][y] == p[x][y - 1] && p[x][y] == p[x][y - 2] && p[x][y] == p[x][y + 1] && p[x][y] == p[x][y + 2]) {
	  if (p[x][y] == -1)
		  return -1;
	  else return 1;
}
  if (p[x][y] == p[x - 1][y - 1] && p[x][y] == p[x - 2][y - 2] && p[x][y] == p[x + 1][y + 1] && p[x][y] == p[x + 2][y + 2]) {
	  if (p[x][y] == -1)
		  return -1;
	  else return 1;
  }
  if (p[x][y] == p[x - 1][y + 1] && p[x][y] == p[x - 2][y + 2] && p[x][y] == p[x + 1][y - 1] && p[x][y] == p[x + 2][y - 2]) {
	  if (p[x][y] == -1)
		  return -1;
	  else return 1;
  }
  return 0;
}
int check1() 
{
	for(int i=0;i<N;i++)
		for (int j = 0; j < N; j++) {
			if (p[i][j] == 0)
				continue;
			if (check_5(i, j) == -1)
			{
				return -1;
				break;
			}
			if (check_5(i, j) == 1)
			{
				return 1;
				break;
			}
		}
	return 0;
}

void open() {
	//p[N][N] = { 0 };
	for(int i=0;i<15;i++)
		for (int j = 0; j < 15; j++) {
			p[i][j] = 0;
		}
	bg();
	wenzi();

	//cleardevice();
	loadimage(&img, _T("pic/1.jpg"));
	putimage(0, 0, &img);
	
	Playbgm();
	draw_line();
	draw_point();
	
	zhixing();
	
}
void zhixing() {
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			draw_piece(m.x, m.y);

		}
		if (check1() == -1) {
			
			int a = MessageBox(GetForegroundWindow(), _T("白棋获胜，是否重新开始"),
				_T("游戏结束"), MB_YESNO);
			if (a == IDYES)
			{
				open();
				playlastBGM();
			}
			else if (a == IDNO)
				break;
		}
		if (check1() == 1) {
			
			int a = MessageBox(GetForegroundWindow(), _T("黑棋获胜，是否重新开始"),
				_T("游戏结束"), MB_YESNO);
			if (a == IDYES) {
				open();
				playlastBGM();
			}
			else if (a == IDNO)
				break;
		}
	}
	biao();
	closegraph();
}
int main() {
	open();

	return 0;
}

	