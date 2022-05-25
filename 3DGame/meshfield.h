//
// メッシュフィールドクラス [meshfield.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"
#include "scene3D.h"
//=============================================================================
// マクロ定義
//=============================================================================

//*****************************************************************************
//	メッシュフィールドクラス
//*****************************************************************************
class CMeshField : public CScene3D
{
public:
	CMeshField(int nPriority = PRIORITY_FIELD);	// コンストラクタ
	~CMeshField();								// デストラクタ

	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	// 生成処理
	static CMeshField *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nWidth, int nDepth, int nType);

	// 取得処理
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetSize(void) { return m_size; }

	// 設定処理
	void BindTexture(int nType) { m_pTexture = CTexture::SetTexture(nType); } // テクスチャの割り当て

	// 当たり判定
	bool Collision(CMeshField *pMeshField, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float& BackPos);

private:
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;	// メッシュフィールドの頂点バッファのポインタ
	LPDIRECT3DINDEXBUFFER9		m_pIdxBuff;	// メッシュフィールドのインデックスへのポインタ
	static LPDIRECT3DTEXTURE9	m_pTexture;	// 共有テクスチャのポインタ
	D3DXMATRIX					m_mtxWorld;	//	ワールドマトリックス
	D3DXVECTOR3					m_move;		// 移動量
	D3DXVECTOR3					m_pos;		// 位置
	D3DXVECTOR3					m_rot;		// 向き
	D3DXVECTOR3					m_size;		// 大きさ
	D3DXCOLOR					m_color;	// 色
	bool						m_bUninit;	// 破棄
	int							m_nWidth;
	int							m_nDepth;
	int							m_nType;
};
#endif //!_MESHFIELD_H_