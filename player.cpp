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
// �R���X�g���N�^
//--------------------------------------------------
CPlayer::CPlayer()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CPlayer::~CPlayer()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CPlayer::Init()
{
	CObject2D::Init();

	return S_OK;
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CPlayer::Update()
{
	CObject2D::Update();
	Control_();
}

//--------------------------------------------------
// ����
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
// ����
//--------------------------------------------------
void CPlayer::Control_()
{
	// �C���v�b�g
	CInputKeyboard *pInputKeyoard = CManager::GetInputKeyboard();
	//CInputJoyPad *pInputJoyPad = CManager::GetInputJoyPad();

	D3DXVECTOR3 rot = GetRot();

	if (pInputKeyoard->GetPress(DIK_A))
	{// ��
		rot.z += -0.1f;
	}
	if (pInputKeyoard->GetPress(DIK_D))
	{// �E
		rot.z += 0.1f;
	}

	// �p�x��ݒ�
	SetRot(rot);
}
