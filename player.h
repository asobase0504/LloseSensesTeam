//==================================================
// player.h
// Author: Buriya Kota
//==================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//**************************************************
// インクルード
//**************************************************
#include "object2D.h"

//**************************************************
// クラス
//**************************************************
class CPlayer : public CObject2D
{
public:
	CPlayer();
	~CPlayer() override;

	HRESULT Init();
	void Update();

	bool GetDeath() { return m_bDeath; }

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	void Control_();

private:
	float m_rotMove;	// 常に足される角度
	bool m_bDeath;
	int m_nTime;
};

#endif	// _PLAYER_H_