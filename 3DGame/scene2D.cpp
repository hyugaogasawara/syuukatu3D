//=============================================================================
//
// 2Dオブジェクトクラス [scene2D.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "scene2D.h"
#include "manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CScene2D::CScene2D(int nPriority) : CScene(nPriority)
{
	// メンバ変数をクリア
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
// デストラクタ
//=============================================================================
CScene2D::~CScene2D()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene2D::Init(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX2D,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,											// 頂点バッファの使用法
		FVF_VERTEX_2D,												// 使用する頂点フォーマット
		D3DPOOL_MANAGED,											// リソースのバッファを保持するメモリ
		&m_pVtxBuff,												// 頂点バッファへのポインタ
		NULL);														// NULLに設定

	VERTEX_2D *pVtx; //頂点バッファへのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標を設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CScene2D::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScene2D::Update(void)
{
	VERTEX_2D *pVtx; //頂点バッファへのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), m_pos.z);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void CScene2D::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}
//=============================================================================
// 生成処理
//=============================================================================
CScene2D * CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType)
{
	CScene2D *pScene2D = NULL;
	pScene2D = new CScene2D;

	if (pScene2D != NULL)
	{
		pScene2D->SetPosition(pos);
		pScene2D->SetSize(size);
		pScene2D->Init();
	}

	return pScene2D;
}
//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void CScene2D::SetVtxTexture(int nPatteernAnimU, float fAnimU, int nPatteernAnimV, float fAnimV, float fTexU, float fTexV)
{
	VERTEX_2D *pVtx; //頂点バッファへのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標を設定
	pVtx[0].tex = D3DXVECTOR2((nPatteernAnimU * fAnimU) + 0.0f,  (nPatteernAnimV * fAnimV) + 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nPatteernAnimU * fAnimU) + fTexU, (nPatteernAnimV * fAnimV) + 0.0f);
	pVtx[2].tex = D3DXVECTOR2((nPatteernAnimU * fAnimU) + 0.0f,  (nPatteernAnimV * fAnimV) + fTexV);
	pVtx[3].tex = D3DXVECTOR2((nPatteernAnimU * fAnimU) + fTexU, (nPatteernAnimV * fAnimV) + fTexV);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
// テクスチャパターン設定
//=============================================================================
void CScene2D::SetTexPattern(int nPattern, float fTexU)
{
	VERTEX_2D *pVtx; //頂点バッファへのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].tex = D3DXVECTOR2(nPattern * fTexU, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nPattern * fTexU + fTexU, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nPattern * fTexU, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nPattern * fTexU + fTexU, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
// 回転情報を設定
//=============================================================================
void CScene2D::SetRotate(float fAngleX, float fAngleY, float fVec)
{
	VERTEX_2D *pVtx; //頂点バッファへのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - sinf(fAngleX), m_pos.y - cosf(fAngleY), m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + cosf(fAngleX), m_pos.y - sinf(fAngleY), m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - cosf(fAngleX), m_pos.y + sinf(fAngleY), m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(fAngleX), m_pos.y + cosf(fAngleY), m_pos.z);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}
//=============================================================================
// 頂点カラーを設定
//=============================================================================
void CScene2D::SetColor(D3DCOLORVALUE color)
{
	m_color = color;

	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラー設定
	pVtx[0].col = D3DCOLOR_RGBA((int)m_color.r, (int)m_color.g, (int)m_color.b, (int)m_color.a);
	pVtx[1].col = D3DCOLOR_RGBA((int)m_color.r, (int)m_color.g, (int)m_color.b, (int)m_color.a);
	pVtx[2].col = D3DCOLOR_RGBA((int)m_color.r, (int)m_color.g, (int)m_color.b, (int)m_color.a);
	pVtx[3].col = D3DCOLOR_RGBA((int)m_color.r, (int)m_color.g, (int)m_color.b, (int)m_color.a);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

}
//=============================================================================
// 頂点カラーを設定
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR color)
{

	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラー設定
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

}
//=============================================================================
// スクロール設定
//=============================================================================
void CScene2D::SetScrollTex(float fTexU, float fTexV)
{
	m_fTexU = fTexU;
	m_fMoveTexV += fTexV;

	if (m_fMoveTexV >= 1.0f)
	{
		m_fMoveTexV -= 1.0f;
	}
	else if (m_fMoveTexV < 0.0f)
	{
		m_fMoveTexV += 1.0f;
	}

	if (m_fTexU >= 1.0f)
	{
		m_fTexU -= 1.0f;
	}
	else if (m_fTexU < 0.0f)
	{
		m_fTexU += 1.0f;
	}

	VERTEX_2D *pVtx;// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャのUV設定
	pVtx[0].tex = D3DXVECTOR2(m_fTexU,			m_fMoveTexV);
	pVtx[1].tex = D3DXVECTOR2(m_fTexU + 1.0f,	m_fMoveTexV);
	pVtx[2].tex = D3DXVECTOR2(m_fTexU,			m_fMoveTexV + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_fTexU + 1.0f,	m_fMoveTexV + 1.0f);

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}
//=============================================================================
// テクスチャ座標を設定
//=============================================================================
void CScene2D::SetNumber(int nNumber)
{
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nNumber * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nNumber * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 1.0f);

	m_pVtxBuff->Unlock();
}
