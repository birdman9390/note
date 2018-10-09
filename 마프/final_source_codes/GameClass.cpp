#include "GameClass.h"
using namespace std;

float distance(float x1, float y1, float x2, float y2)
{
	float dx, dy;
	dx = x1 - x2;
	dy = y1 - y2;
	return sqrt(pow(dx, 2) + pow(dy, 2));
}

Map::Map() {
	//initializing Map! �Ѽ� is doing this!
}
void Map::setmap(int x, int y, int value)
{
	map[x][y] = value;
}
int Map::getmap(int n, int m)
{
	return map[n][m];
}



User::User() {
	direction = 2;
	isDead = false;
	item01_num = 0;
	item02_num = 0;
}
User::User(float x, float y) {
	pos_x = x;
	pos_y = y;
	direction = 2;
	isDead = false;
	item01_num = 0;
	item02_num = 0;
}
void User::move()
{
	//
}
//private �ٷ�� �Լ��� �� �˾Ƽ� �����
void User::set_direction(int dir)
{
	direction = dir;
}
int User::get_direction()
{
	return direction;
}
float User::get_pos_x()
{
	return pos_x;
}
float User::get_pos_y()
{
	return pos_y;
}
void User::set_pos(float x, float y)
{
	pos_x = x;
	pos_y = y;
}
int User::get_item_num(int item_type)
{
	if(item_type==1)
		return item01_num;
	if (item_type == 2)
		return item02_num;
}
//������ ������ return

void User::increase_item_num(int item_type)
{
	if (item_type == 1)
		item01_num++;
	if (item_type == 2)
		item02_num++;
}
//������ �������� �Ծ����� �����۰����� ������Ű�� �Լ�
void User::decrease_item_num(int item_type)
{
	if (item_type == 1)
		item01_num--;
	if (item_type == 2)
		item02_num--;
}
//������ �������� ������� �� �����۰����� ���ҽ�Ű�� �Լ�
bool User::isvalidDirection(int dir)
{
	switch (dir)
	{
	case 0:
		//��
		if (Map::getmap(int(pos_x - 0.5), int(pos_y + 0.5)) == 1 || Map::getmap(int(pos_x + 0.49), int(pos_y + 0.5)) == 1)
			return false;
		return true;
	case 1:
		//��
		if (Map::getmap(int(pos_x + 0.5), int(pos_y + 0.499)) == 1 || Map::getmap(int(pos_x + 0.5), int(pos_y - 0.5)) == 1)
			return false;
		return true;
	case 2:
		//��
		if (Map::getmap(int(pos_x - 0.5), int(pos_y - 0.501)) == 1 || Map::getmap(int(pos_x + 0.499), int(pos_y - 0.501)) == 1)
			return false;
		return true;
	case 3:
		//��
		if (Map::getmap(int(pos_x - 0.501), int(pos_y + 0.499)) == 1 || Map::getmap(int(pos_x - 0.501), int(pos_y - 0.5)) == 1)
			return false;
		return true;
	}
}
//dir �������� ���� �����ϼ� �ִ��� Ȯ���ؼ� �����ϼ� ������ true�� return�Ѵ�

int User::itemCheck() {
	if (Map::getmap(int(pos_x), int(pos_y)) == 4) {
		cout << "item01" << endl;
		Map::setmap(int(pos_x), int(pos_y), 0);
		increase_item_num(1);
		return 1;
	}
	else if (Map::getmap(int(pos_x), int(pos_y)) == 5) {
		cout << "item02" << endl;
		Map::setmap(int(pos_x), int(pos_y), 0);
		increase_item_num(2);
		return 2;
	}
	else
		return 0;
}	

void User::set_isDead() {
	isDead = true;
}
bool User::get_isDead() {
	return isDead;
}
void User::set_clear() {
	isClear = true;
}
bool User::get_clear() {
	return isClear;
}


Enemy::Enemy() {
	direction = 2;
	enemy_list.push_back(this);
}
Enemy::Enemy(float x, float y)
{
	direction = 2;
	pos_x = x;
	pos_y = y;
	enemy_list.push_back(this);
}
void Enemy::move() {
	//
}//is_aggro ���õȰſ� ���� ���긦 �Ѵ�. �÷��̾�� ��������� �÷��̾ ���δ�! �Ѿ˿� ���� �״°� �Ѿ�Ŭ������ �־�����Ŵ� ���� ���ʿ�. 
 //�����δ� �������ؾ���. �������� ������. �ð����� �����ϰ� ����������. ������ �����ڰ� �˾Ƽ� ����!
float Enemy::get_pos_x()
{
	return pos_x;
}
float Enemy::get_pos_y()
{
	return pos_y;
}
void Enemy::set_pos(float x, float y)
{
	pos_x = x;
	pos_y = y;
}
Enemy* Enemy::get_enemy(int i)
{
	return enemy_list[i];
}
//i��° enemy�� �ҷ���
vector<Enemy*> Enemy::get_enemy_list()
{
	return enemy_list;
}
//enemy_list�� �ҷ���
void Enemy::remove_enemy(int i)
{
	enemy_list.erase(enemy_list.begin() + i);//???delete �Ƚᵵ �Ǵ� �ɱ�.
	
	int enemy_num = enemy_list.size();
	cout << enemy_num << " enemy left..." << endl;
	if (enemy_num == 0)
		User::set_clear();
}
//i ��° enemy�� �����ϴ� �Լ�
int Enemy::get_enemy_num()
{
	return enemy_list.size();
}
bool Enemy::isUserNear()
{
	return distance(pos_x, pos_y, User::get_pos_x(), User::get_pos_y()) <= AGGRO_DISTANCE;
}
//������ ����� ��� true�� return�Ѵ�. �Ÿ� ������ AGGRO_DISTANCE���� ����� ��츦 �������� ��
bool Enemy::isUserCollide() {
	return distance(pos_x, pos_y, User::get_pos_x(), User::get_pos_y()) <= DEATH_DISTANCE;
}
//������ �浹�� ��� true�� return�Ѵ�. �Ÿ� ������ DEATH_DISTANCE���� ����� ��츦 �������� ��.
bool Enemy::isvalidDirection(int dir)
{
	switch (dir)
	{
	case 0:
		//��
		if (Map::getmap(int(pos_x - 0.5), int(pos_y + 0.5)) == 1 || Map::getmap(int(pos_x + 0.49), int(pos_y + 0.5)) == 1)
			return false;
		return true;
	case 1:
		//��
		if (Map::getmap(int(pos_x + 0.5), int(pos_y + 0.499)) == 1 || Map::getmap(int(pos_x + 0.5), int(pos_y - 0.5)) == 1)
			return false;
		return true;
	case 2:
		//��
		if (Map::getmap(int(pos_x - 0.5), int(pos_y - 0.501)) == 1 || Map::getmap(int(pos_x + 0.499), int(pos_y - 0.501)) == 1)
			return false;
		return true;
	case 3:
		//��
		if (Map::getmap(int(pos_x - 0.501), int(pos_y + 0.499)) == 1 || Map::getmap(int(pos_x - 0.501), int(pos_y - 0.5)) == 1)
			return false;
		return true;
	case 4:
		return true;
	}
}

bool Enemy::istickzero()
{
	return tick == 0;
}
void Enemy::increasetick()
{
	tick = (tick + 1) % 10;
}

void Enemy::moveAll()
{
	tick = (tick + 1) % 10;
	if (tick == 0)
	{
		for (int i = 0; i < get_enemy_num(); i++)
		{
			if (enemy_list[i]->isUserNear()) {
				enemy_list[i]->setdirectionToUser();
			}
			else
				enemy_list[i]->setdirection(rand() % 5);
		}
	}
	for (int i = 0; i < get_enemy_num(); i++)
	{
		switch (enemy_list[i]->getdirection())
		{
		case 0://��
			if(enemy_list[i]->isvalidDirection(0))
				enemy_list[i]->add_to_y(0.05); break;
			break;
		case 1://��
			if (enemy_list[i]->isvalidDirection(1))
				enemy_list[i]->add_to_x(0.05); break;
			break;
		case 2://��
			if (enemy_list[i]->isvalidDirection(2))
				enemy_list[i]->add_to_y(-0.05); break;
			break;
		case 3://��
			if (enemy_list[i]->isvalidDirection(3))
				enemy_list[i]->add_to_x(-0.05); break;
			break;
		case 4:
			break;
		}
	}

}
void Enemy::add_to_x(float i)
{
	pos_x += i;
}
void Enemy::add_to_y(float i)
{
	pos_y += i;
}
void Enemy::setdirection(int dir)
{
	direction = dir;
}
int Enemy::getdirection()
{
	return direction;
}

void Enemy::setdirectionToUser() {
	float user_x=User::get_pos_x();
	float user_y=User::get_pos_y();
	float x_distance = pow(pos_x - user_x, 2);
	float y_distance = pow(pos_y - user_y, 2);
	
	if (x_distance > y_distance) {//x, y�� �� �հŸ��� �����������.
		if (pos_x < user_x)
			setdirection(1);//������ ����
		else
			setdirection(3);//��
	}
	else {
		if (pos_y < user_y)
			setdirection(0);//��
		else
			setdirection(2);//��
	}

}


Bullet::Bullet() {
	switch (User::get_direction())
	{
	case 0://��
		pos_x = User::get_pos_x();
		pos_y = User::get_pos_y() + 0.3;
		break;
	case 1://��
		pos_x = User::get_pos_x() + 0.3;
		pos_y = User::get_pos_y();
		break;
	case 2://��
		pos_x = User::get_pos_x();
		pos_y = User::get_pos_y() - 0.3;
		break;
	case 3://��
		pos_x = User::get_pos_x() - 0.3;
		pos_y = User::get_pos_y();
		break;
	}
	direction = User::get_direction();
	velocity = BULLET_VELOCITY;
	bullet_list.push_back(this);
}
Bullet::Bullet(float x, float y, int dir) {
	pos_x = x;
	pos_y = y;
	direction = dir;
	velocity = BULLET_VELOCITY;
	bullet_list.push_back(this);
}
int Bullet::move()//enemy�� �ε����� enemy���̰� �Ѿ� �����, ���̶� �ε����� �����
{
	switch (direction)
	{
	case 0://��
		pos_y += BULLET_VELOCITY;
		break;
	case 1://��
		pos_x += BULLET_VELOCITY;
		break;
	case 2://��
		pos_y -= BULLET_VELOCITY;
		break;
	case 3://��
		pos_x -= BULLET_VELOCITY;
		break;
	}
	return check_state();
}
int Bullet::check_state()
{
	if (Map::getmap(int(pos_x), int(pos_y)) == 1)
	{
		return -2;
	}
	else
	{
		for (int i = 0; i < Enemy::get_enemy_num(); i++)
		{
			if (distance(pos_x, pos_y, Enemy::get_enemy(i)->get_pos_x(), Enemy::get_enemy(i)->get_pos_y()) <= DEATH_DISTANCE)
			{
				return i;
			}
		}
		return -1;
	}
}//�Ϲ����� ��Ȳ���� -1�� return, ���� �ε������ -2�� return, enemy�� �ε������� enemy�� index�� return
Bullet* Bullet::get_bullet(int i)
{
	return bullet_list[i];
}
int Bullet::get_bullet_num()
{
	return bullet_list.size();
}
vector<Bullet*> Bullet::get_bullet_list()
{
	return bullet_list;
}
float Bullet::get_pos_x()
{
	return pos_x;
}
float Bullet::get_pos_y()
{
	return pos_y;
}

void Bullet::remove_bullet(int i)
{
	bullet_list.erase(bullet_list.begin() + i);
}


int User::direction;
float User::pos_x;
float User::pos_y;
int User::item01_num;
int User::item02_num;
bool User::isDead;
bool User::isClear;
int Map::map[50][50];
int Enemy::tick = 0;
vector<Enemy*> Enemy::enemy_list;
vector<Bullet*> Bullet::bullet_list;