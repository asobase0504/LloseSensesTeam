//==================================================
// model.h
// Author: Buriya Kota
//==================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "object.h"
#include "texture.h"
#include "model_data.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************

//**************************************************
// �}�N����`
//**************************************************
#define MAX_MODEL				(54)
#define MAX_TEXTURE				(54)

//**************************************************
// �N���X
//**************************************************
class CModel
{
public:
	CModel();
	~CModel();

	HRESULT Init(CModelData::MODEL_TYPE modelData);
	void Uninit();
	void Update();
	void Draw(D3DXMATRIX *mtxWorld);

	static CModel *Create(CModelData::MODEL_TYPE modelData);

	// �Z�b�^�[
	void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetScale(const D3DXVECTOR3& scale) { m_scale = scale; }
	void SetRot(const D3DXVECTOR3& rot) { m_rot = rot; }
	void SetParent(CModel *pModel) { m_pParent = pModel; }
	void SetModelData(CModelData::MODEL_TYPE modelData) { m_modelData = modelData; }	// ���f���̐ݒ�

	// �Q�b�^�[
	const D3DXVECTOR3& GetPos() const { return m_pos; }
	const D3DXVECTOR3& GetScale() const { return m_scale; }
	const D3DXVECTOR3& GetRot() const { return m_rot; }
	D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }
	CModelData::MODEL_TYPE GetModelData() { return m_modelData; }

	void SetStencil(bool isStencil) { m_isStencil = isStencil; }

private:
	void DrawShadow_();

private:
	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	// ���[���h�}�g���b�N�X
	D3DXMATRIX m_mtxWorld;
	// �ʒu
	D3DXVECTOR3 m_pos;
	// �傫��
	D3DXVECTOR3 m_scale;
	// ����
	D3DXVECTOR3 m_rot;
	// �ŏ��l
	D3DXVECTOR3 m_vtxMinModel;
	// �ő�l
	D3DXVECTOR3 m_vtxMaxModel;
	// �e�̏��
	CModel *m_pParent;
	// 
	int m_nType;
	// 
	bool m_isStencil;
	// ���f���f�[�^�̗񋓌^
	CModelData::MODEL_TYPE m_modelData;
};

#endif	// _MODEL_H_