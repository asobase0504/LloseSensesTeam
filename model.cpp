//==================================================
// model.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include <assert.h>

#include "utility.h"

#include "manager.h"

#include "model.h"
#include "light.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CModel::CModel()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CModel::~CModel()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CModel::Init(CModelData::MODEL_TYPE modelData)
{
	m_modelData = modelData;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_isStencil = false;

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CModel::Uninit()
{
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CModel::Update()
{
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CModel::Draw(D3DXMATRIX *mtxWorld)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CModelData* modelData = CManager::GetModelData();
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxScale, mtxParent;
	// ���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;
	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;

	if (m_isStencil)
	{
		// �X�e���V���o�b�t�@ -> �L��
		pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

		// �X�e���V���o�b�t�@�Ɣ�r����Q�ƒl�ݒ� -> ref
		pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

		// �X�e���V���o�b�t�@�̒l�ɑ΂��Ẵ}�X�N�ݒ� -> 0xff(�S�Đ^)
		pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

		// �X�e���V���e�X�g�̔�r���@ ->
		// �i�Q�ƒl >= �X�e���V���o�b�t�@�̎Q�ƒl�j�Ȃ獇�i
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);

		// �X�e���V���e�X�g�̌��ʂɑ΂��Ă̔��f�ݒ�
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);		// Z�ƃX�e���V������
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);			// Z�ƃX�e���V�����s
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);			// Z�̂ݎ��s
	}
	else
	{
		// �X�e���V���o�b�t�@ -> ����
		pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	}

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �s��g�k�֐�
	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != nullptr)
	{
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{
		mtxParent = *mtxWorld;
	}

	// �}�g���b�N�X�̊|���Z
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

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

	// �X�e���V���o�b�t�@ -> ����
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	DrawShadow_();
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CModel *CModel::Create(CModelData::MODEL_TYPE modelData)
{
	CModel *pModel;
	pModel = new CModel;

	if (pModel != nullptr)
	{
		pModel->Init(modelData);
	}
	else
	{
		assert(false);
	}

	return pModel;
}

//--------------------------------------------------
// �e�̕`��
//--------------------------------------------------
void CModel::DrawShadow_()
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
	pDevice->SetRenderState(D3DRS_AMBIENT, 0);

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
	pDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
}
