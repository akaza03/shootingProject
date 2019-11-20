#include "Enemy.h"



Enemy::Enemy()
{
	//Sprite::create("image/Sprites/enemies/crab-idle/crab-idle-1.png");
	//setPosition(cocos2d::Vec2(100, 100));

	_actData.cType = CharaType::ENEMY;

	this->scheduleUpdate();
}


Enemy::~Enemy()
{
}

void Enemy::update(float d)
{
}

void Enemy::AnimStateUpdate()
{

}
