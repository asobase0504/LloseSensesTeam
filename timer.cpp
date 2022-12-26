//==================================================
// score.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include "manager.h"
#include "timer.h"
#include "number.h"

//**************************************************
// �ÓI�����o�ϐ�
//**************************************************

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CTime::CTime(int nPriority /* =4 */) : CObject(nPriority)
{
	m_nTime = 0;
	SetType(TYPE_SCORE);
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTime::~CTime()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CTime::Init()
{
	return S_OK;
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CTime::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_nTime = 0;
	m_isStart = false;

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
void CTime::Uninit()
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

void CTime::Update()
{
	if (m_isStart)
	{
		AddTime();
	}
}

//--------------------------------------------------
// �ʒu�̐ݒ�Ƒ傫���̐ݒ�
//--------------------------------------------------
void CTime::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_pNumber[nCnt]->SetPos(D3DXVECTOR3(size.x * nCnt + pos.x, pos.y, 0.0f));
	}
}

//--------------------------------------------------
// �^�C�}�[�X�^�[�g
//--------------------------------------------------
void CTime::Start()
{
	m_nTime = timeGetTime();
	m_isStart = true;
}

//--------------------------------------------------
// �^�C�}�[�G���h
//--------------------------------------------------
int CTime::End()
{
	m_isStart = false;
	return m_nTime;
}

//--------------------------------------------------
// �X�R�A�̐ݒ�
//--------------------------------------------------
void CTime::SetTime(int nTime)
{
	int aPosTexU[8];		// �e���̐������i�[

	{
		int score = nTime;
		for (int nCnt = MAX_TIME; nCnt >= 0; --nCnt)
		{
			aPosTexU[nCnt] = score % 10;
			score /= 10;
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
CTime *CTime::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CTime *pTime;
	pTime = new CTime;

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
