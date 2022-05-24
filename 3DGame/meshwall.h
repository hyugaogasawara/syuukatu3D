//
// メッシュウォールクラス [meshwall.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"
#include "scene3D.h"

//*****************************************************************************
//	メッシュウォールクラス
//*****************************************************************************
class CMeshWall : public CScene3D
{
public:
	CMeshWall(int nPriority = PRIORITY_NONE);	// デフォルトコンストラクタ
	~CMeshWall();								// デストラクタ

	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	static CMeshWall *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nWidth, int nDepth, int nType);	// 生成処理

	// 設定処理
	void BindTexture(int nType) { m_nType = nType; }	// テクスチャの割り当て

	// 取得処理
	D3DXVECTOR3 GetPosition(void) { return m_pos; }		// 位置の取得
	D3DXVECTOR3 GetSize(void) { return m_size; }		// 大きさの取得
	bool Collision(CMeshWall *pMeshField, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float& BackPos);

private:
	D3DXMATRIX	m_mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3	m_pos;		// 位置
	D3DXVECTOR3	m_rot;		// 向き
	D3DXVECTOR3	m_size;		// 大きさ
	bool		m_bUninit;	// 破棄
	int			m_nWidth;	// 横の分割数
	int			m_nHeight;	// 高さの分割数
	int			m_nType;	// テクスチャの種類
};
#endif //!_MESHWALL_H_