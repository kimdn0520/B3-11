#include "pch.h"
#include "ColliderBase.h"
#include "GameObject.h"
#include "Transform.h"
#include "Rigidbody.h"

ColliderBase::ColliderBase(GameObject* gameObject)
	: Component(gameObject, COMPONENT_TYPE::BOX_COLLIDER),
	  _isTrigger(false)
{
	  transform = gameObject->GetComponent<Transform>();
	  rigidbody = gameObject->GetComponent<Rigidbody>();
	  position = transform->GetWorldPosition();
	  _isCollision = false;
}

ColliderBase::~ColliderBase()
{}

bool ColliderBase::CompareTag(TAG tag)
{
	if(GetGameObject()->GetTag() == (int)tag)
		return true;

	return false;
}

void ColliderBase::SetCollision(bool value)
{
	if (value == _isCollision)
		return;

	_isCollision = value;
}

bool ColliderBase::GetOtherColliderInfo(ColliderBase* col)
{
	bool result = _otherColliderInfo[col];

	return result;
}

void ColliderBase::SetOtherColliderInfo(ColliderBase* col, bool value)
{
	_otherColliderInfo[col] = value;
}

void ColliderBase::ResetCollsionInfo()
{
	for (auto it = _otherColliderInfo.begin(); it != _otherColliderInfo.end(); ++it)
	{
		it->second = false;
	}

	_isCollision = false;
}
