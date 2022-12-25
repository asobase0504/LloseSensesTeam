//==================================================
// camera.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include "debug_proc.h"
#include "manager.h"
#include "game.h"
#include "input_keyboard.h"
#include "input.h"

#include "camera.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CCamera::CCamera()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CCamera::~CCamera()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CCamera::Init()
{
	// ���_�E�����_�E�������ݒ肷��
	m_localPosV = D3DXVECTOR3(0.0f, 300.0f, -550.0f);
	m_localPosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_worldPosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���_
	m_worldPosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����_
	m_posVDest = D3DXVECTOR3(0.0f, 100.0f, -100.0f);	// �ړI�̎��_
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړI�̒����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// �p�x�̏�����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CCamera::Uninit()
{
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CCamera::Update()
{
	CInputKeyboard *pInputKeyoard = CManager::GetInputKeyboard();

	//���_�̐���
	if (pInputKeyoard->GetPress(DIK_Z))
	{
		m_rot.y += 0.01f;
	}
	if (pInputKeyoard->GetPress(DIK_C))
	{
		m_rot.y -= 0.01f;
	}

	//���_�̏㉺
	if (pInputKeyoard->GetPress(DIK_T))
	{
		m_rot.x += 0.01f;
	}
	if (pInputKeyoard->GetPress(DIK_G))
	{
		m_rot.x -= 0.01f;
	}

	//�p�x�̐��K��
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	if (m_rot.x > D3DX_PI)
	{
		m_rot.x -= D3DX_PI * 2.0f;
	}
	else if (m_rot.x < -D3DX_PI)
	{
		m_rot.x += D3DX_PI * 2.0f;
	}

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �����𔽉f								��rot�̏����g���ĉ�]�s������
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);		//�s��|���Z�֐�		������ * ��O���� ���@�������Ɋi�[

	//// �ʒu�𔽉f								��pos�̏����g���Ĉړ��s������
	//D3DXMatrixTranslation(&mtxTrans, playerPos.x, playerPos.y, playerPos.z);
	//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	D3DXVec3TransformCoord(&m_worldPosV, &m_localPosV, &mtxWorld);
	D3DXVec3TransformCoord(&m_worldPosR, &m_localPosR, &mtxWorld);

	//// �����_�̎Z�o
	//m_posV.z = m_posR.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDis;
	//m_posV.x = m_posR.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDis;
	//m_posV.y = m_posR.y - cosf(m_rot.x) * m_fDis;

#ifdef _DEBUG
	// �f�o�b�O�\��
	CDebugProc::Print("���_ : \n x : %f , y : %f , z : %f \n", m_worldPosV.x, m_worldPosV.y, m_worldPosV.z);
	CDebugProc::Print("�����_ : \n x : %f , y : %f , z : %f \n\n", m_worldPosR.x, m_worldPosR.y, m_worldPosR.z);
#endif // DEBUG
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CCamera::Set()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_worldPosV,
		&m_worldPosR,
		&m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),								// ����p
		(float)CManager::SCREEN_WIDTH / (float)CManager::SCREEN_HEIGHT,			// �A�X�y�N�g��
		10.0f,												// �j�A
		10000.0f);											// �t�@�[

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}
