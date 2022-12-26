//==================================================
// player.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include "manager.h"
#include "game.h"
#include "debug_proc.h"
#include "input_keyboard.h"
#include "input_joypad.h"

#include "player.h"
#include "wind.h"
#include "fade.h"
#include "tutorial.h"

//**************************************************
// マクロ定義
//**************************************************
#define ROT_MOVE		(0.15f)
#define ROT_DEATH		(1.57f)
#define ROT_GRAVITY		(0.005f)

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CPlayer::CPlayer()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CPlayer::~CPlayer()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CPlayer::Init()
{
	CObject2D::Init();

	m_bDeath = false;
	m_nTime = 0;

	SetTexture(CTexture::TEXTURE_PLAYER);

	return S_OK;
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CPlayer::Update()
{
	CObject2D::Update();
	Control_();

	if (m_bDeath)
	{
		m_nTime++;
		if (m_nTime > 60)
		{
			// 遷移
			CFade::GetInstance()->SetFade(CManager::MODE_RANKING);
		}
	}
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{
		pPlayer->Init();
		pPlayer->SetPos(pos);
		pPlayer->SetSize(size);
	}
	else
	{
		assert(false);
	}

	return pPlayer;
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
void CPlayer::Control_()
{
	// インプット
	CInputKeyboard *pInputKeyoard = CManager::GetInputKeyboard();
	CInputJoyPad *pInputJoyPad = CManager::GetInputJoyPad();

	if (CManager::GetGameMode() == CManager::MODE_TUTORIAL)
	{
		if (CTutorial::GetWind() != nullptr)
		{
			float wind = CTutorial::GetWind()->GetAirFlow();


			m_rotMove += wind;
		}
	}
	else
	{
		if (CGame::GetWind() != nullptr)
		{
			float wind = CGame::GetWind()->GetAirFlow();


			m_rotMove += wind;
		}
	}

	if (!m_bDeath)
	{
		if (pInputKeyoard->GetTrigger(DIK_A) ||
			pInputJoyPad->GetJoypadTrigger(pInputJoyPad->JOYKEY_UP, 0)
			|| pInputJoyPad->GetJoypadTrigger(pInputJoyPad->JOYKEY_DOWN, 0)
			|| pInputJoyPad->GetJoypadTrigger(pInputJoyPad->JOYKEY_LEFT, 0)
			|| pInputJoyPad->GetJoypadTrigger(pInputJoyPad->JOYKEY_RIGHT, 0))
		{// 左
			m_rotMove += -ROT_MOVE;
		}
		if (pInputKeyoard->GetTrigger(DIK_D) ||
			pInputJoyPad->GetJoypadTrigger(pInputJoyPad->JOYKEY_A, 0)
			|| pInputJoyPad->GetJoypadTrigger(pInputJoyPad->JOYKEY_B, 0)
			|| pInputJoyPad->GetJoypadTrigger(pInputJoyPad->JOYKEY_Y, 0)
			|| pInputJoyPad->GetJoypadTrigger(pInputJoyPad->JOYKEY_X, 0))
		{// 右
			m_rotMove += ROT_MOVE;
		}
	}

	// 傾いてる方向によって角度を足す
	if (m_rotMove > 0.0f)
	{
		m_rotMove += ROT_GRAVITY;
	}
	if (m_rotMove < 0.0f)
	{
		m_rotMove += -ROT_GRAVITY;
	}

	// 死亡フラグ
	if (m_rotMove > ROT_DEATH || m_rotMove < -ROT_DEATH)
	{
		m_bDeath = true;
	}

	// 死亡フラグ
	if (m_rotMove > ROT_DEATH)
	{
		m_rotMove = ROT_DEATH;
	}
	if (m_rotMove < -ROT_DEATH)
	{
		m_rotMove = -ROT_DEATH;
	}

	// 角度を設定
	SetRot(D3DXVECTOR3(0.0f, 0.0f, m_rotMove));

#ifdef _DEBUG
	CDebugProc::Print("プレイヤーの角度 z : %f\n\n", m_rotMove);
	//CDebugProc::Print("風の強さ : %f\n\n", wind);
#endif // DEBUG


}
