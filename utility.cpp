//==================================================
// utility.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include "utility.h"
#include "manager.h"
#include "camera.h"

//--------------------------------------------------
// ���[���h���W����X�N���[�����W�ɕύX����֐�
//--------------------------------------------------
D3DXVECTOR3 GetWorldToScreenPos(const D3DXVECTOR3& pos)
{
	// https://dxlib.xsrv.jp/cgi/patiobbs/patio.cgi?mode=view&no=3145

	D3DXMATRIX mtx;

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtx, pos.x, pos.y, pos.z);

	// �r���[�ϊ��ƃv���W�F�N�V�����ϊ�
	mtx = mtx * CManager::GetCamera()->GetViewMatrix() * CManager::GetCamera()->GetProjMatrix();

	// ���W���擾
	D3DXVECTOR3 pOut(mtx.m[3]);

	// z�Ŋ�����-1~1�͈̔͂Ɏ��߂�
	pOut /= pOut.z;

	// �X�N���[���s��
	D3DXMATRIX viewport;
	D3DXMatrixIdentity(&viewport);
	viewport._11 = CManager::SCREEN_WIDTH / 2.0f; 
	viewport._22 = -CManager::SCREEN_HEIGHT / 2.0f;
	viewport._41 = CManager::SCREEN_WIDTH / 2.0f;
	viewport._42 = CManager::SCREEN_HEIGHT / 2.0f;

	// �X�N���[���ϊ�
	D3DXVec3TransformCoord(&pOut, &pOut, &viewport);

	return pOut;

#if 0
	// http://yamatyuu.net/computer/program/directx9/3dview/index.html

	D3DVIEWPORT9 viewport;
	viewport.X = 0.0f;
	viewport.Y = 0.0f;

	// �r���[�|�[�g�̕�
	viewport.Width = CManager::SCREEN_WIDTH;
	// �r���[�|�[�g�̍���
	viewport.Height = CManager::SCREEN_HEIGHT;
	// �r���[�|�[�g�[�x�ݒ�
	viewport.MinZ = 0.0f;
	viewport.MaxZ = 1.0f;

	D3DXMATRIX view, proj, mtxWorld;

	// �r���[�s��Ǝˉe�s��̎擾
	view = CManager::GetCamera()->GetViewMatrix();
	proj = CManager::GetCamera()->GetProjMatrix();
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	D3DXVECTOR3 pOut;
	D3DXVec3Project(&pOut, &pos, &viewport, &proj, &view, &mtxWorld);

	return pOut;
#endif
}

//--------------------------------------------------
// 2D�x�N�g���̊O��
//--------------------------------------------------
float Vec2Cross(D3DXVECTOR3* v1, D3DXVECTOR3* v2)
{
	return v1->x * v2->z - v1->z * v2->x;
}

//--------------------------------------------------
// 2D�x�N�g���̓���
//--------------------------------------------------
float D3DXVec2Dot(D3DXVECTOR3* v1, D3DXVECTOR3* v2)
{
	return v1->x * v2->x + v1->z * v2->z;
}

//---------------------------------------------------------------------------
// �����_�̃����_��
//---------------------------------------------------------------------------
float FloatRandam(float fMax, float fMin)
{
	return ((rand() / (float)RAND_MAX) * (fMax - fMin)) + fMin;
}
