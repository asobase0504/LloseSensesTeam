//==================================================
// object2D.h
// Author: Buriya Kota
//==================================================
#ifndef _BG_H_
#define _BG_H_

//**************************************************
// インクルード
//**************************************************
#include "main.h"
#include "object.h"

//**************************************************
// 前方前言　実態はNG　ポインタだけならOK
//**************************************************
class CObject2D;

//**************************************************
// クラス
//**************************************************
class CBG : public CObject
{
public:
	explicit CBG(int nPriority = PRIORITY_OBJECT);
	~CBG() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetTexture(int i);
private:
	CObject2D* m_bg[4];
	CObject2D* m_tree[4][4];

	int select;
	float alpha;
};

#endif	// _OBJECT2D_H_