#pragma once
#include "Scene.h"

/// <summary>
/// 최소한의 게임 진행을 위한 
/// 캐릭터 점프와 대시, 공격을 구현하는 씬
/// 
/// 2022.02.08
/// </summary>

class GameObject;

class TutorialScene : public Scene
{
public:
	virtual void Init() override;
};

