//==================================================
// manager.h
// Author: Buriya Kota
//==================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//**************************************************
// インクルード
//**************************************************
#include <d3dx9.h>

//**************************************************
// 前方前言　実態はNG　ポインタだけならOK
//**************************************************
class CObject;
class CRenderer;
class CInputKeyboard;
class CTexture;
class CCamera;
class CLight;
class CEnemy3D;
class CInputJoyPad;
class CInputJoyPad;
class CDebugProc;
class CPlayer3D;
class CSound;
class CModelData;

//**************************************************
// クラス
//**************************************************
class CManager
{
public:
	// スクリーンの幅
	static const int SCREEN_WIDTH = 1280;
	// スクリーンの高さ
	static const int SCREEN_HEIGHT = 720;

public:
	//画面(モード)の種類
	enum MODE
	{
		MODE_TITLE = 0,		//タイトル画面
		MODE_TUTORIAL,		//チュートリアル
		MODE_GAME,			//ゲーム画面
		MODE_GAMEOVER,		//ゲームオーバー画面
		MODE_RESULT,		//リザルト画面
		MODE_RANKING,		//ランキング
		MODE_MAX
	};

	CManager();
	~CManager();

	HRESULT Init(const HINSTANCE hInstance, const HWND hWnd);
	void Uninit();
	void Update();
	void Draw();

	static CManager *Create(const HINSTANCE hInstance, const HWND hWnd);
	// レンダラーの情報の取得
	static CRenderer *GetRenderer() { return m_pRenderer; }
	// キーボードの情報の取得
	static CInputKeyboard *GetInputKeyboard() { return m_pInputKeyboard; }
	// ジョイパッドの情報の取得
	static CInputJoyPad *GetInputJoyPad() { return m_pInputJoyPad; }
	// テクスチャの情報の取得
	static CTexture* GetTexture() { return m_pTexture; }
	// モデルデータの情報の取得
	static CModelData* GetModelData() { return m_pModelData; }
	// カメラの情報の取得
	static CCamera* GetCamera() { return m_pCamera; }
	// ライトの情報の取得
	static CLight* GetLight() { return m_pLight; }
	// マネージャーの情報の取得
	static CManager* GetManager() { return m_pManager; }

	// サウンド情報の取得
	static CSound* GetSound() { return m_pSound; }

	static void SetNowScore(int score) { m_nowScore = score; }
	static int GetNowScore() { return m_nowScore; }

	static MODE GetGameMode() { return m_mode; }

	static void SetMode(MODE mode);

private:
	// 現在のモード
	static MODE m_mode;
	static CObject *m_pGameMode;
	static CRenderer *m_pRenderer;
	static CInputKeyboard *m_pInputKeyboard;
	static CInputJoyPad *m_pInputJoyPad;
	static CTexture *m_pTexture;
	static CModelData *m_pModelData;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static CDebugProc *m_pDebug;
	static CSound *m_pSound;
	static CManager *m_pManager;

	// 現在のスコア
	static int m_nowScore;

};

#endif	// _MANAGER_H_