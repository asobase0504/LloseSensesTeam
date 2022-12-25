//==================================================
// game.h
// Author: Buriya Kota
//==================================================
#ifndef _GAME_H_
#define _GAME_H_

//**************************************************
// インクルード
//**************************************************
#include "game_mode.h"

//**************************************************
// 前方前言　実態はNG　ポインタだけならOK
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
// クラス
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

	// プレイヤーの情報の取得
	static CPlayer3D* GetPlayer3D() { return m_pPlayer3D; }
	static CScore* GetScore() { return m_pScore; }
	static CPause* GetPause() { return m_pPause; }
	static CMeshField* GetMeshField() { return m_pMeshField; }
	static CGimmick* GetGimmick() { return m_pGimmick; }
	static CGoal* GetGoal() { return m_pGoal; }
	static CTimer* GetTimer() { return m_pTimer; }

	// フレームの設定
	int GetFrame() { return m_time; }

	static CGame *Create();

private:
	int m_time;		// ゲーム開始からの時間
	
	static CPlayer3D *m_pPlayer3D;
	static CScore *m_pScore;
	static CPause *m_pPause;
	static CMeshField *m_pMeshField;
	static CGimmick *m_pGimmick;
	static CGoal *m_pGoal;
	static CTimer *m_pTimer;
};

#endif	// _GAME_H_