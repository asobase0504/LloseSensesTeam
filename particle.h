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

	void SetMovePos(const D3DXVECTOR3& inMove) { m_posMove = inMove; }
	void SetMoveRot(const D3DXVECTOR3& inMove) { m_rotMove = inMove; }
	void SetMoveSize(const D3DXVECTOR3& inMove) { m_sizeMove = inMove; }

	void SetLife(const int inLife) { m_life = inLife; }
private:
	int m_life;
	D3DXVECTOR3 m_posMove;
	D3DXVECTOR3 m_rotMove;
	D3DXVECTOR3 m_sizeMove;
};

#endif	// _OBJECT2D_H_