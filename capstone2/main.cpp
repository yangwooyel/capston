//AI.h -> Process.h ->Board.h ��
#define _CRT_SECURE_NO_WARNINGS
//#pragma comment(linker,"/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#include "Al.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>  
#include <opencv2/core/mat.hpp>  
#include <opencv2/imgcodecs.hpp>  
#include <opencv2/imgproc.hpp>  
#include <opencv2/highgui.hpp>
#include <thread>
#include <math.h>
#include "test.h"

////////////////////////////////////////////////////////////////////////////
/* define */
// path
#define PATH_PLAYER_INFO 	"./info/player.cfg"
#define PATH_AI_INFO		"./info/ai.cfg"
// side
#define SIDE_PLAYER		0
#define SIDE_AI			1
// arrow key
#define ARROW_UP		0x48
#define ARROW_DOWN		0x50
#define ARROW_LEFT		0x4b
#define ARROW_RIGHT		0x4d
#define SPACE_KEY		0x20
#define ESC_KEY			0x1b
#define BACKSPACE		0x8
#define LEFT_BRACKET	0x5B
#define RIGHT_BRACKET	0x5D
// put stone return value
#define FAILED_TO_PUT		0
#define SUCCESS_TO_PUT		1
// menu
#define START_WITH_WHITE	0
#define REPLAY				1
#define HOW_TO_PLAY			2
#define CREDIT				3
#define EXIT				4
// color
#define COLOR_BLACK		0
#define COLOR_WHITE		1
// board status
#define STATUS_EMPTY	0
#define STATUS_BLACK	1
#define STATUS_WHITE	2
// interface
#define CONSOLE_HEIGHT 	20 // original is 20
#define CONSOLE_WIDTH	78
#define UI_BOARD_X 		22
#define UI_BOARD_Y		0
#define UI_PLAYER_X		0
#define UI_PLAYER_Y		0
#define UI_AI_X			56
#define UI_AI_Y			0
#define UI_TURN_X		0
#define UI_TURN_Y		17
#define UI_WINNER_X		0
#define UI_WINNER_Y		17
/////////////////////////////////////////////////////////////////////////





using namespace cv;
using namespace std;
Board board;
bool put = true;

int pointx = -1, pointy = -1;
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		cout << "���� ���콺 ��ư Ŭ��.. ��ǥ = (" << x << ", " << y << ")" << endl;
	}
}

void gotoxy(int x, int y)  //x, y ��ġ�� ���Ŀ���� �Ű��ִ� �Լ�

{
	COORD pos = { x, y };  //
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}  //x,y��ġ�� ���Ŀ���� �Ű��ְ� x,y,��ġ ����
int main(void)
{

	VideoCapture cap(0);
	Mat gray, img_input, img_pre, img_diff;
	//Mat Edge;
	int x = 0, y = 0;

	//int mw = blob.m_recBlobs[i].width;


	MY_COORD coord;



	vector<Vec3f> circles;

	//��ĸ���� ĸ ó�Ǵ� �̹��� ũ�⸦ 400x400���� ����  
	cap.set(CAP_PROP_FRAME_WIDTH, 400);
	cap.set(CAP_PROP_FRAME_HEIGHT, 400);

	//ī�޶�κ��� �̹����� ������ 
	bool ret = cap.read(img_input);


	if (!ret)
	{
		cout << "ī�޶�κ��� �̹����� ������ �� �����ϴ�." << endl;
		return -1;
	}

	if (!cap.isOpened())
	{
		cout << "��ķ�� �� �� �����ϴ�." << endl;
		return -1;
	}

	img_pre = img_input.clone();

	system("cls");
	for (int i = 0; i < MAX2 * 2; i += 2)  // #define MAX=19 __ Board.h ������ 
										   //19 * 19 �ٵ���  19�����ư���
	{
		for (int j = 0; j < MAX; j++)
			gotoxy(i, j), printf("��");  // x,y��ŭ �̵��ؼ� �ٵ����� �����  ���� 2ĭ�� ��ƸԱ⶧���� i+2�Ѵ�
		printf("\n");
	}


	while (true)
	{
		//img_diff = NULL;

		//Sleep(500);
		cap.read(img_input);
		
		//Edge = cvCreateImage(cvGetSize(gray), IPL_DEPTH_8U, CV_THRESH_BINARY);



		//������
		absdiff(img_pre, img_input, img_diff);

		// ������ ���� �����
		
		cvtColor(img_diff, gray, CV_BGR2GRAY);
		

		// �������ϰ��ؼ� ��Ȯ�� �� ����
		GaussianBlur(gray, gray, Size(9, 9), 2, 2);
		HoughCircles(gray, circles, CV_HOUGH_GRADIENT,
			1, 10, 200, 25, 4, 15);

		for (int i = 0; i < circles.size(); i++) {
			Point center((int)(circles[i][0]), (int)(circles[i][1]));
			int radius = (int)(circles[i][2]);
			circle(img_diff, center, radius, Scalar(0, 255, 0), 2);
			//cout << radius << endl;

			int pixel = 10;
			int startX = 53;
			int startY = 41;
			///////////////////////////////////////////

			for (int i = 0; i < 14; i++)
			{
				if (center.x - (startX * i)< 10)
				{
					pointx = i;
					break;
					//
				}
			}

			for (int i = 0; i < 12; i++)
			{
				if (center.y - (startY * i)< 10)
				{
					pointy = i;
					break;
				}
			}

			///////////////////////////////////////
			//	pointx = (center.x - startX) / 19;
			//	pointy = (center.y - startY) / 19;
			////////////////////////////////////////////

			//cout << "pointx = " << pointx << " " << "pointy = " << pointy << endl;
			//cout << center.x << " " << center.y << endl;

			/*
			if (53 - pixel <= center.x && center.x <= 53 + pixel) {
			pointx = 0;

			}
			if (72 - pixel <= center.x && center.x <= 72 + pixel) {
			pointx = 1;
			}
			if (91 - pixel <= center.x && center.x <= 91 + pixel) {
			pointx = 2;
			}
			if (110 - pixel <= center.x && center.x <= 110 + pixel) {
			pointx = 3;
			}
			if (129 - pixel <= center.x && center.x <= 129 + pixel) {
			pointx = 4;
			}
			if (148 - pixel <= center.x && center.x <= 148 + pixel) {
			pointx = 5;
			}
			if (167 - pixel <= center.x && center.x <= 167 + pixel) {
			pointx = 6;
			}
			if (186 - pixel <= center.x && center.x <= 186 + pixel) {
			pointx = 7;
			}
			if (205 - pixel <= center.x && center.x <= 205 + pixel) {
			pointx = 8;
			}
			if (224 - pixel <= center.x && center.x <= 224 + pixel) {
			pointx = 9;
			}
			if (243 - pixel <= center.x && center.x <= 243 + pixel) {
			pointx = 10;
			}
			if (262 - pixel <= center.x && center.x <= 262 + pixel) {
			pointx = 11;
			}
			if (281 - pixel <= center.x && center.x <= 281 + pixel) {
			pointx = 12;
			}
			if (300 - pixel <= center.x && center.x <= 300 + pixel) {
			pointx = 13;
			}



			if (40 - pixel <= center.y && center.y <= 40 + pixel) {
			pointy = 0;
			}if (59 - pixel <= center.y && center.y <= 59 + pixel) {
			pointy = 1;
			}if (78 - pixel <= center.y && center.y <= 78 + pixel) {
			pointy = 2;
			}if (97 - pixel <= center.y && center.y <= 97 + pixel) {
			pointy = 3;
			}if (116 - pixel <= center.y && center.y <= 116 + pixel) {
			pointy = 4;
			}
			if (135 - pixel <= center.y && center.y <= 135 + pixel) {
			pointy = 5;
			}
			if (154 - pixel <= center.y && center.y <= 154 + pixel) {
			pointy = 6;
			}
			if (173 - pixel <= center.y && center.y <= 173 + pixel) {
			pointy = 7;
			}
			if (192 - pixel <= center.y && center.y <= 192 + pixel) {
			pointy = 8;
			}
			if (211 - pixel <= center.y && center.y <= 211 + pixel) {
			pointy = 9;
			}
			if (230 - pixel <= center.y && center.y <= 230 + pixel) {
			pointy = 10;
			}
			if (249 - pixel <= center.y && center.y <= 249 + pixel) {
			pointy = 11;
			}

			*/





			//���尡 ����ְ�,true ���� �����̸�
			if (board.pos[pointx][pointy].state == BLANK && put == true) // �ٵϵ��� ������
			{

				gotoxy(pointx * 2, pointy);
				doPut(BLACK, &board, std::make_pair(pointx, pointy)); //process.h //make_pair(x,y)--> ���� �˾Ƽ� ��ȯ����               
				printf("��");
				put = false; //�ٵϵ��� ������ false=���� ���ʾƴϴ�.                   
			}

			//���� �� �Ǻ�
			if (getWinner(board) == BLACK) break;
			for (int i = 0; i < MAX2; i++)
				for (int j = 0; j < MAX; j++)
					board.pos[i][j].weight = 1.0;

			if (!put) {

				setWeight(&board);  //�ٵ����� ����ġ ���.
				Points pt = AISetPos(board); //AI.cpp  //��ǻ�Ͱ� �ִ밡��ġ ���� ��ǥ�� �޾ƿ´�.


				if (board.pos[pt.first][pt.second].state == BLANK) //�װ���ġ�� ��ǥ���� �ٵϵ��� ������
				{

					doPut(WHITE, &board, pt);  //��ٵϵ��� ���´�.
					gotoxy(pt.first * 2, pt.second);
					printf("��");
					put = true;   //�ٵϵ��� ���Ҵ�.
				}

			}
			if (getWinner(board) == WHITE)
				break;  //�Ҿ����� �ý��۹̾�

						/*
						if (center.x % 24 >= 12)
						pointx = center.x / 24 + 1;
						else {
						pointy = center.x / 24;
						}*/

		}//circle for ��

		imshow("���� ����", img_input);
		imshow("����", img_diff);

		setMouseCallback("���� ����", CallBackFunc, NULL);//��ǥŬ��

		if (circles.size() == 1)
		{
			img_pre = img_input.clone();//(������ ����)
		}
		//ESCŰ ������ ���α׷� ����   
		if (waitKey(10) == 27) {
			for (int i = 0; i < MAX2; i++) {
				for (int j = 0; j < MAX; j++) {
					printf("%d", board.pos[i][j].state);
				}
				printf("\n");
			}
			break;
		}
		//cout << len12 << " " << len23 << " " << len34 << " " << len41<< endl;


	} //while�� ��
	return 0;
}

