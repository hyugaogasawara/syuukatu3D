//=============================================================================
//
// モデルクラス [modelsingle.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _MODELSINGLE_H_
#define _MODELSINGLE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_VTX 8			// 頂点
#define MODEL_SURFACE_VTX 4 // 面の頂点
#define MODEL_TEX 5
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CXload;

//*****************************************************************************
//	モデルクラス
//*****************************************************************************
class CModelSingle : public CScene
{
public:
	CModelSingle(int nPriority = PRIORITY_MODEL);	// コンストラクタ
	~CModelSingle();	// デストラクタ

	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	// 生成処理
	static CModelSingle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);

	// 取得処理
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }		// ワールドマトリックス
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			// パーツの位置
	D3DXVECTOR3 GetRotation(void) { return m_rot; }			// パーツの向き
	D3DXVECTOR3 GetSize(void) { return m_size; }			// パーツの大きさ

	// 設定処理
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		// パーツの位置
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }		// パーツの向き
	void SetModelType(int nType) { m_nModelType = nType; }	// モデルの種類

	bool Collision(void);	// 当たり判定
private:
	LPDIRECT3DTEXTURE9	m_pTexture[MODEL_TEX];	// テクスチャのポインタ
	LPD3DXMESH			m_pMesh;				// メッシュ（頂点情報）へのポインタ
	LPD3DXBUFFER		m_pBuffMat;				// マテリアル（材質情報）へのポインタ
	DWORD				m_nNumMat;				// マトリックス数
	D3DXMATRIX			m_mtxWorld;				// ワールドマトリックス
	D3DXVECTOR3			m_pos;					// 位置
	D3DXVECTOR3			m_posOld;				// 1フレーム前の位置
	D3DXVECTOR3			m_rot;					// 向き
	D3DXVECTOR3			m_size;					// 大きさ
	D3DXVECTOR3			m_vtxMin, m_vtxMax;		// 頂点の最小値、最大値
	D3DXVECTOR3			m_vtx[MODEL_VTX];		// 頂点のローカル座標
	D3DXMATRIX			m_aMtxWorld[MODEL_VTX];	// 8頂点分のワールドマトリックス
	D3DXVECTOR3			m_aSaveMtxWorld[MODEL_VTX];	// 頂点のワールドマトリックス保存
	CXload				*m_pXload;				// Xファイルの情報
	int					m_nModelType;			// モデルの種類

};
#endif //!_MODELSINGLE_H_