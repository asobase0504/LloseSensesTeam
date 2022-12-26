//==================================================
// score.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include "manager.h"
#include "timer.h"
#include "number.h"

//**************************************************
// 静的メンバ変数
//**************************************************

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CTime::CTime(int nPriority /* =4 */) : CObject(nPriority)
{
	m_nTime = 0;
	SetType(TYPE_SCORE);
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CTime::~CTime()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CTime::Init()
{
	return S_OK;
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CTime::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_nTime = 0;
	m_isStart = false;

	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_pNumber[nCnt] = CNumber::Create(D3DXVECTOR3(size.x * nCnt + pos.x, pos.y, 0.0f), size);
		m_pNumber[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pNumber[nCnt]->SetTexture(CTexture::TEXTURE_NUMBER);
	}

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CTime::Uninit()
{
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		if (m_pNumber[nCnt] == nullptr)
		{
			continue;
		}

		m_pNumber[nCnt]->Uninit();
	}

	CObject::DeletedObj();
}

void CTime::Update()
{
	if (m_isStart)
	{
		AddTime();
	}
}

//--------------------------------------------------
// 位置の設定と大きさの設定
//--------------------------------------------------
void CTime::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_pNumber[nCnt]->SetPos(D3DXVECTOR3(size.x * nCnt + pos.x, pos.y, 0.0f));
	}
}

//--------------------------------------------------
// タイマースタート
//--------------------------------------------------
void CTime::Start()
{
	m_nTime = timeGetTime();
	m_isStart = true;
}

//--------------------------------------------------
// タイマーエンド
//--------------------------------------------------
int CTime::End()
{
	m_isStart = false;
	return m_nTime;
}

//--------------------------------------------------
// スコアの設定
//--------------------------------------------------
void CTime::SetTime(int nTime)
{
	int aPosTexU[8];		// 各桁の数字を格納

	{
		int score = nTime;
		for (int nCnt = MAX_TIME; nCnt >= 0; --nCnt)
		{
			aPosTexU[nCnt] = score % 10;
			score /= 10;
		}
	}

	// テクスチャ座標の設定
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_pNumber[nCnt]->AnimTexture(aPosTexU[nCnt], 10);
	}
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CTime *CTime::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CTime *pTime;
	pTime = new CTime;

	if (pTime != nullptr)
	{
		pTime->Init(pos, size);
	}
	else
	{
		assert(false);
	}

	return pTime;
}
