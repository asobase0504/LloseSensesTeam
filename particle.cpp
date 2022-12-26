#include "particle.h"
#include "object2D.h"

CParticle::CParticle(int nPriority) :
	CObject2D(nPriority)
{
}

CParticle::~CParticle()
{
}

HRESULT CParticle::Init()
{
	CObject2D::Init();
	return S_OK;
}

void CParticle::Uninit()
{
	CObject2D::Uninit();
}

void CParticle::Update()
{
	CObject2D::Update();

	m_life--;

	if (m_life < 0)
	{
		Release();
	}

	MovePos(m_move);
}

void CParticle::Draw()
{
	CObject2D::Draw();
}

CParticle * CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int life, int nPriority)
{
	CParticle *pObject2D;
	pObject2D = new CParticle(nPriority);

	if (pObject2D != nullptr)
	{
		pObject2D->Init();
		pObject2D->SetPos(pos);
		pObject2D->SetSize(size);
		pObject2D->SetLife(life);
	}
	else
	{
		assert(false);
	}

	return pObject2D;
}
