//==================================================
// debug_proc.h
// Author: Buriya Kota
//==================================================
#ifndef _DEBUG_PROC_H_
#define _DEBUG_PROC_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include <functional>

#include "renderer.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************

//**************************************************
// �N���X
//**************************************************
class CDebugProc
{
public:
	CDebugProc();
	~CDebugProc();

	HRESULT Init();
	void Uninit();

	// �o�^�֐�
	static void Print(const char *pFormat, ...);
	// �`��
	static void Draw();

private:
	static LPD3DXFONT m_pFont;
	static char m_str[1024];

};

#endif	// _DEBUG_PROC_H_
