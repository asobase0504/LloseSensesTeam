//==================================================
// player.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include "manager.h"
#include "debug_proc.h"
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

	if (pInputKeyoard->GetPress(DIK_A))
	{// ��
		m_rotMove += -0.1f;
	}
	if (pInputKeyoard->GetPress(DIK_D))
	{// �E
		m_rotMove += 0.1f;
	}

	if (m_rotMove >= 0.0f)
	{
		m_rotMove += 0.02f;
	}
	if (m_rotMove < 0.0f)
	{
		m_rotMove += -0.02f;
	}

	// �p�x��ݒ�
	SetRot(D3DXVECTOR3(0.0f, 0.0f, m_rotMove));

#ifdef _DEBUG
	CDebugProc::Print("�v���C���[�̊p�x z : %f", m_rotMove);
#endif // DEBUG

}
