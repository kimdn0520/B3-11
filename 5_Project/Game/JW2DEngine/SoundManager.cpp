#include "pch.h"
#include "SoundManager.h"

void SoundManager::Init()
{
	System_Create(&_pSystem);

	_pSystem->init(10, FMOD_INIT_NORMAL, NULL);
	_pDatas = new SoundTable();
	LoadJson();
}

// Json 파일 불러오는 곳
void SoundManager::LoadJson()
{
	_pDatas->DeserializeFromFile("..\\..\\4_Resources\\DataTable\\SoundData.json");
	for (int i = 0;i < _pDatas->dataCount;i++)
	{	
		char fileRoot[50];
		strcpy_s(fileRoot, _pDatas->fileRoot[i].c_str());
		if (_pDatas->loop[i] == "TRUE")
		{
			_pSystem->createSound(fileRoot, FMOD_LOOP_NORMAL | FMOD_DEFAULT, NULL, &_pSound[i]);
		}
		else if (_pDatas->loop[i] == "FALSE")
		{
			_pSystem->createSound(fileRoot, FMOD_DEFAULT, NULL, &_pSound[i]);
		}
	}
}

void SoundManager::BgmSetting(string soundName)
{
	for (int i = 0; i < 4; i++)
	{
		if (soundName == _pDatas->soundName[i])
		{
			_pSystem->playSound(_pSound[i], NULL, 0, &_pBgmChannel[i]);
		}
	}
}

void SoundManager::BgmPlay(string soundName)
{
	for (int i = 0; i < 4; i++)
	{
		if (soundName == _pDatas->soundName[i])
			_pBgmChannel[i]->setPaused(false);
	}
}

void SoundManager::BgmPause(string soundName)
{
	for (int i = 0; i < 4; i++)
	{
		if (soundName == _pDatas->soundName[i])
			_pBgmChannel[i]->setPaused(true);
	}
}

void SoundManager::BgmSoundControl(float volume)
{
	for (int i = 0; i < 4; i++)
	{
		_pBgmChannel[i]->setVolume(volume);
	}
}

void SoundManager::PlayerAttack()
{
	for (int i = 0; i < 20; i++)
	{
		if (_pDatas->soundName[i] == "PlayerAttack")
			_pSystem->playSound(_pSound[i], NULL, 0, &_pPlayerChannel[0]);
	}
}

void SoundManager::PlayerMove()
{
	for (int i = 0; i < 20; i++)
	{
		if (_pDatas->soundName[i] == "PlayerMove")
			_pSystem->playSound(_pSound[i], NULL, 0, &_pPlayerChannel[1]);
	}
}

void SoundManager::PlayerJump()
{
	for (int i = 0; i < 20; i++)
	{
		if (_pDatas->soundName[i] == "PlayerJump")
			_pSystem->playSound(_pSound[i], NULL, 0, &_pPlayerChannel[2]);
	}
}

void SoundManager::PlayerWallJump()
{
	for (int i = 0; i < 20; i++)
	{
		if (_pDatas->soundName[i] == "PlayerWallJump")
			_pSystem->playSound(_pSound[i], NULL, 0, &_pPlayerChannel[3]);
	}
}

void SoundManager::PlayerEnergyCharge()
{
	for (int i = 0; i < 20; i++)
	{
		if (_pDatas->soundName[i] == "PlayerEnergyCharge")
			_pPlayerChannel[4]->stop();
	}
}

void SoundManager::PlayerEnergyChargeStop()
{
	for (int i = 0; i < 20; i++)
	{
		if (_pDatas->soundName[i] == "PlayerEnergyCharge")
			_pSystem->playSound(_pSound[i], NULL, 0, &_pPlayerChannel[5]);
	}
}

void SoundManager::PenguinAlert()
{
	for (int i = 0; i < 20; i++)
	{
		if (_pDatas->soundName[i] == "PenguinAlert")
			_pSystem->playSound(_pSound[i], NULL, 0, &_pSFXChannel[0]);
	}
}

void SoundManager::SharkAlert()
{
	for (int i = 0; i < 20; i++)
	{
		if (_pDatas->soundName[i] == "SharkAlert")
			_pSystem->playSound(_pSound[i], NULL, 0, &_pSFXChannel[1]);
	}
}

void SoundManager::ObjectBreak()
{
	for (int i = 0; i < 20; i++)
	{
		if (_pDatas->soundName[i] == "ObjectBreak")
			_pSystem->playSound(_pSound[i], NULL, 0, &_pSFXChannel[2]);
	}
}

void SoundManager::ObjectSaw()
{
	for (int i = 0; i < 20; i++)
	{
		if (_pDatas->soundName[i] == "ObjectSaw")
			_pSystem->playSound(_pSound[i], NULL, 0, &_pSFXChannel[3]);
	}
}

void SoundManager::MenuMove()
{
	for (int i = 0; i < 20; i++)
	{
		if (_pDatas->soundName[i] == "MenuMove")
			_pSystem->playSound(_pSound[i], NULL, 0, &_pSFXChannel[4]);
	}
}

void SoundManager::MenuNoButton()
{
	for (int i = 0; i < 20; i++)
	{
		if (_pDatas->soundName[i] == "MenuNoButton")
			_pSystem->playSound(_pSound[i], NULL, 0, &_pSFXChannel[5]);
	}
}

void SoundManager::MenuYesButton()
{
	for (int i = 0; i < 20; i++)
	{
		if (_pDatas->soundName[i] == "MenuYesButton")
			_pSystem->playSound(_pSound[i], NULL, 0, &_pSFXChannel[6]);
	}
}

void SoundManager::SFXSoundControl(float volume)
{
	for (int i = 0; i < 10; i++)
	{
		_pPlayerChannel[i]->setVolume(volume);
		_pSFXChannel[i]->setVolume(volume);
	}
}

// 해제 작업
void SoundManager::Release()
{
	for (int i = 0;i < 20;i++)
	{
		_pSound[i]->release();
	}
	_pSystem->release();
	_pSystem->close();
	delete _pDatas;
}
