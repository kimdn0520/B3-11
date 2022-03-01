#pragma once
#include "MonoBehaviour.h"

class Panel;

/// <summary>
/// Fade In �� �Ǹ鼭 ���� ��ȯ�ϱ����� ��ũ��Ʈ �Դϴ�.
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

