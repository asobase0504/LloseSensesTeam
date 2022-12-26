//==================================================
// player.h
// Author: Buriya Kota
//==================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "object2D.h"

//**************************************************
// �N���X
//**************************************************
class CPlayer : CObject2D
{
public:
	CPlayer();
	~CPlayer() override;

	HRESULT Init();
	void Update();

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	void Control_();

};

#endif	// _PLAYER_H_