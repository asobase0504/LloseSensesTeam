//==================================================
// player.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include "manager.h"
#include "input_keyboard.h"
#include "input_joypad.h"

#include "player.h"

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

	D3DXVECTOR3 rot = GetRot();

	if (pInputKeyoard->GetPress(DIK_A))
	{// 左
		rot.z += -0.1f;
	}
	if (pInputKeyoard->GetPress(DIK_D))
	{// 右
		rot.z += 0.1f;
	}

	// 角度を設定
	SetRot(rot);
}
