#include "pch.h"
#include "Component.h"

Component::Component(GameObject* gameObject, COMPONENT_TYPE type) : _gameObject(gameObject), _type(type)
{	
}

Component::~Component()
{}

void Component::SetActive(bool _value)
{

}

