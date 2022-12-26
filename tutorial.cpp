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

//**************************************************
// 静的メンバ変数
//**************************************************
CPlayer *CTutorial::m_pPlayer = nullptr;
CPause *CTutorial::m_pPause = nullptr;
CWind *CTutorial::m_pWind = nullptr;
CSeason *CTutorial::m_pSeason = nullptr;
CBG *CTutorial::m_pBG = nullptr;

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

	m_pSeason = CSeason::Create(D3DXVECTOR3(620.0f, 50.0f, 0.0f), D3DXVECTOR3(30.0f, 60.0f, 0.0f));
	m_pSeason->Start();

	m_pPlayer = CPlayer::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT - (320.0f * 0.15f), 0.0f), D3DXVECTOR3(820.0f, 820.0f, 0.0f));
	m_pWind = CWind::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.8f, CManager::SCREEN_WIDTH * 0.3f, 0.0f), D3DXVECTOR3(300.0f, 300.0f, 0.0f));

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
