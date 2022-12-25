//==================================================
// tutorial.h
// Author: Buriya Kota
//==================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//**************************************************
// インクルード
//**************************************************
#include "game_mode.h"

//**************************************************
// 前方前言　実態はNG　ポインタだけならOK
//**************************************************
class CScore;
class CPlayer3D;
class CEnemy3D;
class CLockOnUIManager;

//**************************************************
// クラス
//**************************************************
class CTutorial : public CGameMode
{
public:
	CTutorial();
	~CTutorial() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override {}

	static CLockOnUIManager* GetLockOnUIManager() { return m_pLockOnUIManager; }
	static CScore* GetScore() { return m_pScore; }

	void LoadPlayer(const char *pFdata);

	static CTutorial *Create();

private:
	int m_time;
	CEnemy3D *m_pEnemy[5];
	static CPlayer3D *m_pPlayer3D;
	static CScore *m_pScore;
	static CLockOnUIManager *m_pLockOnUIManager;

};

#endif	// _TUTORIAL_H_