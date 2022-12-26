//==================================================
// object.h
// Author: Buriya Kota
//==================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

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
class CObject
{
public:
	// �I�u�W�F�N�g�̍ő吔
	static const int MAX_OBjECT = 384;
	// �v���C�I���e�B�̍ő吔
	static const int MAX_PRIO = 6;

	enum TYPE_3D
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,
		TYPE_ENEMY,
		TYPE_BULLET,
		TYPE_BOSS_BULLET,
		TYPE_HOMING_LASER,
		TYPE_EXPLOSION,
		TYPE_EFFECT,
		TYPE_BILL,
		TYPE_ROAD,
		TYPE_SCORE,
		TYPE_NUMBER,
		TYPE_LIFE,
		TYPE_MODE,
		TYPE_BOSS,
		TYPE_ITEM,
		TYPE_LOCKON_UI,
		TYPE_WIND,
		TYPE_MAX
	};

	enum PRIORITY
	{
		PRIORITY_BG = 0,
		PRIORITY_PLAYER,
		PRIORITY_OBJECT,
		PRIORITY_EFFECT,
		PRIORITY_UI,
		PRIORITY_FADE,
		PRIORITY_MAX
	};

public:
	explicit CObject(int nPriority = PRIORITY_OBJECT);
	virtual ~CObject();

	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// ���ׂĂ̔j���A�X�V�A�`��
	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();

	static void ReleaseWithoutMode();

	void SetType(TYPE_3D type) { m_type = type; }

	TYPE_3D GetType() { return m_type; }

	void DeletedObj();
	bool IsDeleted() { return m_bDeleted; }

protected:
	void Release();

private:
	// �擪�̃I�u�W�F�N�g�̃|�C���^
	static CObject *m_pTop[MAX_PRIO];
	// ���݁i��Ԍ��j�̃I�u�W�F�N�g�ւ̃|�C���^
	static CObject *m_pCurrent[MAX_PRIO];
	// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pPrev;
	// ���̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pNext;

	// �^�C�v
	TYPE_3D m_type;
	// ����
	static int m_nNumAll;
	// �ԍ�
	int m_Index;
	// �v���C�I���e�B�ԍ�
	int m_nPriority;
	// �폜���ꂽ���ǂ���
	bool m_bDeleted;
};

// ���̓����蔻��
bool IsCollisionSphere(D3DXVECTOR3 targetPos, D3DXVECTOR3 pos, D3DXVECTOR3 targetSize, D3DXVECTOR3 size);
bool IsCollision(D3DXVECTOR3 targetPos, D3DXVECTOR3 pos, D3DXVECTOR3 targetSize, D3DXVECTOR3 size);

#endif	// _OBJECT_H_