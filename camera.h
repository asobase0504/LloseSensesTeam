//--------------------------------------------------
// camera.h
// Author: Buriya Kota
//--------------------------------------------------
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "renderer.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************
class CPlayer3D;

//**************************************************
// �N���X
//**************************************************
class CCamera
{
public:
	CCamera();
	~CCamera();

	void Init();
	void Uninit();
	void Update();

	void Set();
	D3DXVECTOR3 GetPos() { return m_worldPosR; }
	D3DXMATRIX GetViewMatrix() { return m_mtxView; }
	D3DXMATRIX GetProjMatrix() { return m_mtxProjection; }
	const D3DXVECTOR3& GetRot() { return m_rot; }

private:
	D3DXVECTOR3 m_rot;			// ����
	D3DXVECTOR3 m_worldPosV;	// ���_�i���[���h�j
	D3DXVECTOR3 m_worldPosR;	// �����_�i���[���h�j
	D3DXVECTOR3 m_localPosV;	// ���_�i���[�J���j
	D3DXVECTOR3 m_localPosR;	// �����_�i���[�J���j
	D3DXVECTOR3 m_posVDest;		// �ړI
	D3DXVECTOR3 m_posRDest;		// �ړI
	D3DXVECTOR3 m_vecU;			// ������x�N�g��
	D3DXMATRIX m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;		// �r���[�}�g���b�N�X
	D3DXVECTOR3 m_rotDest;		// ����
	float m_fDis;				// ���_���璍���_�܂ł̋���
	CPlayer3D *m_player;		// �v���C���[�̏��
};

#endif
