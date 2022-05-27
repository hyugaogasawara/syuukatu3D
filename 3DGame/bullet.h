//=============================================================================
//
// 弾クラス [bullet.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"
#include "billboard.h"

//*****************************************************************************
//	弾クラス
//*****************************************************************************
class CBullet : public CBillboard
{
public:
	CBullet(int nPriority = PRIORITY_SIGHT);	// デフォルトコンストラクタ
	~CBullet();			// デストラクタ

	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, int nLife, int nType);

	// 設定処理
	void SetUninit(bool bUninit) { m_bUninit = bUninit; }

private:
	D3DXVECTOR3	m_pos;		// 位置
	D3DXVECTOR3	m_rot;		// 向き
	D3DXVECTOR3	m_size;		// 大きさ
	D3DXVECTOR3	m_move;		// 移動量
	int			m_nLife;	// 寿命
	bool		m_bUninit;	// 終了処理判定
};
#endif //!_BULLET_H_