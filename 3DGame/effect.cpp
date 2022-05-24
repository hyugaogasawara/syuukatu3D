//=============================================================================
//
// エフェクトクラス [effect.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//ヘッダファイルのインクルード
//=============================================================================
#include "effect.h"
//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CEffect::CEffect(int nPriority) : CBillboard(nPriority)
{
	// メンバ変数のクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 大きさ
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動量

}
//=============================================================================
// デストラクタ
//=============================================================================
CEffect::~CEffect()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEffect::Init(void)
{
	// オブジェクトの種類設定
	SetObjType(OBJTYPE_BULLET);

	CBillboard::Init();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEffect::Uninit(void)
{
	CBillboard::Uninit();

	// オブジェクトを開放
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEffect::Update(void)
{
	// 位置を取得
	D3DXVECTOR3 pos = CBillboard::GetPosition();

	// 移動量更新
	pos += m_move;

	// 寿命減衰
	m_nLife--;

	// カラー
	m_color.r += m_Subcolor.r;
	m_color.g += m_Subcolor.g;
	m_color.b += m_Subcolor.b;
	m_color.a += m_Subcolor.a;

	// 位置を設定
	CBillboard::SetPosition(pos);
	CBillboard::SetColValue(m_color);
	CBillboard::Update();

	// 0以下で削除
	if (m_nLife <= 0)
	{
		m_bUninit = true;
	}


	// 破棄
	if (m_bUninit == true)
	{
		Uninit();
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CEffect::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// カリングを有効にする
	if (m_bCalling == true)
	{
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	}

	// 継承元の描画処理
	CBillboard::Draw();

	// カリングを無効にする
	if (m_bCalling == true)
	{
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	}

	// αブレンディングを通常合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//=============================================================================
// エフェクトの生成
//=============================================================================
CEffect *CEffect::Create(float fPosX, float fPosY, float fPosZ, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLORVALUE col, D3DCOLORVALUE subcol, int nLife, int nType)
{
	CEffect *pEffect;
	pEffect = new CEffect;

	if (pEffect != NULL)
	{
		pEffect->m_move = move;			// 移動量
		pEffect->m_nLife = nLife;		// 寿命
		pEffect->m_color = col;			// カラー
		pEffect->m_Subcolor = subcol;	// カラー減少
		pEffect->SetSize(size);			// 大きさ
		pEffect->SetPosition({ fPosX, fPosY, fPosZ });	// 位置
		pEffect->BindTexture(nType);	// テクスチャの種類
		pEffect->Init();				// 初期化処理
	}

	return pEffect;
}
