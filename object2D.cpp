//==================================================
// object2D.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include <assert.h>

#include "manager.h"
#include "object2D.h"
#include "renderer.h"

//**************************************************
// �萔��`
//**************************************************
namespace
{
	// �|���S���̕�
	const float POLYGON_WIDTH = 50.0f;
	// �|���S���̕�
	const float POLYGON_HEIGHT = 50.0f;
}

// �`������l�p�`�̊�l
const D3DXVECTOR3 sVtx[4] =
{
	D3DXVECTOR3(-1.0f, -1.0f, 0.0f),
	D3DXVECTOR3(+1.0f, -1.0f, 0.0f),
	D3DXVECTOR3(-1.0f, +1.0f, 0.0f),
	D3DXVECTOR3(+1.0f, +1.0f, 0.0f),
};

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	// ���_�o�b�t�@�ւ̃|�C���^
	m_pVtxBuff = nullptr;
	// ���̍��W
	m_posOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// ���̍��W
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// �l�p�`�̑傫���ύX
	m_fSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// �F
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CObject2D::~CObject2D()
{
	assert(m_pVtxBuff == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CObject2D::Init()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ������
	m_texture = CTexture::TEXTURE_NONE;

	// ���_�o�b�t�@�̐����i���I�m�ہj
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_posOrigin.x - m_fSize.x * 0.5f, m_posOrigin.y - m_fSize.y * 0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_posOrigin.x + m_fSize.x * 0.5f, m_posOrigin.y - m_fSize.y * 0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_posOrigin.x - m_fSize.x * 0.5f, m_posOrigin.y + m_fSize.y * 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_posOrigin.x + m_fSize.x * 0.5f, m_posOrigin.y + m_fSize.y * 0.5f, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CObject2D::Uninit()
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	CObject::DeletedObj();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CObject2D::Update()
{
	VERTEX_2D *pVtx;			// ���_���ւ̃|�C���^

	// �^�C�}�[
	m_fTimer += 1.0f;

	// �T�C���J�[�u
	//float fSin = sinf(m_fTimer * 0.02f);

	D3DXVECTOR3 addPos[4];	// ����pos�̈ʒu
	D3DXMATRIX mtx;			// �v�Z�p�}�g���b�N�X

	// �}�g���b�N�X�̐���
	D3DXMatrixIdentity(&mtx);

	// ���[�A�s�b�`�A���[�����w�肵�ă}�g���b�N�X���쐬
	D3DXMatrixRotationYawPitchRoll(&mtx, 0.0f, 0.0f, m_rot.z);		// ��]
	//D3DXMatrixRotationYawPitchRoll(&mtx, 0.0f, 0.0f, 0.0f);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W						�����_��
	for (int nCntVtx = 0; nCntVtx < 4; ++nCntVtx)
	{
		D3DXVec3TransformCoord(&addPos[nCntVtx], &sVtx[nCntVtx], &mtx);
		pVtx[nCntVtx].pos.x = m_posOrigin.x + addPos[nCntVtx].x * (m_fSize.x * 0.5f/* * fSin*/);	//<-�T�C�Y�ύX
		pVtx[nCntVtx].pos.y = m_posOrigin.y + addPos[nCntVtx].y * (m_fSize.y * 0.5f/* * fSin*/);
		pVtx[nCntVtx].pos.z = m_posOrigin.z + addPos[nCntVtx].z * (m_fSize.z * 0.5f/* * fSin*/);
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CTexture* pTexture = CManager::GetTexture();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�^�C�v�i���_�����т��鏇�Ԃ����߂��肷��j���w�肷��B
		0,		// �`����J�n����ŏ��̒��_�̔ԍ��B
		2);		// �v���~�e�B�u(�|���S��)��

	// �e�N�X�`���̉���
	pDevice->SetTexture(0, nullptr);
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CObject2D *CObject2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriority)
{
	CObject2D *pObject2D;
	pObject2D = new CObject2D(nPriority);

	if (pObject2D != nullptr)
	{
		pObject2D->Init();
		pObject2D->SetPos(pos);
		pObject2D->SetSize(size);
	}
	else
	{
		assert(false);
	}

	return pObject2D;
}

//--------------------------------------------------
// �F�̕ύX
//--------------------------------------------------
void CObject2D::SetCol(const D3DXCOLOR &col)
{
	VERTEX_2D *pVtx;			// ���_���ւ̃|�C���^
	m_col = col;
	//if (m_pVtxBuff != nullptr)
	{
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = col;
		pVtx[1].col = col;
		pVtx[2].col = col;
		pVtx[3].col = col;

		// ���_�o�b�t�@���A�����b�N
		m_pVtxBuff->Unlock();
	}
}

//--------------------------------------------------
// �A�j���[�V�����̐ݒ�
//--------------------------------------------------
void CObject2D::AnimTexture(int nPattern, int nPatternMax)
{
	VERTEX_2D *pVtx;			// ���_���ւ̃|�C���^

	float nDivisionRate = 1.0f / nPatternMax;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nPattern * nDivisionRate, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nPattern + 1) * nDivisionRate, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nPattern * nDivisionRate, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((nPattern + 1) * nDivisionRate, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
