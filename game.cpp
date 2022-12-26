//==================================================
// game.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include <assert.h>

#include "manager.h"
#include "input_keyboard.h"
#include "model.h"
#include "sound.h"
#include "pause.h"

#include "score.h"
#include "game.h"
#include "fade.h"
#include "ranking.h"

#include "meshfield.h"
#include "player.h"
#include "wind.h"

#include "particle.h"
#include "utility.h"
#include "timer.h"
#include "season.h"
#include "count.h"

// jsonのinclude
#include "nlohmann/json.hpp"
#include <fstream>

namespace nl = nlohmann;

static nl::json EnemyList;		//　リストの生成
static nl::json PlayerList;		//　リストの生成

//**************************************************
// 静的メンバ変数
//**************************************************
CPlayer *CGame::m_pPlayer = nullptr;
CPause *CGame::m_pPause = nullptr;
CMeshField *CGame::m_pMeshField = nullptr;
CGimmick *CGame::m_pGimmick = nullptr;
CGoal *CGame::m_pGoal = nullptr;
CTime *CGame::m_pTimer = nullptr;
CWind *CGame::m_pWind = nullptr;
CSeason *CGame::m_pSeason = nullptr;
CScore *CGame::m_pScore = nullptr;
CCount *CGame::m_pCount = nullptr;

//**************************************************
// マクロ定義
//**************************************************

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CGame::CGame()
{
	m_bCreate = false;
	m_time = 0;
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CGame::~CGame()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CGame::Init()
{
	m_time = 0;

	CObject2D* bg = CObject2D::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(CManager::SCREEN_WIDTH, CManager::SCREEN_HEIGHT, 0.0f));

	m_pScore = CScore::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.3f, 50.0f, 0.0f), D3DXVECTOR3(60.0f, 120.0f, 0.0f));
	m_pScore->SetScore(0);

	m_pPause = CPause::Create();

	m_pCount = CCount::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(200.0f, 400.0f, 0.0f));
	m_pCount->Start();

	bg->SetTexture(CTexture::TEXTURE_TITLE_BG);
	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CGame::Uninit()
{
	//CManager::GetSound()->Stop();

	// リリースはリリースオールでやってある

	CObject::DeletedObj();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CGame::Update()
{
	if (m_pCount->GetStart() && !m_bCreate)
	{
		m_pTimer = CTime::Create(D3DXVECTOR3(520.0f, 50.0f, 0.0f), D3DXVECTOR3(30.0f, 60.0f, 0.0f));
		m_pTimer->Start();

		m_pSeason = CSeason::Create(D3DXVECTOR3(620.0f, 50.0f, 0.0f), D3DXVECTOR3(30.0f, 60.0f, 0.0f));
		m_pSeason->Start();

		m_pPlayer = CPlayer::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT - (320.0f * 0.15f), 0.0f), D3DXVECTOR3(820.0f, 820.0f, 0.0f));
		m_pWind = CWind::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.8f, CManager::SCREEN_WIDTH * 0.3f, 0.0f), D3DXVECTOR3(300.0f, 300.0f, 0.0f));
		m_bCreate = true;
	}

	m_time++;

	if (m_time % 1 == 0)
	{
		if (m_pPlayer != nullptr)
		{
			D3DXVECTOR3 rot = m_pPlayer->GetRot();

			int score = 0;
			score += (int)(10.0f * (1.0f - fabs(rot.z)));

			m_pScore->AddScore(score);
		}
	}

	// 風のパーティクル
	if (m_time % 2 == 0)
	{
		CParticle* particle = CParticle::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f), 50);

		if (m_pWind != nullptr)
		{
			switch (m_pWind->GetState())
			{
			case CWind::WIND_ROT::WIND_LEFT:
			{
				particle->SetPos(D3DXVECTOR3(CManager::SCREEN_WIDTH, FloatRandam(0.0f, CManager::SCREEN_HEIGHT - 20.0f), 0.0f));
				particle->SetMovePos(D3DXVECTOR3(FloatRandam(-10.0f, -30.0f), FloatRandam(2.0f, -1.0f), 0.0f));
				particle->SetMoveSize(D3DXVECTOR3(-0.35f, -0.35f, 0.0f));
				particle->SetMoveRot(D3DXVECTOR3(0.0f, 0.0f, 0.05f));
				particle->SetTexture(CTexture::TEXTURE_HANABIRA);
			}
			break;
			case CWind::WIND_ROT::WIND_RIGHT:
			{
				particle->SetPos(D3DXVECTOR3(0.0f, FloatRandam(0.0f, CManager::SCREEN_HEIGHT - 20.0f), 0.0f));
				particle->SetMovePos(D3DXVECTOR3(FloatRandam(30.0f, 10.0f), FloatRandam(2.0f, -1.0f), 0.0f));
				particle->SetMoveSize(D3DXVECTOR3(-0.35f, -0.35f, 0.0f));
				particle->SetMoveRot(D3DXVECTOR3(0.0f, 0.0f, 0.05f));
			}
			break;
			default:
				break;
			}

			switch (m_pSeason->GetSeason())
			{
			case CSeason::SEASON_SPRING:
				particle->SetTexture(CTexture::TEXTURE_HANABIRA);
				break;
			case CSeason::SEASON_SUMMER:
				particle->SetTexture(CTexture::TEXTURE_HANABIRA);
				particle->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
				break;
			case CSeason::SEASON_FALL:
				particle->SetTexture(CTexture::TEXTURE_HANABIRA);

				if (FloatRandam(1.0f, 0.0f) < 0.55f)
				{
					particle->SetCol(D3DXCOLOR(1.0f, 0.25f, 0.0f, 1.0f));
				}
				else
				{
					particle->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
				}
				break;
			case CSeason::SEASON_WINTER:
			{
				float size = FloatRandam(60.0f, 20.0f);
				particle->SetSize(D3DXVECTOR3(size, size, 0.0f));
				particle->SetTexture(CTexture::TEXTURE_SNOW);
			}
			break;
			default:
				break;
			}
		}
	}
}

//--------------------------------------------------
// 風の強さ
//--------------------------------------------------
CWind *CGame::GetWind()
{
	return m_pWind;
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CGame* CGame::Create()
{
	CGame *pGame;
	pGame = new CGame;

	if (pGame != nullptr)
	{
		pGame->Init();
	}
	else
	{
		assert(false);
	}

	return pGame;
}
