//==================================================
// game.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include <assert.h>

#include "manager.h"
#include "input_keyboard.h"
#include "model.h"
#include "sound.h"
#include "pause.h"

#include "score.h"
#include "game.h"
#include "fade.h"
#include "ranking.h"

#include "meshfield.h"

// json��include
#include "nlohmann/json.hpp"
#include <fstream>

namespace nl = nlohmann;

static nl::json EnemyList;		//�@���X�g�̐���
static nl::json PlayerList;		//�@���X�g�̐���

//**************************************************
// �ÓI�����o�ϐ�
//**************************************************
CScore *CGame::m_pScore = nullptr;
CPlayer3D *CGame::m_pPlayer3D = nullptr;
CPause *CGame::m_pPause = nullptr;
CMeshField *CGame::m_pMeshField = nullptr;
CGimmick *CGame::m_pGimmick = nullptr;
CGoal *CGame::m_pGoal = nullptr;
CTimer *CGame::m_pTimer = nullptr;

//**************************************************
// �}�N����`
//**************************************************

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CGame::CGame()
{
	m_time = 0;
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CGame::~CGame()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CGame::Init()
{
	m_time = 0;

	m_pScore = CScore::Create(D3DXVECTOR3(60.0f, 50.0f, 0.0f), D3DXVECTOR3(30.0f, 60.0f, 0.0f));
	m_pScore->SetScore(0);

	m_pPause = CPause::Create();

	m_pMeshField = CMeshField::Create();
	m_pMeshField->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CGame::Uninit()
{
	//CManager::GetSound()->Stop();

	// �X�R�A�̐ݒ�
	//CManager::SetNowScore(m_pScore->GetScore());

	// �����[�X�̓����[�X�I�[���ł���Ă���
	m_pTimer = nullptr;
	m_pScore = nullptr;
	m_pPlayer3D = nullptr;

	CObject::DeletedObj();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CGame::Update()
{
	m_time++;

	CInputKeyboard *pInputKeyoard = CManager::GetInputKeyboard();

	if (pInputKeyoard->GetTrigger(DIK_RETURN))
	{
		// �J��
		CFade::GetInstance()->SetFade(CManager::MODE_RESULT);
	}
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CGame* CGame::Create()
{
	CGame *pGame;
	pGame = new CGame;

	if (pGame != nullptr)
	{
		pGame->Init();
	}
	else
	{
		assert(false);
	}

	return pGame;
}
