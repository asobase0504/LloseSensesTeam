//==================================================
// object.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include <time.h>
#include <assert.h>

#include "object.h"
#include "object2D.h"
#include "renderer.h"

//**************************************************
// �ÓI�����o�ϐ�
//**************************************************
int CObject::m_nNumAll = 0;
CObject *CObject::m_pTop[] = {};
CObject *CObject::m_pCurrent[] = {};

//--------------------------------------------------
// �v���C�I���e�B���g�����R���X�g���N�^
//--------------------------------------------------
CObject::CObject(int nPriority /* PRIORITY_3 */) : m_pPrev(nullptr), m_pNext(nullptr)
{
	if (m_pTop[nPriority] == nullptr)
	{// Top��nullptr�̎�
		m_pTop[nPriority] = this;
	}
	else
	{// Top�����łɐ�������Ă���Ƃ�
		m_pCurrent[nPriority]->m_pNext = this;
		this->m_pPrev = m_pCurrent[nPriority];
	}

	m_pCurrent[nPriority] = this;

	m_nPriority = nPriority;
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CObject::~CObject()
{
}

//--------------------------------------------------
// ���ׂĂ̔j��
//--------------------------------------------------
void CObject::ReleaseAll()
{
	for (int nCnt = 0; nCnt < MAX_PRIO; nCnt++)
	{
		CObject *pCurrentObj = m_pTop[nCnt];

		while (pCurrentObj != nullptr)
		{
			CObject *pObjNext = pCurrentObj->m_pNext;

			if (!pCurrentObj->IsDeleted())
			{
				pCurrentObj->Uninit();
			}

			pCurrentObj = pObjNext;
		}
	}
	//deleted == true �� delete & null���
	for (int nCnt = 0; nCnt < MAX_PRIO; nCnt++)
	{
		CObject *pCurrentObj = m_pTop[nCnt];

		while (pCurrentObj != nullptr)
		{
			CObject *pObjNext = pCurrentObj->m_pNext;

			if (pCurrentObj->IsDeleted())
			{
				pCurrentObj->Release();
			}
			else
			{
				assert(false);
			}

			pCurrentObj = pObjNext;
		}

		m_pTop[nCnt] = nullptr;
		m_pCurrent[nCnt] = nullptr;
	}
}

//--------------------------------------------------
// ���ׂĂ̍X�V
//--------------------------------------------------
void CObject::UpdateAll()
{
	for (int nCnt = 0; nCnt < MAX_PRIO; nCnt++)
	{
		CObject *pCurrentObj = m_pTop[nCnt];

		while (pCurrentObj != nullptr)
		{
			CObject *pObjNext = pCurrentObj->m_pNext;

			if (!pCurrentObj->IsDeleted())
			{
				pCurrentObj->Update();
			}

			pCurrentObj = pObjNext;
		}
	}
	//deleted == true �� delete & null���
	for (int nCnt = 0; nCnt < MAX_PRIO; nCnt++)
	{
		CObject *pCurrentObj = m_pTop[nCnt];

		while (pCurrentObj != nullptr)
		{
			CObject *pObjNext = pCurrentObj->m_pNext;

			if (pCurrentObj->IsDeleted())
			{
				pCurrentObj->Release();
			}
			
			pCurrentObj = pObjNext;
		}
	}
}

//--------------------------------------------------
// ���ׂĂ̕`��
//--------------------------------------------------
void CObject::DrawAll()
{
	for (int nCnt = 0; nCnt < MAX_PRIO; nCnt++)
	{
		if (m_pTop[nCnt] != nullptr)
		{
			CObject *pCurrentObj = m_pTop[nCnt];

			while (pCurrentObj != nullptr && !pCurrentObj->IsDeleted())
			{
				CObject *pObjNext = pCurrentObj->m_pNext;
				pCurrentObj->Draw();
				pCurrentObj = pObjNext;
			}
		}
	}
}

//--------------------------------------------------
// ���[�h�ȊO�������[�X
//--------------------------------------------------
void CObject::ReleaseWithoutMode()
{
	for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	{
		{
			CObject* pObject = m_pTop[nPriority];

			while (pObject != nullptr)
			{
				// pNext�̕ۑ�
				CObject* pObjectNext = pObject->m_pNext;

				if (pObject->GetType() != TYPE_MODE)
				{
					pObject->Release();
				}

				// pObject��pObject��pNext����
				pObject = pObjectNext;
			}
		}

		{
			CObject* pObject = m_pTop[nPriority];

			while (pObject != nullptr)
			{
				// pNext�̕ۑ�
				CObject* pObjectNext = pObject->m_pNext;

				if (pObject->GetType() != TYPE_MODE)
				{
					// �I�������̊֐��Ăяo��
					pObject->DeletedObj();
				}

				// pObject��pObject��pNext����
				pObject = pObjectNext;
			}
		}
	}
}

//--------------------------------------------------
// delete��true�ɂ���
//--------------------------------------------------
void CObject::DeletedObj()
{
	m_bDeleted = true;
}

//--------------------------------------------------
// �����[�X
//--------------------------------------------------
void CObject::Release()
{
	CObject *pDeleteObj = this;

	if (pDeleteObj == nullptr)
	{// �������Ƃ��Ă����g���Ă��邩�ǂ���
		return;
	}
	else if (m_pPrev == nullptr && m_pNext == nullptr)
	{// �I�u�W�F�N�g���铒�����Ȃ��Ƃ�
		m_pTop[m_nPriority] = nullptr;
		m_pCurrent[m_nPriority] = nullptr;
	}
	else if (m_pPrev == nullptr)
	{// Top����������
		m_pTop[m_nPriority] = pDeleteObj->m_pNext;
		m_pTop[m_nPriority]->m_pPrev = nullptr;
	}
	else if (m_pNext == nullptr)
	{// Current����������
		m_pCurrent[m_nPriority] = pDeleteObj->m_pPrev;
		m_pCurrent[m_nPriority]->m_pNext = nullptr;
	}
	else
	{// �Ԃ̃I�u�W�F�N�g����������
		pDeleteObj->m_pPrev->m_pNext = pDeleteObj->m_pNext;
		pDeleteObj->m_pNext->m_pPrev = pDeleteObj->m_pPrev;
	}

	// �I��
	pDeleteObj->Uninit();

	delete pDeleteObj;
}

//--------------------------------------------------
// ���̓����蔻��
//--------------------------------------------------
bool IsCollisionSphere(D3DXVECTOR3 targetPos, D3DXVECTOR3 pos, D3DXVECTOR3 targetSize, D3DXVECTOR3 size)
{
	bool bIsLanding = false;

	// �ړI�̋���
	float fTargetDistance = sqrtf((targetPos.x - pos.x) * (targetPos.x - pos.x) +
		(targetPos.y - pos.y) * (targetPos.y - pos.y) +
		(targetPos.z - pos.z) * (targetPos.z - pos.z));
	// ���݂̋���
	float fCurrentDistance = sqrtf((targetSize.x + size.x) * (targetSize.x + size.x) +
		(targetSize.y + size.y) * (targetSize.y + size.y) +
		(targetSize.z + size.z) * (targetSize.z + size.z));

	if (fTargetDistance < fCurrentDistance)
	{
		bIsLanding = true;
	}

	return bIsLanding;
}

//--------------------------------------------------
// ��`�̓����蔻��
//--------------------------------------------------
bool IsCollision(D3DXVECTOR3 targetPos, D3DXVECTOR3 pos, D3DXVECTOR3 targetSize, D3DXVECTOR3 size)
{
	bool bIsLanding = false;

	if (pos.x + size.x / 2.0f >= targetPos.x - targetSize.x / 2.0f
		&& pos.x - size.x / 2.0f <= targetPos.x + targetSize.x / 2.0f
		&& pos.y - size.y / 2.0f <= targetPos.y + targetSize.y / 2.0f
		&& pos.y + size.y / 2.0f >= targetPos.y - targetSize.y / 2.0f)
	{
		bIsLanding = true;
	}

	return bIsLanding;
}
