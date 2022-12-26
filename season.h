//==================================================
// sceason.h
// Author: Kajita Hiromu
//==================================================
#ifndef _SEASON_H_
#define _SEASON_H_

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
class CSeason : public CObject
{
public:
	static const int MAX_TIME = 1;
public:
	enum SEASON
	{
		SEASON_SPRING,
		SEASON_SUMMER,
		SEASON_FALL,
		SEASON_WINTER,
		SEASON_MAX
	};

	explicit CSeason(int nPriority = PRIORITY_EFFECT);
	~CSeason() override;

	HRESULT Init() override;
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit() override;
	void Update() override;
	void Draw() override {}

	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	void Start();
	int End();

	void SetTime(int nScore);
	void AddTime() { SetTime((int)(timeGetTime() - m_nTime)); }
	int GetTime() { return m_nTime; }
	static SEASON GetSeason() { return m_season; }

	static CSeason *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	// Number�^�̔z��
	CNumber *m_pNumber[MAX_TIME];
	// �X�R�A�̒l
	int m_nTime;
	int m_nTime2;
	int	m_nCntTime;
	// SEASON�^�̕ϐ�
	static SEASON m_season;

	bool m_isStart;
};

#endif	// _SCORE_H_
