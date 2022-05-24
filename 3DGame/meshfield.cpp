//=============================================================================
//
// メッシュフィールドクラス　：　平面 [meshfield.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//ヘッダファイルのインクルード
//=============================================================================
#include "meshfield.h"
#include "keyboard.h"
#include "game.h"
//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CMeshField::CMeshField(int nPriority) : CScene3D(nPriority)
{
	// メンバ変数のクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
// デストラクタ
//=============================================================================
CMeshField::~CMeshField()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshField::Init(void)
{
	SetObjType(OBJTYPE_FIELD);

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	CScene3D::BindTexture(m_nType);	// テクスチャの割り当て
	int nNumVtx = GetNumVtx();		// 頂点数を取得
	int nNumIdx = GetNumIdx();		// インデックス数を取得

	LPDIRECT3DVERTEXBUFFER9	*pVtxBuff = GetVtxBuff();	// 頂点バッファのポインタをScene3Dから参照して取得
	
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

	// 奥行の分割数
	for (int nDepth = 0; nDepth < m_nDepth + 1; nDepth++)
	{	// 横の分割数 
		for (int nWidth = 0; nWidth < m_nWidth + 1; nWidth++, nCntVtx++)
		{
			// 位置の設定				   (大きさ / 2.0f) + (分割数 * (大きさ / 設定した分割数))
			pVtx[nCntVtx].pos = D3DXVECTOR3((-m_size.x / 2.0f) + (nWidth * (m_size.x / m_nWidth)),
				m_pos.y,
				(m_size.z / 2.0f) - (nDepth * (m_size.z / m_nDepth)));

			// 法線ベクトルの設定
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 頂点カラーの設定
			pVtx[nCntVtx].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// テクスチャ座標	  横の分割数 * 1.0f, 奥行の分割数 * 1.0f
			pVtx[nCntVtx].tex = D3DXVECTOR2(nWidth * 1.0f, nDepth * 1.0f);
		}
	}

	// 頂点バッファをアンロックする
	(*pVtxBuff)->Unlock();

	LPDIRECT3DINDEXBUFFER9	*pIdxBuff = GetIdxBuff();	// インデックスへのポインタをScene3Dから参照して取得

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
	for (int nDepth = 0; nDepth < m_nDepth + 1; nDepth++)
	{
		for (int nWidth = 0; nWidth < m_nWidth + 1; nWidth++)
		{
			// 重複しない頂点情報のインデックスを設定
			pIdx[(m_nWidth * 2 + 4) * nDepth + 0 + (nWidth * 2)] = (nWidth + (m_nWidth + 1) + (m_nWidth + 1) * nDepth);
			pIdx[(m_nWidth * 2 + 4) * nDepth + 1 + (nWidth * 2)] = (nWidth + 0 + (m_nWidth + 1) * nDepth);
		}
	}
	// 重複する頂点情報のインデックスを設定
	for (int nDup = 0; nDup < m_nDepth - 1; nDup++)
	{
		pIdx[(m_nWidth * 2 + 2) + 0 + nDup * (m_nWidth * 2 + 4)] = (m_nWidth + (m_nWidth + 1) * nDup);
		pIdx[(m_nWidth * 2 + 2) + 1 + nDup * (m_nWidth * 2 + 4)] = ((m_nWidth * 2 + 2) + (m_nWidth + 1) * nDup);
	}

	// インデックスバッファをアンロックする
	(*pIdxBuff)->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMeshField::Uninit(void)
{
	CScene3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMeshField::Update(void)
{
	CScene3D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshField::Draw(void)
{
	CScene3D::Draw();
}
//=============================================================================
// 生成処理
//=============================================================================
CMeshField *CMeshField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nWidth, int nDepth, int nType)
{
	CMeshField *pMeshField;
	pMeshField = new CMeshField;

	if (pMeshField != NULL)
	{
		pMeshField->m_nType = nType;	// テクスチャの種類を設定
		pMeshField->SetPosition(pos);	// 位置を設定
		pMeshField->m_size = size;		// 床の大きさ
		pMeshField->m_nWidth = nWidth;	// 幅の分割数
		pMeshField->m_nDepth = nDepth;	// 奥行の分割数
		pMeshField->SetNumVtx((nWidth + 1) * (nDepth + 1));	// 頂点数
		pMeshField->SetNumIdx((nWidth + 1) * (nDepth + 1) + ((nWidth + 3) * (nDepth - 1)));	// インデックス数：(頂点数) + (横の分割数 + 3) * (奥行の分割数 - 1)
		pMeshField->SetNumPrimitive((nWidth + 1) * (nDepth + 1) + ((nWidth + 3) * (nDepth - 1)));
		pMeshField->Init();				// 初期化処理
	}

	return pMeshField;
}
//=============================================================================
// 当たり判定
//=============================================================================
bool CMeshField::Collision(CMeshField *pMeshField, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float& BackPos)
{
	if (pMeshField != NULL)
	{
		D3DXVECTOR3 pos = pMeshField->GetPosition();
		D3DXVECTOR3 size = pMeshField->GetSize();

		if (pPos->y <= pos.y && pPosOld->y >= pos.y)
		{
			if (pPos->x >= pos.x - m_size.x + 10.0f && pPos->z <= pos.z + m_size.z + 10.0f &&
				pPos->x <= pos.x + m_size.x + 10.0f && pPos->z >= pos.z - m_size.z + 10.0f)
			{
				pPos->y = pos.y;
				BackPos = pos.y;
				return true;
			}
		}
	}
	return false;
}
