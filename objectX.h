//==================================================
// objectX.h
// Author: Buriya Kota
//==================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "main.h"
#include "texture.h"
#include "object.h"
#include "model_data.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************

//**************************************************
// �N���X
//**************************************************
class CObjectX : public CObject
{
public:
	static const int NUM_TEXTURE = 16;
	static const int MAX_BILLBOARD = 5;
	static const float BILLBORAD_WIDTH;
	static const float BILLBOARD_HEIGHT;

public:
	explicit CObjectX(int nPriority = PRIORITY_OBJECT);
	virtual ~CObjectX() override;

	virtual HRESULT Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;

	// �Z�b�^�[
	void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetPosOld(const D3DXVECTOR3& posOld) { m_posOld = posOld; }
	void SetSize(const D3DXVECTOR3& size) { m_size = size; }
	void SetMove(const D3DXVECTOR3& move) { m_move = move; }
	void SetRot(const D3DXVECTOR3& rot) { m_rot = rot; }
	void SetRotDest(const D3DXVECTOR3& rotDest) { m_rotDest = rotDest; }
	void SetLife(const int &life) { m_nLife = life; }
	void SetWorldMtx(const D3DXMATRIX& mtx) { m_mtxWorld = mtx; }
	void SetQuat(const bool& quatanion) { m_bQuat = quatanion; }
	void SetVecAxis(D3DXVECTOR3 vecAxis) { m_vecAxis = vecAxis; }
	void SetValueRot(float valueRot) { m_fValueRot = valueRot; }
	void SetModelData(CModelData::MODEL_TYPE modelData) { m_modelData = modelData; }	// ���f���̐ݒ�

	// �Q�b�^�[
	D3DXVECTOR3 GetMove() { return m_move; }
	//D3DXVECTOR3 *GetPosPointer() { return &m_posOrigin; }
	const D3DXVECTOR3& GetPos() const { return m_pos; }
	const D3DXVECTOR3& GetPosOld() const { return m_posOld; }
	const D3DXVECTOR3& GetSize() const { return m_size; }
	const D3DXVECTOR3& GetRot() const { return m_rot; }
	const D3DXVECTOR3& GetRotDest() const { return m_rotDest; }
	D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }
	D3DXVECTOR3 GetVtxMax() { return m_vtxMaxModel; }
	D3DXVECTOR3 GetVtxMin() { return m_vtxMinModel; }
	CModelData::MODEL_TYPE GetModelData() { return m_modelData; }

	// �ړ��ʑ��
	void MovePos(const D3DXVECTOR3& move) { m_pos += move; }

	// �p�x�̐��K��
	D3DXVECTOR3 RotNormalization(D3DXVECTOR3 rot);
	D3DXVECTOR3 RotDestNormalization(D3DXVECTOR3 rot, D3DXVECTOR3 rotDest);

	static CObjectX *Create();

private:
	void DrawShadow_();

private:
	// �ʒu
	D3DXVECTOR3 m_pos;
	// �ߋ��̈ʒu
	D3DXVECTOR3 m_posOld;
	// �ʒu
	D3DXVECTOR3 m_move;
	// ����
	D3DXVECTOR3 m_rot;
	// ����
	D3DXVECTOR3 m_rotDest;
	// �ŏ��l
	D3DXVECTOR3 m_vtxMinModel;
	// �ő�l
	D3DXVECTOR3 m_vtxMaxModel;
	// ���[���h�}�g���b�N�X
	D3DXMATRIX m_mtxWorld;
	// �e�N�X�`���̗񋓌^
	LPDIRECT3DTEXTURE9 m_texture[NUM_TEXTURE];
	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	// ���b�V��(���_�̏W�܂�)���ւ̃|�C���^
	LPD3DXMESH m_mesh;
	// �}�e���A�����ւ̃|�C���^	���@1��X�t�@�C���ɕ����̃}�e���A���������Ă���
	LPD3DXBUFFER m_buffMat;
	// �}�e���A�����̐�
	DWORD m_numMat;
	// �傫��
	D3DXVECTOR3 m_size;
	// �̗�
	int m_nLife;
	// �N�H�[�^�j�I�����ǂ���
	bool m_bQuat;
	// 
	D3DXMATRIX m_mtxRot;
	// �N�H�[�^�j�I��
	D3DXQUATERNION m_quat;
	// ��]��
	D3DXVECTOR3 m_vecAxis;
	// ��]�p
	float m_fValueRot;
	// ���f���f�[�^�̗񋓌^
	CModelData::MODEL_TYPE m_modelData;
};

#endif	// _OBJECTX_H_