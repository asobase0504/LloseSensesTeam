//==================================================
// result.h
// Author: Buriya Kota
//==================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "game_mode.h"
#include "texture.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************
class CObject2D;

//**************************************************
// �N���X
//**************************************************
class CResult : public CGameMode
{
public:
	CResult();
	~CResult() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override {}

	static CResult *Create();

private:
	// �I�u�W�F�N�g2D�̔�
	CObject2D *m_pObject2D[2];
	// �ʒu
	D3DXVECTOR3 m_pos;
	// �傫��
	D3DXVECTOR3 m_size;

};

#endif	// _RESULT_H_