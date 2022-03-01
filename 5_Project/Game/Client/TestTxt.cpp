#include "pch.h"
#include "TestTxt.h"
#include "Text.h"
#include "GameObject.h"

TestTxt::TestTxt(GameObject* gameObject)
	: MonoBehaviour(gameObject)
{
	 txt = gameObject->GetComponent<Text>();
	 txt->SetWidth(700);
	 txt->SetHeight(40);
}

TestTxt::~TestTxt()
{}

void TestTxt::Update()
{
	//txt->text = "[이동] ←→ [점프] SpaceBar";
}


