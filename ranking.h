//==================================================
// ranking.h
// Author: Buriya Kota
//==================================================
#ifndef _RANKING_H_
#define _RANKING_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "game_mode.h"
#include "texture.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************
class CObject2D;
class CScore;

//**************************************************
// �N���X
//**************************************************
class CRanking : public CGameMode
{
public:
	static const int MAX_RANK = 5;

public:
	CRanking();
	~CRanking() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override {}

	void LoadRanking();
	void SaveRanking();
	void SetRanking(int nScore);

	static CRanking *Create();

private:
	// �I�u�W�F�N�g2D�̔�
	CObject2D *m_pRanking;
	// �I�u�W�F�N�g2D�̔�
	CObject2D *m_pRankingBg;
	CScore *m_pScore[MAX_RANK];
	// �ʒu
	D3DXVECTOR3 m_pos;
	// �傫��
	D3DXVECTOR3 m_size;
	// �X�R�A�ۑ��ϐ�
	int m_aRankingData[MAX_RANK];

};

#endif	// _RESULT_H_