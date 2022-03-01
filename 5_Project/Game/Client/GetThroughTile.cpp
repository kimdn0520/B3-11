#include "pch.h"
#include "GameObject.h"
#include "GetThroughTile.h"
#include "Transform.h"
#include "ColliderBase.h"
#include "BoxCollider.h"
#include "B3_11.h"

GetThroughTile::GetThroughTile(GameObject* gameObject)
	:MonoBehaviour(gameObject), _gameObject(gameObject), _boxCollider(_gameObject->GetComponent<BoxCollider>())
{
	_boxCollider->SetTrigger(true);
}

GetThroughTile::~GetThroughTile()
{
}


void GetThroughTile::OnCollisionExit(ColliderBase* col)
{
	_gameObject->GetComponent<BoxCollider>()->SetTrigger(true);
}

void GetThroughTile::OnTriggerEnter(ColliderBase* col)
{
	//col->
	if (col->GetGameObject()->GetName() == "Player")
	{
		BoxCollider* playerBox = col->GetGameObject()->GetComponent<BoxCollider>();
		int this_x1 = (_boxCollider->GetPosition().x - (_boxCollider->GetWidth() / 2.0f));
		int this_x2 = (_boxCollider->GetPosition().x + (_boxCollider->GetWidth() / 2.0f));
		int this_y1 = (_boxCollider->GetPosition().y - (_boxCollider->GetHeight() / 2.0f));
		int this_y2 = (_boxCollider->GetPosition().y + (_boxCollider->GetHeight() / 2.0f));

		int other_x1 = (playerBox->GetPosition().x - (playerBox->GetWidth() / 2.0f));
		int other_x2 = (playerBox->GetPosition().x + (playerBox->GetWidth() / 2.0f));
		int other_y1 = (playerBox->GetPosition().y - (playerBox->GetHeight() / 2.0f));
		int other_y2 = (playerBox->GetPosition().y + (playerBox->GetHeight() / 2.0f));

		int minDiff = INT_MAX;
		int rightDiff = abs(this_x2 - other_x1);
		int leftDiff = abs(this_x1 - other_x2);
		int upDiff = abs(this_y1 - other_y2);
		int downDiff = abs(this_y2 - other_y1);

		minDiff = minDiff < rightDiff ? minDiff : rightDiff;
		minDiff = minDiff < leftDiff ? minDiff : leftDiff;
		minDiff = minDiff < downDiff ? minDiff : downDiff;
		minDiff = minDiff < upDiff ? minDiff : upDiff;

		if(minDiff == upDiff)
			_gameObject->GetComponent<BoxCollider>()->SetTrigger(false);
	}

	/*
	int rightDiff = abs(this_x2 - other_x1);
	int leftDiff = abs(this_x1 - other_x2);
	int upDiff = abs(this_y1 - other_y2);
	int downDiff = abs(this_y2 - other_y1);

			if (minDiff == downDiff)
				*col_direction = Down;
			else if (minDiff == rightDiff)
				*col_direction = Right;
			else if (minDiff == leftDiff)
				*col_direction = Left;
			else if (minDiff == upDiff)
				*col_direction = Up;*/

				/*if (col->GetGameObject()->GetName() == "Player" && col->GetColDir())
					col->GetGameObject()->GetScriptComponent<B3_11>()->_bCheckGround = true;*/

}

