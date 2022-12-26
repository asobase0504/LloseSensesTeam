//==================================================
// season.cpp
// Author: Kajita Hiromu
//==================================================

//**************************************************
// include
//**************************************************
#include "manager.h"
#include "season.h"
#include "number.h"

//**************************************************
// �ÓI�����o�ϐ�
//**************************************************
CSeason::SEASON CSeason::m_season = SEASON_SPRING;

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CSeason::CSeason(int nPriority /* =4 */) : CObject(nPriority)
{
	m_nTime = 0;
	SetType(TYPE_SCORE);
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CSeason::~CSeason()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CSeason::Init()
{
	m_nTime2 = 0;
	m_nCntTime = 900;
	return S_OK;
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CSeason::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
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
void CSeason::Uninit()
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

void CSeason::Update()
{
	if (m_isStart)
	{
		AddTime();
	}
}

//--------------------------------------------------
// �ʒu�̐ݒ�Ƒ傫���̐ݒ�
//--------------------------------------------------
void CSeason::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_pNumber[nCnt]->SetPos(D3DXVECTOR3(size.x * nCnt + pos.x, pos.y, 0.0f));
	}
}

//--------------------------------------------------
// �^�C�}�[�X�^�[�g
//--------------------------------------------------
void CSeason::Start()
{
	m_nTime = timeGetTime();
	m_isStart = true;
}

//--------------------------------------------------
// �^�C�}�[�G���h
//--------------------------------------------------
int CSeason::End()
{
	m_isStart = false;
	return m_nTime;
}

//--------------------------------------------------
// �^�C���̐ݒ�
//--------------------------------------------------
void CSeason::SetTime(int nTime)
{
	int aPosTexU[MAX_TIME];		// �e���̐������i�[

	{
		m_nCntTime--;				//nCntTime��������Ă���

		if (m_nCntTime < 0)			//nCntTime��0��菬�����Ȃ�����
		{
			m_nTime2++;				//���Ԃ���b�������Ă���
			m_nCntTime = 900;		//���Ԃ̌���̑���
		}

		aPosTexU[0] = m_nTime2 % 5 / 1;

		if (m_nTime2 == 1)
		{
			m_season = SEASON_SPRING;
		}
		else if (m_nTime2 == 2)
		{
			m_season = SEASON_SUMMER;
		}
		else if (m_nTime2 == 3)
		{
			m_season = SEASON_FALL;
		}
		else if (m_nTime2 == 4)
		{
			m_season = SEASON_WINTER;
		}
		else if (m_nTime2 == 5)
		{
			m_nTime2 = 1;
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
CSeason *CSeason::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CSeason *pTime;
	pTime = new CSeason;

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
