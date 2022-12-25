//==================================================
// number.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include <assert.h>

#include "number.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CNumber::CNumber(int nPriority /* =4 */) : CObject2D(nPriority)
{
	SetType(TYPE_NUMBER);
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CNumber::~CNumber()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CNumber::Init()
{
	CObject2D::Init();

	SetTexture(CTexture::TEXTURE_NONE);

	return S_OK;
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CNumber* CNumber::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	CNumber *pNumber;
	pNumber = new CNumber;

	if (pNumber != nullptr)
	{
		pNumber->Init();
		pNumber->SetPos(pos);
		pNumber->SetSize(size);
	}
	else
	{
		assert(false);
	}

	return pNumber;
}
