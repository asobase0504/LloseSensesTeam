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
	//CInputJoyPad *pInputJoyPad = CManager::GetInputJoyPad();

	float wind = CGame::GetWind()->GetAirFlow();

	m_rotMove += wind;

	if (pInputKeyoard->GetPress(DIK_A))
	{// 左
		m_rotMove += -0.1f;
	}
	if (pInputKeyoard->GetPress(DIK_D))
	{// 右
		m_rotMove += 0.1f;
	}

	// 傾いてる方向によって角度を足す
	if (m_rotMove > 0.0f)
	{
		m_rotMove += 0.02f;
	}
	if (m_rotMove < 0.0f)
	{
		m_rotMove += -0.02f;
	}

	// 死亡フラグ
	if (m_rotMove > 1.57f || m_rotMove < -1.57f)
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
