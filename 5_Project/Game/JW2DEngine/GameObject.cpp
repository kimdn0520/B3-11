#include "pch.h"
#include "JW2DEngine.h"
#include "GameObject.h"
#include "Transform.h"
#include "MonoBehaviour.h"
#include "ColliderBase.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "OBBCollider.h"
#include "Scene.h"
#include "Rigidbody.h"

map<int, vector<int>> GameObject::_notAffectTag;

bool cmp(const pair<int, Info*>& a, const pair<int, Info*>& b)
{
	return a.second->compNum > b.second->compNum;
}

GameObject::GameObject(TAG tag)//ajw 바꾼 곳
	:_tag((int)tag), _script(nullptr)
{
	GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(this);//ajw 바꾼 곳
	for (int i = 0; i < _components.size(); i++)
		_components[i] = nullptr;
}

GameObject::~GameObject()
{}

void GameObject::SetActive(bool value)
{
	_isEnable = value;
}

void GameObject::SetNotColTag(string name)
{
	_notColTagList.push_back(name);
}

void GameObject::Awake()
{
	// 게임오브젝트에 달려있는 컴포넌트들을 초기화 한다.
	for (auto component : _components)
	{
		if (component != nullptr)
			component->Awake();
	}

	// 게임오브젝트에 달려있는 스크립트를 초기화 한다.
	if (_script != nullptr && _isEnable)
		_script->Awake();
}

void GameObject::PreProcess()
{
	if (_script != nullptr && _isEnable)
		_script->PreProcess();
}

void GameObject::FixedUpdate()
{	
	if(_tag == (int)TAG::SPRITE)
		return;

	if (_tag == (int)TAG::Bullet)
	{
		this;
		int a = 10;
	}

	//// 리지드 바디 먼저..?
	//if(_components[(int)COMPONENT_TYPE::RIGIDBODY] != nullptr)
	//	_components[(int)COMPONENT_TYPE::RIGIDBODY]->FixedUpdate();
	
	if (_isCameraView || _tag == (int)TAG::Bullet || _tag == (int)TAG::MovableGround || _tag == (int)TAG::Hurdle || _tag == (int)TAG::Enemy || _tag == (int)TAG::PassHurdle)
	{
		CircleCollider* circleCollider = dynamic_cast<CircleCollider*>(_components[(int)COMPONENT_TYPE::CIRCLE_COLLIDER]);

		bool isAffect = false;

		// 내가 써클 콜라이더를 들고있다면..
		if (circleCollider != nullptr)
		{
			// 모든 게임오브젝트들과 비교
			for (auto gameObjects : SCENE_MANAGER->GetActiveScene()->GetGameObjects())
			{	
				// 내가 아닌 게임오브젝트들 + (enable = true) 상태라면
				if (gameObjects != this && gameObjects->GetEnable())
				{
					/*for (int tag : _notAffectTag[_tag])
					{
						if (gameObjects->GetTag() == tag)
							isAffect = true;
					}

					if (isAffect)
					{
						isAffect = false;
						continue;
					}*/
					// ColliderBase* collider = gameObjects->GetComponent<ColliderBase>();

					/*if (collider == nullptr)
						continue*/;

					//CircleCollider* otherCircleCollider = dynamic_cast<CircleCollider*>(collider);
					
					CircleCollider* otherCircleCollider = dynamic_cast<CircleCollider*>(gameObjects->_components[(int)COMPONENT_TYPE::CIRCLE_COLLIDER]);
					
					// 그 other오브젝트가 써클 콜라이더를 들고있다면
					if (otherCircleCollider != nullptr)
					{
						// 이전에 그 other오브젝트가 충돌했냐 안했냐는 정보를 얻어온다.
						bool isPreCollision = circleCollider->GetOtherColliderInfo(otherCircleCollider);
					
						// 그리고 지금 충돌 했는지 안했는지 
						circleCollider->SetCollision(circleCollider->CheckCollision(otherCircleCollider));

						// 지금 other오브젝트가 충돌했으면 상태를 바꿔준다.
						circleCollider->SetOtherColliderInfo(otherCircleCollider, circleCollider->GetIsOnCollision());
					
						// 내가 트리거가 아니고 충돌한녀석이 트리거가 아니였다면
						if (circleCollider->GetTrigger() == false && otherCircleCollider->GetTrigger() == false && circleCollider->GetGameObject()->GetScript())
						{
							if (isPreCollision == false && circleCollider->GetIsOnCollision() == true)
								circleCollider->GetGameObject()->GetScript()->OnCollisionEnter(otherCircleCollider);
							else if (isPreCollision == true && circleCollider->GetIsOnCollision() == true)
								circleCollider->GetGameObject()->GetScript()->OnCollisionStay(otherCircleCollider);
							else if (isPreCollision == true && circleCollider->GetIsOnCollision() == false)
								circleCollider->GetGameObject()->GetScript()->OnCollisionExit(otherCircleCollider);
						}
						// 그 이외는 다 트리거 작용!
						else
						{
							if (circleCollider->GetGameObject()->GetScript())
							{
								if (isPreCollision == false && circleCollider->GetIsOnCollision() == true)
									circleCollider->GetGameObject()->GetScript()->OnTriggerEnter(otherCircleCollider);
								else if (isPreCollision == true && circleCollider->GetIsOnCollision() == true)
									circleCollider->GetGameObject()->GetScript()->OnTriggerStay(otherCircleCollider);
								else if (isPreCollision == true && circleCollider->GetIsOnCollision() == false)
									circleCollider->GetGameObject()->GetScript()->OnTriggerExit(otherCircleCollider);
							}
						}
					}

					// BoxCollider* otherBoxCollider = dynamic_cast<BoxCollider*>(collider);
					BoxCollider* otherBoxCollider = dynamic_cast<BoxCollider*>(gameObjects->_components[(int)COMPONENT_TYPE::BOX_COLLIDER]);

					// 그 other오브젝트가 박스 콜라이더를 들고있다면
					if (otherBoxCollider != nullptr)
					{
						// 이전에 그 other오브젝트가 충돌했냐 안했냐는 정보를 얻어온다.
						bool isPreCollision = circleCollider->GetOtherColliderInfo(otherBoxCollider);

						// 그리고 지금 충돌 했는지 안했는지 
						circleCollider->SetCollision(circleCollider->CheckCollision(otherBoxCollider));

						// 지금 other오브젝트가 충돌했으면 상태를 바꿔준다.
						circleCollider->SetOtherColliderInfo(otherBoxCollider, circleCollider->GetIsOnCollision());

						// 내가 트리거가 아니고 충돌한녀석이 트리거가 아니였다면
						if (circleCollider->GetTrigger() == false && otherBoxCollider->GetTrigger() == false && circleCollider->GetGameObject()->GetScript())
						{
							if (isPreCollision == false && circleCollider->GetIsOnCollision() == true)
								circleCollider->GetGameObject()->GetScript()->OnCollisionEnter(otherBoxCollider);
							else if (isPreCollision == true && circleCollider->GetIsOnCollision() == true)
								circleCollider->GetGameObject()->GetScript()->OnCollisionStay(otherBoxCollider);
							else if (isPreCollision == true && circleCollider->GetIsOnCollision() == false)
								circleCollider->GetGameObject()->GetScript()->OnCollisionExit(otherBoxCollider);
						}
						// 그 이외는 다 트리거 작용!
						else 
						{
							if(circleCollider->GetGameObject()->GetScript())
							{ 
								if (isPreCollision == false && circleCollider->GetIsOnCollision() == true)
									circleCollider->GetGameObject()->GetScript()->OnTriggerEnter(otherBoxCollider);
								else if (isPreCollision == true && circleCollider->GetIsOnCollision() == true)
									circleCollider->GetGameObject()->GetScript()->OnTriggerStay(otherBoxCollider);
								else if (isPreCollision == true && circleCollider->GetIsOnCollision() == false)
									circleCollider->GetGameObject()->GetScript()->OnTriggerExit(otherBoxCollider);
							}
						}
					}
				}
				// 부딪힌 게임오브젝트가 꺼져있으면 그 부딪힌 게임오브젝트의 콜라이더 정보를 false로 바꿔주는 작업.
				else if (gameObjects != this && !gameObjects->GetEnable())
				{
					ColliderBase* collider = gameObjects->GetComponent<ColliderBase>();

					if (collider == nullptr)
						continue;

					CircleCollider* otherCircleCollider = dynamic_cast<CircleCollider*>(collider);

					// 그 other오브젝트가 써클 콜라이더를 들고있다면
					if (otherCircleCollider != nullptr)
					{
						circleCollider->SetOtherColliderInfo(otherCircleCollider, false);
					}

					BoxCollider* otherBoxCollider = dynamic_cast<BoxCollider*>(collider);

					// 그 other오브젝트가 박스 콜라이더를 들고있다면
					if (otherBoxCollider != nullptr)
					{
						circleCollider->SetOtherColliderInfo(otherBoxCollider, false);
					}
				}
			}
		}

		BoxCollider* boxCollider = dynamic_cast<BoxCollider*>(_components[(int)COMPONENT_TYPE::BOX_COLLIDER]);
		// BoxCollider* boxCollider = dynamic_cast<BoxCollider*>(collider);

		// 내가 박스 콜라이더를 들고있다면..
		if (boxCollider != nullptr)
		{
			boxCollider->ResetColDirVec();

			for (auto gameObjects : SCENE_MANAGER->GetActiveScene()->GetGameObjects())
			{
				// 내가 아닌 게임오브젝트들 + (enable = true) 상태라면
				if (gameObjects != this && gameObjects->GetEnable())
				{
					/*for (int tag : _notAffectTag[_tag])
					{
						if (gameObjects->GetTag() == tag)
							isAffect = true;
					}

					if (isAffect)
					{
						isAffect = false;
						continue;
					}*/

					BoxCollider* otherBoxCollider = dynamic_cast<BoxCollider*>(gameObjects->_components[(int)COMPONENT_TYPE::BOX_COLLIDER]);

					// 그 other오브젝트가 박스 콜라이더를 들고있다면
					if (otherBoxCollider != nullptr)
					{
						// 이전에 그 other오브젝트가 충돌했냐 안했냐는 정보를 얻어온다.
						bool isPreCollision = boxCollider->GetOtherColliderInfo(otherBoxCollider);

						// 그리고 지금 충돌 했는지 안했는지 
						boxCollider->SetCollision(boxCollider->CheckCollision(otherBoxCollider));

						// 체크된애(강체 vs 아닌거) 일때는 이벤트 안하고 넘어간다. 이따가 한다.
						if (boxCollider->GetIsCheck())
						{
							boxCollider->SetIsCheck(false);
							continue;
						}
						
						// 지금 other오브젝트가 충돌했으면 상태를 바꿔준다.
						boxCollider->SetOtherColliderInfo(otherBoxCollider, boxCollider->GetIsOnCollision());

						// 내가 트리거가 아니고 충돌한녀석이 트리거가 아니였다면
						if (boxCollider->GetTrigger() == false && otherBoxCollider->GetTrigger() == false && boxCollider->GetGameObject()->GetScript())
						{
							if (isPreCollision == false && boxCollider->GetIsOnCollision() == true)
								boxCollider->GetGameObject()->GetScript()->OnCollisionEnter(otherBoxCollider);
							else if (isPreCollision == true && boxCollider->GetIsOnCollision() == true)
								boxCollider->GetGameObject()->GetScript()->OnCollisionStay(otherBoxCollider);
							else if (isPreCollision == true && boxCollider->GetIsOnCollision() == false)
								boxCollider->GetGameObject()->GetScript()->OnCollisionExit(otherBoxCollider);
						}
						// 그 이외는 다 트리거 작용!	
						else 
						{
							if(boxCollider->GetGameObject()->GetScript())
							{ 
								if (isPreCollision == false && boxCollider->GetIsOnCollision() == true)
									boxCollider->GetGameObject()->GetScript()->OnTriggerEnter(otherBoxCollider);
								else if (isPreCollision == true && boxCollider->GetIsOnCollision() == true)
									boxCollider->GetGameObject()->GetScript()->OnTriggerStay(otherBoxCollider);
								else if (isPreCollision == true && boxCollider->GetIsOnCollision() == false)
									boxCollider->GetGameObject()->GetScript()->OnTriggerExit(otherBoxCollider);
							}
						}
					}

					//CircleCollider* otherCircleCollider = dynamic_cast<CircleCollider*>(collider);
					CircleCollider* otherCircleCollider = dynamic_cast<CircleCollider*>(gameObjects->_components[(int)COMPONENT_TYPE::CIRCLE_COLLIDER]);
					
					if (otherCircleCollider != nullptr)
					{
						// 이전에 그 other오브젝트가 충돌했냐 안했냐는 정보를 얻어온다.
						bool isPreCollision = boxCollider->GetOtherColliderInfo(otherCircleCollider);

						// 그리고 지금 충돌 했는지 안했는지 
						boxCollider->SetCollision(boxCollider->CheckCollision(otherCircleCollider));

						// 지금 other오브젝트가 충돌했으면 상태를 바꿔준다.
						boxCollider->SetOtherColliderInfo(otherCircleCollider, boxCollider->GetIsOnCollision());

						// 내가 트리거가 아니고 충돌한녀석이 트리거가 아니였다면
						if (boxCollider->GetTrigger() == false && otherCircleCollider->GetTrigger() == false && boxCollider->GetGameObject()->GetScript())
						{
							if (isPreCollision == false && boxCollider->GetIsOnCollision() == true)
								boxCollider->GetGameObject()->GetScript()->OnCollisionEnter(otherCircleCollider);
							else if (isPreCollision == true && boxCollider->GetIsOnCollision() == true)
								boxCollider->GetGameObject()->GetScript()->OnCollisionStay(otherCircleCollider);
							else if (isPreCollision == true && boxCollider->GetIsOnCollision() == false)
								boxCollider->GetGameObject()->GetScript()->OnCollisionExit(otherCircleCollider);
						}
						// 그 이외는 다 트리거 작용!
						else
						{
							if (boxCollider->GetGameObject()->GetScript())
							{
								if (isPreCollision == false && boxCollider->GetIsOnCollision() == true)
									boxCollider->GetGameObject()->GetScript()->OnTriggerEnter(otherCircleCollider);
								else if (isPreCollision == true && boxCollider->GetIsOnCollision() == true)
									boxCollider->GetGameObject()->GetScript()->OnTriggerStay(otherCircleCollider);
								else if (isPreCollision == true && boxCollider->GetIsOnCollision() == false)
									boxCollider->GetGameObject()->GetScript()->OnTriggerExit(otherCircleCollider);
							}
						}
					}

					// OBBCollider* otherOBBCollider = dynamic_cast<OBBCollider*>(collider);
					OBBCollider* otherOBBCollider = dynamic_cast<OBBCollider*>(gameObjects->_components[(int)COMPONENT_TYPE::OBB_COLLIDER]);

					if (otherOBBCollider != nullptr)
					{
						// 이전에 그 other오브젝트가 충돌했냐 안했냐는 정보를 얻어온다.
						bool isPreCollision = boxCollider->GetOtherColliderInfo(otherOBBCollider);

						// 그리고 지금 충돌 했는지 안했는지 
						boxCollider->SetCollision(boxCollider->CheckCollision(otherOBBCollider));

						// 지금 other오브젝트가 충돌했으면 상태를 바꿔준다.
						boxCollider->SetOtherColliderInfo(otherOBBCollider, boxCollider->GetIsOnCollision());

						// 내가 트리거가 아니고 충돌한녀석이 트리거가 아니였다면
						if (boxCollider->GetTrigger() == false && otherOBBCollider->GetTrigger() == false && boxCollider->GetGameObject()->GetScript())
						{
							if (isPreCollision == false && boxCollider->GetIsOnCollision() == true)
								boxCollider->GetGameObject()->GetScript()->OnCollisionEnter(otherOBBCollider);
							else if (isPreCollision == true && boxCollider->GetIsOnCollision() == true)
								boxCollider->GetGameObject()->GetScript()->OnCollisionStay(otherOBBCollider);
							else if (isPreCollision == true && boxCollider->GetIsOnCollision() == false)
								boxCollider->GetGameObject()->GetScript()->OnCollisionExit(otherOBBCollider);
						}
						// 그 이외는 다 트리거 작용!
						else
						{
							if (boxCollider->GetGameObject()->GetScript())
							{
								if (isPreCollision == false && boxCollider->GetIsOnCollision() == true)
									boxCollider->GetGameObject()->GetScript()->OnTriggerEnter(otherOBBCollider);
								else if (isPreCollision == true && boxCollider->GetIsOnCollision() == true)
									boxCollider->GetGameObject()->GetScript()->OnTriggerStay(otherOBBCollider);
								else if (isPreCollision == true && boxCollider->GetIsOnCollision() == false)
									boxCollider->GetGameObject()->GetScript()->OnTriggerExit(otherOBBCollider);
							}
						}
					}
				}
				// 부딪힌 게임오브젝트가 꺼져있으면 그 부딪힌 게임오브젝트의 콜라이더 정보를 false로 바꿔주는 작업.
				else if (gameObjects != this && !gameObjects->GetEnable())
				{
					ColliderBase* collider = gameObjects->GetComponent<ColliderBase>();

					if (collider == nullptr)
						continue;

					CircleCollider* otherCircleCollider = dynamic_cast<CircleCollider*>(collider);

					// 그 other오브젝트가 써클 콜라이더를 들고있다면
					if (otherCircleCollider != nullptr)
					{
						boxCollider->SetOtherColliderInfo(otherCircleCollider, false);
					}

					BoxCollider* otherBoxCollider = dynamic_cast<BoxCollider*>(collider);

					// 그 other오브젝트가 박스 콜라이더를 들고있다면
					if (otherBoxCollider != nullptr)
					{
						boxCollider->SetOtherColliderInfo(otherBoxCollider, false);
					}

					OBBCollider* otherOBBCollider = dynamic_cast<OBBCollider*>(collider);

					if (otherOBBCollider != nullptr)
					{
						boxCollider->SetOtherColliderInfo(otherOBBCollider, false);
					}
				}
			}
			/*rigidbody->SetVelocity(velocityVec);

			transform->SetLocalPosition(transform->GetLocalPosition() + reflectVec);*/
			if (boxCollider->_reflMap.size() != 0)
			{
				// 큰 값부터 밀어낼수있게 값으로 내림차순 정렬을 해준다..
				vector<pair<int, Info*>> vec(boxCollider->_reflMap.begin(), boxCollider->_reflMap.end());
				sort(vec.begin(), vec.end(), cmp);

				// 충돌이 어디까지 일어났는지 알아야한다.
				int colIndex = 0;
				
				// 겹치는곳이 2곳이상이면 x,y 속도 0으로
				if (vec.size() > 1)
				{
					for (int i = 0; i < vec.size(); i++)
					{
 						GetComponent<Rigidbody>()->SetVelocity(vec[i].second->velocityVec);
						GetComponent<Transform>()->SetLocalPosition(GetComponent<Transform>()->GetWorldPosition() + vec[i].second->reflectVec);
					
						boxCollider->Update();

						bool isCheck = false;

						for (int j = 0; j < vec.size(); j++)
						{
							// 밀어냈는데 또 겹치는 부분이있으면..
							if (boxCollider->CheckCollision(vec[j].second->otherCol))
							{
								isCheck = true;
								break;
							}
						}

						// 없으면..
						if (!isCheck)
						{
							boxCollider->SetColDir(vec[i].second->colDir);
							colIndex = i;
							break;
						}
					}

					for (int i = 0; i < vec.size(); i++)
					{
						boxCollider->SetColDirVec(vec[i].second->colDir);
					}
				}
				else
				{
					//this;
					GetComponent<Rigidbody>()->SetVelocity(vec[0].second->velocityVec);
					GetComponent<Transform>()->SetLocalPosition(GetComponent<Transform>()->GetWorldPosition() + vec[0].second->reflectVec);
					
					boxCollider->Update();
					boxCollider->SetColDir(vec[0].second->colDir);
					colIndex = 0;
					boxCollider->SetColDirVec(vec[0].second->colDir);
				}

				// 이전에 그 other오브젝트가 충돌했냐 안했냐는 정보를 얻어온다.
				bool isPreCollision = boxCollider->GetOtherColliderInfo(vec[colIndex].second->otherCol);

				// 그리고 지금 충돌 했는지 안했는지 
				//boxCollider->SetCollision(boxCollider->CheckCollision(vec[colIndex].second->otherCol));

				// 지금 other오브젝트가 충돌했으면 상태를 바꿔준다.
				boxCollider->SetOtherColliderInfo(vec[colIndex].second->otherCol, true);

				// 내가 트리거가 아니고 충돌한녀석이 트리거가 아니였다면
				if (boxCollider->GetGameObject()->GetScript())
				{
					if (isPreCollision == false)
						boxCollider->GetGameObject()->GetScript()->OnCollisionEnter(vec[colIndex].second->otherCol);
					else if (isPreCollision == true)
						boxCollider->GetGameObject()->GetScript()->OnCollisionStay(vec[colIndex].second->otherCol);
				}

				// GetComponent<Rigidbody>()->SetVelocity(vec[vec.size() - 1].second->velocityVec);

				/*for (auto iter = boxCollider->_reflMap.begin(); iter != boxCollider->_reflMap.end(); ++iter)
				{
					GetComponent<Rigidbody>()->SetVelocity(iter->second.second);
					GetComponent<Transform>()->SetLocalPosition(GetComponent<Transform>()->GetLocalPosition() + iter->second.first.first);
				}*/

				//boxCollider->SetColDir(vec[vec.size() - 1].first);
				boxCollider->SetIsCheck(false);
				boxCollider->_reflMap.clear();
				/*GetComponent<Rigidbody>()->SetVelocity(boxCollider->GetVelocityVec());
				GetComponent<Transform>()->SetLocalPosition(GetComponent<Transform>()->GetLocalPosition() + boxCollider->GetReflectVec());
				boxCollider->SetIsCheck(false);*/
			}
		}

		OBBCollider* obbCollider = dynamic_cast<OBBCollider*>(_components[(int)COMPONENT_TYPE::OBB_COLLIDER]);

		// 내가 obb 콜라이더를 들고있다면..
		if (obbCollider != nullptr)
		{
			for (auto gameObjects : SCENE_MANAGER->GetActiveScene()->GetGameObjects())
			{
				// 내가 아닌 게임오브젝트들 + (enable = true) 상태라면
				if (gameObjects != this && gameObjects->GetEnable())
				{
					/*for (int tag : _notAffectTag[_tag])
					{
						if (gameObjects->GetTag() == tag)
							isAffect = true;
					}

					if (isAffect)
					{
						isAffect = false;
						continue;
					}*/

					/*ColliderBase* collider = gameObjects->GetComponent<ColliderBase>();

					if (collider == nullptr)
						continue;

					BoxCollider* otherBoxCollider = dynamic_cast<BoxCollider*>(collider);*/
					
					BoxCollider* otherBoxCollider = dynamic_cast<BoxCollider*>(gameObjects->_components[(int)COMPONENT_TYPE::BOX_COLLIDER]);

					// 그 other오브젝트가 박스 콜라이더를 들고있다면
					if (otherBoxCollider != nullptr)
					{
						// 이전에 그 other오브젝트가 충돌했냐 안했냐는 정보를 얻어온다.
						bool isPreCollision = obbCollider->GetOtherColliderInfo(otherBoxCollider);

						// 그리고 지금 충돌 했는지 안했는지 
						obbCollider->SetCollision(obbCollider->CheckCollision(otherBoxCollider));

						// 지금 other오브젝트가 충돌했으면 상태를 바꿔준다.
						obbCollider->SetOtherColliderInfo(otherBoxCollider, obbCollider->GetIsOnCollision());

						// 내가 트리거가 아니고 충돌한녀석이 트리거가 아니였다면
						if (obbCollider->GetTrigger() == false && otherBoxCollider->GetTrigger() == false && obbCollider->GetGameObject()->GetScript())
						{
							if (isPreCollision == false && obbCollider->GetIsOnCollision() == true)
								obbCollider->GetGameObject()->GetScript()->OnCollisionEnter(otherBoxCollider);
							else if (isPreCollision == true && obbCollider->GetIsOnCollision() == true)
								obbCollider->GetGameObject()->GetScript()->OnCollisionStay(otherBoxCollider);
							else if (isPreCollision == true && obbCollider->GetIsOnCollision() == false)
								obbCollider->GetGameObject()->GetScript()->OnCollisionExit(otherBoxCollider);
						}
						// 그 이외는 다 트리거 작용!
						else
						{
							if (obbCollider->GetGameObject()->GetScript())
							{
								if (isPreCollision == false && obbCollider->GetIsOnCollision() == true)
									obbCollider->GetGameObject()->GetScript()->OnTriggerEnter(otherBoxCollider);
								else if (isPreCollision == true && obbCollider->GetIsOnCollision() == true)
									obbCollider->GetGameObject()->GetScript()->OnTriggerStay(otherBoxCollider);
								else if (isPreCollision == true && obbCollider->GetIsOnCollision() == false)
									obbCollider->GetGameObject()->GetScript()->OnTriggerExit(otherBoxCollider);
							}
						}
					}

					// OBBCollider* otherOBBCollider = dynamic_cast<OBBCollider*>(collider);
					OBBCollider* otherOBBCollider = dynamic_cast<OBBCollider*>(gameObjects->_components[(int)COMPONENT_TYPE::OBB_COLLIDER]);

					if (otherOBBCollider != nullptr)
					{
						// 이전에 그 other오브젝트가 충돌했냐 안했냐는 정보를 얻어온다.
						bool isPreCollision = obbCollider->GetOtherColliderInfo(otherOBBCollider);

						// 그리고 지금 충돌 했는지 안했는지 
						obbCollider->SetCollision(obbCollider->CheckCollision(otherOBBCollider));

						// 지금 other오브젝트가 충돌했으면 상태를 바꿔준다.
						obbCollider->SetOtherColliderInfo(otherOBBCollider, obbCollider->GetIsOnCollision());

						// 내가 트리거가 아니고 충돌한녀석이 트리거가 아니였다면
						if (obbCollider->GetTrigger() == false && otherOBBCollider->GetTrigger() == false && obbCollider->GetGameObject()->GetScript())
						{
							if (isPreCollision == false && obbCollider->GetIsOnCollision() == true)
								obbCollider->GetGameObject()->GetScript()->OnCollisionEnter(otherOBBCollider);
							else if (isPreCollision == true && obbCollider->GetIsOnCollision() == true)
								obbCollider->GetGameObject()->GetScript()->OnCollisionStay(otherOBBCollider);
							else if (isPreCollision == true && obbCollider->GetIsOnCollision() == false)
								obbCollider->GetGameObject()->GetScript()->OnCollisionExit(otherOBBCollider);
						}
						// 그 이외는 다 트리거 작용!
						else
						{
							if (obbCollider->GetGameObject()->GetScript())
							{
								if (isPreCollision == false && obbCollider->GetIsOnCollision() == true)
									obbCollider->GetGameObject()->GetScript()->OnTriggerEnter(otherOBBCollider);
								else if (isPreCollision == true && obbCollider->GetIsOnCollision() == true)
									obbCollider->GetGameObject()->GetScript()->OnTriggerStay(otherOBBCollider);
								else if (isPreCollision == true && obbCollider->GetIsOnCollision() == false)
									obbCollider->GetGameObject()->GetScript()->OnTriggerExit(otherOBBCollider);
							}
						}
					}
				}
				// 부딪힌 게임오브젝트가 꺼져있으면 그 부딪힌 게임오브젝트의 콜라이더 정보를 false로 바꿔주는 작업.
				else if (gameObjects != this && !gameObjects->GetEnable())
				{
					ColliderBase* collider = gameObjects->GetComponent<ColliderBase>();

					if (collider == nullptr)
						continue;

					OBBCollider* otherOBBCollider = dynamic_cast<OBBCollider*>(collider);

					// 그 other오브젝트가 obb 콜라이더를 들고있다면
					if (otherOBBCollider != nullptr)
					{
						obbCollider->SetOtherColliderInfo(otherOBBCollider, false);
					}

					BoxCollider* otherBoxCollider = dynamic_cast<BoxCollider*>(collider);

					// 그 other오브젝트가 박스 콜라이더를 들고있다면
					if (otherBoxCollider != nullptr)
					{
						obbCollider->SetOtherColliderInfo(otherBoxCollider, false);
					}
				}
			}
		}
	}

	// 게임오브젝트에 달려있는 스크립트를 업데이트 한다.
	if (_script != nullptr && _isEnable)
		_script->FixedUpdate();
}

void GameObject::Update()
{
	if (_tag == (int)TAG::SPRITE)
		return;


	if (_isCameraView || _tag == (int)TAG::Bullet || _tag == (int)TAG::MovableGround || _tag == (int)TAG::Hurdle || _tag == (int)TAG::PassHurdle)
	{

		if (_tag == (int)TAG::Bullet)
		{
			int a = 10;
		}

		// 게임오브젝트에 달려있는 스크립트를 업데이트 한다.
		if (_script != nullptr && _isEnable)
			_script->Update();
	
	
		// 게임오브젝트에 달려있는 컴포넌트들을 업데이트 한다.
		for (auto component : _components)
		{
			if(_isEnable && component != nullptr)
				component->Update();
		}
	}
}

void GameObject::LateUpdate()
{
	if (_tag == (int)TAG::SPRITE)
		return;

	if (_isCameraView || _tag == (int)TAG::Bullet || _tag == (int)TAG::MovableGround || _tag == (int)TAG::Hurdle || _tag == (int)TAG::Enemy || _tag == (int)TAG::PassHurdle)
	{
		// 게임오브젝트에 달려있는 스크립트들을 업데이트 한다.
		if (_script != nullptr && _isEnable)
			_script->LateUpdate();

		// 게임오브젝트에 달려있는 컴포넌트들을 업데이트 한다.
		for (auto component : _components)
		{
			if (_isEnable && component != nullptr)
				component->LateUpdate();
		}
	}
}


/// <summary>
/// 마지막에 렌더해주는 업데이트 이다.
/// </summary>
void GameObject::FinalUpdate()
{
this;
	if(_isCameraView || _tag == (int)TAG::Bullet || _tag == (int)TAG::MovableGround || _tag == (int)TAG::Hurdle || _tag == (int)TAG::PassHurdle)
	{
		// 게임오브젝트에 달려있는 스크립트들을 업데이트 한다.
		if (_script != nullptr && _isEnable)
			_script->FinalUpdate();

		// 게임오브젝트에 달려있는 컴포넌트들을 업데이트 한다.
		for (auto component : _components)
		{
			if (_isEnable && component != nullptr)
			{ 
				component->SetDrawCol(_isDrawCol);
				component->FinalUpdate();
			}
		}
	}
}

