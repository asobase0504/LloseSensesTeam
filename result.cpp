//==================================================
// result.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include <assert.h>

#include "manager.h"
#include "input_keyboard.h"

#include "object2D.h"
#include "result.h"
#include "fade.h"
#include "sound.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CResult::CResult()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CResult::~CResult()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CResult::Init()
{
	m_pObject2D[0] = CObject2D::Create(
		D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXVECTOR3((float)CManager::SCREEN_WIDTH, (float)CManager::SCREEN_HEIGHT, 0.0f),
		PRIORITY_BG);
	m_pObject2D[0]->SetTexture(CTexture::TEXTURE_TITLE_BG);

	m_pObject2D[1] = CObject2D::Create(
		D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f),
		PRIORITY_BG);
	m_pObject2D[1]->SetTexture(CTexture::TEXTURE_RESULT);

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CResult::Uninit()
{
	CObject::DeletedObj();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CResult::Update()
{
	CInputKeyboard *pInputKeyoard = CManager::GetInputKeyboard();

	if (pInputKeyoard->GetTrigger(DIK_RETURN))
	{
		// �T�E���h
		CManager::GetSound()->Play(CSound::LABEL_SE_ENTER);

		CFade::GetInstance()->SetFade(CManager::MODE_TITLE);
	}
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CResult* CResult::Create()
{
	CResult *pResult;
	pResult = new CResult;

	if (pResult != nullptr)
	{
		pResult->Init();
	}
	else
	{
		assert(false);
	}

	return pResult;
}
