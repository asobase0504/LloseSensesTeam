//==================================================
// game.h
// Author: Buriya Kota
//==================================================
#ifndef _GAME_H_
#define _GAME_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "game_mode.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************
class CLockOnUIManager;
class CPlayer3D;
class CPause;
class CMeshField;
class CGimmick;
class CGoal;
class CTime;
class CPlayer;
class CWind;
class CSeason;
class CScore;

//**************************************************
// �N���X
//**************************************************
class CGame : public CGameMode
{
public:
	CGame();
	~CGame() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override {}

	// �v���C���[�̏��̎擾
	static CPlayer* GetPlayer() { return m_pPlayer; }
	static CPause* GetPause() { return m_pPause; }
	static CScore* GetScore() { return m_pScore; }
	static CMeshField* GetMeshField() { return m_pMeshField; }
	static CGimmick* GetGimmick() { return m_pGimmick; }
	static CGoal* GetGoal() { return m_pGoal; }
	static CTime* GetTimer() { return m_pTimer; }
	static CSeason* GetSeason() { return m_pSeason; }
	static CWind* GetWind();

	// �t���[���̐ݒ�
	int GetFrame() { return m_time; }

	static CGame *Create();

private:
	int m_time;		// �Q�[���J�n����̎���
	
	static CPlayer *m_pPlayer;
	static CPause *m_pPause;
	static CMeshField *m_pMeshField;
	static CGimmick *m_pGimmick;
	static CGoal *m_pGoal;
	static CScore *m_pScore;
	static CTime *m_pTimer;
	static CWind *m_pWind;
	static CSeason *m_pSeason;
};

#endif	// _GAME_H_