//==================================================
// meshfilde.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include "manager.h"
#include "input_keyboard.h"

#include "game.h"
#include "utility.h"
#include "debug_proc.h"

#include "meshfield.h"

//**************************************************
// �}�N����`
//**************************************************
#define SIN_SIZE				(-500.0f)
#define SIN_ROT					(3.5f)

#define ACCEL_FACTOR			(9.8f / 4.0f)

//**************************************************
// �萔��`
//**************************************************
// ���_�t�H�[�}�b�g
const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);		// ���W�E�@���E�J���[�E�e�N�X�`��

//**************************************************
// �\���̒�`
//**************************************************
// ���_�̏��[3D]�̍\���̂��`
struct VERTEX_3D
{
	D3DXVECTOR3 pos;	// ���_���W	
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;		// ���_�J���[	
	D3DXVECTOR2 tex;	// �e�N�X�`���̍��W
};

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CMeshField::CMeshField(int nPriority /* =1 */) : CObject(nPriority)
{
	// �^�C�v�ݒ�
	SetType(TYPE_ROAD);
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CMeshField::~CMeshField()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CMeshField::Init()
{
	{// ������
	 // ���[���h�}�g���b�N�X
		D3DXMatrixIdentity(&m_mtxWorld);
		// ���_�o�b�t�@�ւ̃|�C���^
		m_pVtxBuff = nullptr;
		// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
		m_pIdxBuff = nullptr;
		// �ʒu
		m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// �ړ���
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// ��]
		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// �T�C�Y
		m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// ����
		m_height = 0.0f;
		// ��]�p�x
		m_rotationAngle = 0.0f;
		// �ړI�̉�]�p�x
		m_rotationAngleDest = 0.0f;
		// �p����]���x�N�g��
		m_postureVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// �ړI�̎p����]���x�N�g��
		m_postureVecDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// ��ӂ̖̂ʐ�
		m_nMeshOneSideNumber = 0;
		// ���b�V���̒��_��
		m_nMeshVtx = 0;
		// ���b�V���̃C���f�b�N�X��
		m_nMeshIdx = 0;
		// ���b�V���̃|���S����
		m_nMeshPrimitive = 0;
		// ���b�V���̑傫��X
		m_fMeshSizeX = 0.0f;
		// ���b�V���̑傫��Z
		m_fMeshSizeZ = 0.0f;
	}

	// ���b�V���̓ǂݍ���
	Load("data/TEXT/mesh.json");

	// �@���̌v�Z
	NorCalculation_();

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CMeshField::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{// ���_�o�b�t�@�̔j��
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	if (m_pIdxBuff != nullptr)
	{// �C���f�b�N�X�o�b�t�@�̔j��
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}

	CObject::DeletedObj();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CMeshField::Update()
{

	NorCalculation_();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CMeshField::Draw()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CTexture* pTexture = CManager::GetTexture();
	D3DXMATRIX mtxRot, mtxTrans;								//�v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f								��rot�̏����g���ĉ�]�s������
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);		//�s��|���Z�֐�		������ * ��O���� ���@�������Ɋi�[

	// �ʒu�𔽉f								��pos�̏����g���Ĉړ��s������
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�VERTEX_3D
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nMeshVtx, 0, m_nMeshPrimitive);

	// �e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CMeshField* CMeshField::Create()
{
	CMeshField *pMeshField;
	pMeshField = new CMeshField;

	if (pMeshField != nullptr)
	{
		pMeshField->Init();
	}
	else
	{
		assert(false);
	}

	return pMeshField;
}

//--------------------------------------------------
// �����蔻��
//--------------------------------------------------
void CMeshField::CollisionMesh(D3DXVECTOR3 *pPos)
{
	D3DXVECTOR3 pos = GetPos();

	int primitive = m_nMeshPrimitive;
	VERTEX_3D* pVtx = NULL;			// ���_���ւ̃|�C���^
	WORD* pIdx;
	const int nTri = 3;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// �C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < primitive; nCnt++)
	{
		D3DXVECTOR3 posPoly[nTri];

		// ���_���W�̎擾
		posPoly[0] = pVtx[pIdx[nCnt + 0]].pos;
		posPoly[1] = pVtx[pIdx[nCnt + 1]].pos;
		posPoly[2] = pVtx[pIdx[nCnt + 2]].pos;

		if ((pIdx[nCnt + 0] == pIdx[nCnt + 1]) ||
			(pIdx[nCnt + 0] == pIdx[nCnt + 2]) ||
			(pIdx[nCnt + 2] == pIdx[nCnt + 1]))
		{// �k�ރ|���S�����΂�
			continue;
		}

		// ���[�J�����烏�[���h�ɕϊ�
		D3DXVec3TransformCoord(&posPoly[0], &posPoly[0], &m_mtxWorld);
		D3DXVec3TransformCoord(&posPoly[1], &posPoly[1], &m_mtxWorld);
		D3DXVec3TransformCoord(&posPoly[2], &posPoly[2], &m_mtxWorld);

		D3DXVECTOR3 vecLine[nTri];

		// ���_���W�̎擾
		vecLine[0] = posPoly[1] - posPoly[0];
		vecLine[1] = posPoly[2] - posPoly[1];
		vecLine[2] = posPoly[0] - posPoly[2];

		D3DXVECTOR3 vecPlayer[nTri];

		// ���_���W�̎擾
		vecPlayer[0] = *pPos - posPoly[0];
		vecPlayer[1] = *pPos - posPoly[1];
		vecPlayer[2] = *pPos - posPoly[2];

		float InOut[nTri];

		InOut[0] = Vec2Cross(&vecLine[0], &vecPlayer[0]);
		InOut[1] = Vec2Cross(&vecLine[1], &vecPlayer[1]);
		InOut[2] = Vec2Cross(&vecLine[2], &vecPlayer[2]);

		if ((InOut[0] > 0 && InOut[1] > 0 && InOut[2] > 0)
			|| (InOut[0] < 0 && InOut[1] < 0 && InOut[2] < 0))
		{
			D3DXVECTOR3 V1 = posPoly[1] - posPoly[0];
			D3DXVECTOR3 V2 = posPoly[2] - posPoly[0];

			// ���ʂ̔�
			D3DXVECTOR3 vecNormal;
			// ���b�V���̖@�������߂�
			D3DXVec3Cross(&vecNormal, &V1, &V2);
			// �傫�����P�ɂ���
			D3DXVec3Normalize(&vecNormal, &vecNormal);

			if (nCnt % 2 == 1)
			{// �@���x�N�g���̌����𐳂�
				vecNormal *= -1;
			}

			// ���������I�u�W�F�N�g�̈ʒu��ݒ�
			pPos->y = posPoly[0].y - (vecNormal.x * (pPos->x - posPoly[0].x) + vecNormal.z * (pPos->z - posPoly[0].z)) / vecNormal.y;
		}
	}

	// �C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
	// ���_�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();
}

//--------------------------------------------------
// ���_�̏グ����
//--------------------------------------------------
void CMeshField::UpVtxMesh(D3DXVECTOR3 *pPos)
{
	D3DXVECTOR3 pos = GetPos();
	CInputKeyboard *pInputKeyoard = CManager::GetInputKeyboard();

	int primitive = m_nMeshPrimitive;
	VERTEX_3D* pVtx = NULL;			// ���_���ւ̃|�C���^
	WORD* pIdx;
	const int nTri = 3;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// �C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < primitive; nCnt++)
	{
		D3DXVECTOR3 posPoly[nTri];

		// ���_���W�̎擾
		posPoly[0] = pVtx[pIdx[nCnt + 0]].pos;
		posPoly[1] = pVtx[pIdx[nCnt + 1]].pos;
		posPoly[2] = pVtx[pIdx[nCnt + 2]].pos;

		if ((pIdx[nCnt + 0] == pIdx[nCnt + 1]) ||
			(pIdx[nCnt + 0] == pIdx[nCnt + 2]) ||
			(pIdx[nCnt + 2] == pIdx[nCnt + 1]))
		{// �k�ރ|���S�����΂�
			continue;
		}

		// ���[�J�����烏�[���h�ɕϊ�
		D3DXVec3TransformCoord(&posPoly[0], &posPoly[0], &m_mtxWorld);
		D3DXVec3TransformCoord(&posPoly[1], &posPoly[1], &m_mtxWorld);
		D3DXVec3TransformCoord(&posPoly[2], &posPoly[2], &m_mtxWorld);

		D3DXVECTOR3 vecLine[nTri];

		// ���_���W�̎擾
		vecLine[0] = posPoly[1] - posPoly[0];
		vecLine[1] = posPoly[2] - posPoly[1];
		vecLine[2] = posPoly[0] - posPoly[2];

		D3DXVECTOR3 vecPlayer[nTri];

		// ���_���W�̎擾
		vecPlayer[0] = *pPos - posPoly[0];
		vecPlayer[1] = *pPos - posPoly[1];
		vecPlayer[2] = *pPos - posPoly[2];

		float InOut[nTri];

		InOut[0] = Vec2Cross(&vecLine[0], &vecPlayer[0]);
		InOut[1] = Vec2Cross(&vecLine[1], &vecPlayer[1]);
		InOut[2] = Vec2Cross(&vecLine[2], &vecPlayer[2]);

		if ((InOut[0] > 0 && InOut[1] > 0 && InOut[2] > 0)
			|| (InOut[0] < 0 && InOut[1] < 0 && InOut[2] < 0))
		{
			if (pInputKeyoard->GetPress(DIK_I))
			{// UP
				pVtx[pIdx[nCnt + 0]].pos.y += 1.0f;
				pVtx[pIdx[nCnt + 1]].pos.y += 1.0f;
				pVtx[pIdx[nCnt + 2]].pos.y += 1.0f;
			}
			if (pInputKeyoard->GetPress(DIK_I))
			{// DOWN
				pVtx[pIdx[nCnt + 0]].pos.y += -1.0f;
				pVtx[pIdx[nCnt + 1]].pos.y += -1.0f;
				pVtx[pIdx[nCnt + 2]].pos.y += -1.0f;
			}
		}
	}

	// �C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
	// ���_�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();

}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CMeshField::Load(const char *pFileName)
{
	// �t�@�C���I�[�v��
	std::ifstream ifs(pFileName);

	if (ifs)
	{// �J������
		ifs >> m_JMesh;

		// �ʒu
		D3DXVECTOR3 pos(0.0f, 0.0f, 0.0f);

		// �ʒu�̓ǂݍ���
		m_pos = D3DXVECTOR3(m_JMesh["WORLD_POS"]["POS"]["X"], m_JMesh["WORLD_POS"]["POS"]["Y"], m_JMesh["WORLD_POS"]["POS"]["Z"]);

		// �p�x�̓ǂݍ���
		m_rot = D3DXVECTOR3(m_JMesh["WORLD_ROT"]["ROT"]["X"], m_JMesh["WORLD_ROT"]["ROT"]["Y"], m_JMesh["WORLD_ROT"]["ROT"]["Z"]);

		// ��ӂ̖ʐ��̓ǂݍ���
		m_nMeshOneSideNumber = m_JMesh["MESH_ONESIDE_NUMBER"];

		// �ʂ̃T�C�Y X Z
		m_fMeshSizeX = m_JMesh["MESH_SIZEX"];
		m_fMeshSizeZ = m_JMesh["MESH_SIZEZ"];

		MeshVtxAndIdxCalculation_();

		VERTEX_3D* pVtx = NULL;
		// ���_���W�����b�N
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < m_nMeshVtx; nCnt++)
		{
			// JSON�t�@�C���^�O�ݒ�
			std::string name = "VTX";
			std::string Number = std::to_string(nCnt);
			name += Number;

			// �ʒu�̓ǂݍ���
			pos = D3DXVECTOR3(m_JMesh[name]["POS"]["X"], m_JMesh[name]["POS"]["Y"], m_JMesh[name]["POS"]["Z"]);

			// ���W�̐ݒ�
			pVtx[nCnt].pos = D3DXVECTOR3(pos.x, pos.y, pos.z);

			// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
			pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		// ���_���W���A�����b�N
		m_pVtxBuff->Unlock();
	}
}

//--------------------------------------------------
// ���b�V���̒��_�ƃC���f�b�N�X�̌v�Z
//--------------------------------------------------
void CMeshField::MeshVtxAndIdxCalculation_()
{
	// ���b�V���̒��_��
	m_nMeshVtx = (((m_nMeshOneSideNumber)+1) * ((m_nMeshOneSideNumber)+1));
	// ���b�V���̃C���f�b�N�X��
	m_nMeshIdx = ((m_nMeshOneSideNumber + 1) * 2 * m_nMeshOneSideNumber + (m_nMeshOneSideNumber - 1) * 2);
	// ���b�V���̃|���S���� 
	m_nMeshPrimitive = ((m_nMeshOneSideNumber) * (m_nMeshOneSideNumber) * 2 + 4 * ((m_nMeshOneSideNumber)-1));

	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nMeshVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nMeshIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	// �e�N�X�`���̐ݒ�
	CMeshField::SetTexture(CTexture::TEXTURE_NONE);

	VERTEX_3D* pVtx = NULL;			// ���_���ւ̃|�C���^
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int z = 0; z < (m_nMeshOneSideNumber + 1); z++)
	{
		for (int x = 0; x < (m_nMeshOneSideNumber + 1); x++)
		{
			pVtx[x + z * (m_nMeshOneSideNumber + 1)].pos = D3DXVECTOR3(x * m_fMeshSizeX, 0.0f, -z * m_fMeshSizeZ);
			pVtx[x + z * (m_nMeshOneSideNumber + 1)].pos.x -= m_nMeshOneSideNumber * m_fMeshSizeX * 0.5f;
			//pVtx[x + z * (m_nMeshX + 1)].pos.y = sinf(x * D3DXToRadian(SIN_ROT) + m_height) * SIN_SIZE;
			pVtx[x + z * (m_nMeshOneSideNumber + 1)].pos.z += m_nMeshOneSideNumber * m_fMeshSizeZ * 0.5f;
			pVtx[x + z * (m_nMeshOneSideNumber + 1)].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[x + z * (m_nMeshOneSideNumber + 1)].col = D3DXCOLOR(1.0f, 1.0f, 0.7f, 1.0f);
			pVtx[x + z * (m_nMeshOneSideNumber + 1)].tex = D3DXVECTOR2((float)1.0f / m_nMeshOneSideNumber * x, (float)1.0f / m_nMeshOneSideNumber * z);
		}
	}

	WORD* pIdx;

	// �C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int z = 0; z < m_nMeshOneSideNumber; z++)
	{// z�̕���
		int nLineTop = z * ((m_nMeshOneSideNumber + 1) * 2 + 2);
		for (int x = 0; x < m_nMeshOneSideNumber + 1; x++)
		{// x�̕���
		 // �����Ԗ�
			pIdx[(x * 2) + nLineTop] = (WORD)((m_nMeshOneSideNumber + 1) + x + z * (m_nMeshOneSideNumber + 1));
			// ��Ԗ�
			pIdx[(x * 2 + 1) + nLineTop] = (WORD)(pIdx[(x * 2) + nLineTop] - (m_nMeshOneSideNumber + 1));
		}
		// �k�ރ|���S��(�����A�����鎞)
		if (z < m_nMeshOneSideNumber - 1)
		{
			pIdx[(m_nMeshOneSideNumber + 1) * 2 + nLineTop] = (WORD)(m_nMeshOneSideNumber + (m_nMeshOneSideNumber + 1) * z);
			pIdx[(m_nMeshOneSideNumber + 1) * 2 + 1 + nLineTop] = (WORD)((m_nMeshOneSideNumber + 1) * (2 + z));
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	// �C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();
}

//--------------------------------------------------
// �@���̌v�Z
//--------------------------------------------------
void CMeshField::NorCalculation_()
{
	// �O�p�`�̒��_��
	const int nTri = 3;
	// ���O�v�����Ȃ�
	D3DXVECTOR3 posCorner[nTri];
	// primitive��ۑ�
	int primitive = m_nMeshPrimitive;

	// ���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;
	WORD* pIdx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// �C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int i = 0; i < m_nMeshVtx; i++)
	{// ���_����������
		pVtx[i].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	for (int nCnt = 0; nCnt < primitive; nCnt++)
	{// �e���_�̍��W���擾
		posCorner[0] = pVtx[pIdx[nCnt + 0]].pos;
		posCorner[1] = pVtx[pIdx[nCnt + 1]].pos;
		posCorner[2] = pVtx[pIdx[nCnt + 2]].pos;

		if ((pIdx[nCnt + 0] == pIdx[nCnt + 1]) ||
			(pIdx[nCnt + 0] == pIdx[nCnt + 2]) ||
			(pIdx[nCnt + 2] == pIdx[nCnt + 1]))
		{// �k�ރ|���S�����Ƃ΂�
			continue;
		}

		// �|���h�������̃x�N�g�������
		D3DXVECTOR3 V1 = posCorner[1] - posCorner[0];
		D3DXVECTOR3 V2 = posCorner[2] - posCorner[0];

		// ���߂��@�����i�[���锠
		D3DXVECTOR3 vecNormal;

		if (nCnt % 2 == 0)
		{
			// ���b�V���̖@�������߂�
			D3DXVec3Cross(&vecNormal, &V1, &V2);
		}
		else
		{
			// ���b�V���̖@�������߂�
			D3DXVec3Cross(&vecNormal, &V2, &V1);
		}

		// �傫�����P�ɂ���
		D3DXVec3Normalize(&vecNormal, &vecNormal);

		for (int i = 0; i < nTri; i++)
		{// ���߂��@�����e���_�ɐݒ�
			pVtx[pIdx[nCnt + i]].nor += vecNormal;
		}
	}

	for (int nCnt = 0; nCnt < m_nMeshVtx; nCnt++)
	{// ���ׂĂ̖@���𐳋K������
		D3DXVec3Normalize(&pVtx[nCnt].nor, &pVtx[nCnt].nor);
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	// �C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();
}
