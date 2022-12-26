//==================================================
// particle.h
// Author: Buriya Kota
//==================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//**************************************************
// インクルード
//**************************************************
#include "main.h"
#include "texture.h"
#include "object2D.h"
#include <unordered_map>

//**************************************************
// 前方前言　実態はNG　ポインタだけならOK
//**************************************************
class CObject2D;

//**************************************************
// クラス
//**************************************************
class CParticle : public CObject2D
{
public:
	explicit CParticle(int nPriority = PRIORITY_OBJECT);
	~CParticle() override;

	virtual HRESULT Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;

	static CParticle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int life,int nPriority = PRIORITY_OBJECT);

	void SetMove(const D3DXVECTOR3& inMove) { m_move = inMove; }

	void SetLife(const int inLife) { m_life = inLife; }
private:
	//std::unordered_map<int, CObject2D*> m_effect;
	//D3DXVECTOR3 m_popSize;
	int m_life;
	D3DXVECTOR3 m_move;
};

#endif	// _OBJECT2D_H_