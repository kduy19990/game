#pragma once
// gán giá trị cho hướng di chuyển của con rắn
#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2

#define MAX 100 // chiều dài tối đa của con rắn

// các hàm xử lý trong game
void initGrid(int, int);
void drawGrid();
void drawSnake();
void drawFood();;
void random(int&, int&);


