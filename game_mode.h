//==================================================
// game_mode.h
// Author: Buriya Kota
//==================================================
#ifndef _GAME_MODE_H_
#define _GAME_MODE_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "object.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************

//**************************************************
// �N���X
//**************************************************
class CGameMode : public CObject
{
public:
	CGameMode();
	~CGameMode() override;

	HRESULT Init() override { return S_OK; }
	void Uninit() override {}
	void Update() override {}
	void Draw() override {}

private:

};

#endif	// _GAME_MODE_H_