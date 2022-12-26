//==================================================
// tutorial.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include <assert.h>

#include "manager.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "sound.h"

#include "score.h"
#include "tutorial.h"
#include "fade.h"
#include "ranking.h"

#include "bg.h"
#include "pause.h"
#include "season.h"
#include "player.h"
#include "wind.h"
#include "particle.h"
#include "utility.h"
#include "timer.h"

//**************************************************
// 静的メンバ変数
//**************************************************
CPlayer *CTutorial::m_pPlayer = nullptr;
CPause *CTutorial::m_pPause = nullptr;
CWind *CTutorial::m_pWind = nullptr;
CSeason *CTutorial::m_pSeason = nullptr;
CBG *CTutorial::m_pBG = nullptr;
CTime * CTutorial::m_pTimer = nullptr;

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CTutorial::CTutorial()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CTutorial::~CTutorial()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CTutorial::Init()
{
	CManager::GetSound()->Play(CSound::LABEL_BGM_GAME);
	m_time = 0;

	m_pBG = new CBG;
	m_pBG->Init();

	m_pPause = CPause::Create();

	m_pTimer = CTime::Create(D3DXVECTOR3(520.0f, 50.0f, 0.0f), D3DXVECTOR3(30.0f, 60.0f, 0.0f));
	m_pTimer->Start();

	m_pSeason = CSeason::Create(D3DXVECTOR3(620.0f, 50.0f, 0.0f), D3DXVECTOR3(30.0f, 60.0f, 0.0f));
	m_pSeason->Start();

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CTutorial::Uninit()
{
	// リリースはリリースオールでやってある
	//m_pScore = nullptr;

	CObject::DeletedObj();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CTutorial::Update()
{
	CInputKeyboard *pInputKeyoard = CManager::GetInputKeyboard();
	CInputJoyPad *pInputJoyPad = CManager::GetInputJoyPad();

	if (pInputKeyoard->GetTrigger(DIK_BACKSPACE) || pInputJoyPad->GetJoypadTrigger(pInputJoyPad->JOYKEY_B, 0))
	{
		// サウンド
		CManager::GetSound()->Play(CSound::LABEL_SE_ENTER);

		CFade::GetInstance()->SetFade(CManager::MODE_TITLE);
	}

	if (pInputKeyoard->GetTrigger(DIK_B))
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT - (320.0f * 0.15f), 0.0f), D3DXVECTOR3(820.0f, 820.0f, 0.0f));
		m_pWind = CWind::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.8f, CManager::SCREEN_WIDTH * 0.3f, 0.0f), D3DXVECTOR3(300.0f, 300.0f, 0.0f));
	}

	m_pBG->SetTexture(m_pSeason->GetSeason());

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
// 生成
//--------------------------------------------------
CTutorial* CTutorial::Create()
{
	CTutorial *pTutorial;
	pTutorial = new CTutorial;

	if (pTutorial != nullptr)
	{
		pTutorial->Init();
	}
	else
	{
		assert(false);
	}

	return pTutorial;
}
