//==================================================
// object2D.h
// Author: Buriya Kota
//==================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//**************************************************
// インクルード
//**************************************************
#include "main.h"
#include "texture.h"
#include "object.h"

//**************************************************
// 前方前言　実態はNG　ポインタだけならOK
//**************************************************

//**************************************************
// 定数定義
//**************************************************
// 頂点フォーマット
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

//**************************************************
// 構造体定義
//**************************************************
// 頂点データ
struct VERTEX_2D
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 座標変換用係数(1.0fで固定)
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャの座標
};

//**************************************************
// クラス
//**************************************************
class CObject2D : public CObject
{
public:
	explicit CObject2D(int nPriority = PRIORITY_OBJECT);
	~CObject2D() override;

	virtual HRESULT Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;

	void SetTexture(CTexture::TEXTURE texture) { m_texture = texture; }	// テクスチャの設定
	void AnimTexture(int nPattern, int nPatternMax);

	static CObject2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,int nPriority = PRIORITY_OBJECT);

	void SetPos(const D3DXVECTOR3& pos) { m_posOrigin = pos; }
	void SetRot(const D3DXVECTOR3& rot) { m_rot = rot; }
	void SetSize(const D3DXVECTOR3& size) { m_fSize = size; }
	void SetCol(const D3DXCOLOR& col);

	void MovePos(const D3DXVECTOR3& move) { m_posOrigin += move; }

	const D3DXVECTOR3& GetPos() const { return m_posOrigin; }
	const D3DXVECTOR3& GetRot() const { return m_rot; }
	const D3DXVECTOR3& GetSize() const { return m_fSize; }
	const D3DXCOLOR& GetCol() const { return m_col; }

private:
	// 元の座標
	D3DXVECTOR3 m_posOrigin;
	// 四角形の大きさ変更
	D3DXVECTOR3 m_fSize;
	// ポリゴンの色
	D3DXCOLOR m_col;
	// 角度
	D3DXVECTOR3 m_rot;
	// 頂点バッファへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	// テクスチャの列挙型
	CTexture::TEXTURE m_texture;
	// タイマー
	float m_fTimer;
};

#endif	// _OBJECT2D_H_