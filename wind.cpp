//==================================================
// wind.cpp
// Author: Kajita Hiromu
//==================================================
//**************************************************
// include
//**************************************************
#include <assert.h>

#include "wind.h"
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CWind::CWind(int nPriority /* =4 */) : CObject2D(nPriority)
{
	SetType(TYPE_WIND);
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CWind::~CWind()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CWind::Init()
{
	CObject2D::Init();

	SetTexture(CTexture::TEXTURE_GROUND);

	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

void CWind::Uninit()
{
	CObject2D::Uninit();
}

void CWind::Update()
{
	CObject2D::Update();
}

void CWind::Draw()
{
	CObject2D::Draw();
}

void CWind::SetWind(D3DXVECTOR3 rot, float air)
{
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CWind * CWind::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	CWind *pWind;
	pWind = new CWind;

	if (pWind != nullptr)
	{
		pWind->Init();
		pWind->SetPos(pos);
		pWind->SetSize(size);
	}
	else
	{
		assert(false);
	}

	return pWind;
}
