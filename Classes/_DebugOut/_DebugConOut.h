#pragma once
#ifdef _DEBUG
#include <Windows.h>
#include <memory>

//	デバッグメッセージ用
//	「...」で任意の数(可変)にでき、「__VA_ARGS__」でばらす
#define TRACE(fmt, ...) printf(fmt, __VA_ARGS__)


#define AST() {\
	CHAR ast_mes[256];\
	wsprintf(ast_mes, "%s %d行目\0", __FILE__, __LINE__);\
	MessageBox(0, ast_mes, "ｱｻｰﾄ表示", MB_OK);\
	}


class _DebugConOut
{
public:
	static _DebugConOut& GetInstance()
	{
		return *s_Instance;
	}

private:
	struct _DebugConOutDeleter
	{
		void operator()(_DebugConOut* _debugConOut)const
		{
			delete _debugConOut;
		}
	};

	_DebugConOut();
	~_DebugConOut();

	FILE* _debugFp = nullptr;

	static std::unique_ptr<_DebugConOut,_DebugConOutDeleter> s_Instance;
};

#else

#define TRACE(fmt, ...)
#define AST()

#endif // _DEBUG