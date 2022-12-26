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
	enum WIND_ROT	//現在の向き
	{
		WIND_LEFT,
		WIND_RIGHT,
		WIND_MAX
	};

	explicit CWind(int nPriority = PRIORITY_EFFECT);
	~CWind();

	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了処理
	void Update() override;		//更新処理
	void Draw() override;		//描画処理

	WIND_ROT GetState();		//状態取得
	static CWind *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	//生成

private:
	WIND_ROT m_state;		//状態

	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_size;		//サイズ
	D3DXVECTOR3 m_rot;		//向き
	D3DXVECTOR3 m_move;		//位置

	int m_nFrame;			//フレーム数
	float m_nRandom;		//ランダム用変数
};


#endif	// _NUMBER_H_
