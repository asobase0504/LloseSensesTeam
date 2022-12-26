//==================================================
// score.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include "manager.h"
#include "score.h"
#include "number.h"

//**************************************************
// �ÓI�����o�ϐ�
//**************************************************

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CScore::CScore(int nPriority /* =4 */) : CObject(nPriority)
{
	m_nScore = 0;
	SetType(TYPE_SCORE);
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CScore::~CScore()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CScore::Init()
{
	return S_OK;
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CScore::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_nScore = 0;
	m_nTime = 0;

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
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
void CScore::Uninit()
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (m_pNumber[nCnt] == nullptr)
		{
			continue;
		}

		m_pNumber[nCnt]->Uninit();
	}

	CObject::DeletedObj();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CScore::Update()
{
	//ENTER�̓_��
	m_nTime++;
	m_nTime %= 61;

	if (m_nTime > 31)
	{
		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else
	{
		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	}

	if (m_isLight)
	{
		for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
		{
			m_pNumber[nCnt]->SetCol(m_col);
		}
	}

}

//--------------------------------------------------
// �ʒu�̐ݒ�Ƒ傫���̐ݒ�
//--------------------------------------------------
void CScore::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_pNumber[nCnt]->SetPos(D3DXVECTOR3(size.x * nCnt + pos.x, pos.y, 0.0f));
	}
}

//--------------------------------------------------
// �X�R�A�̐ݒ�
//--------------------------------------------------
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;

	if (m_nScore < 0)
	{
		m_nScore = 0;
	}

	int aPosTexU[8];		// �e���̐������i�[

	{
		int score = m_nScore;
		for (int nCnt = 7; nCnt >= 0; --nCnt)
		{
			aPosTexU[nCnt] = score % 10;
			score /= 10;
		}
	}

	// �e�N�X�`�����W�̐ݒ�
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_pNumber[nCnt]->AnimTexture(aPosTexU[nCnt], 10);
	}
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CScore *CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScore *pScore;
	pScore = new CScore;

	if (pScore != nullptr)
	{
		pScore->Init(pos, size);
	}
	else
	{
		assert(false);
	}

	return pScore;
}
