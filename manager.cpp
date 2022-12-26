//==================================================
// manager.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include <time.h>
#include <assert.h>

#include "manager.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "model_data.h"
#include "debug_proc.h"
#include "sound.h"

#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "ranking.h"

#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "model.h"

#include "meshfield.h"

//**************************************************
// �ÓI�����o�ϐ�
//**************************************************
CRenderer *CManager::m_pRenderer = nullptr;
CInputKeyboard *CManager::m_pInputKeyboard = nullptr;
CInputJoyPad *CManager::m_pInputJoyPad = nullptr;
CTexture *CManager::m_pTexture = nullptr;
CModelData *CManager::m_pModelData = nullptr;
CCamera *CManager::m_pCamera = nullptr;
CLight *CManager::m_pLight = nullptr;
CManager *CManager::m_pManager = nullptr;
CObject *CManager::m_pGameMode = nullptr;
CDebugProc *CManager::m_pDebug = nullptr;
CSound *CManager::m_pSound = nullptr;
CManager::MODE CManager::m_mode = MODE_TITLE;

int CManager::m_nowScore = 0;

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CManager::CManager()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CManager::~CManager()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CManager::Init(const HINSTANCE hInstance, const HWND hWnd)
{
	// �^�������̏�����
	srand((unsigned int)time(NULL));

	m_pTexture = new CTexture;
	m_pModelData = new CModelData;
	m_pRenderer = new CRenderer;

	// ����������
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))		// ����FALSE�ɂ���ƃt���X�N���[���ɂȂ�TRUE�̓E�B���h�E���[�h
	{//�����������s�����ꍇ
		return -1;
	}

	m_pInputKeyboard = new CInputKeyboard;

	// ����������
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{//�����������s�����ꍇ
		return -1;
	}

	m_pInputJoyPad = new CInputJoyPad;

	// ����������
	if (FAILED(m_pInputJoyPad->Init()))
	{//�����������s�����ꍇ
		return -1;
	}

	m_pSound = new CSound;

	// ����������
	if (FAILED(m_pSound->Init(hWnd)))
	{//�����������s�����ꍇ
		return -1;
	}

	// ����������
	m_pCamera = new CCamera;
	m_pCamera->Init();

	// ����������
	m_pLight = new CLight;
	m_pLight->Init();

	m_pDebug = new CDebugProc;
	m_pDebug->Init();

	SetMode(MODE_TITLE);

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CManager::Uninit()
{
	// ���ׂẴ����[�X
	CObject::ReleaseAll();

	if (m_pRenderer != nullptr)
	{// �I������
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pInputKeyboard != nullptr)
	{// �I������
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	if (m_pInputJoyPad != nullptr)
	{// �I������
		m_pInputJoyPad->Uninit();
		delete m_pInputJoyPad;
		m_pInputJoyPad = nullptr;
	}

	if (m_pTexture != nullptr)
	{// �I������
		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	if (m_pModelData != nullptr)
	{// �I������
		m_pModelData->ReleaseAll();
		delete m_pModelData;
		m_pModelData = nullptr;
	}

	// �J�����I������
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	// ���C�g�I������
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	// �f�o�b�O�̏I������
	if (m_pDebug != nullptr)
	{
		m_pDebug->Uninit();
		delete m_pDebug;
		m_pDebug = nullptr;
	}

	if (m_pSound != nullptr)
	{// �I������
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CManager::Update()
{
	// �X�V����
	m_pInputKeyboard->Update();
	// �X�V����
	m_pInputJoyPad->Update();
	// �J�����̃Z�b�g
	m_pCamera->Update();
	// �X�V����
	m_pRenderer->Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CManager::Draw()
{
	// �`�揈��
	m_pRenderer->Draw();
}

//==================================================
// ����
//==================================================
CManager * CManager::Create(const HINSTANCE hInstance, const HWND hWnd)
{
	assert(m_pManager == nullptr);

	m_pManager = new CManager;

	if (m_pManager != nullptr)
	{
		m_pManager->Init(hInstance, hWnd);
	}
	else
	{
		assert(false);
	}

	return m_pManager;
}

//==================================================
// �Q�[�����[�h�̕ύX
//==================================================
void CManager::SetMode(MODE mode)
{
	if (m_pGameMode != nullptr)
	{// �`�F�b�N
		m_pGameMode->Uninit();
		m_pGameMode = nullptr;
	}

	CManager::GetSound()->Stop();
	m_mode = mode;

	CObject::ReleaseWithoutMode();

	//���݂̉��(���[�h)�̏I������
	switch (m_mode)
	{
	case MODE_TITLE:				// �^�C�g�����
		m_pGameMode = CTitle::Create();
		break;

	case MODE_TUTORIAL:
		m_pGameMode = CTutorial::Create();
		break;

	case MODE_GAME:					// �Q�[�����
		m_pGameMode = CGame::Create();
		break;

	case MODE_GAMEOVER:				// �Q�[�����
		break;

	case MODE_RESULT:				// ���U���g���
		m_pGameMode = CResult::Create();
		break;

	case MODE_RANKING:				// ���U���g���
		CRanking *pRanking;

		pRanking = CRanking::Create();
		pRanking->SetRanking(GetNowScore());

		m_pGameMode = pRanking;
		break;

	default:
		assert(false);
		break;
	}
}
