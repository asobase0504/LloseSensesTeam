//==================================================
// wind.h
// Author: Kajita Hiromu
//==================================================
#ifndef _WIND_H_
#define _WIND_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "object2D.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************

//**************************************************
// �萔��`
//**************************************************

//**************************************************
// �\���̒�`
//**************************************************

//**************************************************
// �N���X
//**************************************************
class CWind : public CObject2D
{
public:
	enum WIND_ROT	//���݂̌���
	{
		WIND_LEFT,
		WIND_RIGHT,
		WIND_STOP,
		WIND_MAX
	};

	explicit CWind(int nPriority = PRIORITY_EFFECT);
	~CWind();

	HRESULT Init() override;	//������
	void Uninit() override;		//�I������
	void Update() override;		//�X�V����
	void Draw() override;		//�`�揈��

	WIND_ROT GetState();		//��Ԏ擾
	float GetAirFlow();			//���ʎ擾
	static CWind *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	//����

private:
	WIND_ROT m_state;		//���

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_size;		//�T�C�Y
	D3DXVECTOR3 m_rot;		//����
	D3DXVECTOR3 m_move;		//�ʒu
	float fAirFlow;			//����

	int m_nFrame;			//�t���[����
	int m_nSwitchFrame;		//�؂�ւ��t���[��
	int m_nTime;			//���������ς��܂ł̃^�C��
	bool m_bSwitch;			//���������ς��^�C�~���O
	float m_nRandom;		//�����_���p�ϐ�
	WIND_ROT m_nextRot;
};


#endif	// _NUMBER_H_
