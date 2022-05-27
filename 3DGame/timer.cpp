//=============================================================================
//
// タイマークラス [timer.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "timer.h"
#include "polygon.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTimer::CTimer(int nPriority) : CScene(nPriority)
{
	// メンバ変数のクリア
	memset(&m_apNumber[0], NULL, sizeof(CPolygon));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nTimer = 0;
	m_nFrame = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CTimer::~CTimer()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTimer::Init(void)
{
	// ポリゴンの生成処理
	for (int nCntNum = 0; nCntNum < TIME_DIGIT; nCntNum++)
	{
		m_apNumber[nCntNum] = CPolygon::Create(D3DXVECTOR3(m_pos.x + 45.0f * nCntNum, m_pos.y, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), 6);
	}
	// オブジェクトの種類設定
	SetObjType(OBJTYPE_UI);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTimer::Uninit(void)
{
	//FILE *pFile;
	//pFile = fopen("data/SAVEDATA/currentscore.txt", "w");
	//if (pFile != NULL)
	//{
	//	fprintf(pFile, "%d", m_nTimer);
	//}
	//else
	//{
	//	printf("ファイルが開けませんでした\n");
	//}
	//fclose(pFile);


	// 桁数分破棄
	for (int nCntNum = 0; nCntNum < TIME_DIGIT; nCntNum++)
	{
		if (m_apNumber[nCntNum] != NULL)
		{
			// ポリゴンの終了処理
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
void CTimer::Update(void)
{
	// 加算されたスコアの情報を剰余算で計算する
	// ポリゴン1枚毎に計算された数字を格納
	m_apNumber[0]->SetNumber(m_nTimer % (int)pow(10, 2) / (int)pow(10, 1));
	m_apNumber[1]->SetNumber(m_nTimer % (int)pow(10, 1));

	// フレーム数カウント
	m_nFrame++;

	if (m_nFrame == 60)
	{
		m_nTimer--;		// カウントダウン
		m_nFrame = 0;	// フレーム数リセット

		if (m_nTimer <= 0)
		{
			m_nTimer = 0;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CTimer::Draw(void)
{
	// ポリゴンの描画処理
	for (int nCntNum = 0; nCntNum < TIME_DIGIT; nCntNum++)
	{
		m_apNumber[nCntNum]->Draw();
	}
}
//=============================================================================
// スコアの生成
//=============================================================================
CTimer *CTimer::Create(D3DXVECTOR3 pos, int nTime)
{
	CTimer *pTimer = nullptr;
	if (pTimer == nullptr)
	{
		pTimer = new CTimer;

		if (pTimer != nullptr)
		{
			pTimer->m_pos = pos;		// 位置
			pTimer->m_nTimer = nTime;	// 時間
			pTimer->Init();				// 初期化処理
		}
	}
	return pTimer;
}
