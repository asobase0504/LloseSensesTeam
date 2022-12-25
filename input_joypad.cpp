//==================================================
// input_joypad.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include "input_joypad.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CInputJoyPad::CInputJoyPad()
{
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		// メモリーのクリア
		memset(&m_JoyKeyState[nCnt], 0, sizeof(XINPUT_STATE));
		memset(&m_JoyKeyStateTrigger[nCnt], 0, sizeof(XINPUT_STATE));

		// ジョイパッドの振動制御の０クリア
		ZeroMemory(&m_JoyMoter[nCnt], sizeof(XINPUT_VIBRATION));

		// 振動制御用の初期化
		m_nStrength[nCnt] = 0;
		m_nTime[nCnt] = 0;
		m_bUseJoypad[nCnt] = false;
	}
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CInputJoyPad::~CInputJoyPad()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CInputJoyPad::Init()
{
	// XInputのステートを設定（有効にする）
	XInputEnable(true);

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		// メモリーのクリア
		memset(&m_JoyKeyState[nCnt], 0, sizeof(XINPUT_STATE));
		memset(&m_JoyKeyStateTrigger[nCnt], 0, sizeof(XINPUT_STATE));

		// ジョイパッドの振動制御の０クリア
		ZeroMemory(&m_JoyMoter[nCnt], sizeof(XINPUT_VIBRATION));

		// 振動制御用の初期化
		m_nStrength[nCnt] = 0;
		m_nTime[nCnt] = 0;
		m_bUseJoypad[nCnt] = false;
	}
	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CInputJoyPad::Uninit(void)
{
	// XInputのステートを設定（無効にする）
	XInputEnable(false);
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CInputJoyPad::Update(void)
{
	XINPUT_STATE JoyKeyState[MAX_PLAYER];		// ジョイパッド入力情報

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		// ジョイパッドの状態を取得
		if (XInputGetState(nCnt, &JoyKeyState[nCnt]) == ERROR_SUCCESS)
		{
			m_JoyKeyStateTrigger[nCnt].Gamepad.wButtons
				= ~m_JoyKeyState[nCnt].Gamepad.wButtons
				& JoyKeyState[nCnt].Gamepad.wButtons; // トリガー情報を保存
			m_JoyKeyState[nCnt] = JoyKeyState[nCnt];  // プレス処理
			m_bUseJoypad[nCnt] = true;
		}
		else
		{
			m_bUseJoypad[nCnt] = false;
		}

		// ジョイパッドの振動
		m_JoyMoter[nCnt].wLeftMotorSpeed = m_nStrength[nCnt];
		m_JoyMoter[nCnt].wRightMotorSpeed = m_nStrength[nCnt];
		XInputSetState(nCnt, &m_JoyMoter[nCnt]);

		if (m_nTime[nCnt] > 0)
		{
			m_nTime[nCnt]--;
		}
		else
		{
			m_nStrength[nCnt] = 0;
			m_nTime[nCnt] = 0;
		}
	}
}

//--------------------------------------------------
// ジョイパッドプレス処理
//--------------------------------------------------
bool CInputJoyPad::GetJoypadPress(JOYKEY Key, int nPlayer)
{
	return (m_JoyKeyState[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//--------------------------------------------------
// ジョイパッドトリガー処理
//--------------------------------------------------
bool CInputJoyPad::GetJoypadTrigger(JOYKEY Key, int nPlayer)
{
	return (m_JoyKeyStateTrigger[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//--------------------------------------------------
// ジョイパッドスティック処理
//--------------------------------------------------
D3DXVECTOR3 CInputJoyPad::GetJoypadStick(JOYKEY Key, int nPlayer)
{
	switch (Key)
	{
	case JOYKEY_LEFT_STICK:
		m_JoyStickPos[nPlayer] = D3DXVECTOR3(m_JoyKeyState[nPlayer].Gamepad.sThumbLX / 32767.0f, -m_JoyKeyState[nPlayer].Gamepad.sThumbLY / 32767.0f, 0.0f);
		break;
	case JOYKEY_RIGHT_STICK:
		m_JoyStickPos[nPlayer] = D3DXVECTOR3(m_JoyKeyState[nPlayer].Gamepad.sThumbRX / 32767.0f, -m_JoyKeyState[nPlayer].Gamepad.sThumbRY / 32767.0f, 0.0f);
		break;
	}

	return m_JoyStickPos[nPlayer];
}

//--------------------------------------------------
// ジョイパッドトリガーペダル処理
//--------------------------------------------------
int CInputJoyPad::GetJoypadTriggerPedal(JOYKEY Key, int nPlayer)
{
	int nJoypadTriggerPedal = 0;
	switch (Key)
	{
	case JOYKEY_LEFT_TRIGGER:
		nJoypadTriggerPedal = m_JoyKeyState[nPlayer].Gamepad.bLeftTrigger;
		break;
	case JOYKEY_RIGHT_TRIGGER:
		nJoypadTriggerPedal = m_JoyKeyState[nPlayer].Gamepad.bRightTrigger;
		break;
	}

	return nJoypadTriggerPedal;
}

//--------------------------------------------------
// ジョイパッドの使用状況を取得
//--------------------------------------------------
bool * CInputJoyPad::GetUseJoypad(void)
{
	return &m_bUseJoypad[0];
}
