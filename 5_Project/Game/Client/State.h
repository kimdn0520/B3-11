#pragma once

#include "Input.h"
#include "ObjectPool.h"
#include "Bullet.h"
#include "Timer.h"
#include "MonoBehaviour.h"
#include "Transform.h"
#include "RigidBody.h"
#include "AnimationClip.h"
#include "Animator.h"
#include "AnimClipLoader.h"
#include "SoundManager.h"

#define AnimClipPath(x) "AnimClip\\" + string(x) + ".json"

class State
{
public:
	virtual void Start() = 0;
	virtual int FixedUpdate() = 0;
	virtual void Update() = 0;
	virtual void End() = 0;
};