//==================================================
// light.h
// Author: Buriya Kota
//==================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "renderer.h"

//**************************************************
// �N���X
//**************************************************
class CLight
{
public:
	static const int MAX_LIGHT = 3;		// ���C�g�̍ő吔

public:
	CLight();
	~CLight();

	//�v���g�^�C�v�錾
	void Init();
	void Uninit();
	void Update();
	void Set(D3DLIGHTTYPE type, D3DXCOLOR col, D3DXVECTOR3 vec, int nNum);
	D3DLIGHT9 Get() { return m_light[0]; }

private:
	D3DLIGHT9 m_light[MAX_LIGHT];				// ���C�g���

};

#endif