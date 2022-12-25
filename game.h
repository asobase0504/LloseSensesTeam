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
class CScore;
class CLockOnUIManager;
class CPlayer3D;
class CPause;
class CMeshField;
class CGimmick;
class CGoal;
class CTimer;

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
	static CPlayer3D* GetPlayer3D() { return m_pPlayer3D; }
	static CScore* GetScore() { return m_pScore; }
	static CPause* GetPause() { return m_pPause; }
	static CMeshField* GetMeshField() { return m_pMeshField; }
	static CGimmick* GetGimmick() { return m_pGimmick; }
	static CGoal* GetGoal() { return m_pGoal; }
	static CTimer* GetTimer() { return m_pTimer; }

	// �t���[���̐ݒ�
	int GetFrame() { return m_time; }

	static CGame *Create();

private:
	int m_time;		// �Q�[���J�n����̎���
	
	static CPlayer3D *m_pPlayer3D;
	static CScore *m_pScore;
	static CPause *m_pPause;
	static CMeshField *m_pMeshField;
	static CGimmick *m_pGimmick;
	static CGoal *m_pGoal;
	static CTimer *m_pTimer;
};

#endif	// _GAME_H_