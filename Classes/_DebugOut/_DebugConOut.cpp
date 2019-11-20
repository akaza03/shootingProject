#ifdef _DEBUG

#include <Windows.h>
#include "_DebugConOut.h"

std::unique_ptr<_DebugConOut,_DebugConOut::_DebugConOutDeleter> _DebugConOut::s_Instance(new _DebugConOut);


_DebugConOut::_DebugConOut()
{
	////	前にあるウィンドウのハンドルを取得する
	HWND hWnd = GetForegroundWindow();

	//	デバッグウィンドウを表示する
	AllocConsole();

	//	文字列の出力
	freopen_s(&_debugFp,"CONOUT$","w",stdout);
	//	文字列の入力
	freopen_s(&_debugFp,"CONIN$", "r", stdin);


	////	ゲームのウィンドウをデバッグウィンドウより前に表示する
	SetForegroundWindow(hWnd);
}


_DebugConOut::~_DebugConOut()
{
	FreeConsole();
}


#endif // _DEBUG