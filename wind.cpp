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
#include "tutorial.h"
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
	SetTexture(CTexture::TEXTURE_NONE);
	SetCol(D3DXCOLOR(0.0f,0.0f,0.0f,0.0f));
	m_state = WIND_STOP;
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFrame = 0;
	m_nSwitchFrame = 0;
	m_nTime = 0;
	fAirFlow = 0.0f;

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
	if (CManager::GetGameMode() == CManager::MODE_TUTORIAL)
	{
		CTime *pTimer = CTutorial::GetTimer();
		int Timer = pTimer->GetTime() / 100;

		switch (CSeason::GetSeason())
		{
		case CSeason::SEASON_SPRING:
		{
			fAirFlow = SPRING_SPEED + Timer * MAX_BROW;
		}
		break;

		case CSeason::SEASON_SUMMER:
		{
			fAirFlow = SUMMER_SPEED + Timer * MAX_BROW;
		}
		break;

		case CSeason::SEASON_FALL:
		{
			fAirFlow = FALL_SPEED + Timer * MAX_BROW;
		}
		break;

		case CSeason::SEASON_WINTER:
		{
			fAirFlow = WINTER_SPEED + Timer * MAX_BROW;
		}
		break;

		default:
			break;
		}
	}
	else
	{
		CTime *pTime = CGame::GetTimer();
		int Timer = pTime->GetTime() / 100;

		switch (CSeason::GetSeason())
		{
		case CSeason::SEASON_SPRING:
		{
			fAirFlow = 0.01f + Timer * 0.000003f;
		}
		break;

		case CSeason::SEASON_SUMMER:
		{
			fAirFlow = 0.02f + Timer * 0.000003f;
		}
		break;

		case CSeason::SEASON_FALL:
		{
			fAirFlow = 0.03f + Timer * 0.000003f;
		}
		break;

		case CSeason::SEASON_WINTER:
		{
			fAirFlow = 0.035f + Timer * 0.000005f;
		}
		break;

		default:
			break;
		}
	}

	//フレームを加算
	m_nFrame++;

	if (m_state == WIND_STOP)
	{
		fAirFlow = 0;

		if (m_nFrame > 30)
		{//フレーム数が30を超えたら
		 //ランダムの値を変える

			m_state = m_nextRot;
			m_nFrame = 0;
		}
	}
	else
	{
		fAirFlow *= -1.0f;

		if (m_nFrame > 180)
		{//フレーム数が180を超えたら
			m_state = WIND_STOP;
			m_nRandom = FloatRandam(3.0f, 0.0f);

			if (m_nRandom <= 1.5f)
			{//ランダムの値が1.5f以下なら
				m_nextRot = WIND_RIGHT;
			}
			else
			{//1.5f以上なら	
				m_state = WIND_STOP;
				m_nextRot = WIND_LEFT;
			}

			m_nFrame = 0;
		}
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
