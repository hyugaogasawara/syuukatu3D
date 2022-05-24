//=============================================================================
//
// ビルボードクラス [billboard.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"
#include "scene3D.h"

//*****************************************************************************
//	ビルボードクラス
//*****************************************************************************
class CBillboard : public CScene
{
public:
	CBillboard(int nPriority = PRIORITY_NONE);	// デフォルトコンストラクタ
	~CBillboard();		// デストラクタ

	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	static CBillboard *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType);

	// 設定処理
	void BindTexture(int nType) { m_pTexture = CTexture::SetTexture(nType); } // テクスチャの割り当て
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		// 位置
	void SetSize(D3DXVECTOR3 size) { m_size = size; }		// 大きさ
	void SetColValue(D3DCOLORVALUE col) { m_color = col; }	// カラー

	// 取得処理
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	D3DXMATRIX				m_mtxWorld;		// ワールドマトリックス
	D3DXVECTOR3		m_pos;		// 位置
	D3DXVECTOR3		m_rot;		// 向き
	D3DXVECTOR3		m_size;		// 大きさ
	D3DXVECTOR3		m_move;		// 移動量
	D3DCOLORVALUE	m_color;	// カラー
};
#endif //!_BILLBOARD_H_