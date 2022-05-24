//=============================================================================
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

//*****************************************************************************
//	メッシュフィールドクラス
//*****************************************************************************
class CMeshField : public CScene3D
{
public:
	CMeshField(int nPriority = PRIORITY_FIELD);	// デフォルトコンストラクタ
	~CMeshField();				// デストラクタ

	HRESULT Init(void);			// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理

	// 生成処理
	static CMeshField *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nWidth, int nDepth, int nType);

	// 取得処理
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// 位置
	D3DXVECTOR3 GetSize(void) {return m_size; }		// 大きさ

	// 当たり判定
	bool Collision(CMeshField *pMeshField, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float& BackPos);

private:
	D3DXMATRIX	m_mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3	m_pos;		// 位置
	D3DXVECTOR3	m_rot;		// 向き
	D3DXVECTOR3	m_size;		// 大きさ
	bool		m_bUninit;	// 破棄
	int			m_nWidth;	// 横の分割数
	int			m_nDepth;	// 奥行の分割数
	int			m_nType;		// テクスチャの種類
};
#endif //!_MESHFIELD_H_