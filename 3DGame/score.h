//=============================================================================
//
// スコアクラス [score.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_DIGIT	6		// 最大桁数

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPolygon;
class CScene2D;
//*****************************************************************************
//	スコアクラス
//*****************************************************************************
class CScore : public CScene
{
public:
	CScore(int nPriority = PRIORITY_UI);	// コンストラクタ
	~CScore();				// デストラクタ

	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	// 生成処理
	static CScore *Create(D3DXVECTOR3 pos);

	// 取得処理
	int GetScore(void) { return m_nScore; }							// スコアの取得
	CPolygon *GetNumber(int nNumber) { return m_apNumber[nNumber]; }// 数字クラス取得

	// 設定処理
	void SetScore(int nScore) { m_nScore = nScore; }			// スコアの設定
	void AddScore(int nValue) { m_nScore += nValue; }			// スコアの加算

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;				// 共有テクスチャのポインタ
	CPolygon					*m_apNumber[MAX_DIGIT];	// 最大桁数分の数字
	D3DXVECTOR3					m_pos;					// 位置
	int							m_nScore;				// スコアの値
	int							m_nValue;				// 増減値
};
#endif //!_SCORE_H_