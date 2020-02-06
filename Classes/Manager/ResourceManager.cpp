#include "ResourceManager.h"

ResourceManager *ResourceManager::s_Instance = nullptr;

ResourceManager::ResourceManager()
{
	LoadInit();
}

ResourceManager::~ResourceManager()
{
}
std::string ResourceManager::GetID(std::string key)
{
	if (resMap.find(key) == resMap.end())
	{
		return "null";
	}
	return resMap[key];
}

std::string ResourceManager::SetID(std::string key, std::string filePass)
{
	if (resMap.find(key) == resMap.end())
	{
		resMap[key] = filePass;
	}
	return resMap[key];
}

void ResourceManager::LoadInit()
{
	//	タイトル画像
	SetID("logo", "image/logo.png");
	SetID("GameStart", "image/UI/GameStart.png");
	SetID("GameClear", "image/UI/GameClear.png");
	SetID("GameOver", "image/UI/GameOver.png");
	SetID("credit", "image/UI/credit.png");

	//	ユニット画像
	SetID("p0unit", "image/player/00-unit.png");
	SetID("p1unit", "image/player/01-unit.png");
	SetID("p2unit", "image/player/02-unit.png");
	SetID("e0unit", "image/enemy/00-unit.png");
	SetID("e1unit", "image/enemy/01-unit.png");
	SetID("e2unit", "image/enemy/02-unit.png");
	SetID("e3unit", "image/enemy/03-unit.png");
	//	立ち絵
	SetID("p0stand", "image/player/00-stand.png");
	SetID("p1stand", "image/player/01-stand.png");
	SetID("p2stand", "image/player/02-stand.png");
	//	顔画像
	SetID("p0face", "image/player/00-face.png");
	SetID("p1face", "image/player/01-face.png");
	SetID("p2face", "image/player/02-face.png");
	//	アイコン画像
	SetID("p0icon", "image/player/00-icon.png");
	SetID("p1icon", "image/player/01-icon.png");
	SetID("p2icon", "image/player/02-icon.png");
	//	弾画像
	SetID("p0Shot", "image/Sprites/Fx/power-up/power-up-1.png");
	SetID("p1Shot", "image/Sprites/Fx/shot/shot-1.png");
	SetID("p2Shot", "image/Sprites/Fx/impact/impact-1.png");
	//	背景
	SetID("BackG01", "image/iseki.jpg");
	SetID("Title", "image/title(kari).png");
	//	HPバー
	SetID("HPBase", "image/UI/hpBarBase.png");
	SetID("HP", "image/UI/hpBar.png");
	SetID("ReMain", "image/UI/remaining.png");

	//	エフェクト
	SetID("changeEff", "effect/Laser01.efk");
	SetID("hitEff", "effect/hit.efk");
	SetID("deathEff", "effect/death.efk");
}