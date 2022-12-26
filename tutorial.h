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
class CLockOnUIManager;
class CPause;
class CPlayer;
class CWind;
class CSeason;
class CBG;
class CTime;

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

	// プレイヤーの情報の取得
	static CPlayer* GetPlayer() { return m_pPlayer; }
	static CPause* GetPause() { return m_pPause; }
	static CSeason* GetSeason() { return m_pSeason; }
	static CWind* GetWind() { return m_pWind; }
	static CTime* GetTimer() { return m_pTimer; }

	void LoadPlayer(const char *pFdata);

	static CTutorial *Create();

private:
	int m_time;

	static CPlayer *m_pPlayer;
	static CPause *m_pPause;
	static CWind *m_pWind;
	static CSeason *m_pSeason;
	static CBG *m_pBG;
	static CTime *m_pTimer;
};

#endif	// _TUTORIAL_H_