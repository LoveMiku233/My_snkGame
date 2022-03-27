#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;
//游戏结束标志
bool gameOver;
const int width = 20; //地图X
const int height = 20; //地图y
//蛇和食物坐标    
int x, y,foodX,foodY,score;
int tailX[100]; //尾巴数组
int tailY[100]; 
int taillen; //尾巴长度
enum _Dir { //方向
	STOP=0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
_Dir dir;

void Draw() {
	system("cls"); // 刷新
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0)
				cout << "#";
			//绘制蛇
			if (i == y && j == x)cout << "0";
			//绘制食物
			else if (i == foodY && j == foodX)cout << "F";
			else { 
				bool print =false;
				for (int m = 0; m < taillen; m++) {
					if (tailX[m] == j && tailY[m] == i) {
						//绘制尾巴
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

	cout << "分数：" << score << endl;
}

void Setup() {
	//初始化
	gameOver = false;
	score = 0;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	foodX = rand() % width;
	foodY = rand() % height;
}

void Input() {
	//获取输入 
	//TODO 需要处理方向冲突 
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
	//蛇尾巴逻辑
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
	//判断是否出地图
	if (x > width || x<0 || y>height || y < 0)
		gameOver = true;
	//判断是否碰到尾巴
	for (int i = 0; i < taillen; i++) {
		if(tailX[i]==x&&tailY[i]==y){
			gameOver = true;
		}
	}
	//判断是否吃到食物
	if (x == foodX && y == foodY) {
		score++;
		foodX = rand() % width;
		foodY = rand() % height;
		taillen++;
	}
}

//主函数
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