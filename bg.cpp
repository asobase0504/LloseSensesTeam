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
		m_tree[i][1] = CObject2D::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.85f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(350.0f, 600.0f, 0.0f), PRIORITY_BG);
		m_tree[i][2] = CObject2D::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.25f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(325.0f, 550.0f, 0.0f), PRIORITY_BG);
		m_tree[i][3] = CObject2D::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.75f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(325.0f, 550.0f, 0.0f), PRIORITY_BG);
	}

	m_bg[0]->SetTexture(CTexture::TEXTURE_BG0);
	m_tree[0][0]->SetTexture(CTexture::TEXTURE_TREE0);
	m_tree[0][1]->SetTexture(CTexture::TEXTURE_TREE0);
	m_tree[0][2]->SetTexture(CTexture::TEXTURE_TREE0);
	m_tree[0][3]->SetTexture(CTexture::TEXTURE_TREE0);

	m_bg[1]->SetTexture(CTexture::TEXTURE_BG1);
	m_tree[1][0]->SetTexture(CTexture::TEXTURE_TREE1);
	m_tree[1][1]->SetTexture(CTexture::TEXTURE_TREE1);
	m_tree[1][2]->SetTexture(CTexture::TEXTURE_TREE1);
	m_tree[1][3]->SetTexture(CTexture::TEXTURE_TREE1);

	m_bg[2]->SetTexture(CTexture::TEXTURE_BG2);
	m_tree[2][0]->SetTexture(CTexture::TEXTURE_TREE2);
	m_tree[2][1]->SetTexture(CTexture::TEXTURE_TREE2);
	m_tree[2][2]->SetTexture(CTexture::TEXTURE_TREE2);
	m_tree[2][3]->SetTexture(CTexture::TEXTURE_TREE2);

	m_bg[3]->SetTexture(CTexture::TEXTURE_BG3);
	m_tree[3][0]->SetTexture(CTexture::TEXTURE_TREE3);
	m_tree[3][1]->SetTexture(CTexture::TEXTURE_TREE3);
	m_tree[3][2]->SetTexture(CTexture::TEXTURE_TREE3);
	m_tree[3][3]->SetTexture(CTexture::TEXTURE_TREE3);

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
			m_tree[i][0]->SetCol(color);
			m_tree[i][1]->SetCol(color);
			m_tree[i][2]->SetCol(color);
			m_tree[i][3]->SetCol(color);
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
			m_tree[i][0]->SetCol(color);
			m_tree[i][1]->SetCol(color);
			m_tree[i][2]->SetCol(color);
			m_tree[i][3]->SetCol(color);
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
