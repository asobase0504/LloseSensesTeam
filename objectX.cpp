//==================================================
// objectX.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include <assert.h>

#include "manager.h"
#include "objectX.h"
#include "renderer.h"
#include "camera.h"
#include "light.h"

//**************************************************
// �ÓI�����o�ϐ�
//**************************************************
const float CObjectX::BILLBOARD_HEIGHT = 10.0f;
const float CObjectX::BILLBORAD_WIDTH = 10.0f;

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CObjectX::CObjectX(int nPriority /* =3 */) : CObject(nPriority)
{
	// �ʒu
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// �ߋ��̈ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// ����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// �ŏ��l
	m_vtxMinModel = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	// �ő�l
	m_vtxMaxModel = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	// �傫��
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{// �e�N�X�`���̗񋓌^
		m_texture[nCnt] = nullptr;
	}
	// ���_�o�b�t�@�ւ̃|�C���^
	m_pVtxBuff = nullptr;
	// ���b�V��(���_�̏W�܂�)���ւ̃|�C���^
	m_mesh = nullptr;
	// �}�e���A�����ւ̃|�C���^	���@1��X�t�@�C���ɕ����̃}�e���A���������Ă���
	m_buffMat = nullptr;
	// �}�e���A�����̐�
	m_numMat = NULL;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxRot);
	// �N�H�[�^�j�I���̏�����
	D3DXQuaternionIdentity(&m_quat);
	// �N�H�[�^�j�I�����ǂ���
	m_bQuat = false;

	// ���f���̃f�[�^
	m_modelData = CModelData::MODEL_NONE;
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CObjectX::~CObjectX()
{
	assert(m_pVtxBuff == nullptr);
	assert(m_mesh == nullptr);
	assert(m_buffMat == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CObjectX::Init()
{
	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CObjectX::Uninit()
{
	for (int i = 0; i < (int)m_numMat; i++)
	{
		if (m_texture[i] != nullptr)
		{// �e�N�X�`���̉��
			m_texture[i]->Release();
			m_texture[i] = nullptr;
		}
	}
	// ���b�V���̔j��
	if (m_mesh != nullptr)
	{
		m_mesh->Release();
		m_mesh = nullptr;
	}
	// �}�e���A���̔j��
	if (m_buffMat != nullptr)
	{
		m_buffMat->Release();
		m_buffMat = nullptr;
	}

	CObject::DeletedObj();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CObjectX::Update()
{
	
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CObjectX::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CModelData* modelData = CManager::GetModelData();
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
	// ���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;
	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	if (m_bQuat)
	{// �N�H�[�^�j�I���̎g�p
		// �N�H�[�^�j�I�����쐬
		D3DXQuaternionRotationAxis(&m_quat, &m_vecAxis, m_fValueRot);
		// �N�H�[�^�j�I�������]�}�g���b�N�X���쐬
		D3DXMatrixRotationQuaternion(&mtxRot, &m_quat);
		// 
		D3DXMatrixMultiply(&m_mtxRot, &m_mtxRot, &mtxRot);
		// �s��̊|���Z
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);
	}
	else
	{
		// �����𔽉f							��rot�̏����g���ĉ�]�s������
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);		// �s��|���Z�֐�		������ * ��O���� ���@�������Ɋi�[
	}

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	DrawShadow_();

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A���ێ�
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)modelData->GetModel(m_modelData).buffMat->GetBufferPointer();

	for (int i = 0; i < (int)modelData->GetModel(m_modelData).numMat; i++)
	{
		pMat[i].MatD3D.Ambient = pMat[i].MatD3D.Diffuse;
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[i].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, modelData->GetModel(m_modelData).texture[i]);

		// ���f���p�[�c�̕`��
		modelData->GetModel(m_modelData).mesh->DrawSubset(i);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
}

//--------------------------------------------------
// ���݂̊p�x�̐��K��
//--------------------------------------------------
D3DXVECTOR3 CObjectX::RotNormalization(D3DXVECTOR3 rot)
{
	m_rot = rot;

	// ���݂̊p�x�̐��K��
	if (m_rot.x > D3DX_PI)
	{
		m_rot.x -= D3DX_PI * 2.0f;
	}
	else if (m_rot.x < -D3DX_PI)
	{
		m_rot.x += D3DX_PI * 2.0f;
	}

	// ���݂̊p�x�̐��K��
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}

	// ���݂̊p�x�̐��K��
	if (m_rot.z > D3DX_PI)
	{
		m_rot.z -= D3DX_PI * 2.0f;
	}
	else if (m_rot.z < -D3DX_PI)
	{
		m_rot.z += D3DX_PI * 2.0f;
	}

	return m_rot;
}

//--------------------------------------------------
// �ړI�̊p�x�̐��K��
//--------------------------------------------------
D3DXVECTOR3 CObjectX::RotDestNormalization(D3DXVECTOR3 rot, D3DXVECTOR3 rotDest)
{
	m_rot = rot;
	m_rotDest = rotDest;

	// �ړI�̊p�x�̐��K��
	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{
		m_rotDest.y -= D3DX_PI * 2.0f;
	}
	else if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{
		m_rotDest.y += D3DX_PI * 2.0f;
	}

	return m_rotDest;
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CObjectX *CObjectX::Create()
{
	CObjectX *pObjectX;
	pObjectX = new CObjectX;

	if (pObjectX != nullptr)
	{
		pObjectX->Init();
	}
	else
	{
		assert(false);
	}

	return pObjectX;
}

//--------------------------------------------------
// �e�̕`��
//--------------------------------------------------
void CObjectX::DrawShadow_()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CModelData* modelData = CManager::GetModelData();
	// ���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;
	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;
	D3DXMATRIX mtxShadow;
	D3DXPLANE planeField;
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, normal;

	// �A���r�G���g�𖳌��ɂ���
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_AMBIENT, 0);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);

	// ���C�g������Ă���
	CLight *pLight = CManager::GetLight();

	D3DXVECTOR3 vecDir = pLight->Get().Direction;

	vecLight = D3DXVECTOR4(-vecDir.x, -vecDir.y, -vecDir.z, 0.0f);

	pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	// 
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	// �s��̊|���Z
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	// ���݂̃}�e���A���ێ�
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)modelData->GetModel(m_modelData).buffMat->GetBufferPointer();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	for (int i = 0; i < (int)modelData->GetModel(m_modelData).numMat; i++)
	{
		// �}�e���A�����̐ݒ�
		D3DMATERIAL9 matD3D = pMat[i].MatD3D;

		// ������F�ɐݒ�
		matD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		matD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&matD3D);

		// ���f���p�[�c�̕`��
		modelData->GetModel(m_modelData).mesh->DrawSubset(i);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
	// �A���r�G���g�����Ƃɖ߂�
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
}
