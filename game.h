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
	static CPlayer* GetPlayer() { return m_pPlayer; }
	static CPause* GetPause() { return m_pPause; }
	static CScore* GetScore() { return m_pScore; }
	static CMeshField* GetMeshField() { return m_pMeshField; }
	static CGimmick* GetGimmick() { return m_pGimmick; }
	static CGoal* GetGoal() { return m_pGoal; }
	static CTime* GetTimer() { return m_pTimer; }
	static CSeason* GetSeason() { return m_pSeason; }
	static CWind* GetWind();

	// フレームの設定
	int GetFrame() { return m_time; }

	static CGame *Create();

private:
	int m_time;		// ゲーム開始からの時間
	
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