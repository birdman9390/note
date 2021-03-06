#include "GameClass.h"
#include<time.h>
#include<fstream>
#include<sstream>

//map Info.
#define blank 0
#define wall 1
#define player 2
#define enemy 3
#define item01 4
#define item02 5
using namespace std;

int window_w;
int window_h;

void draw_square(float x, float y, float unit, float R, float G, float B) {
	glColor3f(R, G, B);
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x, y + unit);
	glVertex2f(x + unit, y + unit);
	glVertex2f(x + unit, y);
	glEnd();
}

void draw_triangle(float x, float y, float unit, float R, float G, float B) {
	glColor3f(R, G, B);
	glBegin(GL_TRIANGLES);
	glVertex2f(x, y);
	glVertex2f(x + unit, y);
	glVertex2f(x + unit / 2, y + unit);
	glEnd();
}

void draw_wall(float x, float y, float unit) {
	draw_square(x, y, unit, 0.7, 0.7, 0.7);
}
void draw_blank(float x, float y, float unit) {
	draw_square(x, y, unit, 0, 0, 0);
}
void draw_player(float x, float y, float unit) {
	draw_square(x, y, unit, 0, 0, 1);
	draw_square(x + unit * 0.15, y + unit * 0.65, unit*0.2, 1, 1, 1);
	draw_square(x + unit * 0.65, y + unit * 0.65, unit*0.2, 1, 1, 1);
	draw_triangle(x + unit * 0.4, y + unit * 0.2, unit*0.2, 1, 1, 1);
}

void draw_item01(float x, float y, float unit) {
	draw_square(x + unit * 0.4, y + unit * 0.7, unit*0.2, 0, 1, 0);
	draw_square(x + unit * 0.15, y + unit * 0.1, unit*0.7, 0, 1, 0);
	draw_triangle(x + unit * 0.3, y + unit * 0.2, unit*0.4, 0, 0, 0);
}
void draw_item02(float x, float y, float unit) {
	draw_square(x + unit * 0.4, y + unit * 0.7, unit*0.2, 1, 1, 0);
	draw_square(x + unit * 0.15, y + unit * 0.1, unit*0.7, 1, 1, 0);
	draw_triangle(x + unit * 0.3, y + unit * 0.2, unit*0.4, 0, 0, 0);
}

void draw_enemy(float x, float y, float unit) {
	draw_square(x, y, unit, 1, 0, 0);
	draw_square(x + unit * 0.15, y + unit * 0.65, unit*0.2, 1, 1, 1);
	draw_square(x + unit * 0.65, y + unit * 0.65, unit*0.2, 1, 1, 1);
	draw_triangle(x + unit * 0.4, y + unit * 0.2, unit*0.2, 1, 1, 1);
}

void draw_map(int row, int col, int unit) {
	int object;
	for (int i = 0; i <row; i++) {
		for (int j = 0; j < col; j++) {
			object = Map::getmap(i, j);
			switch (object) {
			case blank:
				draw_blank(i, j , unit); break;
			case wall:
				draw_wall(i, j , unit); break;
			case item01:
				draw_blank(i, j, unit);
				draw_item01(i, j, unit); break;
			case item02:
				draw_blank(i, j, unit);
				draw_item02(i, j, unit); break;
			}
		}
	}
}


void init(void)
{
	srand((unsigned int)time(NULL));
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT); 


	string filePath = "game_map_easy.csv";
	ifstream openFile(filePath.data());
	if (openFile.is_open()) {
		string line;
		int i = 0;
		int j = 0;
		while (getline(openFile, line, '\n')) {
			stringstream lineStream(line);
			string cell;
			j = 0;
			while (getline(lineStream, cell, ',')) {
				Map::setmap(j, (50 - 1) - i, stoi(cell));
				if (stoi(cell) == player)
					new User((float)j + 0.5, (50-1)-(float)i+ 0.5);
				else if (stoi(cell) == enemy)
					new Enemy((float)j + 0.5, (50 - 1) - (float)i + 0.5);
				j++;
			}
			i++;
		}
		openFile.close();
	}
}
void display(void)
{
	//====================================첫 번째 Viewport 구간 시작====================================
	glViewport(0, 0, window_w, window_h*0.85);
	glLoadIdentity();
	gluOrtho2D(User::get_pos_x() - 7.5, User::get_pos_x() + 7.5, User::get_pos_y() - 7.5, User::get_pos_y() + 7.5);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glClear(GL_COLOR_BUFFER_BIT);

	draw_map(50, 50, 1);

	draw_player(User::get_pos_x() - 0.5, User::get_pos_y() - 0.5, 1);

	for (int i = 0; i < Enemy::get_enemy_num(); i++)
	{
		draw_enemy(Enemy::get_enemy(i)->get_pos_x() - 0.5, Enemy::get_enemy(i)->get_pos_y() - 0.5,1);
	}

	for (int i = Bullet::get_bullet_num() - 1; i >= 0; i--)
	{
		draw_square(Bullet::get_bullet(i)->get_pos_x() - 0.05, Bullet::get_bullet(i)->get_pos_y() - 0.05, 0.1, 255,204,0);
	}

	if (User::get_isDead()) {
		cout << "User is dead :(" << endl;
		draw_square(0, 0, 50, 1, 0, 0);//패배의 붉은색.
	}

	if (User::get_clear()) {
		cout << "Game Clear!!!" << endl;
		draw_square(0, 0, 50, 0, 0, 1);//승리의 파란색.
	}

	//====================================두 번째 Viewport 구간 시작====================================
	glViewport(0, window_h*0.85, window_w, window_h-window_h*0.85);
	glLoadIdentity();
	gluOrtho2D(0,10,0,2); //2x10 크기의 아이템 창 설정. unit단위가 변경됨.

	int item01_num=User::get_item_num(1);
	int item02_num=User::get_item_num(2);
	for (int i = 0; i < item01_num; i++)
		draw_item01(i, 0, 1);
	for (int i = 0; i < item02_num; i++)
		draw_item02(i, 1, 1);

	glutSwapBuffers();
}
void reshape(int w, int h)
{
	window_w = w;
	window_h = h;
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == ' ')
	{
		new Bullet();
	}
	glutPostRedisplay();
}

void specialkeyboard(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		User::set_direction(0);
		if(User::isvalidDirection(0))
			User::set_pos(User::get_pos_x(),User::get_pos_y()+UNIT_SPEED);
		break;
	case GLUT_KEY_DOWN:
		User::set_direction(2);
		if (User::isvalidDirection(2))
			User::set_pos(User::get_pos_x(), User::get_pos_y()- UNIT_SPEED);
		break;
	case GLUT_KEY_RIGHT:
		User::set_direction(1);
		if (User::isvalidDirection(1))
			User::set_pos(User::get_pos_x()+ UNIT_SPEED, User::get_pos_y());
		break;
	case GLUT_KEY_LEFT:
		User::set_direction(3);
		if (User::isvalidDirection(3))
			User::set_pos(User::get_pos_x()- UNIT_SPEED, User::get_pos_y());
		break;
	}
	glutPostRedisplay();
}



void timer(int value) {

	for (int i = Bullet::get_bullet_num() - 1; i >= 0; i--)
	{
		int state=Bullet::get_bullet(i)->move();
		cout << "TIMER!!!, "<<state<<'\n';
		if (state == -2)
		{
			Bullet::remove_bullet(i);
		}
		else if (state >= 0)
		{
			Enemy::remove_enemy(state);
			Bullet::remove_bullet(i);
		}
	}
	Enemy::moveAll();

	for (int i = 0; i < Enemy::get_enemy_num(); i++) {
		if (Enemy::get_enemy(i)->isUserCollide()) {
			User::set_isDead();
		}
	}	//유저가 죽었는지 체크.
	User::itemCheck();	//먹은 아이템종류의 수를 증가시키고 콘솔에 출력.

	glutPostRedisplay();      //윈도우를 다시 그리도록 요청
	glutTimerFunc(30, timer, 0); //다음 타이머 이벤트는 30밀리세컨트 후  호출됨.
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 600); //viewport 2개 사용: 게임 플레이 사이즈는 500x500, 상단 아이템 정보창 사이즈는 500x100
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeyboard);
	glutTimerFunc(0, timer, 0);
	glutMainLoop(); 

	return 0;
}