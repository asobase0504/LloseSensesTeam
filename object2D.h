//==================================================
// object2D.h
// Author: Buriya Kota
//==================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "main.h"
#include "texture.h"
#include "object.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************

//**************************************************
// �萔��`
//**************************************************
// ���_�t�H�[�}�b�g
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

//**************************************************
// �\���̒�`
//**************************************************
// ���_�f�[�^
struct VERTEX_2D
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`���̍��W
};

//**************************************************
// �N���X
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

	void SetTexture(CTexture::TEXTURE texture) { m_texture = texture; }	// �e�N�X�`���̐ݒ�
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
	// ���̍��W
	D3DXVECTOR3 m_posOrigin;
	// �l�p�`�̑傫���ύX
	D3DXVECTOR3 m_fSize;
	// �|���S���̐F
	D3DXCOLOR m_col;
	// �p�x
	D3DXVECTOR3 m_rot;
	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	// �e�N�X�`���̗񋓌^
	CTexture::TEXTURE m_texture;
	// �^�C�}�[
	float m_fTimer;
};

#endif	// _OBJECT2D_H_