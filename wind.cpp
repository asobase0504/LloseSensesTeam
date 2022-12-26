//==================================================
// wind.cpp
// Author: Kajita Hiromu
//==================================================
//**************************************************
// include
//**************************************************
#include <assert.h>

#include "manager.h"
#include "season.h"
#include "utility.h"
#include "wind.h"
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CWind::CWind(int nPriority /* =4 */) : CObject2D(nPriority)
{
	SetType(TYPE_WIND);
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CWind::~CWind()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CWind::Init()
{
	CObject2D::Init();
	SetTexture(CTexture::TEXTURE_WIND);

	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFrame = 0;
	fAirFlow = 0.0f;

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CWind::Uninit()
{
	CObject2D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CWind::Update()
{
	switch (CSeason::GetSeason())
	{
	case CSeason::SEASON_SPRING:
	{
		fAirFlow = 0.01f;
	}
	break;

	case CSeason::SEASON_SUMMER:
	{
		fAirFlow = 0.02f;
	}
	break;

	case CSeason::SEASON_FALL:
	{
		fAirFlow = 0.03f;
	}
	break;

	case CSeason::SEASON_WINTER:
		fAirFlow = 0.05f;
		break;
	default:
		break;
	}

	//�t���[�������Z
	m_nFrame++;

	if (m_nFrame > 60)
	{//�t���[������45�𒴂�����
		//�����_���̒l��ς���
		m_nRandom = FloatRandam(3.0f, 0.0f);

		//�t���[����0�ɖ߂�
		m_nFrame = 0;
	}

	if (m_nRandom <= 1.5f)
	{//�����_���̒l��1.5f�ȉ��Ȃ�
		m_state = WIND_LEFT;
		m_pos = D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.8f, CManager::SCREEN_WIDTH * 0.3f, 0.0f);
	}
	else
	{//1.5f�ȏ�Ȃ�
		m_state = WIND_RIGHT;
		m_pos = D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.2f, CManager::SCREEN_WIDTH * 0.3f, 0.0f);
	}

	//pos�̒l���X�V
	SetPos(m_pos);
	CObject2D::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CWind::Draw()
{
	CObject2D::Draw();
}

//--------------------------------------------------
// ���݂̌������擾
//--------------------------------------------------
CWind::WIND_ROT CWind::GetState()
{
	return m_state;
}

float CWind::GetAirFlow()
{
	return fAirFlow;
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CWind * CWind::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	CWind *pWind;
	pWind = new CWind;

	if (pWind != nullptr)
	{
		pWind->Init();
		pWind->SetPos(pos);
		pWind->SetSize(size);
	}
	else
	{
		assert(false);
	}

	return pWind;
}
