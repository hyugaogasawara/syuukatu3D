//=============================================================================
//
// ライトクラス [light.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
//	ライトクラス
//*****************************************************************************
class CLight
{
public:
	CLight();			// デフォルトコンストラクタ
	~CLight();			// デストラクタ

	HRESULT Init(D3DXVECTOR3 vecDir, D3DXVECTOR3 pos, D3DXCOLOR col, int nCntLight);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理

	static CLight *Create(D3DXVECTOR3 vecDir, D3DXVECTOR3 pos, D3DXCOLOR col, int nCntLight);	// 生成処理

private:
	D3DLIGHT9		m_aLight[MAX_LIGHT];	// ライト情報
	D3DXVECTOR3		m_vecDir;		// 設定用方向ベクトル
	D3DXVECTOR3		m_vecDirection;	// 拡散光の方向
	D3DLIGHTTYPE	m_type;			// 種類
	D3DXCOLOR		m_color;		// 色
	static int		m_nNumLight;	// 番号
	int				m_nCntLight;	// 生成数を保存

};
#endif //!_LIGHT_H_