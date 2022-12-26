//==================================================
// count.h
// Author: Kajita Hiromu
//==================================================
#ifndef _COUNT_H_
#define _COUNT_H_

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
class CCount : public CObject
{
public:
	static const int MAX_TIME = 1;
public:
	explicit CCount(int nPriority = PRIORITY_EFFECT);
	~CCount() override;

	HRESULT Init() override;
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit() override;
	void Update() override;
	void Draw() override {}

	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	void Start();
	int End();

	void StartTimer(bool bStart);
	bool GetStart();

	void SetTime(int nScore);
	void AddTime() { SetTime((int)(timeGetTime() - m_nTime)); }
	int GetTime() { return m_nTime; }

	static CCount *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	// Number型の配列
	CNumber *m_pNumber[MAX_TIME];
	// スコアの値
	int m_nTime;
	int m_nTime2;
	int	m_nCntTime;

	bool m_isStart;
	bool m_bStart;
};

#endif	// _SCORE_H_
