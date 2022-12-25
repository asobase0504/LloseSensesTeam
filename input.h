//==================================================
// input.h
// Author: Buriya Kota
//==================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//**************************************************
//ライブラリーファイルのリンク
//**************************************************
#pragma comment(lib,"dinput8.lib")		// 入力処理に必要(キーボード)
#pragma comment(lib,"dxguid.lib")		// DirectXコンポーネントに使用

//**************************************************
// インクルード
//**************************************************
#include <Windows.h>
#include <d3dx9.h>
#define	 DIRECTINPUT_VERSION (0x0800)	// ビルド時の警告対策用マクロ(この位置から動かさない)
#include <dinput.h>						// 入力処理に必要

//**************************************************
// クラス
//**************************************************
class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(const HINSTANCE hInstance, const HWND hWnd);	//入力処理全部の初期化
	virtual void Uninit();									//入力処理全部の終了処理
	virtual void Update() = 0;								//入力処理全部の更新処理

protected:
	static LPDIRECTINPUT8 m_pInput;						// DirectInputオブジェクトへのポインタ
	LPDIRECTINPUTDEVICE8 m_pDevKeyboard;				// 入力デバイス（キーボード（コントローラー用は別に作る））へのポインタ

};

#endif // _INPUT_H_
