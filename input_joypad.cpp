//==================================================
// input_joypad.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include "input_joypad.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CInputJoyPad::CInputJoyPad()
{
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		// �������[�̃N���A
		memset(&m_JoyKeyState[nCnt], 0, sizeof(XINPUT_STATE));
		memset(&m_JoyKeyStateTrigger[nCnt], 0, sizeof(XINPUT_STATE));

		// �W���C�p�b�h�̐U������̂O�N���A
		ZeroMemory(&m_JoyMoter[nCnt], sizeof(XINPUT_VIBRATION));

		// �U������p�̏�����
		m_nStrength[nCnt] = 0;
		m_nTime[nCnt] = 0;
		m_bUseJoypad[nCnt] = false;
	}
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CInputJoyPad::~CInputJoyPad()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CInputJoyPad::Init()
{
	// XInput�̃X�e�[�g��ݒ�i�L���ɂ���j
	XInputEnable(true);

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		// �������[�̃N���A
		memset(&m_JoyKeyState[nCnt], 0, sizeof(XINPUT_STATE));
		memset(&m_JoyKeyStateTrigger[nCnt], 0, sizeof(XINPUT_STATE));

		// �W���C�p�b�h�̐U������̂O�N���A
		ZeroMemory(&m_JoyMoter[nCnt], sizeof(XINPUT_VIBRATION));

		// �U������p�̏�����
		m_nStrength[nCnt] = 0;
		m_nTime[nCnt] = 0;
		m_bUseJoypad[nCnt] = false;
	}
	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CInputJoyPad::Uninit(void)
{
	// XInput�̃X�e�[�g��ݒ�i�����ɂ���j
	XInputEnable(false);
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CInputJoyPad::Update(void)
{
	XINPUT_STATE JoyKeyState[MAX_PLAYER];		// �W���C�p�b�h���͏��

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		// �W���C�p�b�h�̏�Ԃ��擾
		if (XInputGetState(nCnt, &JoyKeyState[nCnt]) == ERROR_SUCCESS)
		{
			m_JoyKeyStateTrigger[nCnt].Gamepad.wButtons
				= ~m_JoyKeyState[nCnt].Gamepad.wButtons
				& JoyKeyState[nCnt].Gamepad.wButtons; // �g���K�[����ۑ�
			m_JoyKeyState[nCnt] = JoyKeyState[nCnt];  // �v���X����
			m_bUseJoypad[nCnt] = true;
		}
		else
		{
			m_bUseJoypad[nCnt] = false;
		}

		// �W���C�p�b�h�̐U��
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
// �W���C�p�b�h�v���X����
//--------------------------------------------------
bool CInputJoyPad::GetJoypadPress(JOYKEY Key, int nPlayer)
{
	return (m_JoyKeyState[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//--------------------------------------------------
// �W���C�p�b�h�g���K�[����
//--------------------------------------------------
bool CInputJoyPad::GetJoypadTrigger(JOYKEY Key, int nPlayer)
{
	return (m_JoyKeyStateTrigger[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//--------------------------------------------------
// �W���C�p�b�h�X�e�B�b�N����
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
// �W���C�p�b�h�g���K�[�y�_������
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
// �W���C�p�b�h�̎g�p�󋵂��擾
//--------------------------------------------------
bool * CInputJoyPad::GetUseJoypad(void)
{
	return &m_bUseJoypad[0];
}
