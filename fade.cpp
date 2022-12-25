//==================================================
// fade.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include <assert.h>

#include "manager.h"
#include "fade.h"

//**************************************************
// �ÓI�����o�ϐ�
//**************************************************
CFade *CFade::m_pFade = nullptr;

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CFade::CFade(int nPriority /* =6 */) : CObject2D(nPriority)
{
	m_pObject2D = nullptr;
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CFade::~CFade()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CFade::Init()
{
	CObject2D::Init();

	SetType(TYPE_MODE);
	m_fFadeSpeed = 0.07f;
	m_fMaxAlpha = 0.0f;
	m_fade = FADE_NONE;

	m_pObject2D = CObject2D::Create(
		D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXVECTOR3((float)CManager::SCREEN_WIDTH, (float)CManager::SCREEN_HEIGHT, 0.0f),
		PRIORITY_FADE);
	m_pObject2D->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_pObject2D->SetType(TYPE_MODE);

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CFade::Uninit()
{
	// �����[�X�̓����[�X�I�[���ł���Ă���
	m_pFade = nullptr;

	CObject2D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CFade::Update()
{
	CObject2D::Update();

	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{// ���l�̑���
			m_fMaxAlpha -= m_fFadeSpeed;

			if (m_fMaxAlpha <= 0.0f)
			{// �����O�ȉ��ɂȂ��������
				m_fMaxAlpha = 0.0f;
				m_fade = FADE_NONE;
			}
		}
		else if (m_fade == FADE_OUT)
		{
			m_fMaxAlpha += m_fFadeSpeed;

			if (m_fMaxAlpha >= 1.0f)
			{// ���l���ʒu�𒴂����烂�[�h�ύX
				m_fMaxAlpha = 1.0f;
				m_fade = FADE_IN;
				CManager::SetMode(m_modeNext);
			}
		}
	}

	if (m_pObject2D != nullptr)
	{
		// �F�̕ύX
		m_pObject2D->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_fMaxAlpha));
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CFade::Draw()
{
	CObject2D::Draw();
}

//--------------------------------------------------
// �t�F�[�h�̐ݒ�
//--------------------------------------------------
void CFade::SetFade(CManager::MODE modeNext)
{
	// �t�F�[�h�A�E�g��Ԃ�
	m_fade = FADE_OUT;
	// ���̉�ʂ�ݒ�
	m_modeNext = modeNext;

	if (m_pObject2D != nullptr)
	{
		// �����|���S���ɂ��Ă���
		m_pObject2D->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
}

//--------------------------------------------------
// �V���O���g���̃C���X�^���X�擾
//--------------------------------------------------
CFade *CFade::GetInstance()
{
	if (m_pFade == nullptr)
	{
		m_pFade = new CFade;
		m_pFade->Init();
	}

	return m_pFade;
}
