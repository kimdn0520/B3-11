#include "pch.h"
#include "JW2DEngine.h"
#include "Text.h"
#include "GameObject.h"
#include "Transform.h"

Text::Text(GameObject* gameObject)
	: Component(gameObject, COMPONENT_TYPE::TEXT),
	  text(""), _width(700), _height(40), _rotation(30), stride{}
{
	_transform = gameObject->GetComponent<Transform>();
	_textTransform = new Transform(nullptr);
}

Text::~Text()
{}

void Text::FinalUpdate()
{
	_textTransform->SetLocalPosition(_transform->GetLocalPosition());
	GEngine->SetTransform(_textTransform->GetWorldMatrix());

	// ���⼭ string -> const char* �� ��ȯ�ؼ� �־��ִ°ɷ� �Ͽ���..!
	const char* transText = text.c_str();

	GEngine->DrawTextScreen(stride.x, stride.y,
		_width, _height, _rotation, transText);
}
