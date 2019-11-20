#ifdef _DEBUG

#include <tuple>
#include <cocos2d.h>
#include "_DebugDispOut.h"

std::unique_ptr<_DebugDispOut, _DebugDispOut::_DebugDispOutDeleter> _DebugDispOut::s_Instance(new _DebugDispOut);


void _DebugDispOut::SetAlpha()
{
	//if (CheckHitKey(KEY_INPUT_F3))
	//{
	//	_alpha = 150;
	//}
	//if (CheckHitKey(KEY_INPUT_F4))
	//{
	//	_alpha = 0;
	//}
}

void _DebugDispOut::DrawBox(int x, int y, int fx, int fy, unsigned int color, bool fillFlag)
{
	//SetScreen();
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);

	//DxLib::DrawBox(x, y, fx, fy, color, fillFlag);
	////DxLib::DrawBox(x, y, fx, fy, color, fillFlag);

	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//RevScreen();
}

void _DebugDispOut::DrawLine(int x, int y, int fx, int fy, int color)
{
	//SetScreen();
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);

	//DxLib::DrawLine(x, y, fx, fy, color);

	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//RevScreen();
}

void _DebugDispOut::DrawGraph(int x, int y, int Handle, bool Trans)
{
	//SetScreen();
	//DxLib::DrawGraph(x, y, Handle,Trans);
	//RevScreen();
}

void _DebugDispOut::DrawString(int x, int y, const char *str, unsigned color)
{
	//SetScreen();
	//DxLib::DrawString(x, y, str, color);
	//RevScreen();
}

void _DebugDispOut::ScreenClear()
{
	//SetScreen();
	//ClsDrawScreen();
	//SetDrawScreen(ghBefor);
}


void _DebugDispOut::SetScreen()
{
	//ghBefor = GetDrawScreen();
	//SetDrawScreen(_debugScreen);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
}

void _DebugDispOut::RevScreen()
{
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//lpSceneMng.addDrawQue({ _debugScreen,0,0 });

	////SetWaitTime(0);
	////WaitMode();

	////lpSceneMng.addDrawQue({ _debugScreen, lpSceneMng.gameScreenPos.x, lpSceneMng.gameScreenPos.y });
	//SetDrawScreen(ghBefor);
}

void _DebugDispOut::SetWaitTime(int time)
{
	_waitTime = time;
}

void _DebugDispOut::WaitMode()
{
	//if (CheckHitKey(KEY_INPUT_ADD))
	//{
	//	_waitTime += 20;
	//}
	//if (CheckHitKey(KEY_INPUT_SUBTRACT))
	//{
	//	_waitTime -= 20;
	//	if (_waitTime <= 0.0)
	//	{
	//		_waitTime = 0.0;
	//	}
	//}
	//if (CheckHitKey(KEY_INPUT_DIVIDE))
	//{
	//	_waitTime = 0.0;
	//}
	//_startTime = ChronoClock::now();
	//do
	//{
	//	_endTime = ChronoClock::now();
	//	while (ProcessMessage() != 0 || CheckHitKey(KEY_INPUT_ESCAPE) == 1)
	//	{
	//		break;
	//	}
	//} while (std::chrono::duration_cast<std::chrono::milliseconds>(_endTime - _startTime).count() < _waitTime);
}


_DebugDispOut::_DebugDispOut()
{
	//_alpha = 150;
	////	ƒXƒNƒŠ[ƒ“‚Ì“o˜^
	//_debugScreen = MakeScreen(lpSceneMng.screenSize.x, lpSceneMng.screenSize.y, true);
}

_DebugDispOut::~_DebugDispOut()
{
	
}

#endif // _DEBUG
