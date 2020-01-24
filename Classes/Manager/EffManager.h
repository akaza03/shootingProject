#pragma once
#include <memory>
#include <cocos2d.h>
#include <Effekseer/Effekseer.h>

#define lpEffectManager EffManager::GetInstance()

using EffectList = std::map < std::string, efk::Effect* >;

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
	void update(cocos2d::Camera* camera);

	//	�G�t�F�N�g�t�@�C���̃p�X,���C���[��,�J�����}�X�N��ǉ����邩�ǂ���,���W,�傫��,�ǉ����ɍĐ����J�n���邩�ǂ���
	void SetEffect(const char* pass, const char* layer, bool mask, cocos2d::Vec2 pos,int scale, bool playEnter);
private:
	EffManager();
	static EffManager* s_Instance;

	void EffectListInit();

	std::unique_ptr<efk::EffectManager> effectMng;
	void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags)
	{
		effectMng->begin(renderer, _globalZOrder);
		cocos2d::Scene::visit(renderer, parentTransform, parentFlags);
		effectMng->end(renderer, _globalZOrder);
	}

	EffectList effectList;
};

