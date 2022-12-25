//==================================================
// score.h
// Author: Buriya Kota
//==================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "object.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************
class CNumber;

//**************************************************
// �N���X
//**************************************************
class CScore : public CObject
{
public:
	static const int MAX_SCORE = 8;
public:
	explicit CScore(int nPriority = PRIORITY_EFFECT);
	~CScore() override;

	HRESULT Init() override;
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit() override;
	void Update() override {}
	void Draw() override {}

	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	void SetScore(int nScore);
	void AddScore(int nValue) { SetScore(m_nScore + nValue); }
	int GetScore() { return m_nScore; }

	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	// Number�^�̔z��
	CNumber *m_pNumber[MAX_SCORE];
	// �X�R�A�̒l
	int m_nScore;
};

#endif	// _SCORE_H_