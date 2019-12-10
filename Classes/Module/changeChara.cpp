#include "Unit/Character.h"
#include "changeChara.h"


bool changeChara::operator()(cocos2d::Sprite & sp, ActData & act)
{
	int number = act.charaID;
	int oldNumber = number;

	if (std::get<0>(act.key[UseKey::K_A]) && !std::get<1>(act.key[UseKey::K_A]))
	{
		if (number <= 0)
		{
			number = 2;
		}
		else
		{
			number--;
		}
	}
	else if (std::get<0>(act.key[UseKey::K_S]) && !std::get<1>(act.key[UseKey::K_S]))
	{
		if (number >= 2)
		{
			number = 0;
		}
		else
		{
			number++;
		}
	}

	if (number != oldNumber)
	{
		if (act.changeCnt[number] == 0)
		{
			act.charaID = number;
			act.changeCnt[number] = 100;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (act.changeCnt[i] > 0)
		{
			act.changeCnt[i]--;
		}	
	}
	return false;
}
