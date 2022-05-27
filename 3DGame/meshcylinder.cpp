//=============================================================================
//
// メッシュシリンダークラス　：　円柱 [meshcylinder.h]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//ヘッダファイルのインクルード
//=============================================================================
#include "meshcylinder.h"
#include "keyboard.h"
#include "game.h"
#include "texture.h"
//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CMeshCylinder::CMeshCylinder(int nPriority) : CScene3D(nPriority)
{
	// メンバ変数のクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nSide = 0;
	m_nVertical = 0;
	m_bOutSide = false;
}
//=============================================================================
// デストラクタ
//=============================================================================
CMeshCylinder::~CMeshCylinder()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshCylinder::Init(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CScene3D::BindTexture(m_nType);	//テクスチャの割り当て
	int nNumVtx = GetNumVtx();		// 頂点数を取得
	int nNumIdx = GetNumIdx();		// インデックス数を取得
	float fAngle = atan2f(m_size.x, m_size.z);		// 角度を求める
	float fAddValue = (D3DX_PI / (m_nSide / 2.0f));	// 加算する角度の値
	float fAddAngle = 0;			// 加算する角度

	LPDIRECT3DVERTEXBUFFER9	*pVtxBuff = GetVtxBuff();	// 頂点バッファのポインタをScene3Dから参照して取得

	// 頂点バッファの生成					  
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * nNumVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&(*pVtxBuff),
		NULL);

	VERTEX_3D *pVtx; //頂点バッファへのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	(*pVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点数
	int nCntVtx = 0;

	m_fRadius = 100.0f;

	// 縦の分割数
	for (int nVertical = 0; nVertical < m_nVertical + 1; nVertical++)
	{	// 側の分割数
		for (int nSide = 0; nSide < m_nSide + 1; nSide++, nCntVtx++)
		{
			// 頂点座標の設定
			pVtx[nCntVtx].pos = D3DXVECTOR3(
				(-m_size.x / 2) * cosf(fAngle - fAddAngle),
				m_size.y - (nVertical * (m_size.y / m_nVertical)),
				(-m_size.z / 2) * sinf(fAngle - fAddAngle));

			// 頂点が重複しないときに角度を加算する
			if (nSide != m_nSide)
			{
				if (m_bOutSide == false)
				{	// シリンダーの内側に描画
					fAddAngle += fAddValue;
				}
				else
				{	// シリンダーの外側に描画
					fAddAngle -= fAddValue;
				}
			}

			// 法線ベクトルの設定
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

			// 頂点カラーの設定
			pVtx[nCntVtx].col = D3DCOLOR_RGBA(255, 255, 255, 255);;

			// テクスチャ座標	  側の分割数 * 1.0f, 縦の分割数 * 1.0f
			pVtx[nCntVtx].tex = D3DXVECTOR2(0.0f + (nSide * 1.0f), 0.0f + (nVertical * 1.0f));
		}
	}

	//頂点バッファをアンロックする
	(*pVtxBuff)->Unlock();

	LPDIRECT3DINDEXBUFFER9	*pIdxBuff = GetIdxBuff();	// インデックスへのポインタをScene3Dから参照して取得

	//インデックスバッファの生成			 
	pDevice->CreateIndexBuffer(sizeof(WORD) * nNumIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&(*pIdxBuff),
		NULL);

	WORD *pIdx;		//インデックス情報へのポインタ

	//インデックスバッファをロックし、頂点データへのポインタを取得
	(*pIdxBuff)->Lock(0, 0, (void**)&pIdx, 0);

	// 縮退ポリゴンの番号データを設定
	for (int nVertical = 0; nVertical < m_nVertical + 1; nVertical++)
	{
		for (int nSide = 0; nSide < m_nSide + 1; nSide++)
		{
			// 重複しない頂点情報のインデックスを設定
			pIdx[(m_nSide * 2 + 4) * nVertical + 0 + (nSide * 2)] = (nSide + (m_nSide + 1) + (m_nSide + 1) * nVertical);
			pIdx[(m_nSide * 2 + 4) * nVertical + 1 + (nSide * 2)] = (nSide + 0             + (m_nSide + 1) * nVertical);
		}
	}
	// 重複する頂点情報のインデックスを設定
	for (int nVertical = 0; nVertical < m_nVertical - 1; nVertical++)
	{
		pIdx[(m_nSide * 2 + 2) + 0 + nVertical * (m_nSide * 2 + 4)] = (m_nSide           + (m_nSide + 1) * nVertical);
		pIdx[(m_nSide * 2 + 2) + 1 + nVertical * (m_nSide * 2 + 4)] = ((m_nSide * 2 + 2) + (m_nSide + 1) * nVertical);
	}

	// インデックスバッファをアンロックする
	(*pIdxBuff)->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMeshCylinder::Uninit(void)
{
	CScene3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMeshCylinder::Update(void)
{
	CScene3D::Update();

	m_rot.y += m_fRotateSpeed;

	// 向きを3.14から-3.14の値の範囲内に収める
	if (m_rot.y >= D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}

	SetRotation(m_rot);
}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshCylinder::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// カリングを有効にする
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	CScene3D::Draw();

	// カリングを無効にする
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}
//=============================================================================
// 生成処理
//=============================================================================
CMeshCylinder *CMeshCylinder::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nVertical, int nSide, int nType, float fRotateSpeed)
{
	CMeshCylinder *pMeshCylinder;
	pMeshCylinder = new CMeshCylinder;

	if (pMeshCylinder != NULL)
	{
		pMeshCylinder->m_nType = nType;			// テクスチャの種類を設定
		pMeshCylinder->SetPosition(pos);		// 位置を設定
		pMeshCylinder->m_rot = rot;				// 向きを設定
		pMeshCylinder->m_size = size;			// 円柱の大きさ
		pMeshCylinder->m_nVertical = nVertical;	// 縦の頂点数
		pMeshCylinder->m_nSide = nSide;			// 側の頂点数
		pMeshCylinder->SetNumVtx((nSide + 1) * (nVertical + 1));	// 頂点数
		pMeshCylinder->SetRotateSpeed(fRotateSpeed);
		pMeshCylinder->SetNumIdx(((nSide * nVertical * 2) + (nVertical * 4)));	// インデックス数：(側の分割数 * 縦の分割数 * 2) + (縦の分割数 * 4)
		pMeshCylinder->SetNumPrimitive(((nSide * nVertical * 2) + (nVertical * 4)));
		pMeshCylinder->m_bOutSide = true;		// 外側に描画するかどうか
		pMeshCylinder->Init();					// 初期化処理
	}

	return pMeshCylinder;
}
