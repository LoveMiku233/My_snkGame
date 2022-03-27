#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;
//��Ϸ������־
bool gameOver;
const int width = 20; //��ͼX
const int height = 20; //��ͼy
//�ߺ�ʳ������    
int x, y,foodX,foodY,score;
int tailX[100]; //β������
int tailY[100]; 
int taillen; //β�ͳ���
enum _Dir { //����
	STOP=0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
_Dir dir;

void Draw() {
	system("cls"); // ˢ��
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0)
				cout << "#";
			//������
			if (i == y && j == x)cout << "0";
			//����ʳ��
			else if (i == foodY && j == foodX)cout << "F";
			else { 
				bool print =false;
				for (int m = 0; m < taillen; m++) {
					if (tailX[m] == j && tailY[m] == i) {
						//����β��
						cout << "o";
						print=true;
					}
				}
				if(!print)
					cout << " "; 
			}
			if (j == width - 2)
				cout << "#";
		}
		cout << endl;
	}
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;

	cout << "������" << score << endl;
}

void Setup() {
	//��ʼ��
	gameOver = false;
	score = 0;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	foodX = rand() % width;
	foodY = rand() % height;
}

void Input() {
	//��ȡ���� 
	//TODO ��Ҫ�������ͻ 
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'q':
			gameOver = true;
			break;

		}
	}
}

void Log() {
	//��β���߼�
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < taillen; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	//�ж��Ƿ����ͼ
	if (x > width || x<0 || y>height || y < 0)
		gameOver = true;
	//�ж��Ƿ�����β��
	for (int i = 0; i < taillen; i++) {
		if(tailX[i]==x&&tailY[i]==y){
			gameOver = true;
		}
	}
	//�ж��Ƿ�Ե�ʳ��
	if (x == foodX && y == foodY) {
		score++;
		foodX = rand() % width;
		foodY = rand() % height;
		taillen++;
	}
}

//������
int main() {
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Log();
		Sleep(20);
	}
	return 0;
}