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
#include "bg.h"
#include "sound.h"
#include "particle.h"
#include "utility.h"

#define SUKINASUUZI (0)

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

	m_pBG = new CBG;
	m_pBG->Init();

	randam = SUKINASUUZI;
	m_pBG->SetTexture(randam);

	// タイトル
	m_pObject2D[1] = CObject2D::Create(
		D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, 200.0f, 0.0f),
		D3DXVECTOR3(500.0f * 2.0f, 100.0f * 2.0f, 0.0f),
		PRIORITY_BG);
	m_pObject2D[1]->SetTexture(CTexture::TEXTURE_TITLE);

	// スタート
	m_pMenu[0] = CObject2D::Create(
		D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT - 250.0f, 0.0f),
		D3DXVECTOR3(200.0f * 2.25f, 50.0f * 2.25f, 0.0f),
		PRIORITY_BG);
	m_pMenu[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pMenu[0]->SetTexture(CTexture::TEXTURE_START);

	// チュートリアル
	m_pMenu[1] = CObject2D::Create(
		D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT - 125.0f, 0.0f),
		D3DXVECTOR3(200.0f * 2.25f, 50.0f * 2.25f, 0.0f),
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

	// 風のパーティクル
	static int cnt = 0;
	cnt++;
	if (cnt % 7 == 0)
	{
		CParticle* particle = CParticle::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f), 50);

		particle->SetPos(D3DXVECTOR3(CManager::SCREEN_WIDTH, FloatRandam(0.0f, CManager::SCREEN_HEIGHT - 20.0f), 0.0f));
		particle->SetMovePos(D3DXVECTOR3(FloatRandam(-10.0f, -30.0f), FloatRandam(2.0f, -1.0f), 0.0f));
		particle->SetMoveSize(D3DXVECTOR3(-0.35f, -0.35f, 0.0f));
		particle->SetMoveRot(D3DXVECTOR3(0.0f, 0.0f, 0.05f));
		particle->SetTexture(CTexture::TEXTURE_HANABIRA);

		switch (randam)
		{
		case 0:
			particle->SetTexture(CTexture::TEXTURE_HANABIRA);
			break;
		case 1:
			particle->SetTexture(CTexture::TEXTURE_HANABIRA);
			particle->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			break;
		case 2:
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
		case 3:
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
