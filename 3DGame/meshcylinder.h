//
// メッシュシリンダークラス：円柱 [meshcylinder.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"
#include "scene3D.h"

//*****************************************************************************
//	メッシュフィールドクラス
//*****************************************************************************
class CMeshCylinder : public CScene3D
{
public:
	CMeshCylinder(int nPriority = PRIORITY_NONE);	// デフォルトコンストラクタ
	~CMeshCylinder();								// デストラクタ

	HRESULT Init(void);			// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理

	static CMeshCylinder *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nVertical, int nSide, int ntype, float fRotateSpeed);	// 生成処理

	// 取得処理
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// 位置の取得
	D3DXVECTOR3 GetSize(void) { return m_size; }	// 大きさの取得

	// 設定処理
	void SetRotateSpeed(float fSpeed) { m_fRotateSpeed = fSpeed; }
private:
	D3DXVECTOR3	m_pos;			// 位置
	D3DXVECTOR3	m_rot;			// 向き
	D3DXVECTOR3	m_size;			// 大きさ
	D3DXCOLOR	m_col;			// 色
	bool		m_bUninit;		// 破棄
	bool		m_bOutSide;		// 外側かどうか
	int			m_nVertical;	// 縦の分割数
	int			m_nSide;		// 側の分割数
	float		m_fRotateSpeed;	// 回転速度
	float		m_fRadius;		// 半径
	int			m_nType;		// テクスチャの種類
};
#endif //!_MESHCYLINDER_H_