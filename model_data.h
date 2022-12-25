//**************************************************
// model_data.h
// Author: Buriya Kota
//**************************************************
#ifndef _MODEL_DATA_H_
#define _MODEL_DATA_H_

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//**************************************************
// �}�N����`
//**************************************************
#define MAX_TEXTURE				(54)

//==================================================
// ��`
//==================================================
class CModelData
{
public: /* ��` */
	enum MODEL_TYPE
	{
		MODEL_PLAYER_BODY = 0,		// ��
		MODEL_PLAYER_HEAD,			// ��
		MODEL_PLAYER_RIGHT_ARM,		// �E�r
		MODEL_PLAYER_LEFT_ARM,		// ���r
		MODEL_PLAYER_BOARD,			// ��
		MODEL_PLAYER_LFT_THIGH,		// ��������
		MODEL_PLAYER_RIGHT_THIGH,	// �E������
		MODEL_PLAYER_LEFT_LEG,		// ����
		MODEL_PLAYER_RIGHT_LEG,		// �E��
		MODEL_BALL,					// ��
		MODEL_GIMMICK,				// �M�~�b�N
		MODEL_GOAL,					// �S�[��
		MODEL_MAX,					// �ő吔
		MODEL_NONE,					// �g�p���Ȃ�
	};

	struct MODEL
	{
		// ���b�V��(���_�̏W�܂�)���ւ̃|�C���^
		LPD3DXMESH mesh;
		// �}�e���A�����ւ̃|�C���^	���@1��X�t�@�C���ɕ����̃}�e���A���������Ă���
		LPD3DXBUFFER buffMat;
		// �}�e���A�����̐�
		DWORD numMat;
		// �e�N�X�`���̗񋓌^
		LPDIRECT3DTEXTURE9 texture[MAX_TEXTURE];
		// �ő�l
		D3DXVECTOR3 vtxMax;
		// �ŏ��l
		D3DXVECTOR3 vtxMin;
		// �傫��
		D3DXVECTOR3 size;
	};

	static const char* s_FileName[];	// �t�@�C���p�X

public:
	CModelData();		// �f�t�H���g�R���X�g���N�^
	~CModelData();		// �f�X�g���N�^

	void LoadAll();								// �S�Ă̓ǂݍ���
	void Load(MODEL_TYPE inModel);				// �w��̓ǂݍ���
	void ReleaseAll();							// �S�Ă̔j��
	void Release(MODEL_TYPE inModel);			// �w��̔j��
	MODEL GetModel(MODEL_TYPE inModel);	// ���̎擾

private:
	MODEL m_model[MODEL_MAX];
};

#endif // !_MODEL_DATA_H_
