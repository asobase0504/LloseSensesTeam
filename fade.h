//==================================================
// fade.h
// Author: Buriya Kota
//==================================================
#ifndef _FADE_H_
#define _FADE_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "object2D.h"

//**************************************************
// �N���X
//**************************************************
class CFade : CObject2D
{
private:
	explicit CFade(int nPriority = PRIORITY_FADE);

public:
	// �t�F�[�h�̏��
	enum FADE
	{
		FADE_NONE = 0,			//�������ĂȂ�
		FADE_IN,				//�t�F�[�h�C��
		FADE_OUT,				//�t�F�[�h�A�E�g
		FADE_MAX
	};

	~CFade();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	void SetFade(CManager::MODE modeNext);
	FADE GetFade() { return m_fade; }

	static CFade *GetInstance();

private:
	static CFade *m_pFade;
	// �I�u�W�F�N�g2D�̔�
	CObject2D *m_pObject2D;
	// ���̉��
	CManager::MODE m_modeNext;
	// �t�F�[�h�̏��
	FADE m_fade;
	// �t�F�[�h�̑��x
	float m_fFadeSpeed;
	// ���l�̏��
	float m_fMaxAlpha;
};

#endif	// _FADE_H_