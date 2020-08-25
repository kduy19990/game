#include <stdio.h>
#include <stdlib.h> 
#include "Dependencies\freeglut\freeglut.h"
#include <gl/GL.h>
#include <ctime>
#include "game-source.h"

int gridX, gridY; // tọa độ lưới
int snake_length = 5; // chiều dài của con rắn (5 ô)
bool food = true; // thức ăn con rắn mặc định có
int foodX, foodY; // tọa độ thức ăn
short sDirection = DOWN; // hướng di chuyển mặc định của con rắn
int posX[100] = { 20,20,20,20,20 }, posY[100] = { 39,38,37,36,35 }; // vị trí mặc định của con rắn
extern int score; // tạo biến đếm số điểm
extern bool gameOver; // biến điều kiện kết thúc trò chơi
int bo = 0;

void initGrid(int x, int y) // khởi tạo lưới (khu vực con rắn có thể di chuyển được)
{
	gridX = x; // gán gridX bằng  x
	gridY = y; // gán gridY bằng  y
}

void unit(int, int); // khởi tạo ô vuông

void drawGrid() // vẽ lưới

{
	// chạy vòng lặp tạo thành lưới (gồm các ô vuông)
	for (int x = 0; x < gridX; x++)
	{
		for (int y = 0; y < gridY; y++)
		{
			unit(x, y); // tạo 1 ô vuông
		}
	}
}

void unit(int x, int y) // tạo ô vuông
{
	if (x == 0 + bo || y == 0 + bo || x == gridX - 1 - bo || y == gridY - 1 - bo) // tạo biên cho con rắn
	{
		glLineWidth(3.0); // độ dày đường thẳng
		glColor3f(1.0, 0.0, 1.0); // màu tím
	}
	else // vùng con rắn có thể di chuyển được
	{
		glLineWidth(1.0);
		glColor3f(0.0, 0.0, 0.0); // màu đen
	}

	glBegin(GL_LINE_LOOP); // vòng lặp  các đường thẳng
	glVertex2f(x, y);
	glVertex2f(x + 1, y);
	glVertex2f(x + 1, y + 1);
	glVertex2f(x, y + 1);
	glEnd();
}

void drawSnake()
{
	// vòng lặp chèn các ô vuông vào đuôi con rắn 
	for (int i = snake_length - 1; i > 0; i--)
	{
		posX[i] = posX[i - 1];
		posY[i] = posY[i - 1];
	}

	// hướng di chuyển của đầu con rắn theo input bàn phím
	if (sDirection == UP) // nếu con rắn đi lên
		posY[0]++; // tăng tọa độ y lên 1 ô
	else if (sDirection == DOWN) // nếu con rắn đi xuống
		posY[0]--; // giảm tọa độ y xuống 1 ô
	else if (sDirection == RIGHT)
		posX[0]++;
	else if (sDirection == LEFT)
		posX[0]--;

	// đầu con rắn
	for (int i = 0; i < snake_length; i++)
	{
		if (i == 0) // cho i=0 là đầu con rắn
			glColor3f(1.0, 0.0, 0.0); // màu đỏ
		else
			glColor3f(0.0, 1.0, 0.0);
		glRectd(posX[i], posY[i], posX[i] + 1, posY[i] + 1); // tạo các ô vuông
	}

	static int dem = 0; // biến đếm
	if (posX[0] == foodX && posY[0] == foodY) // nếu đầu con rắn ăn được food
	{
		snake_length++; // tăng chiều dài (1 ô)
		score++; // tăng điểm (1đ)
		dem++; // tăng biến đếm
			   // điều kiện vòng bo
		if (dem == 5)
		{
			bo++;
			dem = 0;
		}


		//chiều dài tối đa của con rắn
		if (snake_length > MAX)
			snake_length = MAX;
		food = true;
	}

	//điều kiện thua
	if (posX[0] == 0 + bo || posX[0] == gridX - 1 - bo || posY[0] == 0 + bo || posY[0] == gridY - 1 - bo) // nếu đầu con rắn trùng với tọa độ của biên
		gameOver = true; // trò chơi kết thúc

}


void random(int& x, int& y) // hàm tạo food ngẫu nhiên
{
	// vị trí lớn nhất của  food sẽ trừ đi 2 ô ( tính từ biên)
	int _maxX = gridX - 3 - bo;
	int _maxY = gridY - 3 - bo;
	// vị trí nhỏ nhất của food sẽ ở ô 1 (ô 0 là biên)
	int _min = 1 + bo;
	// hàm tạo ngẫu nhiên
	srand(time(NULL));
	x = _min + rand() % (_maxX - _min);
	y = _min + rand() % (_maxY - _min);

}

// hàm vẽ food
void drawFood()
{

	if (food) // nếu food=true
	{

		random(foodX, foodY); // food sẽ xuất hiện ngẫu nhiên
	}
	food = false; // reset lại food 
	glColor3f(0.0, 1.0, 1.0);
	glRectf(foodX, foodY, foodX + 1, foodY + 1); // food là ô vuông
}