//==================================================
// season.cpp
// Author: Kajita Hiromu
//==================================================

//**************************************************
// include
//**************************************************
#include "manager.h"
#include "season.h"
#include "number.h"

//**************************************************
// 静的メンバ変数
//**************************************************
CSeason::SEASON CSeason::m_season = SEASON_SPRING;

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CSeason::CSeason(int nPriority /* =4 */) : CObject(nPriority)
{
	m_nTime = 0;
	SetType(TYPE_SCORE);
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CSeason::~CSeason()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CSeason::Init()
{
	m_nTime2 = 0;
	m_nCntTime = 900;
	return S_OK;
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CSeason::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
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
void CSeason::Uninit()
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

void CSeason::Update()
{
	if (m_isStart)
	{
		AddTime();
	}
}

//--------------------------------------------------
// 位置の設定と大きさの設定
//--------------------------------------------------
void CSeason::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_pNumber[nCnt]->SetPos(D3DXVECTOR3(size.x * nCnt + pos.x, pos.y, 0.0f));
	}
}

//--------------------------------------------------
// タイマースタート
//--------------------------------------------------
void CSeason::Start()
{
	m_nTime = timeGetTime();
	m_isStart = true;
}

//--------------------------------------------------
// タイマーエンド
//--------------------------------------------------
int CSeason::End()
{
	m_isStart = false;
	return m_nTime;
}

//--------------------------------------------------
// タイムの設定
//--------------------------------------------------
void CSeason::SetTime(int nTime)
{
	int aPosTexU[MAX_TIME];		// 各桁の数字を格納

	{
		m_nCntTime--;				//nCntTimeが引かれていく

		if (m_nCntTime < 0)			//nCntTimeが0より小さくなったら
		{
			m_nTime2++;				//時間が一秒ずつ減っていく
			m_nCntTime = 900;		//時間の減りの速さ
		}

		aPosTexU[0] = m_nTime2 % 5 / 1;

		if (m_nTime2 == 1)
		{
			m_season = SEASON_SPRING;
		}
		else if (m_nTime2 == 2)
		{
			m_season = SEASON_SUMMER;
		}
		else if (m_nTime2 == 3)
		{
			m_season = SEASON_FALL;
		}
		else if (m_nTime2 == 4)
		{
			m_season = SEASON_WINTER;
		}
		else if (m_nTime2 == 5)
		{
			m_nTime2 = 1;
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
CSeason *CSeason::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CSeason *pTime;
	pTime = new CSeason;

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
