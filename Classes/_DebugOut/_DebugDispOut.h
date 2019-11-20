#pragma once
#ifdef _DEBUG
#include <memory>
#include <chrono>

#define DBG_CLEAR() (_DebugDispOut::GetInstance().ScreenClear())						//	このスクリーンのClsDrawScreen
#define DBG_CHAGE_ALPHA() (_DebugDispOut::GetInstance().SetAlpha())						//	表示非表示の切り替え
#define DBG_BOX(...) (_DebugDispOut::GetInstance().DrawBox(__VA_ARGS__))				//	BOXの表示
#define DBG_LINE(...) (_DebugDispOut::GetInstance().DrawLine(__VA_ARGS__))				//	線の表示
#define DBG_IMAGE(...) (_DebugDispOut::GetInstance().DrawGraph(__VA_ARGS__))			//	画像の表示
#define DBG_STR(...) (_DebugDispOut::GetInstance().DrawString(__VA_ARGS__))				//	文字の表示

#define DBG_WAIT_TIME(fmt) (_DebugDispOut::GetInstance().SetWaitTime(fmt))				//	_waitTimeのセット
#define DBG_WAIT() (_DebugDispOut::GetInstance().WaitMode())							//	ゲームのスピード管理用

//	書式付き文字列の表示
#define DBG_FORSTR(...) {\
	_DebugDispOut::GetInstance().SetScreen();\
	DxLib::DrawFormatString(__VA_ARGS__);\
	_DebugDispOut::GetInstance().RevScreen();\
	}

using ChronoClock = std::chrono::system_clock;
using TimePoint = ChronoClock::time_point;

class _DebugDispOut
{
public:
	static _DebugDispOut& GetInstance()
	{
		return *s_Instance;
	}

	void SetAlpha();
	void DrawBox(int x, int y, int fx, int fy, unsigned int color, bool fillFlag);
	void DrawLine(int x, int y, int fx, int fy, int color);
	void DrawGraph(int x, int y, int Handle, bool Trans);										
	void DrawString(int x, int y, const char *str, unsigned color);
	
	void ScreenClear();

	void SetScreen();						//	描画開始時に呼び出し
	void RevScreen();						//	描画終了時に呼び出し

	void SetWaitTime(int time);
	void WaitMode();

private:
	struct _DebugDispOutDeleter
	{
		void operator()(_DebugDispOut* _debugDispOut)const
		{
			delete _debugDispOut;
		}
	};

	_DebugDispOut();
	~_DebugDispOut();

	static std::unique_ptr<_DebugDispOut, _DebugDispOutDeleter> s_Instance;

	int _alpha;								//	透明度

	int ghBefor;							//	前のスクリーンの保存用
	int _debugScreen;						//	このシーンの描画を保存するためのスクリーン

	int _waitTime;							//	時間のウェイト値
	TimePoint _startTime;
	TimePoint _endTime;
};

#else

#define DBG_CLEAR()
#define DBG_CHAGE_ALPHA()
#define DBG_BOX(...)
#define DBG_LINE(...)
#define DBG_IMAGE(...)
#define DBG_STR(...)
#define DBG_FORSTR(...)

#endif // _DEBUG