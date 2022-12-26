//==================================================
// sceason.h
// Author: Kajita Hiromu
//==================================================
#ifndef _SEASON_H_
#define _SEASON_H_

//**************************************************
// インクルード
//**************************************************
#include "object.h"

//**************************************************
// 前方前言　実態はNG　ポインタだけならOK
//**************************************************
class CNumber;

//**************************************************
// クラス
//**************************************************
class CSeason : public CObject
{
public:
	static const int MAX_TIME = 1;
public:
	enum SEASON
	{
		SEASON_SPRING,
		SEASON_SUMMER,
		SEASON_FALL,
		SEASON_WINTER,
		SEASON_MAX
	};

	explicit CSeason(int nPriority = PRIORITY_EFFECT);
	~CSeason() override;

	HRESULT Init() override;
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit() override;
	void Update() override;
	void Draw() override {}

	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	void Start();
	int End();

	void SetTime(int nScore);
	void AddTime() { SetTime((int)(timeGetTime() - m_nTime)); }
	int GetTime() { return m_nTime; }
	static SEASON GetSeason() { return m_season; }

	static CSeason *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	// Number型の配列
	CNumber *m_pNumber[MAX_TIME];
	// スコアの値
	int m_nTime;
	int m_nTime2;
	int	m_nCntTime;
	// SEASON型の変数
	static SEASON m_season;

	bool m_isStart;
};

#endif	// _SCORE_H_
