//=============================================================================
//
// 照準クラス [sight.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _SIGHT_H_
#define _SIGHT_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"
#include "billboard.h"

//*****************************************************************************
//	マクロ定義
//*****************************************************************************
#define SPEED 2.5f
//*****************************************************************************
//	前方宣言
//*****************************************************************************
class CInputKeyboard;
class CMouse;
class CBullet;
//*****************************************************************************
//	弾クラス
//*****************************************************************************
class CSight : public CBillboard
{
public:
	CSight(int nPriority = PRIORITY_SIGHT);	// コンストラクタ
	~CSight();			// デストラクタ

	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	// 生成処理
	static CSight *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType);

private:
	void Move(void);	// 移動処理

	D3DXVECTOR3	m_pos;		// 位置
	D3DXVECTOR3	m_rot;		// 向き
	D3DXVECTOR3	m_size;		// 大きさ
	D3DXVECTOR3	m_move;		// 移動量
	int			m_nLife;	// 寿命
	bool		m_bUninit;	// 破棄
	CBullet		*m_pBullet;	// 弾クラスのポインタ
	CInputKeyboard	*m_pKeyboard;	// キーボードクラスのポインタ
	CMouse			*m_pMouse;		// マウスクラスのポインタ
};
#endif //!_SIGHT_H_