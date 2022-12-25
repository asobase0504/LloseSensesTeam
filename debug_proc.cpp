//==================================================
// debug_proc.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <tchar.h> // _T

#include "manager.h"

#include "debug_proc.h"

//**************************************************
// �ÓI�����o�ϐ�
//**************************************************
LPD3DXFONT CDebugProc::m_pFont = nullptr;
char CDebugProc::m_str[1024] = {};

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CDebugProc::CDebugProc()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CDebugProc::~CDebugProc()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CDebugProc::Init()
{
#ifdef _DEBUG
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);
#endif

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CDebugProc::Uninit()
{
}

//--------------------------------------------------
// �o�^
//--------------------------------------------------
void CDebugProc::Print(const char *pFormat, ...)
{
	char strCpy[256] = {};

	va_list args;
	va_start(args, pFormat);
	vsprintf(strCpy, pFormat, args);
	va_end(args);

	strcat(m_str, strCpy);
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CDebugProc::Draw()
{
	RECT rect = { 0, 0, CManager::SCREEN_WIDTH, CManager::SCREEN_HEIGHT };

	if (m_pFont != nullptr)
	{// �e�L�X�g�`��
		m_pFont->DrawText(NULL, m_str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		m_str[0] = '\0';
	}
}
