//==================================================
// manager.h
// Author: Buriya Kota
//==================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include <d3dx9.h>

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
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
// �N���X
//**************************************************
class CManager
{
public:
	// �X�N���[���̕�
	static const int SCREEN_WIDTH = 1280;
	// �X�N���[���̍���
	static const int SCREEN_HEIGHT = 720;

public:
	//���(���[�h)�̎��
	enum MODE
	{
		MODE_TITLE = 0,		//�^�C�g�����
		MODE_TUTORIAL,		//�`���[�g���A��
		MODE_GAME,			//�Q�[�����
		MODE_GAMEOVER,		//�Q�[���I�[�o�[���
		MODE_RESULT,		//���U���g���
		MODE_RANKING,		//�����L���O
		MODE_MAX
	};

	CManager();
	~CManager();

	HRESULT Init(const HINSTANCE hInstance, const HWND hWnd);
	void Uninit();
	void Update();
	void Draw();

	static CManager *Create(const HINSTANCE hInstance, const HWND hWnd);
	// �����_���[�̏��̎擾
	static CRenderer *GetRenderer() { return m_pRenderer; }
	// �L�[�{�[�h�̏��̎擾
	static CInputKeyboard *GetInputKeyboard() { return m_pInputKeyboard; }
	// �W���C�p�b�h�̏��̎擾
	static CInputJoyPad *GetInputJoyPad() { return m_pInputJoyPad; }
	// �e�N�X�`���̏��̎擾
	static CTexture* GetTexture() { return m_pTexture; }
	// ���f���f�[�^�̏��̎擾
	static CModelData* GetModelData() { return m_pModelData; }
	// �J�����̏��̎擾
	static CCamera* GetCamera() { return m_pCamera; }
	// ���C�g�̏��̎擾
	static CLight* GetLight() { return m_pLight; }
	// �}�l�[�W���[�̏��̎擾
	static CManager* GetManager() { return m_pManager; }

	// �T�E���h���̎擾
	static CSound* GetSound() { return m_pSound; }

	static void SetNowScore(int score) { m_nowScore = score; }
	static int GetNowScore() { return m_nowScore; }

	static MODE GetGameMode() { return m_mode; }

	static void SetMode(MODE mode);

private:
	// ���݂̃��[�h
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

	// ���݂̃X�R�A
	static int m_nowScore;

};

#endif	// _MANAGER_H_