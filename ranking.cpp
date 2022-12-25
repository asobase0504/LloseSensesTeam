//==================================================
// ranking.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include <assert.h>

#include "manager.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "fade.h"
#include "ranking.h"
#include "score.h"
#include "sound.h"

// json��include
#include "nlohmann/json.hpp"
#include <fstream>

// ���O�̏ȗ�
namespace nl = nlohmann;
// �t�@�C���p�X�̐ݒ�
const char* pathToJSON = "data/FILE/ranking.json";

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CRanking::CRanking()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CRanking::~CRanking()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CRanking::Init()
{
	//CManager::GetSound()->Play(CSound::LABEL_BGM_RANKING);

	// �����L���O�̔w�i
	m_pRankingBg = CObject2D::Create(
		D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXVECTOR3((float)CManager::SCREEN_WIDTH, (float)CManager::SCREEN_HEIGHT, 0.0f),
		PRIORITY_BG);
	m_pRankingBg->SetTexture(CTexture::TEXTURE_NONE);

	// ����
	m_pRanking = CObject2D::Create(
		D3DXVECTOR3(300.0f, 380.0f, 0.0f),
		D3DXVECTOR3(120.0f, 500.0f, 0.0f),
		PRIORITY_BG);
	m_pRanking->SetTexture(CTexture::TEXTURE_NONE);
	m_pRanking->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		m_aRankingData[nCntRank] = 0;
		// �X�R�A
		m_pScore[nCntRank] = CScore::Create(D3DXVECTOR3(500.0f, 180.0f + nCntRank * 100.0f, 0.0f), D3DXVECTOR3(60.0f, 80.0f, 0.0f));
		m_pScore[nCntRank]->SetScore(m_aRankingData[nCntRank]);
	}

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CRanking::Uninit()
{
	CManager::GetSound()->Stop();

	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		if (m_pScore[nCnt] == nullptr)
		{
			continue;
		}

		m_pScore[nCnt]->Uninit();
	}

	if (m_pRanking != nullptr)
	{
		m_pRanking->Uninit();
	}

	if (m_pRankingBg != nullptr)
	{
		m_pRankingBg->Uninit();
	}

	CObject::DeletedObj();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CRanking::Update()
{
	CInputKeyboard *pInputKeyoard = CManager::GetInputKeyboard();
	CInputJoyPad *pInputJoyPad = CManager::GetInputJoyPad();

	if (pInputKeyoard->GetTrigger(DIK_RETURN) || pInputJoyPad->GetJoypadTrigger(pInputJoyPad->JOYKEY_A, 0))
	{
		// �T�E���h
		//CManager::GetSound()->Play(CSound::LABEL_SE_ENTER);

		CFade::GetInstance()->SetFade(CManager::MODE_TITLE);
	}
}

//--------------------------------------------------
// �����L���O�̃��Z�b�g
//--------------------------------------------------
void CRanking::LoadRanking()
{
	// �t�@�C���I�[�v��
	std::ifstream ifs(pathToJSON);

	if (ifs)
	{// �t�@�C���J�����Ƃ�
		nl::json j;	// ���X�g�̐���
		ifs >> j;	// ���X�g�ɕ������Ԃ�����

		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{//	�^�O�t��
			std::string name = "RANKING";
			// ���^�𕶎��^�ɕς���
			std::string Number = std::to_string(nCnt);
			name += Number;

			m_aRankingData[nCnt] = j[name];
		}
	}
}

//--------------------------------------------------
// �����L���O�̃Z�[�u
//--------------------------------------------------
void CRanking::SaveRanking()
{
	nl::json j;	// ���X�g�̐���

	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{//	�^�O�t��
		std::string name = "RANKING";
		// ���^�𕶎��^�ɕς���
		std::string Number = std::to_string(nCnt);
		name += Number;

		j[name] = m_aRankingData[nCnt];
	}

	// jobj�Ƀf�[�^������
	auto jobj = j.dump();
	std::ofstream writing_file;
	writing_file.open(pathToJSON, std::ios::out);
	writing_file << jobj << std::endl;
	writing_file.close();
}

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
void CRanking::SetRanking(int nScore)
{
	LoadRanking();

	int nCheck = 0;

	//�����L���O�̍ŉ��ʂƍ���̃X�R�A���ׂ�
	if (nScore >= m_aRankingData[MAX_RANK - 1])
	{
		//��r�������l������
		m_aRankingData[MAX_RANK - 1] = nScore;
	}

	for (int nCntRank1 = 0; nCntRank1 < MAX_RANK - 1; nCntRank1++)
	{
		for (int nCntRnak2 = nCntRank1 + 1; nCntRnak2 < MAX_RANK; nCntRnak2++)
		{//��L�̌J��Ԃ����i�ނ��тɌJ��Ԃ��񐔂�-1�������B

			// ��̃f�[�^���r����
			if (m_aRankingData[nCntRank1] <= m_aRankingData[nCntRnak2])
			{
				//�ϐ����ꎞ�i�[
				nCheck = m_aRankingData[nCntRnak2];

				//��r�������l������
				m_aRankingData[nCntRnak2] = m_aRankingData[nCntRank1];
				m_aRankingData[nCntRank1] = nCheck;
			}
		}
	}

	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		m_pScore[nCntRank]->SetScore(m_aRankingData[nCntRank]);
	}

	// �����L���O�̃Z�[�u
	SaveRanking();
}

//--------------------------------------------------
// �����L���O�̐ݒ菈��
//--------------------------------------------------
CRanking *CRanking::Create()
{
	CRanking *pRanking;
	pRanking = new CRanking;

	if (pRanking != nullptr)
	{
		pRanking->Init();
	}
	else
	{
		assert(false);
	}

	return pRanking;
}
