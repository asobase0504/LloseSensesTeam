//==================================================
// title.h
// Author: Buriya Kota
//==================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "game_mode.h"
#include "texture.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************
class CObject2D;
class CBG;

//**************************************************
// �N���X
//**************************************************
class CTitle : public CGameMode
{
public:
	static const int BG_TITLE = 2;
	static const int MENU = 2;

public:
	enum SELECT_GAMEMODE
	{
		SELECT_GAMEMODE_START = 0,
		SELECT_GAMEMODE_TUTRIAL,
		SELECT_GAMEMODE_MAX
	};

	CTitle();
	~CTitle() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override {}

	static CTitle *Create();

private:
	// �I�u�W�F�N�g2D�̔�
	CObject2D *m_pObject2D[BG_TITLE];
	CObject2D *m_pMenu[MENU];
	// �ʒu
	D3DXVECTOR3 m_pos;
	// �傫��
	D3DXVECTOR3 m_size;
	// �I�����Ă��郂�[�h�̃J�E���g
	int m_nSelect;
	CBG *m_pBG;

	int randam;
};

#endif	// _TITLE_H_