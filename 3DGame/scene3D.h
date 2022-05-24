//=============================================================================
//
// 3Dポリゴンクラス [scene3D.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FVF_VERTEX_3D	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// 3D 頂点フォーマット
#define NUM_VERTEX		4					// 頂点数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos; // 頂点座標
	D3DXVECTOR3 nor; // 法線ベクトル
	D3DCOLOR    col; // 頂点カラー
	D3DXVECTOR2 tex; // テクスチャ座標
} VERTEX_3D;

//*****************************************************************************
//	3Dポリゴンクラス
//*****************************************************************************
class CScene3D : public CScene
{
public:
	CScene3D(int nPriority = PRIORITY_NONE);		// コンストラクタ
	virtual ~CScene3D();		// デストラクタ
	virtual HRESULT Init(void);	// 初期化処理
	virtual void Uninit(void);	// 終了処理
	virtual void Update(void);	// 更新処理
	virtual void Draw(void);	// 描画処理

	// 取得処理
	LPDIRECT3DVERTEXBUFFER9 *GetVtxBuff(void) { return &m_pVtxBuff; }	// 頂点バッファのアドレス
	LPDIRECT3DINDEXBUFFER9 *GetIdxBuff(void) { return &m_pIdxBuff; }	// インデックスバッファのアドレス
	int GetNumVtx(void) { return m_nNumVtx; }				// 頂点数
	int GetNumIdx(void) { return m_nNumIdx; }				// インデックス数
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			// 位置
	D3DXVECTOR3 GetRotation(void) { return m_rot; }			// 向き

	// 設定処理
	void BindTexture(int nType) { m_pTexture = CTexture::SetTexture(nType); } // テクスチャの割り当て
	void SetNumVtx(int nNumVtx) { m_nNumVtx = nNumVtx; }	// 頂点数
	void SetNumIdx(int nNumIdx) { m_nNumIdx = nNumIdx; }	// インデックス数
	void SetNumPrimitive(int nNumPrimitive) { m_nNumPrimitve = nNumPrimitive; }	// プリミティブ数
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		// 位置
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }		// 向き

private:
	LPDIRECT3DTEXTURE9		m_pTexture;	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;	// メッシュフィールドのインデックスへのポインタ
	D3DXMATRIX				m_mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3				m_pos;		// 位置
	D3DXVECTOR3				m_rot;		// 向き
	D3DXVECTOR3				m_size;		// サイズ
	int						m_nNumVtx;	// 頂点数
	int						m_nNumIdx;	// インデックス数
	int						m_nNumPrimitve;	// プリミティブ数(三角形ポリゴン数)
};
#endif //!_SCENE3D_H_