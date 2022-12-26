//==================================================
// wind.h
// Author: Kajita Hiromu
//==================================================
#ifndef _WIND_H_
#define _WIND_H_

//**************************************************
// インクルード
//**************************************************
#include "object2D.h"

//**************************************************
// 前方前言　実態はNG　ポインタだけならOK
//**************************************************

//**************************************************
// 定数定義
//**************************************************

//**************************************************
// 構造体定義
//**************************************************

//**************************************************
// クラス
//**************************************************
class CWind : public CObject2D
{
public:
	explicit CWind(int nPriority = PRIORITY_EFFECT);
	~CWind();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetWind(D3DXVECTOR3 rot, float air);

	static CWind *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);

private:
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_size;		//サイズ
	D3DXVECTOR3 m_rot;		//向き
	D3DXVECTOR3 m_move;		//位置

};


#endif	// _NUMBER_H_
