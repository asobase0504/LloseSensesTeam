//==================================================
// wind.cpp
// Author: Kajita Hiromu
//==================================================
//**************************************************
// include
//**************************************************
#include <assert.h>

#include "debug_proc.h"
#include "game.h"
#include "manager.h"
#include "season.h"
#include "timer.h"
#include "utility.h"
#include "wind.h"
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CWind::CWind(int nPriority /* =4 */) : CObject2D(nPriority)
{
	SetType(TYPE_WIND);
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CWind::~CWind()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CWind::Init()
{
	CObject2D::Init();
	SetTexture(CTexture::TEXTURE_WIND);

	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFrame = 0;
	m_nLeftTime = 0;
	m_nRightTime = 0;
	m_nTime = 0;
	fAirFlow = 0.0f;
	m_bSwitch = false;

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CWind::Uninit()
{
	CObject2D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CWind::Update()
{
	CTime *pTime = CGame::GetTimer();
	int Timer = pTime->GetTime() / 100;

	int m_nTimeHarf = m_nTime / 0.5f;

	switch (CSeason::GetSeason())
	{
	case CSeason::SEASON_SPRING:
	{
		if (m_nTime <= m_nTimeHarf)
		{
			fAirFlow = 0.01f + Timer * 0.000003f;
		}
		else
		{
			fAirFlow = 0.01f - Timer * 0.000003f;
		}
	}
	break;

	case CSeason::SEASON_SUMMER:
	{
		if (m_nTime <= m_nTimeHarf)
		{
			fAirFlow = 0.02f + Timer * 0.000003f;
		}
		else
		{
			fAirFlow = 0.02f - Timer * 0.000003f;
		}
	}
	break;

	case CSeason::SEASON_FALL:
	{
		fAirFlow = 0.03f + Timer * 0.000003f;
	}
	break;

	case CSeason::SEASON_WINTER:
	{
		fAirFlow = 0.05f + Timer * 0.000005f;
	}
	break;

	default:
		break;
	}

	//フレームを加算
	m_nFrame++;

	if (m_nFrame > 60)
	{//フレーム数が45を超えたら
		//ランダムの値を変える
		m_nRandom = FloatRandam(3.0f, 0.0f);

		//フレームを0に戻す
		m_nFrame = 0;
	}

	if (m_nRandom <= 1.5f)
	{//ランダムの値が1.5f以下なら
		m_state = WIND_LEFT;
		m_bSwitch = false;
		fAirFlow *= -1.0f;
		m_pos = D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.8f, CManager::SCREEN_WIDTH * 0.3f, 0.0f);
	}
	else
	{//1.5f以上なら
		m_state = WIND_RIGHT;
		m_bSwitch = true;
		fAirFlow *= -1.0f;

		m_pos = D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.2f, CManager::SCREEN_WIDTH * 0.3f, 0.0f);
	}

	switch (m_state)
	{
	case CWind::WIND_LEFT:
		m_nLeftTime++;
		if (!m_bSwitch)
		{
			m_nTime = m_nLeftTime - m_nRightTime;
		}
		break;
	case CWind::WIND_RIGHT:
		m_nRightTime++;
		if (m_bSwitch)
		{
			m_nTime = m_nLeftTime - m_nRightTime;
		}
		break;
	default:
		break;
	}

	//posの値を更新
	SetPos(m_pos);
	CObject2D::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CWind::Draw()
{
	CObject2D::Draw();
}

//--------------------------------------------------
// 現在の向きを取得
//--------------------------------------------------
CWind::WIND_ROT CWind::GetState()
{
	return m_state;
}

float CWind::GetAirFlow()
{
	if (m_state == CWind::WIND_LEFT)
	{
		return fAirFlow;
	}
	return fAirFlow * -1.0f;
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CWind * CWind::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	CWind *pWind;
	pWind = new CWind;

	if (pWind != nullptr)
	{
		pWind->Init();
		pWind->SetPos(pos);
		pWind->SetSize(size);
	}
	else
	{
		assert(false);
	}

	return pWind;
}
