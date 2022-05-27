//=============================================================================
//
// スコアクラス [score.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "score.h"
#include "polygon.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CScore::CScore(int nPriority) : CScene(nPriority)
{
	// メンバ変数のクリア
	memset(&m_apNumber[0], NULL, sizeof(CPolygon));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nScore = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CScore::~CScore()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScore::Init(void)
{
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		m_apNumber[nCntNum] = CPolygon::Create(D3DXVECTOR3(m_pos.x + 45.0f * nCntNum, m_pos.y, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), 6);
	}
	SetObjType(OBJTYPE_UI);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScore::Uninit(void)
{
	//FILE *pFile;
	//pFile = fopen("data/SAVEDATA/currentscore.txt", "w");
	//if (pFile != NULL)
	//{
	//	fprintf(pFile, "%d", m_nScore);
	//}
	//else
	//{
	//	printf("ファイルが開けませんでした\n");
	//}
	//fclose(pFile);


	// 桁数分破棄
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		if (m_apNumber[nCntNum] != NULL)
		{
			m_apNumber[nCntNum]->Uninit();
			delete m_apNumber[nCntNum];
			m_apNumber[nCntNum] = NULL;
		}
	}

	// オブジェクトの開放
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScore::Update(void)
{
	// 加算されたスコアの情報を剰余算で計算する
	// ポリゴン1枚毎に計算された数字を格納
	m_apNumber[0]->SetNumber(m_nScore / (int)pow(10, 6));
	m_apNumber[1]->SetNumber(m_nScore % (int)pow(10, 5) / (int)pow(10, 4));
	m_apNumber[2]->SetNumber(m_nScore % (int)pow(10, 4) / (int)pow(10, 3));
	m_apNumber[3]->SetNumber(m_nScore % (int)pow(10, 3) / (int)pow(10, 2));
	m_apNumber[4]->SetNumber(m_nScore % (int)pow(10, 2) / (int)pow(10, 1));
	m_apNumber[5]->SetNumber(m_nScore % (int)pow(10, 1));

}

//=============================================================================
// 描画処理
//=============================================================================
void CScore::Draw(void)
{
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		m_apNumber[nCntNum]->Draw();
	}
}
//=============================================================================
// スコアの生成
//=============================================================================
CScore *CScore::Create(D3DXVECTOR3 pos)
{
	CScore *pScore = nullptr;
	if (pScore == nullptr)
	{
		pScore = new CScore;

		if (pScore != nullptr)
		{
			pScore->m_pos = pos;
			pScore->Init();
		}
	}
	return pScore;
}
