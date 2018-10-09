#pragma once

#include <windows.h>
#include <gl/gl.h>/
#include <gl/glut.h>
#include <vector>
#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define DEATH_DISTANCE 0.5
#define AGGRO_DISTANCE 5
#define BULLET_VELOCITY 1
#define UNIT_SPEED 0.5
using namespace std;

float distance(float x1, float y1, float x2, float y2);
class Map
{
private:
	static int map[50][50];//0 : ���, 1: ��, 2: User, 3: Enemy, 4: Item
							 //���⼭ ������ ��������!
public:
	Map();
	static void setmap(int x, int y, int value);
	static int getmap(int n, int m);
};

class User
{
private:
	static int direction;// 0:��, 1: ��, 2: ��, 3: �� 
						 //User�� direction�� default�� ����(2)���� �����Ǿ� �ִ�.
	static float pos_x, pos_y;
	static int item01_num;//������ ���� ������01�� ����
	static int item02_num;
	static bool isDead;
	static bool isClear;
public:
	User();
	User(float x, float y);
	void move();
	//private �ٷ�� �Լ��� �� �˾Ƽ� �����
	static void set_direction(int dir);
	static int get_direction();
	static float get_pos_x();
	static float get_pos_y();
	static void set_pos(float x, float y);
	static int get_item_num(int item_type);
	//������ ������ return
	static void increase_item_num(int item_type);
	//������ �������� �Ծ����� �����۰����� ������Ű�� �Լ�
	static void decrease_item_num(int item_type);
	//������ �������� ������� �� �����۰����� ���ҽ�Ű�� �Լ�
	static bool isvalidDirection(int dir);
	//dir �������� ���� �����ϼ� �ִ��� Ȯ���ؼ� �����ϼ� ������ true�� return�Ѵ�
	static int itemCheck();
	// ���� ������ ���� ��ȯ. �� ������ 0 ��ȯ.
	static void set_isDead();
	static bool get_isDead();
	static void set_clear();
	static bool get_clear();
};


class Enemy
{
private:
	float pos_x, pos_y;
	bool is_aggro;//0 : ��׷� �Ȳ���, 1: ��׷� ����.  default�� ��׷� �Ȳ��� ����(0)�� �����Ǿ� ����
	static vector<Enemy*> enemy_list;
	static int tick;
	int direction;
public:
	Enemy();
	Enemy(float x, float y);
	void move();
	 //�����δ� �������ؾ���. �������� ������. �ð����� �����ϰ� ����������. ������ �����ڰ� �˾Ƽ� ����!

	static void moveAll();
	float get_pos_x();
	float get_pos_y();
	void set_pos(float x, float y);
	static Enemy* get_enemy(int i);
	//i��° enemy�� �ҷ���
	static vector<Enemy*> get_enemy_list();
	//enemy_list�� �ҷ���
	static void remove_enemy(int i);
	//i ��° enemy�� �����ϴ� �Լ�
	static int get_enemy_num();
	bool isUserNear();
	//������ ����� ��� true�� return�Ѵ�. �Ÿ� ������ AGGRO_DISTANCE���� ����� ��츦 �������� ��
	bool isUserCollide();
	//������ �浹�� ��� true�� return�Ѵ�. �Ÿ� ������ DEATH_DISTANCE���� ����� ��츦 �������� ��.
	bool isvalidDirection(int dir);
	//dir �������� ���� �����ϼ� �ִ��� Ȯ���ؼ� �����ϼ� ������ true�� return�Ѵ�
	static bool istickzero();
	static void increasetick();
	void setdirection(int dir);
	int getdirection();
	void add_to_x(float i);
	void add_to_y(float i);

	void setdirectionToUser();//������ �����Ÿ� ��������� �� ������ ���󰡰� direction����.
};


class Bullet
{
private:
	float pos_x, pos_y;
	int direction;
	int velocity;
	static vector<Bullet*> bullet_list;
public:
	Bullet();
	Bullet(float x, float y, int dir);
	int move();
	int check_state();
	static Bullet* get_bullet(int i);
	static vector<Bullet*> get_bullet_list();
	static int get_bullet_num();
	static void remove_bullet(int i);
	float get_pos_x();
	float get_pos_y();
};
