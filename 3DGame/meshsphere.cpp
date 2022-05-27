//=============================================================================
//
// メッシュスフィアクラス　：　球 [meshsphere.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//ヘッダファイルのインクルード
//=============================================================================
#include "meshsphere.h"
#include "keyboard.h"
#include "game.h"
//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CMeshSphere::CMeshSphere(int nPriority) : CScene3D(nPriority)
{
	// メンバ変数のクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nType = 0;
	m_nLine = 0;
	m_nVertical = 0;
	m_fRadius = 0.0f;
}
//=============================================================================
// デストラクタ
//=============================================================================
CMeshSphere::~CMeshSphere()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshSphere::Init(void)
{
	// オブジェクトの種類を設定
	SetObjType(OBJTYPE_SPHERE);

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	CScene3D::BindTexture(m_nType);	// テクスチャの割り当て
	int nNumVtx = GetNumVtx();		// 頂点数を取得
	int nNumIdx = GetNumIdx();		// インデックス数を取得

	// 頂点バッファのポインタをScene3Dから取得
	LPDIRECT3DVERTEXBUFFER9	*pVtxBuff = GetVtxBuff();

	// 頂点バッファの生成					  
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * nNumVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&(*pVtxBuff),
		NULL);

	VERTEX_3D *pVtx; // 頂点バッファへのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	(*pVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点数
	int nCntVtx = 0;

	// 縦の分割数
	for (int nVertical = 0; nVertical < m_nVertical + 1; nVertical++)
	{	// 横の分割数 
		for (int nLine = 0; nLine < m_nLine + 1; nLine++, nCntVtx++)
		{	// 頂点座標の角度を算出
			float fPhi = (D3DX_PI * 2) / m_nVertical * nVertical;
			float ftheta = (D3DX_PI * 2) / m_nVertical * nLine;

			// 頂点座標の設定
			pVtx[nCntVtx].pos = D3DXVECTOR3(
				m_fRadius * sinf(ftheta) * cosf(fPhi),
				m_fRadius * sinf(ftheta + D3DX_PI / 2),
				m_fRadius * sinf(ftheta) * sinf(fPhi));

			// 法線ベクトルの設定
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

			// 頂点カラーの設定
			pVtx[nCntVtx].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// テクスチャ座標			テクスチャの分割 / 横の分割数, 1.0f / 縦の分割数
			pVtx[nCntVtx].tex = D3DXVECTOR2((0.2f / m_nLine * nLine), (2.0f / m_nVertical * nVertical));
		}
	}

	// 頂点バッファをアンロックする
	(*pVtxBuff)->Unlock();

	// インデックスへのポインタをScene3Dから取得
	LPDIRECT3DINDEXBUFFER9	*pIdxBuff = GetIdxBuff();

	// インデックスバッファの生成			 
	pDevice->CreateIndexBuffer(sizeof(WORD) * nNumIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&(*pIdxBuff),
		NULL);

	WORD *pIdx;		// インデックス情報へのポインタ

	// インデックスバッファをロックし、頂点データへのポインタを取得
	(*pIdxBuff)->Lock(0, 0, (void**)&pIdx, 0);

	// 縮退ポリゴンの番号データを設定
	for (int nVertical = 0; nVertical < m_nVertical + 1; nVertical++)
	{
		for (int nLine = 0; nLine < m_nLine + 1; nLine++)
		{
			// 重複しない頂点情報のインデックスを設定
			pIdx[(m_nLine * 2 + 4) * nVertical + 0 + (nLine * 2)] = (nLine + (m_nLine + 1) + (m_nLine + 1) * nVertical);
			pIdx[(m_nLine * 2 + 4) * nVertical + 1 + (nLine * 2)] = (nLine + 0 + (m_nLine + 1) * nVertical);
		}
	}
	// 重複する頂点情報のインデックスを設定
	for (int nDup = 0; nDup < m_nVertical - 1; nDup++)
	{
		pIdx[(m_nLine * 2 + 2) + 0 + nDup * (m_nLine * 2 + 4)] = (m_nLine + (m_nLine + 1) * nDup);
		pIdx[(m_nLine * 2 + 2) + 1 + nDup * (m_nLine * 2 + 4)] = ((m_nLine * 2 + 2) + (m_nLine + 1) * nDup);
	}

	// インデックスバッファをアンロックする
	(*pIdxBuff)->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMeshSphere::Uninit(void)
{
	// 継承元の終了処理
	CScene3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMeshSphere::Update(void)
{
	// 回転速度
	m_rot.y += 0.0001f;

	// 角度制限
	if (m_rot.y >= D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}

	// 向きを設定
	CScene3D::SetRotation(m_rot);

}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshSphere::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// カリングを有効にする
	if (m_bCalling == true)
	{
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	}

	// 継承元の描画処理
	CScene3D::Draw();

	// カリングを無効にする
	if (m_bCalling == true)
	{
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	}

	// ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//=============================================================================
// 生成処理
//=============================================================================
CMeshSphere *CMeshSphere::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, int nVertical, int nLine, int nType)
{
	CMeshSphere *pMeshSphere;
	pMeshSphere = new CMeshSphere;

	if (pMeshSphere != NULL)
	{
		pMeshSphere->m_bCalling = false;		// カリングの状態
		pMeshSphere->m_nType = nType;			// テクスチャの種類を設定
		pMeshSphere->m_fRadius = fRadius;		// 球の大きさ
		pMeshSphere->m_nLine = nLine;			// 横の分割数
		pMeshSphere->m_nVertical = nVertical;	// 縦の分割数
		pMeshSphere->SetPosition(pos);			// 位置を設定
		pMeshSphere->SetRotation(rot);			// 向きを設定
		pMeshSphere->SetNumVtx((nLine + 1) * (nVertical + 1));	// 頂点数
		pMeshSphere->SetNumIdx((2 * nLine * (nVertical * 2)));	// インデックス数
		pMeshSphere->SetNumPrimitive(2 * nLine * nVertical + (nVertical * 4) - 2);	// プリミティブ(三角形の面)数
		pMeshSphere->Init();					// 初期化処理
	}

	return pMeshSphere;
}
