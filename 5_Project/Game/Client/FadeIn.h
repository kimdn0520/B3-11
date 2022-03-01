#pragma once
#include "MonoBehaviour.h"

class Panel;

/// <summary>
/// Fade In 이 되면서 씬을 전환하기위한 스크립트 입니다.
/// </summary>
class FadeIn : public MonoBehaviour
{
public:
	FadeIn(GameObject* gameObject);
	~FadeIn();

private:
	Panel* _panel;

	string _loadScene;

private:
	virtual void FinalUpdate() override;

public:
	void SetLoadSceneName(string loadSceneName) { _loadScene = loadSceneName; }
};

