#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <Windows.h> // thư viện để sử dụng MessageBox
#include "Dependencies\freeglut\freeglut.h"
#include <gl/GL.h>
#include "game-source.h" // thư viện của trò chơi
#include <stdio.h>


#define COLUMNS 40 //khai báo số cột (x)
#define ROWS 40 // khai báo số dòng (y)
#define FPS 10 // khai báo tốc độ khung hình ( trong 1 giây con rắn đi được 20 ô)

extern short sDirection; // khai báo biến hướng đi mặc định của con rắn
bool gameOver = false; // khai báo điều kiện thua mặc định
int score = 0; // biến đếm số điểm

			   //khai báo các biến xử lý của trò chơi
void timer(int);
void display();
void reshape(int, int);
void keyboard(int, int, int);

void init() // khởi tạo background
{
	glClearColor(0.0, 0.0, 0.0, 1.0); // màu background đen
	initGrid(COLUMNS, ROWS); // khởi tạo lưới (lấy số dòng và số cột)
}


void display() // hàm thực hiện các thao tác hiển thị ra màn hình
{
	glClear(GL_COLOR_BUFFER_BIT); // chạy màu background
	drawGrid(); // vẽ lưới
	drawSnake(); // vẽ con rắn
	drawFood(); // vẽ thức ăn
	glutSwapBuffers(); // chạy hoán đổi 2 buffer

					   // hiện ra bảng thông báo trò chơi kết thúc và số điểm
	if (gameOver)
	{
		char _score[10]; // chuỗi _score có độ dài 3 chữ số
		itoa(score, _score, 10); // chuyển đổi int sang chuỗi
		char text[20] = "So Diem Cua Ban: "; // chuỗi thông báo điểm có độ dài 20 kí tự
		strcat(text, _score); // nối 2 chuỗi lại với nhau
		MessageBoxA(NULL, text, "GAME OVER", 0);
		exit(0); // thoát chương trình

	}
}

void reshape(int w, int h) // các thao tác cần làm khi cửa sổ bị thay đổi kích thước 
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION); // ma trận dạng projection(chiếu)
	glLoadIdentity(); // reset lại ma trận projection
	glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0); // đặt phạm vi giới hạn tọa độ  từ 0 đến số Cột(40),từ 0 đến số Dòng(40)
	glMatrixMode(GL_MODELVIEW); // ma trận dạng model-view
}

void timer(int) // giới hạn fps
{
	glutPostRedisplay(); /*cập nhật lại màn hình hiển thị*/
	glutTimerFunc(800 / FPS, timer, 0); // số frame hiển thị trong 1s



}
void keyboard(int key, int, int) // các thao tác từ bàn phím để điều khiển con rắn
{
	// trong trò chơi con rắn nếu con rắn đang ở hướng nào thì sẽ không di chuyển theo hướng đối nghịch
	// VD: con rắn đang đi theo hướng lên thì sẽ không đi theo hướng xuống được
	switch (key)
	{
	case GLUT_KEY_UP: // nút mũi tên đi lên
		if (sDirection != DOWN) //kiểm tra không phải hướng đi đối nghịch
			sDirection = UP; // con rắn sẽ đi lên
		break;

	case GLUT_KEY_DOWN: // nút mũi tên đi xuống
		if (sDirection != UP)
			sDirection = DOWN;
		break;

	case GLUT_KEY_RIGHT: // nút mũi tên đi qua phải
		if (sDirection != LEFT)
			sDirection = RIGHT;
		break;

	case GLUT_KEY_LEFT: // nút mũi tên đi qua trái
		if (sDirection != RIGHT)
			sDirection = LEFT;
		break;

	}
}
int main(int argc, char** argv)
{
	system("pause");
	glutInit(&argc, argv); // khởi tạo thông số của glut
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // thiết lập chế độ màu, buffer cho bàn hình
	glutInitWindowSize(500, 500); // thiết lập kích thước cửa sổ màn hình
	glutCreateWindow("SNAEK"); // tạo tiêu đề cho cửa sổ màn hình
	glutDisplayFunc(display); // gọi hàm thực hiện việc vẽ (display)
	glutReshapeFunc(reshape); // gọi hàm thực hiện điều chỉnh kích thước cửa sổ (reshape)
	glutTimerFunc(0, timer, 0); // hàm timer sẽ được gọi đầu tiên sau khi chạy trò chơi
	glutSpecialUpFunc(keyboard); // thao tác điểu khiển từ bàn phím
	init(); // gọi hàm khởi tạo background
	glutMainLoop(); // vòng lặp xử lý các sự kiện glut
	return 0; // thoát chương trình
}

