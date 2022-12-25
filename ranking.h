//==================================================
// ranking.h
// Author: Buriya Kota
//==================================================
#ifndef _RANKING_H_
#define _RANKING_H_

//**************************************************
// インクルード
//**************************************************
#include "game_mode.h"
#include "texture.h"

//**************************************************
// 前方前言　実態はNG　ポインタだけならOK
//**************************************************
class CObject2D;
class CScore;

//**************************************************
// クラス
//**************************************************
class CRanking : public CGameMode
{
public:
	static const int MAX_RANK = 5;

public:
	CRanking();
	~CRanking() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override {}

	void LoadRanking();
	void SaveRanking();
	void SetRanking(int nScore);

	static CRanking *Create();

private:
	// オブジェクト2Dの箱
	CObject2D *m_pRanking;
	// オブジェクト2Dの箱
	CObject2D *m_pRankingBg;
	CScore *m_pScore[MAX_RANK];
	// 位置
	D3DXVECTOR3 m_pos;
	// 大きさ
	D3DXVECTOR3 m_size;
	// スコア保存変数
	int m_aRankingData[MAX_RANK];

};

#endif	// _RESULT_H_