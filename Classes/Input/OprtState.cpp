#include "OprtState.h"


OprtState::OprtState()
{
	for (auto itrKey : UseKey())
	{
		_oprtKeyList[itrKey] = false;
	}
}

OprtState::~OprtState()
{
}

OprtKeyList OprtState::GetKeyList()
{
	return _oprtKeyList;
}
