//==================================================
// count.cpp
// Author: Kajita Hiromu
//==================================================

//**************************************************
// include
//**************************************************
#include "count.h"
#include "manager.h"
#include "number.h"

//**************************************************
// �ÓI�����o�ϐ�
//**************************************************

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CCount::CCount(int nPriority /* =4 */) : CObject(nPriority)
{
	SetType(TYPE_SCORE);
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CCount::~CCount()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CCount::Init()
{
	return S_OK;
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CCount::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_nTime = 0;
	m_nTime2 = 4;
	m_nCntTime = 0;
	m_isStart = false;
	m_bStart = false;

	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_pNumber[nCnt] = CNumber::Create(D3DXVECTOR3(size.x * nCnt + pos.x, pos.y, 0.0f), size);
		m_pNumber[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pNumber[nCnt]->SetTexture(CTexture::TEXTURE_NUMBER);
	}

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CCount::Uninit()
{
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		if (m_pNumber[nCnt] == nullptr)
		{
			continue;
		}

		m_pNumber[nCnt]->Uninit();
	}

	CObject::DeletedObj();
}

void CCount::Update()
{
	if (m_isStart)
	{
		AddTime();
	}
}

//--------------------------------------------------
// �ʒu�̐ݒ�Ƒ傫���̐ݒ�
//--------------------------------------------------
void CCount::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_pNumber[nCnt]->SetPos(D3DXVECTOR3(size.x * nCnt + pos.x, pos.y, 0.0f));
	}
}

//--------------------------------------------------
// �^�C�}�[�X�^�[�g
//--------------------------------------------------
void CCount::Start()
{
	m_nTime = timeGetTime();
	m_isStart = true;
}

//--------------------------------------------------
// �^�C�}�[�G���h
//--------------------------------------------------
int CCount::End()
{
	m_isStart = false;
	return m_nTime;
}

void CCount::StartTimer(bool bStart)
{
	m_bStart = bStart;
}

bool CCount::GetStart()
{
	return m_bStart;
}

//--------------------------------------------------
// �^�C���̐ݒ�
//--------------------------------------------------
void CCount::SetTime(int nTime)
{
	int aPosTexU[MAX_TIME];		// �e���̐������i�[

	if (!m_bStart)
	{
		m_nCntTime--;				//nCntTime��������Ă���

		if (m_nCntTime < 0)			//nCntTime��0��菬�����Ȃ�����
		{
			m_nTime2--;				//���Ԃ���b�������Ă���
			m_nCntTime = 60;		//���Ԃ̌���̑���
		}

		aPosTexU[0] = m_nTime2 % 4 / 1;

		if (m_nTime2 == 0)
		{
			StartTimer(true);
		}
	}

	// �e�N�X�`�����W�̐ݒ�
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_pNumber[nCnt]->AnimTexture(aPosTexU[nCnt], 10);
	}
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CCount *CCount::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CCount *pTime;
	pTime = new CCount;

	if (pTime != nullptr)
	{
		pTime->Init(pos, size);
	}
	else
	{
		assert(false);
	}

	return pTime;
}
