#include "Unit/Character.h"
#include "DirCheck.h"


bool DirCheck::operator()(cocos2d::Sprite & sp, ActData & act)
{
	auto oldDir = act.dir;

	//if (act.distance.x < 0)
	//{
	//	act.dir = DIR::LEFT;
	//}
	//else if (act.distance.x > 0)
	//{
	//	act.dir = DIR::RIGHT;
	//}

	if (std::get<0>(act.key[UseKey::K_LEFT]))
	{
		act.dir = DIR::LEFT;
	}
	else if (std::get<0>(act.key[UseKey::K_RIGHT]))
	{
		act.dir = DIR::RIGHT;
	}

	if (oldDir != act.dir)
	{
		if (act.dir == DIR::RIGHT)
		{
			sp.setFlippedX(true);
		}
		else if (act.dir == DIR::LEFT)
		{
			sp.setFlippedX(false);
		}
	}
	return false;
}
