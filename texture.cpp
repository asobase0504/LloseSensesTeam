//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
const char* CTexture::s_FileName[] =
{// �e�N�X�`���̃p�X
	"data/TEXTURE/player2.png",		// �v���C���[
	"data/TEXTURE/thumbnail.png",	// �n��
	"data/TEXTURE/shadow000.jpg",	// �e
	"data/TEXTURE/snow.png",		// TITLE_BG
	"data/TEXTURE/TITLE0.png",		// TITLE
	"data/TEXTURE/TUTORIAL.png",	// TUTORIAL
	"data/TEXTURE/START.png",		// START
	"data/TEXTURE/RESULT.png",		// RESULT
	"data/TEXTURE/number001.png",		// �^�C��
	"data/TEXTURE/ranking.png",		// �^�C��
	"data/TEXTURE/����000.png",		// ��
	"data/TEXTURE/hanabira.png",	// �Ԃт�
	"data/TEXTURE/snow1.png",	// ��
	"data/TEXTURE/restart.png",		// ���߂���
	"data/TEXTURE/backTitle.png",	// �^�C�g����
	"data/TEXTURE/close.png",		// ����
	"data/TEXTURE/pause.png",		// �|�[�Y
	"data/TEXTURE/tree3.png",		// ��
	"data/TEXTURE/tree1.png",		// ��
	"data/TEXTURE/tree2.png",		// ��
	"data/TEXTURE/tree4.png",		// ��
	"data/TEXTURE/bg1.png",		// ��
	"data/TEXTURE/bg2.png",		// ��
	"data/TEXTURE/bg3.png",		// ��
	"data/TEXTURE/bg4.png",		// ��
	"data/TEXTURE/tutorial_key.png",		// �`���[�g���A���L�[
	"data/TEXTURE/tutorial_tutorial.png",		// �`���[�g���A���L�[
	"data/TEXTURE/score_text.png",		// ��
};

static_assert(sizeof(CTexture::s_FileName) / sizeof(CTexture::s_FileName[0]) == CTexture::TEXTURE_MAX, "aho");

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTexture::CTexture() :
	s_pTexture()
{
	memset(s_pTexture, 0, sizeof(s_pTexture));
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTexture::~CTexture()
{
}

//--------------------------------------------------
// �S�Ă̓ǂݍ���
//--------------------------------------------------
void CTexture::LoadAll()
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != nullptr)
		{// �e�N�X�`���̓ǂݍ��݂�����Ă���
			continue;
		}

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			s_FileName[i],
			&s_pTexture[i]);
	}
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CTexture::Load(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	if (s_pTexture[inTexture] != nullptr)
	{// �e�N�X�`���̓ǂݍ��݂�����Ă���
		return;
	}

	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		s_FileName[inTexture],
		&s_pTexture[inTexture]);
}

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CTexture::ReleaseAll(void)
{
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != nullptr)
		{// �e�N�X�`���̉��
			s_pTexture[i]->Release();
			s_pTexture[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CTexture::Release(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	if (s_pTexture[inTexture] != nullptr)
	{// �e�N�X�`���̉��
		s_pTexture[inTexture]->Release();
		s_pTexture[inTexture] = nullptr;
	}
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE inTexture)
{
	if (inTexture == TEXTURE_NONE)
	{// �e�N�X�`�����g�p���Ȃ�
		return nullptr;
	}

	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	// �ǂݍ���
	Load(inTexture);

	return s_pTexture[inTexture];
}
