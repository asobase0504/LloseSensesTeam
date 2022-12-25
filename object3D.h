//==================================================
// object3D.h
// Author: Buriya Kota
//==================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "object.h"
#include "texture.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************

//**************************************************
// �萔��`
//**************************************************
// ���_�t�H�[�}�b�g
const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);		// ���W�E�@���E�J���[�E�e�N�X�`��

//**************************************************
// �\���̒�`
//**************************************************
// ���_�̏��[3D]�̍\���̂��`
struct VERTEX_3D
{
	D3DXVECTOR3 pos;	// ���_���W	
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;		// ���_�J���[	
	D3DXVECTOR2 tex;	// �e�N�X�`���̍��W
};

//**************************************************
// �N���X
//**************************************************
class CObject3D : public CObject
{
public:
	static const float BILLBORAD_WIDTH;
	static const float BILLBOARD_HEIGHT;

public:
	explicit CObject3D(int nPriority = PRIORITY_OBJECT);
	virtual ~CObject3D() override;

	virtual HRESULT Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;

	// �Z�b�^�[
	void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetSize(const D3DXVECTOR3& size) { m_size = size; }
	void SetWorldMtx(const D3DXMATRIX& mtx) { m_mtxWorld = mtx; }
	void SetBillboard(const bool& billboard) { m_bBill = billboard; }
	void SetTexture(CTexture::TEXTURE texture) { m_texture = texture; }	// �e�N�X�`���̐ݒ�
	void SetMove(const D3DXVECTOR3& move) { m_move = move; }

	// �Q�b�^�[
	D3DXVECTOR3 GetMove() { return m_move; }
	const D3DXVECTOR3& GetPos() const { return m_pos; }
	const D3DXVECTOR3& GetSize() const { return m_size; }
	const D3DXMATRIX& GetWorldMtx() const { return m_mtxWorld; }

	static CObject3D *Create(const D3DXVECTOR3 size);

	void AnimTexture(int nPattern, int nPatternMax);
	void MovePos(const D3DXVECTOR3& move) { m_pos += move; }

private:
	// �ʒu
	D3DXVECTOR3 m_pos;
	// �ړ���
	D3DXVECTOR3 m_move;
	// ��]
	D3DXVECTOR3 m_rot;
	// ���_�J���[
	D3DXCOLOR m_col;
	// ���[���h�}�g���b�N�X
	D3DXMATRIX m_mtxWorld;
	// �e�N�X�`���̗񋓌^
	CTexture::TEXTURE m_texture;
	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	// �傫��
	D3DXVECTOR3 m_size;
	// �r���{�[�h���ǂ���
	bool m_bBill;
	// �e�q���ǂ���
	bool m_bFamily;

};

#endif	// _OBJECT3D_H_