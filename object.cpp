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
// 静的メンバ変数
//**************************************************
int CObject::m_nNumAll = 0;
CObject *CObject::m_pTop[] = {};
CObject *CObject::m_pCurrent[] = {};

//--------------------------------------------------
// プライオリティを使ったコンストラクタ
//--------------------------------------------------
CObject::CObject(int nPriority /* PRIORITY_3 */) : m_pPrev(nullptr), m_pNext(nullptr)
{
	if (m_pTop[nPriority] == nullptr)
	{// Topがnullptrの時
		m_pTop[nPriority] = this;
	}
	else
	{// Topがすでに生成されているとき
		m_pCurrent[nPriority]->m_pNext = this;
		this->m_pPrev = m_pCurrent[nPriority];
	}

	m_pCurrent[nPriority] = this;

	m_nPriority = nPriority;
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CObject::~CObject()
{
}

//--------------------------------------------------
// すべての破棄
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
	//deleted == true を delete & null代入
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
// すべての更新
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
	//deleted == true を delete & null代入
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
// すべての描画
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
// モード以外をリリース
//--------------------------------------------------
void CObject::ReleaseWithoutMode()
{
	for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	{
		{
			CObject* pObject = m_pTop[nPriority];

			while (pObject != nullptr)
			{
				// pNextの保存
				CObject* pObjectNext = pObject->m_pNext;

				if (pObject->GetType() != TYPE_MODE)
				{
					pObject->Release();
				}

				// pObjectにpObjectのpNextを代入
				pObject = pObjectNext;
			}
		}

		{
			CObject* pObject = m_pTop[nPriority];

			while (pObject != nullptr)
			{
				// pNextの保存
				CObject* pObjectNext = pObject->m_pNext;

				if (pObject->GetType() != TYPE_MODE)
				{
					// 終了処理の関数呼び出し
					pObject->DeletedObj();
				}

				// pObjectにpObjectのpNextを代入
				pObject = pObjectNext;
			}
		}
	}
}

//--------------------------------------------------
// deleteをtrueにする
//--------------------------------------------------
void CObject::DeletedObj()
{
	m_bDeleted = true;
}

//--------------------------------------------------
// リリース
//--------------------------------------------------
void CObject::Release()
{
	CObject *pDeleteObj = this;

	if (pDeleteObj == nullptr)
	{// 消そうとしてるやつが使われているかどうか
		return;
	}
	else if (m_pPrev == nullptr && m_pNext == nullptr)
	{// オブジェクトが秘湯しかないとき
		m_pTop[m_nPriority] = nullptr;
		m_pCurrent[m_nPriority] = nullptr;
	}
	else if (m_pPrev == nullptr)
	{// Topが消えた時
		m_pTop[m_nPriority] = pDeleteObj->m_pNext;
		m_pTop[m_nPriority]->m_pPrev = nullptr;
	}
	else if (m_pNext == nullptr)
	{// Currentが消えた時
		m_pCurrent[m_nPriority] = pDeleteObj->m_pPrev;
		m_pCurrent[m_nPriority]->m_pNext = nullptr;
	}
	else
	{// 間のオブジェクトが消えた時
		pDeleteObj->m_pPrev->m_pNext = pDeleteObj->m_pNext;
		pDeleteObj->m_pNext->m_pPrev = pDeleteObj->m_pPrev;
	}

	// 終了
	pDeleteObj->Uninit();

	delete pDeleteObj;
}

//--------------------------------------------------
// 球の当たり判定
//--------------------------------------------------
bool IsCollisionSphere(D3DXVECTOR3 targetPos, D3DXVECTOR3 pos, D3DXVECTOR3 targetSize, D3DXVECTOR3 size)
{
	bool bIsLanding = false;

	// 目的の距離
	float fTargetDistance = sqrtf((targetPos.x - pos.x) * (targetPos.x - pos.x) +
		(targetPos.y - pos.y) * (targetPos.y - pos.y) +
		(targetPos.z - pos.z) * (targetPos.z - pos.z));
	// 現在の距離
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
// 矩形の当たり判定
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
