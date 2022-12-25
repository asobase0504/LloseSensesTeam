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

//**************************************************
// 静的メンバ変数
//**************************************************
CScore *CTutorial::m_pScore = nullptr;
CPlayer3D *CTutorial::m_pPlayer3D = nullptr;
CLockOnUIManager *CTutorial::m_pLockOnUIManager = nullptr;

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
	m_time = 0;

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CTutorial::Uninit()
{
	// リリースはリリースオールでやってある
	m_pScore = nullptr;
	m_pPlayer3D = nullptr;
	m_pLockOnUIManager = nullptr;

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
