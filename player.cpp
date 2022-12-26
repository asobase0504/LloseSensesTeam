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

//**************************************************
// マクロ定義
//**************************************************
#define ROT_MOVE		(0.05f)
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
		// 遷移
		CFade::GetInstance()->SetFade(CManager::MODE_RANKING);
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

	float wind = CGame::GetWind()->GetAirFlow();

	m_rotMove += wind;

	if (pInputKeyoard->GetPress(DIK_A) || pInputJoyPad->GetJoypadPress(pInputJoyPad->JOYKEY_LEFT_SHOULDER, 0))
	{// 左
		m_rotMove += -ROT_MOVE;
	}
	if (pInputKeyoard->GetPress(DIK_D) || pInputJoyPad->GetJoypadPress(pInputJoyPad->JOYKEY_RIGHT_SHOULDER, 0))
	{// 右
		m_rotMove += ROT_MOVE;
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

	// 角度を設定
	SetRot(D3DXVECTOR3(0.0f, 0.0f, m_rotMove));

#ifdef _DEBUG
	CDebugProc::Print("プレイヤーの角度 z : %f\n\n", m_rotMove);
	CDebugProc::Print("風の強さ : %f\n\n", wind);
#endif // DEBUG


}
