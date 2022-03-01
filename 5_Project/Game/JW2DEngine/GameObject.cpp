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

GameObject::GameObject(TAG tag)//ajw �ٲ� ��
	:_tag((int)tag), _script(nullptr)
{
	GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(this);//ajw �ٲ� ��
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
	// ���ӿ�����Ʈ�� �޷��ִ� ������Ʈ���� �ʱ�ȭ �Ѵ�.
	for (auto component : _components)
	{
		if (component != nullptr)
			component->Awake();
	}

	// ���ӿ�����Ʈ�� �޷��ִ� ��ũ��Ʈ�� �ʱ�ȭ �Ѵ�.
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

	//// ������ �ٵ� ����..?
	//if(_components[(int)COMPONENT_TYPE::RIGIDBODY] != nullptr)
	//	_components[(int)COMPONENT_TYPE::RIGIDBODY]->FixedUpdate();
	
	if (_isCameraView || _tag == (int)TAG::Bullet || _tag == (int)TAG::MovableGround || _tag == (int)TAG::Hurdle || _tag == (int)TAG::Enemy || _tag == (int)TAG::PassHurdle)
	{
		CircleCollider* circleCollider = dynamic_cast<CircleCollider*>(_components[(int)COMPONENT_TYPE::CIRCLE_COLLIDER]);

		bool isAffect = false;

		// ���� ��Ŭ �ݶ��̴��� ����ִٸ�..
		if (circleCollider != nullptr)
		{
			// ��� ���ӿ�����Ʈ��� ��
			for (auto gameObjects : SCENE_MANAGER->GetActiveScene()->GetGameObjects())
			{	
				// ���� �ƴ� ���ӿ�����Ʈ�� + (enable = true) ���¶��
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
					
					// �� other������Ʈ�� ��Ŭ �ݶ��̴��� ����ִٸ�
					if (otherCircleCollider != nullptr)
					{
						// ������ �� other������Ʈ�� �浹�߳� ���߳Ĵ� ������ ���´�.
						bool isPreCollision = circleCollider->GetOtherColliderInfo(otherCircleCollider);
					
						// �׸��� ���� �浹 �ߴ��� ���ߴ��� 
						circleCollider->SetCollision(circleCollider->CheckCollision(otherCircleCollider));

						// ���� other������Ʈ�� �浹������ ���¸� �ٲ��ش�.
						circleCollider->SetOtherColliderInfo(otherCircleCollider, circleCollider->GetIsOnCollision());
					
						// ���� Ʈ���Ű� �ƴϰ� �浹�ѳ༮�� Ʈ���Ű� �ƴϿ��ٸ�
						if (circleCollider->GetTrigger() == false && otherCircleCollider->GetTrigger() == false && circleCollider->GetGameObject()->GetScript())
						{
							if (isPreCollision == false && circleCollider->GetIsOnCollision() == true)
								circleCollider->GetGameObject()->GetScript()->OnCollisionEnter(otherCircleCollider);
							else if (isPreCollision == true && circleCollider->GetIsOnCollision() == true)
								circleCollider->GetGameObject()->GetScript()->OnCollisionStay(otherCircleCollider);
							else if (isPreCollision == true && circleCollider->GetIsOnCollision() == false)
								circleCollider->GetGameObject()->GetScript()->OnCollisionExit(otherCircleCollider);
						}
						// �� �ܴ̿� �� Ʈ���� �ۿ�!
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

					// �� other������Ʈ�� �ڽ� �ݶ��̴��� ����ִٸ�
					if (otherBoxCollider != nullptr)
					{
						// ������ �� other������Ʈ�� �浹�߳� ���߳Ĵ� ������ ���´�.
						bool isPreCollision = circleCollider->GetOtherColliderInfo(otherBoxCollider);

						// �׸��� ���� �浹 �ߴ��� ���ߴ��� 
						circleCollider->SetCollision(circleCollider->CheckCollision(otherBoxCollider));

						// ���� other������Ʈ�� �浹������ ���¸� �ٲ��ش�.
						circleCollider->SetOtherColliderInfo(otherBoxCollider, circleCollider->GetIsOnCollision());

						// ���� Ʈ���Ű� �ƴϰ� �浹�ѳ༮�� Ʈ���Ű� �ƴϿ��ٸ�
						if (circleCollider->GetTrigger() == false && otherBoxCollider->GetTrigger() == false && circleCollider->GetGameObject()->GetScript())
						{
							if (isPreCollision == false && circleCollider->GetIsOnCollision() == true)
								circleCollider->GetGameObject()->GetScript()->OnCollisionEnter(otherBoxCollider);
							else if (isPreCollision == true && circleCollider->GetIsOnCollision() == true)
								circleCollider->GetGameObject()->GetScript()->OnCollisionStay(otherBoxCollider);
							else if (isPreCollision == true && circleCollider->GetIsOnCollision() == false)
								circleCollider->GetGameObject()->GetScript()->OnCollisionExit(otherBoxCollider);
						}
						// �� �ܴ̿� �� Ʈ���� �ۿ�!
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
				// �ε��� ���ӿ�����Ʈ�� ���������� �� �ε��� ���ӿ�����Ʈ�� �ݶ��̴� ������ false�� �ٲ��ִ� �۾�.
				else if (gameObjects != this && !gameObjects->GetEnable())
				{
					ColliderBase* collider = gameObjects->GetComponent<ColliderBase>();

					if (collider == nullptr)
						continue;

					CircleCollider* otherCircleCollider = dynamic_cast<CircleCollider*>(collider);

					// �� other������Ʈ�� ��Ŭ �ݶ��̴��� ����ִٸ�
					if (otherCircleCollider != nullptr)
					{
						circleCollider->SetOtherColliderInfo(otherCircleCollider, false);
					}

					BoxCollider* otherBoxCollider = dynamic_cast<BoxCollider*>(collider);

					// �� other������Ʈ�� �ڽ� �ݶ��̴��� ����ִٸ�
					if (otherBoxCollider != nullptr)
					{
						circleCollider->SetOtherColliderInfo(otherBoxCollider, false);
					}
				}
			}
		}

		BoxCollider* boxCollider = dynamic_cast<BoxCollider*>(_components[(int)COMPONENT_TYPE::BOX_COLLIDER]);
		// BoxCollider* boxCollider = dynamic_cast<BoxCollider*>(collider);

		// ���� �ڽ� �ݶ��̴��� ����ִٸ�..
		if (boxCollider != nullptr)
		{
			boxCollider->ResetColDirVec();

			for (auto gameObjects : SCENE_MANAGER->GetActiveScene()->GetGameObjects())
			{
				// ���� �ƴ� ���ӿ�����Ʈ�� + (enable = true) ���¶��
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

					// �� other������Ʈ�� �ڽ� �ݶ��̴��� ����ִٸ�
					if (otherBoxCollider != nullptr)
					{
						// ������ �� other������Ʈ�� �浹�߳� ���߳Ĵ� ������ ���´�.
						bool isPreCollision = boxCollider->GetOtherColliderInfo(otherBoxCollider);

						// �׸��� ���� �浹 �ߴ��� ���ߴ��� 
						boxCollider->SetCollision(boxCollider->CheckCollision(otherBoxCollider));

						// üũ�Ⱦ�(��ü vs �ƴѰ�) �϶��� �̺�Ʈ ���ϰ� �Ѿ��. �̵��� �Ѵ�.
						if (boxCollider->GetIsCheck())
						{
							boxCollider->SetIsCheck(false);
							continue;
						}
						
						// ���� other������Ʈ�� �浹������ ���¸� �ٲ��ش�.
						boxCollider->SetOtherColliderInfo(otherBoxCollider, boxCollider->GetIsOnCollision());

						// ���� Ʈ���Ű� �ƴϰ� �浹�ѳ༮�� Ʈ���Ű� �ƴϿ��ٸ�
						if (boxCollider->GetTrigger() == false && otherBoxCollider->GetTrigger() == false && boxCollider->GetGameObject()->GetScript())
						{
							if (isPreCollision == false && boxCollider->GetIsOnCollision() == true)
								boxCollider->GetGameObject()->GetScript()->OnCollisionEnter(otherBoxCollider);
							else if (isPreCollision == true && boxCollider->GetIsOnCollision() == true)
								boxCollider->GetGameObject()->GetScript()->OnCollisionStay(otherBoxCollider);
							else if (isPreCollision == true && boxCollider->GetIsOnCollision() == false)
								boxCollider->GetGameObject()->GetScript()->OnCollisionExit(otherBoxCollider);
						}
						// �� �ܴ̿� �� Ʈ���� �ۿ�!	
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
						// ������ �� other������Ʈ�� �浹�߳� ���߳Ĵ� ������ ���´�.
						bool isPreCollision = boxCollider->GetOtherColliderInfo(otherCircleCollider);

						// �׸��� ���� �浹 �ߴ��� ���ߴ��� 
						boxCollider->SetCollision(boxCollider->CheckCollision(otherCircleCollider));

						// ���� other������Ʈ�� �浹������ ���¸� �ٲ��ش�.
						boxCollider->SetOtherColliderInfo(otherCircleCollider, boxCollider->GetIsOnCollision());

						// ���� Ʈ���Ű� �ƴϰ� �浹�ѳ༮�� Ʈ���Ű� �ƴϿ��ٸ�
						if (boxCollider->GetTrigger() == false && otherCircleCollider->GetTrigger() == false && boxCollider->GetGameObject()->GetScript())
						{
							if (isPreCollision == false && boxCollider->GetIsOnCollision() == true)
								boxCollider->GetGameObject()->GetScript()->OnCollisionEnter(otherCircleCollider);
							else if (isPreCollision == true && boxCollider->GetIsOnCollision() == true)
								boxCollider->GetGameObject()->GetScript()->OnCollisionStay(otherCircleCollider);
							else if (isPreCollision == true && boxCollider->GetIsOnCollision() == false)
								boxCollider->GetGameObject()->GetScript()->OnCollisionExit(otherCircleCollider);
						}
						// �� �ܴ̿� �� Ʈ���� �ۿ�!
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
						// ������ �� other������Ʈ�� �浹�߳� ���߳Ĵ� ������ ���´�.
						bool isPreCollision = boxCollider->GetOtherColliderInfo(otherOBBCollider);

						// �׸��� ���� �浹 �ߴ��� ���ߴ��� 
						boxCollider->SetCollision(boxCollider->CheckCollision(otherOBBCollider));

						// ���� other������Ʈ�� �浹������ ���¸� �ٲ��ش�.
						boxCollider->SetOtherColliderInfo(otherOBBCollider, boxCollider->GetIsOnCollision());

						// ���� Ʈ���Ű� �ƴϰ� �浹�ѳ༮�� Ʈ���Ű� �ƴϿ��ٸ�
						if (boxCollider->GetTrigger() == false && otherOBBCollider->GetTrigger() == false && boxCollider->GetGameObject()->GetScript())
						{
							if (isPreCollision == false && boxCollider->GetIsOnCollision() == true)
								boxCollider->GetGameObject()->GetScript()->OnCollisionEnter(otherOBBCollider);
							else if (isPreCollision == true && boxCollider->GetIsOnCollision() == true)
								boxCollider->GetGameObject()->GetScript()->OnCollisionStay(otherOBBCollider);
							else if (isPreCollision == true && boxCollider->GetIsOnCollision() == false)
								boxCollider->GetGameObject()->GetScript()->OnCollisionExit(otherOBBCollider);
						}
						// �� �ܴ̿� �� Ʈ���� �ۿ�!
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
				// �ε��� ���ӿ�����Ʈ�� ���������� �� �ε��� ���ӿ�����Ʈ�� �ݶ��̴� ������ false�� �ٲ��ִ� �۾�.
				else if (gameObjects != this && !gameObjects->GetEnable())
				{
					ColliderBase* collider = gameObjects->GetComponent<ColliderBase>();

					if (collider == nullptr)
						continue;

					CircleCollider* otherCircleCollider = dynamic_cast<CircleCollider*>(collider);

					// �� other������Ʈ�� ��Ŭ �ݶ��̴��� ����ִٸ�
					if (otherCircleCollider != nullptr)
					{
						boxCollider->SetOtherColliderInfo(otherCircleCollider, false);
					}

					BoxCollider* otherBoxCollider = dynamic_cast<BoxCollider*>(collider);

					// �� other������Ʈ�� �ڽ� �ݶ��̴��� ����ִٸ�
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
				// ū ������ �о���ְ� ������ �������� ������ ���ش�..
				vector<pair<int, Info*>> vec(boxCollider->_reflMap.begin(), boxCollider->_reflMap.end());
				sort(vec.begin(), vec.end(), cmp);

				// �浹�� ������ �Ͼ���� �˾ƾ��Ѵ�.
				int colIndex = 0;
				
				// ��ġ�°��� 2���̻��̸� x,y �ӵ� 0����
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
							// �о�´µ� �� ��ġ�� �κ���������..
							if (boxCollider->CheckCollision(vec[j].second->otherCol))
							{
								isCheck = true;
								break;
							}
						}

						// ������..
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

				// ������ �� other������Ʈ�� �浹�߳� ���߳Ĵ� ������ ���´�.
				bool isPreCollision = boxCollider->GetOtherColliderInfo(vec[colIndex].second->otherCol);

				// �׸��� ���� �浹 �ߴ��� ���ߴ��� 
				//boxCollider->SetCollision(boxCollider->CheckCollision(vec[colIndex].second->otherCol));

				// ���� other������Ʈ�� �浹������ ���¸� �ٲ��ش�.
				boxCollider->SetOtherColliderInfo(vec[colIndex].second->otherCol, true);

				// ���� Ʈ���Ű� �ƴϰ� �浹�ѳ༮�� Ʈ���Ű� �ƴϿ��ٸ�
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

		// ���� obb �ݶ��̴��� ����ִٸ�..
		if (obbCollider != nullptr)
		{
			for (auto gameObjects : SCENE_MANAGER->GetActiveScene()->GetGameObjects())
			{
				// ���� �ƴ� ���ӿ�����Ʈ�� + (enable = true) ���¶��
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

					// �� other������Ʈ�� �ڽ� �ݶ��̴��� ����ִٸ�
					if (otherBoxCollider != nullptr)
					{
						// ������ �� other������Ʈ�� �浹�߳� ���߳Ĵ� ������ ���´�.
						bool isPreCollision = obbCollider->GetOtherColliderInfo(otherBoxCollider);

						// �׸��� ���� �浹 �ߴ��� ���ߴ��� 
						obbCollider->SetCollision(obbCollider->CheckCollision(otherBoxCollider));

						// ���� other������Ʈ�� �浹������ ���¸� �ٲ��ش�.
						obbCollider->SetOtherColliderInfo(otherBoxCollider, obbCollider->GetIsOnCollision());

						// ���� Ʈ���Ű� �ƴϰ� �浹�ѳ༮�� Ʈ���Ű� �ƴϿ��ٸ�
						if (obbCollider->GetTrigger() == false && otherBoxCollider->GetTrigger() == false && obbCollider->GetGameObject()->GetScript())
						{
							if (isPreCollision == false && obbCollider->GetIsOnCollision() == true)
								obbCollider->GetGameObject()->GetScript()->OnCollisionEnter(otherBoxCollider);
							else if (isPreCollision == true && obbCollider->GetIsOnCollision() == true)
								obbCollider->GetGameObject()->GetScript()->OnCollisionStay(otherBoxCollider);
							else if (isPreCollision == true && obbCollider->GetIsOnCollision() == false)
								obbCollider->GetGameObject()->GetScript()->OnCollisionExit(otherBoxCollider);
						}
						// �� �ܴ̿� �� Ʈ���� �ۿ�!
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
						// ������ �� other������Ʈ�� �浹�߳� ���߳Ĵ� ������ ���´�.
						bool isPreCollision = obbCollider->GetOtherColliderInfo(otherOBBCollider);

						// �׸��� ���� �浹 �ߴ��� ���ߴ��� 
						obbCollider->SetCollision(obbCollider->CheckCollision(otherOBBCollider));

						// ���� other������Ʈ�� �浹������ ���¸� �ٲ��ش�.
						obbCollider->SetOtherColliderInfo(otherOBBCollider, obbCollider->GetIsOnCollision());

						// ���� Ʈ���Ű� �ƴϰ� �浹�ѳ༮�� Ʈ���Ű� �ƴϿ��ٸ�
						if (obbCollider->GetTrigger() == false && otherOBBCollider->GetTrigger() == false && obbCollider->GetGameObject()->GetScript())
						{
							if (isPreCollision == false && obbCollider->GetIsOnCollision() == true)
								obbCollider->GetGameObject()->GetScript()->OnCollisionEnter(otherOBBCollider);
							else if (isPreCollision == true && obbCollider->GetIsOnCollision() == true)
								obbCollider->GetGameObject()->GetScript()->OnCollisionStay(otherOBBCollider);
							else if (isPreCollision == true && obbCollider->GetIsOnCollision() == false)
								obbCollider->GetGameObject()->GetScript()->OnCollisionExit(otherOBBCollider);
						}
						// �� �ܴ̿� �� Ʈ���� �ۿ�!
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
				// �ε��� ���ӿ�����Ʈ�� ���������� �� �ε��� ���ӿ�����Ʈ�� �ݶ��̴� ������ false�� �ٲ��ִ� �۾�.
				else if (gameObjects != this && !gameObjects->GetEnable())
				{
					ColliderBase* collider = gameObjects->GetComponent<ColliderBase>();

					if (collider == nullptr)
						continue;

					OBBCollider* otherOBBCollider = dynamic_cast<OBBCollider*>(collider);

					// �� other������Ʈ�� obb �ݶ��̴��� ����ִٸ�
					if (otherOBBCollider != nullptr)
					{
						obbCollider->SetOtherColliderInfo(otherOBBCollider, false);
					}

					BoxCollider* otherBoxCollider = dynamic_cast<BoxCollider*>(collider);

					// �� other������Ʈ�� �ڽ� �ݶ��̴��� ����ִٸ�
					if (otherBoxCollider != nullptr)
					{
						obbCollider->SetOtherColliderInfo(otherBoxCollider, false);
					}
				}
			}
		}
	}

	// ���ӿ�����Ʈ�� �޷��ִ� ��ũ��Ʈ�� ������Ʈ �Ѵ�.
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

		// ���ӿ�����Ʈ�� �޷��ִ� ��ũ��Ʈ�� ������Ʈ �Ѵ�.
		if (_script != nullptr && _isEnable)
			_script->Update();
	
	
		// ���ӿ�����Ʈ�� �޷��ִ� ������Ʈ���� ������Ʈ �Ѵ�.
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
		// ���ӿ�����Ʈ�� �޷��ִ� ��ũ��Ʈ���� ������Ʈ �Ѵ�.
		if (_script != nullptr && _isEnable)
			_script->LateUpdate();

		// ���ӿ�����Ʈ�� �޷��ִ� ������Ʈ���� ������Ʈ �Ѵ�.
		for (auto component : _components)
		{
			if (_isEnable && component != nullptr)
				component->LateUpdate();
		}
	}
}


/// <summary>
/// �������� �������ִ� ������Ʈ �̴�.
/// </summary>
void GameObject::FinalUpdate()
{
this;
	if(_isCameraView || _tag == (int)TAG::Bullet || _tag == (int)TAG::MovableGround || _tag == (int)TAG::Hurdle || _tag == (int)TAG::PassHurdle)
	{
		// ���ӿ�����Ʈ�� �޷��ִ� ��ũ��Ʈ���� ������Ʈ �Ѵ�.
		if (_script != nullptr && _isEnable)
			_script->FinalUpdate();

		// ���ӿ�����Ʈ�� �޷��ִ� ������Ʈ���� ������Ʈ �Ѵ�.
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

