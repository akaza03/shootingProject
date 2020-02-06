#include "Unit/Character.h"
#include "SetPos.h"

bool SetPos::operator()(cocos2d::Sprite & sp, ActData & act)
{
	act.distance.y += act.Gravity;
	sp.setPosition(sp.getPosition().x + act.distance.x, sp.getPosition().y + act.distance.y);
	return false;
}
