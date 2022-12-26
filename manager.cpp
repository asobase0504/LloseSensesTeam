//==================================================
// manager.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include <time.h>
#include <assert.h>

#include "manager.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "model_data.h"
#include "debug_proc.h"
#include "sound.h"

#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "ranking.h"

#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "model.h"

#include "meshfield.h"

//**************************************************
// 静的メンバ変数
//**************************************************
CRenderer *CManager::m_pRenderer = nullptr;
CInputKeyboard *CManager::m_pInputKeyboard = nullptr;
CInputJoyPad *CManager::m_pInputJoyPad = nullptr;
CTexture *CManager::m_pTexture = nullptr;
CModelData *CManager::m_pModelData = nullptr;
CCamera *CManager::m_pCamera = nullptr;
CLight *CManager::m_pLight = nullptr;
CManager *CManager::m_pManager = nullptr;
CObject *CManager::m_pGameMode = nullptr;
CDebugProc *CManager::m_pDebug = nullptr;
CSound *CManager::m_pSound = nullptr;
CManager::MODE CManager::m_mode = MODE_TITLE;

int CManager::m_nowScore = 0;

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CManager::CManager()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CManager::~CManager()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CManager::Init(const HINSTANCE hInstance, const HWND hWnd)
{
	// 疑似乱数の初期化
	srand((unsigned int)time(NULL));

	m_pTexture = new CTexture;
	m_pModelData = new CModelData;
	m_pRenderer = new CRenderer;

	// 初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))		// ここFALSEにするとフルスクリーンになるTRUEはウィンドウモード
	{//初期化が失敗した場合
		return -1;
	}

	m_pInputKeyboard = new CInputKeyboard;

	// 初期化処理
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{//初期化が失敗した場合
		return -1;
	}

	m_pInputJoyPad = new CInputJoyPad;

	// 初期化処理
	if (FAILED(m_pInputJoyPad->Init()))
	{//初期化が失敗した場合
		return -1;
	}

	m_pSound = new CSound;

	// 初期化処理
	if (FAILED(m_pSound->Init(hWnd)))
	{//初期化が失敗した場合
		return -1;
	}

	// 初期化処理
	m_pCamera = new CCamera;
	m_pCamera->Init();

	// 初期化処理
	m_pLight = new CLight;
	m_pLight->Init();

	m_pDebug = new CDebugProc;
	m_pDebug->Init();

	SetMode(MODE_TITLE);

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CManager::Uninit()
{
	// すべてのリリース
	CObject::ReleaseAll();

	if (m_pRenderer != nullptr)
	{// 終了処理
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pInputKeyboard != nullptr)
	{// 終了処理
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	if (m_pInputJoyPad != nullptr)
	{// 終了処理
		m_pInputJoyPad->Uninit();
		delete m_pInputJoyPad;
		m_pInputJoyPad = nullptr;
	}

	if (m_pTexture != nullptr)
	{// 終了処理
		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	if (m_pModelData != nullptr)
	{// 終了処理
		m_pModelData->ReleaseAll();
		delete m_pModelData;
		m_pModelData = nullptr;
	}

	// カメラ終了処理
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	// ライト終了処理
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	// デバッグの終了処理
	if (m_pDebug != nullptr)
	{
		m_pDebug->Uninit();
		delete m_pDebug;
		m_pDebug = nullptr;
	}

	if (m_pSound != nullptr)
	{// 終了処理
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CManager::Update()
{
	// 更新処理
	m_pInputKeyboard->Update();
	// 更新処理
	m_pInputJoyPad->Update();
	// カメラのセット
	m_pCamera->Update();
	// 更新処理
	m_pRenderer->Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CManager::Draw()
{
	// 描画処理
	m_pRenderer->Draw();
}

//==================================================
// 生成
//==================================================
CManager * CManager::Create(const HINSTANCE hInstance, const HWND hWnd)
{
	assert(m_pManager == nullptr);

	m_pManager = new CManager;

	if (m_pManager != nullptr)
	{
		m_pManager->Init(hInstance, hWnd);
	}
	else
	{
		assert(false);
	}

	return m_pManager;
}

//==================================================
// ゲームモードの変更
//==================================================
void CManager::SetMode(MODE mode)
{
	if (m_pGameMode != nullptr)
	{// チェック
		m_pGameMode->Uninit();
		m_pGameMode = nullptr;
	}

	CManager::GetSound()->Stop();
	m_mode = mode;

	CObject::ReleaseWithoutMode();

	//現在の画面(モード)の終了処理
	switch (m_mode)
	{
	case MODE_TITLE:				// タイトル画面
		m_pGameMode = CTitle::Create();
		break;

	case MODE_TUTORIAL:
		m_pGameMode = CTutorial::Create();
		break;

	case MODE_GAME:					// ゲーム画面
		m_pGameMode = CGame::Create();
		break;

	case MODE_GAMEOVER:				// ゲーム画面
		break;

	case MODE_RESULT:				// リザルト画面
		m_pGameMode = CResult::Create();
		break;

	case MODE_RANKING:				// リザルト画面
		CRanking *pRanking;

		pRanking = CRanking::Create();
		pRanking->SetRanking(GetNowScore());

		m_pGameMode = pRanking;
		break;

	default:
		assert(false);
		break;
	}
}
