//=============================================================================
//
// エフェクトクラス [effect.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"
#include "billboard.h"

//*****************************************************************************
//	弾クラス
//*****************************************************************************
class CEffect : public CBillboard
{
public:
	CEffect(int nPriority = PRIORITY_EFFECT);	// デフォルトコンストラクタ
	~CEffect();			// デストラクタ

	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	// 生成処理
	static CEffect *Create(float fPosX, float fPosY, float fPosZ, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLORVALUE col, D3DCOLORVALUE subcol, int nLife, int nType);

protected:
	bool		m_bCalling;		// カリングの状態
	int			m_nLife;		// 寿命

private:
	D3DXVECTOR3		m_pos;		// 位置
	D3DXVECTOR3		m_rot;		// 向き
	D3DXVECTOR3		m_size;		// 大きさ
	D3DXVECTOR3		m_move;		// 移動量
	D3DCOLORVALUE	m_color;	// カラー
	D3DCOLORVALUE	m_Subcolor;	// カラー
	bool			m_bUninit;	// 破棄
};
#endif //!_EFFECT_H_