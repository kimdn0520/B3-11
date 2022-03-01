#include "pch.h"
#include "FadeOut.h"
#include "GameObject.h"
#include "Panel.h"
#include "Sprite.h"

FadeOut::FadeOut(GameObject* gameObject)
	: MonoBehaviour(gameObject),
	_panel(gameObject->GetComponent<Panel>())
{}

FadeOut::~FadeOut()
{}

void FadeOut::FinalUpdate()
{
	_panel->GetSprite()->opacity -= 0.01f;

	if (_panel->GetSprite()->opacity <= 0.f)
	{
		this->GetGameObject()->SetActive(false);
		//SCENE_MANAGER->SetActiveFalseGameObject(this->GetGameObject());
		//Destroy(this->GetGameObject());
	}
}
