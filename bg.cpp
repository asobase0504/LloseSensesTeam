#include "bg.h"
#include "object2D.h"
#include "manager.h"

CBG::CBG(int nPriority) : CObject(nPriority)
{
	
}

CBG::~CBG()
{
}

HRESULT CBG::Init()
{
	alpha = 0.01f;
	SetTexture(0);
	for (int i = 0; i < 4; i++)
	{
		m_bg[i] = CObject2D::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(CManager::SCREEN_WIDTH, CManager::SCREEN_HEIGHT, 0.0f), PRIORITY_BG);
		m_tree[i][0] = CObject2D::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.15f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(350.0f, 600.0f, 0.0f), PRIORITY_BG);
		m_tree[i][2] = CObject2D::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.25f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(325.0f, 525.0f, 0.0f), PRIORITY_BG);
		m_tree[i][4] = CObject2D::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.35f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(300.0f, 475.0f, 0.0f), PRIORITY_BG);
		m_tree[i][6] = CObject2D::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.45f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(275.0f, 400.0f, 0.0f), PRIORITY_BG);
		m_tree[i][7] = CObject2D::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.55f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(275.0f, 400.0f, 0.0f), PRIORITY_BG);
		m_tree[i][5] = CObject2D::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.65f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(300.0f, 475.0f, 0.0f), PRIORITY_BG);
		m_tree[i][3] = CObject2D::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.75f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(325.0f, 525.0f, 0.0f), PRIORITY_BG);
		m_tree[i][1] = CObject2D::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.85f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(350.0f, 600.0f, 0.0f), PRIORITY_BG);
	}

	m_bg[0]->SetTexture(CTexture::TEXTURE_BG0);
	for (int i = 0; i < 8; i++)
	{
		m_tree[0][i]->SetTexture(CTexture::TEXTURE_TREE0);
	}

	m_bg[1]->SetTexture(CTexture::TEXTURE_BG1);
	for (int i = 0; i < 8; i++)
	{
		m_tree[1][i]->SetTexture(CTexture::TEXTURE_TREE1);
	}

	m_bg[2]->SetTexture(CTexture::TEXTURE_BG2);
	for (int i = 0; i < 8; i++)
	{
		m_tree[2][i]->SetTexture(CTexture::TEXTURE_TREE2);
	}

	m_bg[3]->SetTexture(CTexture::TEXTURE_BG3);
	for (int i = 0; i < 8; i++)
	{
		m_tree[3][i]->SetTexture(CTexture::TEXTURE_TREE3);
	}

	return E_NOTIMPL;
}

void CBG::Uninit()
{
	CObject::DeletedObj();
}

void CBG::Update()
{
	for (int i = 0; i < 4; i++)
	{
		if (select == i)
		{
			D3DXCOLOR color = m_bg[i]->GetCol();
			if (color.a > 1.0f)
			{
				continue;
			}
			color.a += alpha;
			m_bg[i]->SetCol(color);
			for (int j = 0; j < 8; j++)
			{
				m_tree[i][j]->SetCol(color);
			}
		}
		else
		{
			D3DXCOLOR color = m_bg[i]->GetCol();
			if (color.a < 0.0f)
			{
				continue;
			}
			color.a -= alpha;
			m_bg[i]->SetCol(color);
			for (int j = 0; j < 8; j++)
			{
				m_tree[i][j]->SetCol(color);
			}
		}
	}
}

void CBG::Draw()
{
}

void CBG::SetTexture(int i)
{
	select = i;
}
