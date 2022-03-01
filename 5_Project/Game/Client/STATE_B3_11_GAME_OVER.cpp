#include "pch.h"
#include "State.h"
#include "B3_11.h"
#include "STATE_B3_11_GAME_OVER.h"
#include "UIManager.h"

STATE_B3_11_GAME_OVER::STATE_B3_11_GAME_OVER(B3_11* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("B3_11_GameOver"))), 
	gameOverClip(AnimClipLoader::LoadClip(AnimClipPath("GameOverText")))
{

}

void STATE_B3_11_GAME_OVER::Start()
{
	
}

int STATE_B3_11_GAME_OVER::FixedUpdate()
{
	if (ref->_deadDelay >= 1.1f)
	{
		if(!(GET_SINGLE(UIManager)->GetInGameOverPanel()->GetEnable()))
		{ 
			SCENE_MANAGER->SetSavePointPos();
			GET_SINGLE(UIManager)->SetIsGameOver(true);
			GET_SINGLE(UIManager)->SetIsTrueInGameOverPanel();
		}
	}



	ref->_deadDelay += DELTA_TIME;

	return B3_11::GAME_OVER;
}

void STATE_B3_11_GAME_OVER::Update()
{
	ref->_animator->Play(animClip);
	//ref->_animator->Play(gameOverClip);
}

void STATE_B3_11_GAME_OVER::End()
{

}
