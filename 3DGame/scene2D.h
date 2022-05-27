//=============================================================================
//
// 2Dオブジェクトクラス [scene2D.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// 頂点フォーマット
#define NUM_VERTEX2D		4										// 頂点数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos; //頂点座標
	float		rhw; //1.0fで固定
	D3DCOLOR    col; //頂点カラー
	D3DXVECTOR2 tex; //テクスチャ座標
} VERTEX_2D;

//*****************************************************************************
//	2Dオブジェクトクラス
//*****************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority = PRIORITY_NONE);	// コンストラクタ
	~CScene2D();				// デストラクタ

	HRESULT Init(void);			// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理

	// 生成処理
	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType);

	// 取得処理
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// 位置を取得
	D3DXVECTOR3 GetSize(void) { return m_size; }	// サイズを取得

	// 設定処理
	void BindTexture(int nType) { m_pTexture = CTexture::SetTexture(nType); }	// テクスチャの割り当て
	void SetVtxTexture(int nPatternAnimU, float fAnimU, int nPatternAnimV, float fAnimV, float fTexU, float fTexV);	// テクスチャ座標の設定
	void SetTexPattern(int nPattern, float fTexU);								// テクスチャパターン
	void SetRotate(float fAngleX, float fAngleY, float fVec);					// 回転情報
	void SetColor(D3DCOLORVALUE colval);										// 頂点カラー
	void SetColor(D3DXCOLOR color);				
	void SetScrollTex(float fTexU, float fTexV);								// テクスチャスクロール
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }// 位置
	void SetSize(D3DXVECTOR3 size) { m_size = size; }	// 大きさ
	void SetNumber(int nNum);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	D3DXVECTOR3				m_pos;			// 位置
	D3DXVECTOR3				m_size;			// サイズ
	D3DXCOLOR				m_color;		// 頂点カラー
	D3DCOLORVALUE			m_colval;		// 頂点カラー
	float					m_fTexU;
	float					m_fTexV;
	float					m_fMoveTexV;
};
#endif //!_SCENE2D_H_
