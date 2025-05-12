#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
}

void Enemy::Update(float deltaTime)
{

}

void Enemy::Render()
{
}

void Enemy::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Enemy::SetSpeed(float speed)
{
	this->speed = speed;
}

float Enemy::GetX() const
{
	return x;
}

float Enemy::GetY() const
{
	return y;
}

float Enemy::GetSpeed() const
{
	return speed;
}
