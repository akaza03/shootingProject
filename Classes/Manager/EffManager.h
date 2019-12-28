#pragma once
#include <memory>
#include <cocos2d.h>
#include <Effekseer/Effekseer.h>

#define lpEffectManager EffManager::GetInstance()

class EffManager : public cocos2d::Scene
{
public:
	static EffManager& GetInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new EffManager();
		}
		return *s_Instance;
	}

	~EffManager();
	void update();

	//	�G�t�F�N�g�t�@�C���̃p�X,���C���[��,���W,�傫��,�ǉ����ɍĐ����J�n���邩�ǂ���
	void SetEffect(const char* pass, const char* layer, cocos2d::Vec2 pos,int scale, bool playEnter);
private:
	EffManager();
	static EffManager* s_Instance;

	std::unique_ptr<efk::EffectManager> effectMng;
	void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags)
	{
		effectMng->begin(renderer, _globalZOrder);
		cocos2d::Scene::visit(renderer, parentTransform, parentFlags);
		effectMng->end(renderer, _globalZOrder);
	}
};
