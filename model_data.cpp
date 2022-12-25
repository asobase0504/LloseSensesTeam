//==================================================
// model_data.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include "manager.h"
#include "renderer.h"

#include "model_data.h"

//**************************************************
// ��`
//**************************************************
const char* CModelData::s_FileName[] =
{// �e�N�X�`���̃p�X
	"data/MODEL/player/body.x",			// ��
	"data/MODEL/player/head.x",			// ��
	"data/MODEL/player/right_arm.x",	// �E�r
	"data/MODEL/player/left_arm.x",		// ���r
	"data/MODEL/player/board.x",		// ��
	"data/MODEL/player/left_thigh.x",	// ��������
	"data/MODEL/player/right_thigh.x",	// �E������
	"data/MODEL/player/left_leg.x",		// ����
	"data/MODEL/player/right_leg.x",	// �E��
	"data/MODEL/ball.x",				// ��
	"data/MODEL/cube4.x",				// �M�~�b�N
	"data/MODEL/gimmick/goal.x",		// �S�[��
};

static_assert(sizeof(CModelData::s_FileName) / sizeof(CModelData::s_FileName[0]) == CModelData::MODEL_MAX, "aho");

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CModelData::CModelData() : m_model()
{
	memset(m_model, 0, sizeof(m_model));
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CModelData::~CModelData()
{
}

//--------------------------------------------------
// �S�Ă̓ǂݍ���
//--------------------------------------------------
void CModelData::LoadAll()
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCnt = 0; nCnt < MODEL_MAX; ++nCnt)
	{// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(s_FileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_model[nCnt].buffMat,
			NULL,
			&m_model[nCnt].numMat,
			&m_model[nCnt].mesh);

		// �o�b�t�@�̐擪�|�C���^��D3DXMATERIAL�ɃL���X�g���Ď擾
		D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_model[nCnt].buffMat->GetBufferPointer();

		// �e���b�V���̃}�e���A�������擾����
		for (int i = 0; i < (int)m_model[i].numMat; i++)
		{
			m_model[nCnt].texture[i] = NULL;

			if (pMat[i].pTextureFilename != NULL)
			{// �}�e���A���Őݒ肳��Ă���e�N�X�`���ǂݍ���
				D3DXCreateTextureFromFileA(pDevice,
					pMat[i].pTextureFilename,
					&m_model[nCnt].texture[i]);
			}
		}

		int nNumVtx;		// ���_��
		DWORD pSizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;		// ���_�o�b�t�@�̃|�C���^

		// ���_���̎擾
		nNumVtx = m_model[nCnt].mesh->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾
		pSizeFVF = D3DXGetFVFVertexSize(m_model[nCnt].mesh->GetFVF());

		// ���_�o�b�t�@�̃��b�N
		m_model[nCnt].mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			// ���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			// ��r(�ŏ��l�����߂�)x
			if (vtx.x < m_model[nCnt].vtxMin.x)
			{
				m_model[nCnt].vtxMin.x = vtx.x;
			}
			// ��r(�ŏ��l�����߂�)y
			if (vtx.y < m_model[nCnt].vtxMin.y)
			{
				m_model[nCnt].vtxMin.y = vtx.y;
			}
			// ��r(�ŏ��l�����߂�)z
			if (vtx.z < m_model[nCnt].vtxMin.z)
			{
				m_model[nCnt].vtxMin.z = vtx.z;
			}

			// ��r(�ő�l�����߂�)x
			if (vtx.x > m_model[nCnt].vtxMax.x)
			{
				m_model[nCnt].vtxMax.x = vtx.x;
			}
			// ��r(�ő�l�����߂�)y
			if (vtx.y > m_model[nCnt].vtxMax.y)
			{
				m_model[nCnt].vtxMax.y = vtx.y;
			}
			// ��r(�ő�l�����߂�)z
			if (vtx.z > m_model[nCnt].vtxMax.z)
			{
				m_model[nCnt].vtxMax.z = vtx.z;
			}

			// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += pSizeFVF;
		}

		// �T�C�Y�̌v�Z
		m_model[nCnt].size = m_model[nCnt].vtxMax - m_model[nCnt].vtxMin;

		// ���_�o�b�t�@�̃A�����b�N
		m_model[nCnt].mesh->UnlockVertexBuffer();
	}
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CModelData::Load(MODEL_TYPE inModel)
{
	if (m_model[inModel].mesh != nullptr)
	{// �e�N�X�`���̓ǂݍ��݂�����Ă���
		return;
	}

	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(s_FileName[inModel],
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_model[inModel].buffMat,
		NULL,
		&m_model[inModel].numMat,
		&m_model[inModel].mesh);

	// �o�b�t�@�̐擪�|�C���^��D3DXMATERIAL�ɃL���X�g���Ď擾
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_model[inModel].buffMat->GetBufferPointer();

	// �e���b�V���̃}�e���A�������擾����
	for (int i = 0; i < (int)m_model[inModel].numMat; i++)
	{
		m_model[inModel].texture[i] = NULL;

		if (pMat[i].pTextureFilename != NULL)
		{// �}�e���A���Őݒ肳��Ă���e�N�X�`���ǂݍ���
			D3DXCreateTextureFromFileA(pDevice,
				pMat[i].pTextureFilename,
				&m_model[inModel].texture[i]);
		}
	}

	int nNumVtx;		// ���_��
	DWORD pSizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_�o�b�t�@�̃|�C���^

	// ���_���̎擾
	nNumVtx = m_model[inModel].mesh->GetNumVertices();

	// ���_�t�H�[�}�b�g�̃T�C�Y���擾
	pSizeFVF = D3DXGetFVFVertexSize(m_model[inModel].mesh->GetFVF());

	// ���_�o�b�t�@�̃��b�N
	m_model[inModel].mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		// ���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		// ��r(�ŏ��l�����߂�)x
		if (vtx.x < m_model[inModel].vtxMin.x)
		{
			m_model[inModel].vtxMin.x = vtx.x;
		}
		// ��r(�ŏ��l�����߂�)y
		if (vtx.y < m_model[inModel].vtxMin.y)
		{
			m_model[inModel].vtxMin.y = vtx.y;
		}
		// ��r(�ŏ��l�����߂�)z
		if (vtx.z < m_model[inModel].vtxMin.z)
		{
			m_model[inModel].vtxMin.z = vtx.z;
		}

		// ��r(�ő�l�����߂�)x
		if (vtx.x > m_model[inModel].vtxMax.x)
		{
			m_model[inModel].vtxMax.x = vtx.x;
		}
		// ��r(�ő�l�����߂�)y
		if (vtx.y > m_model[inModel].vtxMax.y)
		{
			m_model[inModel].vtxMax.y = vtx.y;
		}
		// ��r(�ő�l�����߂�)z
		if (vtx.z > m_model[inModel].vtxMax.z)
		{
			m_model[inModel].vtxMax.z = vtx.z;
		}

		// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += pSizeFVF;
	}

	// �T�C�Y�̌v�Z
	m_model[inModel].size = m_model[inModel].vtxMax - m_model[inModel].vtxMin;

	// ���_�o�b�t�@�̃A�����b�N
	m_model[inModel].mesh->UnlockVertexBuffer();
}

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CModelData::ReleaseAll()
{
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		for (int i = 0; i < (int)m_model[nCnt].numMat; i++)
		{
			if (m_model[nCnt].texture[i] != nullptr)
			{// �e�N�X�`���̉��
				m_model[nCnt].texture[i]->Release();
				m_model[nCnt].texture[i] = nullptr;
			}
		}

		// ���b�V���̔j��
		if (m_model[nCnt].mesh != nullptr)
		{
			m_model[nCnt].mesh->Release();
			m_model[nCnt].mesh = nullptr;
		}

		// �}�e���A���̉��
		if (m_model[nCnt].buffMat != nullptr)
		{
			m_model[nCnt].buffMat->Release();
			m_model[nCnt].buffMat = nullptr;
		}
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CModelData::Release(MODEL_TYPE inModel)
{
	assert(inModel >= 0 && inModel < MODEL_MAX);

	for (int i = 0; i < (int)m_model[inModel].numMat; i++)
	{
		if (m_model[inModel].texture[i] != nullptr)
		{// �e�N�X�`���̉��
			m_model[inModel].texture[i]->Release();
			m_model[inModel].texture[i] = nullptr;
		}
	}

	// ���b�V���̔j��
	if (m_model[inModel].mesh != nullptr)
	{
		m_model[inModel].mesh->Release();
		m_model[inModel].mesh = nullptr;
	}

	// �}�e���A���̉��
	if (m_model[inModel].buffMat != nullptr)
	{
		m_model[inModel].buffMat->Release();
		m_model[inModel].buffMat = nullptr;
	}
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
CModelData::MODEL CModelData::GetModel(MODEL_TYPE inModel)
{
	assert(inModel >= 0 && inModel < MODEL_MAX);

	// �ǂݍ���
	Load(inModel);

	return m_model[inModel];
}
