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

	m_bg = CObject2D::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(CManager::SCREEN_WIDTH, CManager::SCREEN_HEIGHT, 0.0f), PRIORITY_BG);
	m_tree[0] = CObject2D::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.15f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(350.0f, 600.0f, 0.0f), PRIORITY_BG);
	m_tree[1] = CObject2D::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.85f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(350.0f, 600.0f, 0.0f), PRIORITY_BG);

	m_bg->SetTexture(CTexture::TEXTURE_BG0);
	m_tree[0]->SetTexture(CTexture::TEXTURE_TREE0);
	m_tree[1]->SetTexture(CTexture::TEXTURE_TREE0);
	return E_NOTIMPL;
}

void CBG::Uninit()
{
	CObject::DeletedObj();
}

void CBG::Update()
{
}

void CBG::Draw()
{
}

void CBG::SetTexture(int i)
{
	switch (i)
	{
	case 0:
		m_bg->SetTexture(CTexture::TEXTURE_BG0);
		m_tree[0]->SetTexture(CTexture::TEXTURE_TREE0);
		m_tree[1]->SetTexture(CTexture::TEXTURE_TREE0);
		break;
	case 1:
		m_bg->SetTexture(CTexture::TEXTURE_BG1);
		m_tree[0]->SetTexture(CTexture::TEXTURE_TREE1);
		m_tree[1]->SetTexture(CTexture::TEXTURE_TREE1);
		break;
	case 2:
		m_bg->SetTexture(CTexture::TEXTURE_BG2);
		m_tree[0]->SetTexture(CTexture::TEXTURE_TREE2);
		m_tree[1]->SetTexture(CTexture::TEXTURE_TREE2);
		break;
	case 3:
		m_bg->SetTexture(CTexture::TEXTURE_BG3);
		m_tree[0]->SetTexture(CTexture::TEXTURE_TREE3);
		m_tree[1]->SetTexture(CTexture::TEXTURE_TREE3);
		break;
	default:
		break;
	}
}
