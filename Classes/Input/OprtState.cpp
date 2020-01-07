#include "OprtState.h"


OprtState::OprtState()
{
	for (auto itrKey : UseKey())
	{
		_oprtKeyList[itrKey] = false;
	}
	touchPoint = cocos2d::Vec2(-10, -10);
}

OprtState::~OprtState()
{
}

OprtKeyList OprtState::GetKeyList()
{
	return _oprtKeyList;
}

cocos2d::Vec2 OprtState::GetTouchPoint()
{
	return touchPoint;
}
