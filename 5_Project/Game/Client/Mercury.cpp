#include "pch.h"
#include "Mercury.h"
#include "Input.h"
#include "Timer.h"
#include "GameObject.h"
#include "Transform.h"

Mercury::Mercury(GameObject* gameObject)
	: MonoBehaviour(gameObject)
{
	_transform = gameObject->GetComponent<Transform>();
}

Mercury::~Mercury()
{

}

void Mercury::Update()
{
	/*_transform->Rotate(_rotateSpeed * DELTA_TIME);
	_transform->RotateArounds(_player, _rotateAroundSpeed * DELTA_TIME, 140.f);*/
}
