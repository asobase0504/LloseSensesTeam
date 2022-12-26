//==================================================
// count.cpp
// Author: Kajita Hiromu
//==================================================

//**************************************************
// include
//**************************************************
#include "count.h"
#include "manager.h"
#include "number.h"

//**************************************************
// 静的メンバ変数
//**************************************************

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CCount::CCount(int nPriority /* =4 */) : CObject(nPriority)
{
	SetType(TYPE_SCORE);
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CCount::~CCount()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CCount::Init()
{
	return S_OK;
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CCount::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_nTime = 0;
	m_nTime2 = 4;
	m_nCntTime = 0;
	m_isStart = false;
	m_bStart = false;

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
void CCount::Uninit()
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

void CCount::Update()
{
	if (m_isStart)
	{
		AddTime();
	}
}

//--------------------------------------------------
// 位置の設定と大きさの設定
//--------------------------------------------------
void CCount::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_pNumber[nCnt]->SetPos(D3DXVECTOR3(size.x * nCnt + pos.x, pos.y, 0.0f));
	}
}

//--------------------------------------------------
// タイマースタート
//--------------------------------------------------
void CCount::Start()
{
	m_nTime = timeGetTime();
	m_isStart = true;
}

//--------------------------------------------------
// タイマーエンド
//--------------------------------------------------
int CCount::End()
{
	m_isStart = false;
	return m_nTime;
}

void CCount::StartTimer(bool bStart)
{
	m_bStart = bStart;
}

bool CCount::GetStart()
{
	return m_bStart;
}

//--------------------------------------------------
// タイムの設定
//--------------------------------------------------
void CCount::SetTime(int nTime)
{
	int aPosTexU[MAX_TIME];		// 各桁の数字を格納

	if (!m_bStart)
	{
		m_nCntTime--;				//nCntTimeが引かれていく

		if (m_nCntTime < 0)			//nCntTimeが0より小さくなったら
		{
			m_nTime2--;				//時間が一秒ずつ減っていく
			m_nCntTime = 60;		//時間の減りの速さ
		}

		aPosTexU[0] = m_nTime2 % 4 / 1;

		if (m_nTime2 == 0)
		{
			StartTimer(true);
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
CCount *CCount::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CCount *pTime;
	pTime = new CCount;

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
