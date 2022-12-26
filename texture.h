//**************************************************
// texture.h
// Author  : katsuki mizuki
//**************************************************
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// ��`
//==================================================
class CTexture
{
public: /* ��` */
	enum TEXTURE
	{
		TEXTURE_PLAYER = 0,			// �v���C���[
		TEXTURE_GROUND,				// �n��
		TEXTURE_SHADOW,				// �e
		TEXTURE_TITLE_BG,			// TITLE_BG
		TEXTURE_TITLE,				// TITLE
		TEXTURE_TUTORIAL,			// TUTORIAL
		TEXTURE_START,				// START
		TEXTURE_RESULT,				// RESULT
		TEXTURE_NUMBER,				// �^�C��
		TEXTURE_WIND,
		TEXTURE_MAX,
		TEXTURE_NONE,				// �g�p���Ȃ�
	};

	static const char* s_FileName[];	// �t�@�C���p�X

public:
	CTexture();		// �f�t�H���g�R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

public: /* �����o�֐� */
	void LoadAll();										// �S�Ă̓ǂݍ���
	void Load(TEXTURE inTexture);						// �w��̓ǂݍ���
	void ReleaseAll();									// �S�Ă̔j��
	void Release(TEXTURE inTexture);					// �w��̔j��
	LPDIRECT3DTEXTURE9 GetTexture(TEXTURE inTexture);	// ���̎擾

private: /* �����o�ϐ� */
	LPDIRECT3DTEXTURE9 s_pTexture[TEXTURE_MAX];	// �e�N�X�`���̏��
};

#endif // !_TEXTURE_H_
