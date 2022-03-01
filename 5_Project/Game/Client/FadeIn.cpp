#include "pch.h"
#include "FadeIn.h"
#include "GameObject.h"
#include "Panel.h"
#include "Sprite.h"

FadeIn::FadeIn(GameObject* gameObject)
	: MonoBehaviour(gameObject),
	_panel(gameObject->GetComponent<Panel>())
{}

FadeIn::~FadeIn()
{}

void FadeIn::FinalUpdate()
{
	_panel->GetSprite()->opacity += 0.01f;

	if (_panel->GetSprite()->opacity >= 1.f)
	{	
		SCENE_MANAGER->SetIsReservedTimeControl(false);
		SCENE_MANAGER->LoadScene(_loadScene);
		// Destroy(this->GetGameObject());
	}
}
