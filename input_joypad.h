//==================================================
// input_joypad.h
// Author: Buriya Kota
//==================================================
#ifndef _INPUT_JOYPAD_H_
#define _INPUT_JOYPAD_H_

//**************************************************
// インクルード
//**************************************************
#pragma comment(lib,"xinput.lib")		// 入力処理に必要（ジョイパット）

#include "input.h"
#include <Xinput.h>

//**************************************************
// クラス
//**************************************************
class CInputJoyPad
{
private:
	static const int MAX_PLAYER = 4;		//プレイヤーの最大人数

public:
	//キー種類(ジョイパッド)
	enum JOYKEY
	{
		JOYKEY_UP = 0,			// 十字ボタン上
		JOYKEY_DOWN,			// 十字ボタン下
		JOYKEY_LEFT,			// 十字ボタン左
		JOYKEY_RIGHT,			// 十字ボタン右
		JOYKEY_START,			// スタートボタン
		JOYKEY_BACK,			// バックボタン
		JOYKEY_LEFT_THUMB,		// 左スティック押込み
		JOYKEY_RIGHT_THUMB,		// 右スティック押込み
		JOYKEY_LEFT_SHOULDER,	// L１ボタン
		JOYKEY_RIGHT_SHOULDER,	// R１ボタン
		JOYKEY_LEFT_TRIGGER,	// L２トリガー
		JOYKEY_RIGHT_TRIGGER,	// R２トリガー
		JOYKEY_A,				// Aボタン
		JOYKEY_B,				// Bボタン
		JOYKEY_X,				// Xボタン
		JOYKEY_Y,				// Yボタン
		JOYKEY_LEFT_STICK,		// 左スティック
		JOYKEY_RIGHT_STICK,		// 右スティック
		JOYKEY_MAX
	};

	CInputJoyPad();
	~CInputJoyPad();

	// 入力処理全部の初期化
	HRESULT Init();
	// 入力処理全部の終了処理
	void Uninit();
	// 入力処理全部の更新処理
	void Update();

	// プロトタイプ宣言ジョイパット
	// ジョイパッドプレス処理
	bool GetJoypadPress(JOYKEY Key, int nPlayer);
	// ジョイパッドトリガー処理
	bool GetJoypadTrigger(JOYKEY Key, int nPlayer);
	// ジョイパッドスティック処理
	D3DXVECTOR3 GetJoypadStick(JOYKEY Key, int nPlayer);
	// ジョイパッドトリガーペダル処理
	int GetJoypadTriggerPedal(JOYKEY Key, int nPlayer);
	// ジョイパッドの使用状況を取得
	bool *GetUseJoypad();

private:
	//ジョイパッド
	XINPUT_STATE m_JoyKeyState[MAX_PLAYER];				//ジョイパットのプレス情報
	XINPUT_STATE m_JoyKeyStateTrigger[MAX_PLAYER];		//ジョイパットのトリガー情報
	D3DXVECTOR3 m_JoyStickPos[MAX_PLAYER];				//ジョイスティックの傾き
	XINPUT_VIBRATION m_JoyMoter[MAX_PLAYER];			//ジョイパッドのモーター
	int m_nTime[MAX_PLAYER];							//振動持続時間
	WORD m_nStrength[MAX_PLAYER];						//振動の強さ (0 - 65535)
	bool m_bUseJoypad[MAX_PLAYER];						//ジョイパッドを使用してるかどうか


};

#endif // _INPUT_JOYPAD_H_