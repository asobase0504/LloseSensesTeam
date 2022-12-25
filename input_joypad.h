//==================================================
// input_joypad.h
// Author: Buriya Kota
//==================================================
#ifndef _INPUT_JOYPAD_H_
#define _INPUT_JOYPAD_H_

//**************************************************
// �C���N���[�h
//**************************************************
#pragma comment(lib,"xinput.lib")		// ���͏����ɕK�v�i�W���C�p�b�g�j

#include "input.h"
#include <Xinput.h>

//**************************************************
// �N���X
//**************************************************
class CInputJoyPad
{
private:
	static const int MAX_PLAYER = 4;		//�v���C���[�̍ő�l��

public:
	//�L�[���(�W���C�p�b�h)
	enum JOYKEY
	{
		JOYKEY_UP = 0,			// �\���{�^����
		JOYKEY_DOWN,			// �\���{�^����
		JOYKEY_LEFT,			// �\���{�^����
		JOYKEY_RIGHT,			// �\���{�^���E
		JOYKEY_START,			// �X�^�[�g�{�^��
		JOYKEY_BACK,			// �o�b�N�{�^��
		JOYKEY_LEFT_THUMB,		// ���X�e�B�b�N������
		JOYKEY_RIGHT_THUMB,		// �E�X�e�B�b�N������
		JOYKEY_LEFT_SHOULDER,	// L�P�{�^��
		JOYKEY_RIGHT_SHOULDER,	// R�P�{�^��
		JOYKEY_LEFT_TRIGGER,	// L�Q�g���K�[
		JOYKEY_RIGHT_TRIGGER,	// R�Q�g���K�[
		JOYKEY_A,				// A�{�^��
		JOYKEY_B,				// B�{�^��
		JOYKEY_X,				// X�{�^��
		JOYKEY_Y,				// Y�{�^��
		JOYKEY_LEFT_STICK,		// ���X�e�B�b�N
		JOYKEY_RIGHT_STICK,		// �E�X�e�B�b�N
		JOYKEY_MAX
	};

	CInputJoyPad();
	~CInputJoyPad();

	// ���͏����S���̏�����
	HRESULT Init();
	// ���͏����S���̏I������
	void Uninit();
	// ���͏����S���̍X�V����
	void Update();

	// �v���g�^�C�v�錾�W���C�p�b�g
	// �W���C�p�b�h�v���X����
	bool GetJoypadPress(JOYKEY Key, int nPlayer);
	// �W���C�p�b�h�g���K�[����
	bool GetJoypadTrigger(JOYKEY Key, int nPlayer);
	// �W���C�p�b�h�X�e�B�b�N����
	D3DXVECTOR3 GetJoypadStick(JOYKEY Key, int nPlayer);
	// �W���C�p�b�h�g���K�[�y�_������
	int GetJoypadTriggerPedal(JOYKEY Key, int nPlayer);
	// �W���C�p�b�h�̎g�p�󋵂��擾
	bool *GetUseJoypad();

private:
	//�W���C�p�b�h
	XINPUT_STATE m_JoyKeyState[MAX_PLAYER];				//�W���C�p�b�g�̃v���X���
	XINPUT_STATE m_JoyKeyStateTrigger[MAX_PLAYER];		//�W���C�p�b�g�̃g���K�[���
	D3DXVECTOR3 m_JoyStickPos[MAX_PLAYER];				//�W���C�X�e�B�b�N�̌X��
	XINPUT_VIBRATION m_JoyMoter[MAX_PLAYER];			//�W���C�p�b�h�̃��[�^�[
	int m_nTime[MAX_PLAYER];							//�U����������
	WORD m_nStrength[MAX_PLAYER];						//�U���̋��� (0 - 65535)
	bool m_bUseJoypad[MAX_PLAYER];						//�W���C�p�b�h���g�p���Ă邩�ǂ���


};

#endif // _INPUT_JOYPAD_H_