//=============================================================================
//
// メッシュスフィアクラス ：　球　[meshsphere.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _MESHSPHERE_H_
#define _MESHSPHERE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"
#include "scene3D.h"

//*****************************************************************************
//	メッシュスフィアクラス
//*****************************************************************************
class CMeshSphere : public CScene3D
{
public:
	CMeshSphere(int nPriority = PRIORITY_SPHERE);	// コンストラクタ
	~CMeshSphere();		// デストラクタ

	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	// 生成処理
	static CMeshSphere *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, int nVertical, int nLine, int nType);

	// 取得処理
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// 位置
private:
	D3DXMATRIX	m_mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3	m_pos;		// 位置
	D3DXVECTOR3	m_rot;		// 向き
	bool		m_bUninit;	// 破棄
	bool		m_bCalling;	// カリングの状態
	int			m_nVertical;// 縦の分割数
	int			m_nLine;	// 横の分割数
	int			m_nType;	// テクスチャの種類
	float		m_fRadius;	// 半径
};
#endif //!_MESHSPHERE_H_