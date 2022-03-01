#pragma once
#include "fmod.hpp"
#include "fmod_errors.h"
#include "SoundTable.h"

using namespace std;
using namespace FMOD;

class SoundManager
{
	DECLARE_SINGLE(SoundManager);
public:
	void Init();
	void Update();
	void BgmSetting(string soundName);
	void BgmPlay(string soundName);
	void BgmPause(string soundName);
	void BgmSoundControl(float volume);

	void PlayerAttack();
	void PlayerMove();
	void PlayerJump();
	void PlayerWallJump();
	void PlayerEnergyCharge();
	void PlayerEnergyChargeStop();

	void PenguinAlert();
	void SharkAlert();

	void ObjectBreak();
	void ObjectSaw();

	void MenuMove();
	void MenuNoButton();
	void MenuYesButton();

	void SFXSoundControl(float volume);

	void Release();

private:
	System* _pSystem;
	Sound* _pSound[20];
	Channel* _pBgmChannel[5];
	Channel* _pPlayerChannel[10];
	Channel* _pSFXChannel[10];
	SoundTable* _pDatas;

	int _bgmCount = 0;

private:
	void LoadJson();
};