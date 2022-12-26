//==================================================
// wind.cpp
// Author: Kajita Hiromu
//==================================================
//**************************************************
// include
//**************************************************
#include <assert.h>

#include "manager.h"
#include "season.h"
#include "utility.h"
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
	SetTexture(CTexture::TEXTURE_WIND);

	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFrame = 0;
	fAirFlow = 0.0f;

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CWind::Uninit()
{
	CObject2D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CWind::Update()
{
	switch (CSeason::GetSeason())
	{
	case CSeason::SEASON_SPRING:
	{
		fAirFlow = 0.01f;
	}
	break;

	case CSeason::SEASON_SUMMER:
	{
		fAirFlow = 0.02f;
	}
	break;

	case CSeason::SEASON_FALL:
	{
		fAirFlow = 0.03f;
	}
	break;

	case CSeason::SEASON_WINTER:
		fAirFlow = 0.05f;
		break;
	default:
		break;
	}

	//フレームを加算
	m_nFrame++;

	if (m_nFrame > 60)
	{//フレーム数が45を超えたら
		//ランダムの値を変える
		m_nRandom = FloatRandam(3.0f, 0.0f);

		//フレームを0に戻す
		m_nFrame = 0;
	}

	if (m_nRandom <= 1.5f)
	{//ランダムの値が1.5f以下なら
		m_state = WIND_LEFT;
		m_pos = D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.8f, CManager::SCREEN_WIDTH * 0.3f, 0.0f);
	}
	else
	{//1.5f以上なら
		m_state = WIND_RIGHT;
		m_pos = D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.2f, CManager::SCREEN_WIDTH * 0.3f, 0.0f);
	}

	//posの値を更新
	SetPos(m_pos);
	CObject2D::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CWind::Draw()
{
	CObject2D::Draw();
}

//--------------------------------------------------
// 現在の向きを取得
//--------------------------------------------------
CWind::WIND_ROT CWind::GetState()
{
	return m_state;
}

float CWind::GetAirFlow()
{
	return fAirFlow;
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
