#include "pch.h"
#include "State.h"
#include "B3_11.h"
#include "STATE_B3_11_DASH.h"

STATE_B3_11_DASH::STATE_B3_11_DASH(B3_11* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("BellDash")))
{

}

void STATE_B3_11_DASH::Start()
{
	ref->_dashTimer = 0;

	ref->_rigidbody->SetGravityScale(0);
	ref->_rigidbody->SetVelocity({ 0,0 });
	ref->_rigidbody->AddForce(Vector2(ref->_face, 0) * ref->_dashPower);

	ref->_transform->SetLocalScale({ ref->_face, ref->_transform->GetLocalScale().y });
}

int STATE_B3_11_DASH::FixedUpdate()
{
	if (ref->_groundWay[1] && ref->_input == -1 && ref->_dashTimer > 0.1f)
		return B3_11::WALL;

	if (ref->_groundWay[2] && ref->_input == 1 && ref->_dashTimer > 0.1f)
		return B3_11::WALL;

	if (ref->_dashTimer > ref->_dashTime)
		return B3_11::IDLE;


	ref->_dashTimer += DELTA_TIME;


	return B3_11::DASH;
}

void STATE_B3_11_DASH::Update()
{
	ref->_animator->Play(animClip);
}

void STATE_B3_11_DASH::End()
{
	ref->_rigidbody->SetGravityScale(ref->_defaultGravityScale);
	ref->_bDashKeyPressed = false;
	ref->_isDashing = false;
	ref->_isDashable = false;
	ref->_dashCoolTimer = 0.0f;
}
