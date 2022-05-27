//=============================================================================
//
// タイマークラス [timer.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TIME_DIGIT	2		// タイマーの桁数

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPolygon;

//*****************************************************************************
//	スコアクラス
//*****************************************************************************
class CTimer : public CScene
{
public:
	CTimer(int nPriority = PRIORITY_UI);	// コンストラクタ
	~CTimer();				// デストラクタ

	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	// 生成処理
	static CTimer *Create(D3DXVECTOR3 pos, int nTime);

	void SetScore(int nScore) { m_nTimer = nScore; }	// スコアの設定
	void AddScore(int nValue) { m_nTimer += nValue; }	// スコアの加算
	int GetScore(void) { return m_nTimer; }				// スコアの取得
	CPolygon *GetNumber(int nNumber) { return m_apNumber[nNumber]; }// 数字クラス取得

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;				// 共有テクスチャのポインタ
	CPolygon					*m_apNumber[TIME_DIGIT];// 最大桁数分の数字
	D3DXVECTOR3					m_pos;					// 位置
	int							m_nTimer;				// スコアの値
	int							m_nFrame;				// フレーム
	int							m_nValue;				// 増減値
};
#endif //!_TIMER_H_