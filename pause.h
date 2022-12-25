//==================================================
// pause.h
// Author: Buriya Kota
//==================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "object.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************
class CObject2D;

//**************************************************
// �N���X
//**************************************************
class CPause : public CObject
{
public:
	enum SELECT_MODE
	{
		SELECT_MODE_RESTART = 0,
		SELECT_MODE_TAITLE,
		SELECT_MODE_CLOSE,
		SELECT_MODE_MAX
	};

	explicit CPause(int nPriority = PRIORITY_UI);
	~CPause() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override {}

	bool GetIsPause() { return m_IsPause; }

	static CPause *Create();

private:
	// �I�u�W�F�N�g2D�̔�
	CObject2D *m_pObject2D[2];
	CObject2D *m_pMenu[3];
	// �ʒu
	D3DXVECTOR3 m_pos;
	// �傫��
	D3DXVECTOR3 m_size;
	// �I�����Ă��郂�[�h�̃J�E���g
	int m_nSelect;
	// �����|�[�Y�����ǂ���
	bool m_IsPause;
};

#endif	// _PAUSE_H_