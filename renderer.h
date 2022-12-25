//==================================================
// renderer.h
// Author: Buriya Kota
//==================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include <d3dx9.h>

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************

//**************************************************
// �N���X
//**************************************************
class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(const HWND hWnd, const bool bWindow);
	void Uninit();
	void Update();
	void Draw();
	LPDIRECT3DDEVICE9 GetDevice();		// {return m_pD3DDevice;} return���邾���Ȃ炱������������������

private:
	void DrawFPS();

private:
	// Direct3D�I�u�W�F�N�g
	LPDIRECT3D9 m_pD3D;
	// Device�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	// �t�H���g
	LPD3DXFONT m_pFont;
	// ���C���[�t���[���̐؂�ւ�
	bool m_bMesh;
};

#endif	// _RENDERER_H_