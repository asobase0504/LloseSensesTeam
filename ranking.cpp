//==================================================
// ranking.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include <assert.h>

#include "manager.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "fade.h"
#include "ranking.h"
#include "score.h"
#include "sound.h"

// jsonのinclude
#include "nlohmann/json.hpp"
#include <fstream>

// 名前の省略
namespace nl = nlohmann;
// ファイルパスの設定
const char* pathToJSON = "data/FILE/ranking.json";

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CRanking::CRanking()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CRanking::~CRanking()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CRanking::Init()
{
	//CManager::GetSound()->Play(CSound::LABEL_BGM_RANKING);

	// ランキングの背景
	m_pRankingBg = CObject2D::Create(
		D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXVECTOR3((float)CManager::SCREEN_WIDTH, (float)CManager::SCREEN_HEIGHT, 0.0f),
		PRIORITY_BG);
	m_pRankingBg->SetTexture(CTexture::TEXTURE_NONE);

	// 順位
	m_pRanking = CObject2D::Create(
		D3DXVECTOR3(300.0f, 380.0f, 0.0f),
		D3DXVECTOR3(120.0f, 500.0f, 0.0f),
		PRIORITY_BG);
	m_pRanking->SetTexture(CTexture::TEXTURE_NONE);
	m_pRanking->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		m_aRankingData[nCntRank] = 0;
		// スコア
		m_pScore[nCntRank] = CScore::Create(D3DXVECTOR3(500.0f, 180.0f + nCntRank * 100.0f, 0.0f), D3DXVECTOR3(60.0f, 80.0f, 0.0f));
		m_pScore[nCntRank]->SetScore(m_aRankingData[nCntRank]);
	}

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CRanking::Uninit()
{
	CManager::GetSound()->Stop();

	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		if (m_pScore[nCnt] == nullptr)
		{
			continue;
		}

		m_pScore[nCnt]->Uninit();
	}

	if (m_pRanking != nullptr)
	{
		m_pRanking->Uninit();
	}

	if (m_pRankingBg != nullptr)
	{
		m_pRankingBg->Uninit();
	}

	CObject::DeletedObj();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CRanking::Update()
{
	CInputKeyboard *pInputKeyoard = CManager::GetInputKeyboard();
	CInputJoyPad *pInputJoyPad = CManager::GetInputJoyPad();

	if (pInputKeyoard->GetTrigger(DIK_RETURN) || pInputJoyPad->GetJoypadTrigger(pInputJoyPad->JOYKEY_A, 0))
	{
		// サウンド
		//CManager::GetSound()->Play(CSound::LABEL_SE_ENTER);

		CFade::GetInstance()->SetFade(CManager::MODE_TITLE);
	}
}

//--------------------------------------------------
// ランキングのリセット
//--------------------------------------------------
void CRanking::LoadRanking()
{
	// ファイルオープン
	std::ifstream ifs(pathToJSON);

	if (ifs)
	{// ファイル開いたとき
		nl::json j;	// リストの生成
		ifs >> j;	// リストに文字をぶち込む

		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{//	タグ付け
			std::string name = "RANKING";
			// 数型を文字型に変える
			std::string Number = std::to_string(nCnt);
			name += Number;

			m_aRankingData[nCnt] = j[name];
		}
	}
}

//--------------------------------------------------
// ランキングのセーブ
//--------------------------------------------------
void CRanking::SaveRanking()
{
	nl::json j;	// リストの生成

	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{//	タグ付け
		std::string name = "RANKING";
		// 数型を文字型に変える
		std::string Number = std::to_string(nCnt);
		name += Number;

		j[name] = m_aRankingData[nCnt];
	}

	// jobjにデータを入れる
	auto jobj = j.dump();
	std::ofstream writing_file;
	writing_file.open(pathToJSON, std::ios::out);
	writing_file << jobj << std::endl;
	writing_file.close();
}

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
void CRanking::SetRanking(int nScore)
{
	LoadRanking();

	int nCheck = 0;

	//ランキングの最下位と今回のスコアを比べる
	if (nScore >= m_aRankingData[MAX_RANK - 1])
	{
		//比較した数値を入れる
		m_aRankingData[MAX_RANK - 1] = nScore;
	}

	for (int nCntRank1 = 0; nCntRank1 < MAX_RANK - 1; nCntRank1++)
	{
		for (int nCntRnak2 = nCntRank1 + 1; nCntRnak2 < MAX_RANK; nCntRnak2++)
		{//上記の繰り返しが進むたびに繰り返し回数が-1ずつされる。

			// 二つのデータを比較する
			if (m_aRankingData[nCntRank1] <= m_aRankingData[nCntRnak2])
			{
				//変数を一時格納
				nCheck = m_aRankingData[nCntRnak2];

				//比較した数値を入れる
				m_aRankingData[nCntRnak2] = m_aRankingData[nCntRank1];
				m_aRankingData[nCntRank1] = nCheck;
			}
		}
	}

	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		m_pScore[nCntRank]->SetScore(m_aRankingData[nCntRank]);
	}

	// ランキングのセーブ
	SaveRanking();
}

//--------------------------------------------------
// ランキングの設定処理
//--------------------------------------------------
CRanking *CRanking::Create()
{
	CRanking *pRanking;
	pRanking = new CRanking;

	if (pRanking != nullptr)
	{
		pRanking->Init();
	}
	else
	{
		assert(false);
	}

	return pRanking;
}
