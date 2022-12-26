//==================================================
// score.h
// Author: Buriya Kota
//==================================================
#ifndef _TIME_H_
#define _TIME_H_

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
class CTime : public CObject
{
public:
	static const int MAX_TIME = 5;
public:
	explicit CTime(int nPriority = PRIORITY_EFFECT);
	~CTime() override;

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

	static CTime *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	// Number型の配列
	CNumber *m_pNumber[MAX_TIME];
	// スコアの値
	int m_nTime;

	bool m_isStart;
};

#endif	// _SCORE_H_