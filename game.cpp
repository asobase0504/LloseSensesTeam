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

// jsonのinclude
#include "nlohmann/json.hpp"
#include <fstream>

namespace nl = nlohmann;

static nl::json EnemyList;		//　リストの生成
static nl::json PlayerList;		//　リストの生成

//**************************************************
// 静的メンバ変数
//**************************************************
CScore *CGame::m_pScore = nullptr;
CPlayer3D *CGame::m_pPlayer3D = nullptr;
CPause *CGame::m_pPause = nullptr;
CMeshField *CGame::m_pMeshField = nullptr;
CGimmick *CGame::m_pGimmick = nullptr;
CGoal *CGame::m_pGoal = nullptr;
CTimer *CGame::m_pTimer = nullptr;

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

	m_pScore = CScore::Create(D3DXVECTOR3(60.0f, 50.0f, 0.0f), D3DXVECTOR3(30.0f, 60.0f, 0.0f));
	m_pScore->SetScore(0);

	m_pPause = CPause::Create();

	m_pMeshField = CMeshField::Create();
	m_pMeshField->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CGame::Uninit()
{
	//CManager::GetSound()->Stop();

	// スコアの設定
	//CManager::SetNowScore(m_pScore->GetScore());

	// リリースはリリースオールでやってある
	m_pTimer = nullptr;
	m_pScore = nullptr;
	m_pPlayer3D = nullptr;

	CObject::DeletedObj();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CGame::Update()
{
	m_time++;

	CInputKeyboard *pInputKeyoard = CManager::GetInputKeyboard();

	if (pInputKeyoard->GetTrigger(DIK_RETURN))
	{
		// 遷移
		CFade::GetInstance()->SetFade(CManager::MODE_RESULT);
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
