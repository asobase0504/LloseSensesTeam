//==================================================
// title.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include <assert.h>

#include "manager.h"
#include "input_keyboard.h"
#include "input_joypad.h"

#include "title.h"
#include "object2D.h"
#include "fade.h"
#include "sound.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CTitle::CTitle()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CTitle::~CTitle()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CTitle::Init()
{
	// サウンド
	CManager::GetSound()->Play(CSound::LABEL_BGM_MAIN);

	// BG
	m_pObject2D[0] = CObject2D::Create(
		D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXVECTOR3((float)CManager::SCREEN_WIDTH, (float)CManager::SCREEN_HEIGHT, 0.0f),
		PRIORITY_BG);
	m_pObject2D[0]->SetTexture(CTexture::TEXTURE_TITLE_BG);

	// タイトル
	m_pObject2D[1] = CObject2D::Create(
		D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, 200.0f, 0.0f),
		D3DXVECTOR3(500.0f * 2.0f, 100.0f * 2.0f, 0.0f),
		PRIORITY_BG);
	m_pObject2D[1]->SetTexture(CTexture::TEXTURE_TITLE);

	// スタート
	m_pMenu[0] = CObject2D::Create(
		D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT - 250.0f, 0.0f),
		D3DXVECTOR3(200.0f * 2.0f, 50.0f * 2.0f, 0.0f),
		PRIORITY_BG);
	m_pMenu[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pMenu[0]->SetTexture(CTexture::TEXTURE_START);

	// チュートリアル
	m_pMenu[1] = CObject2D::Create(
		D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT - 150.0f, 0.0f),
		D3DXVECTOR3(300.0f * 2.0f, 50.0f * 2.0f, 0.0f),
		PRIORITY_BG);
	m_pMenu[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	m_pMenu[1]->SetTexture(CTexture::TEXTURE_TUTORIAL);

	m_nSelect = SELECT_GAMEMODE_START;

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CTitle::Uninit()
{
	CObject::DeletedObj();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CTitle::Update()
{
	CInputKeyboard *pInputKeyoard = CManager::GetInputKeyboard();
	CInputJoyPad *pInputJoyPad = CManager::GetInputJoyPad();

	if (pInputKeyoard->GetTrigger(DIK_W) || pInputJoyPad->GetJoypadTrigger(pInputJoyPad->JOYKEY_UP, 0))
	{
		// サウンド
		CManager::GetSound()->Play(CSound::LABEL_SE_SELECT);

		m_pMenu[m_nSelect]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		m_nSelect--;
		if (m_nSelect < 0)
		{
			m_nSelect = 1;
		}

		m_pMenu[m_nSelect]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else if (pInputKeyoard->GetTrigger(DIK_S) || pInputJoyPad->GetJoypadTrigger(pInputJoyPad->JOYKEY_DOWN, 0))
	{
		// サウンド
		CManager::GetSound()->Play(CSound::LABEL_SE_SELECT);

		m_pMenu[m_nSelect]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		m_nSelect++;
		if (m_nSelect >= 2)
		{
			m_nSelect = 0;
		}

		m_pMenu[m_nSelect]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (pInputKeyoard->GetTrigger(DIK_RETURN) || pInputJoyPad->GetJoypadTrigger(pInputJoyPad->JOYKEY_A, 0))
	{
		// サウンド
		CManager::GetSound()->Play(CSound::LABEL_SE_ENTER);

		switch (m_nSelect)
		{
		case CTitle::SELECT_GAMEMODE_START:
			// 遷移
			CFade::GetInstance()->SetFade(CManager::MODE_GAME);
			break;

		case CTitle::SELECT_GAMEMODE_TUTRIAL:
			// 遷移
			CFade::GetInstance()->SetFade(CManager::MODE_TUTORIAL);
			break;

		default:
			assert(false);

			break;
		}
	}
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CTitle *CTitle::Create()
{
	CTitle *pTitle;
	pTitle = new CTitle;

	if (pTitle != nullptr)
	{
		pTitle->Init();
	}
	else
	{
		assert(false);
	}

	return pTitle;
}
