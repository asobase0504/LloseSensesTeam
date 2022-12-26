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

//**************************************************
// マクロ定義
//**************************************************

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CGame::CGame()
{
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

	m_pTimer = CTime::Create(D3DXVECTOR3(520.0f, 50.0f, 0.0f), D3DXVECTOR3(30.0f, 60.0f, 0.0f));
	m_pTimer->Start();

	m_pPause = CPause::Create();

	m_pPlayer = CPlayer::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT - (320.0f * 0.15f), 0.0f), D3DXVECTOR3(820.0f, 820.0f, 0.0f));
	m_pWind = CWind::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.8f, CManager::SCREEN_WIDTH * 0.3f, 0.0f),D3DXVECTOR3(300.0f, 300.0f,0.0f));

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CGame::Uninit()
{
	//CManager::GetSound()->Stop();

	// リリースはリリースオールでやってある
	m_pTimer = nullptr;
	m_pPlayer = nullptr;

	CObject::DeletedObj();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CGame::Update()
{
	m_time++;

	CInputKeyboard *pInputKeyoard = CManager::GetInputKeyboard();

	if (m_pPlayer->GetDeath())
	{
		// 遷移
		CFade::GetInstance()->SetFade(CManager::MODE_RESULT);
	}

	// 風のパーティクル
	if(m_time % 2 == 0)
	{
		CParticle* particle = CParticle::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f), 50);
		switch (m_pWind->GetState())
		{
		case CWind::WIND_ROT::WIND_LEFT:
		{
			particle->SetPos(D3DXVECTOR3(CManager::SCREEN_WIDTH, FloatRandam(0.0f, CManager::SCREEN_HEIGHT), 0.0f));
			particle->SetMovePos(D3DXVECTOR3(FloatRandam(-10.0f,-30.0f), FloatRandam(1.0f, -1.0f), 0.0f));
			particle->SetMoveSize(D3DXVECTOR3(-0.35f, -0.35f, 0.0f));
			particle->SetMoveRot(D3DXVECTOR3(0.0f, 0.0f, 0.05f));
			particle->SetTexture(CTexture::TEXTURE_HANABIRA);
			particle->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		}
		break;
		case CWind::WIND_ROT::WIND_RIGHT:
		{
			particle->SetPos(D3DXVECTOR3(0.0f, FloatRandam(0.0f, CManager::SCREEN_HEIGHT), 0.0f));
			particle->SetMovePos(D3DXVECTOR3(FloatRandam(30.0f, 10.0f), FloatRandam(1.0f, -1.0f), 0.0f));
			particle->SetMoveSize(D3DXVECTOR3(-0.35f, -0.35f, 0.0f));
			particle->SetMoveRot(D3DXVECTOR3(0.0f, 0.0f, 0.05f));
			particle->SetTexture(CTexture::TEXTURE_HANABIRA);

			float randam = FloatRandam(1.0f, 0.0f);
			if (randam < 0.55f)
			{
				particle->SetCol(D3DXCOLOR(1.0f, 0.25f, 0.0f, 1.0f));
			}
			else
			{
				particle->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
			}
		}
		break;
		default:
			break;
		}
	}
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
