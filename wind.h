//==================================================
// wind.h
// Author: Kajita Hiromu
//==================================================
#ifndef _WIND_H_
#define _WIND_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "object2D.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************

//**************************************************
// �萔��`
//**************************************************

//**************************************************
// �\���̒�`
//**************************************************

//**************************************************
// �N���X
//**************************************************
class CWind : public CObject2D
{
public:
	explicit CWind(int nPriority = PRIORITY_EFFECT);
	~CWind();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetWind(D3DXVECTOR3 rot, float air);

	static CWind *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);

private:
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_size;		//�T�C�Y
	D3DXVECTOR3 m_rot;		//����
	D3DXVECTOR3 m_move;		//�ʒu

};


#endif	// _NUMBER_H_
