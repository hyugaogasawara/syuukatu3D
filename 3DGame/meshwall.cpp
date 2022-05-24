//=============================================================================
//
// メッシュウォールクラス　：　壁 [meshwall.h]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//ヘッダファイルのインクルード
//=============================================================================
#include "meshwall.h"
#include "keyboard.h"
#include "game.h"
#include "texture.h"
//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CMeshWall::CMeshWall(int nPriority) : CScene3D(nPriority)
{
	// メンバ変数のクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}
//=============================================================================
// デストラクタ
//=============================================================================
CMeshWall::~CMeshWall()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshWall::Init(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CScene3D::BindTexture(m_nType);		// テクスチャの割り当て
	int nNumVtx = GetNumVtx();	// 頂点数を取得
	int nNumIdx = GetNumIdx();	// インデックス数を取得

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
	for (int nHeight = 0; nHeight < m_nHeight + 1; nHeight++)
	{	// 横の分割数 
		for (int nWidth = 0; nWidth < m_nWidth + 1; nWidth++, nCntVtx++)
		{
			// 位置の設定
			pVtx[nCntVtx].pos = D3DXVECTOR3(
				(-m_size.x / 2.0f) + (nWidth * (m_size.x / m_nWidth)),
				(m_size.y / 2.0f) - (nHeight * (m_size.y / m_nHeight)) + m_pos.y,
				m_pos.z);

			// 法線ベクトルの設定
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

			// 頂点カラーの設定
			pVtx[nCntVtx].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// テクスチャ座標	  横の分割数 * 1.0f, 高さの分割数 * 1.0f
			pVtx[nCntVtx].tex = D3DXVECTOR2(nWidth * 1.0f, nHeight * 1.0f);
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
	for (int nHeight = 0; nHeight < m_nHeight + 1; nHeight++)
	{
		for (int nWidth = 0; nWidth < m_nWidth + 1; nWidth++, nNumVtx++)
		{
			// 重複しない頂点情報のインデックスを設定
			pIdx[(m_nWidth * 2 + 4) * nHeight + 0 + (nWidth * 2)] = (nWidth + (m_nWidth + 1) + (m_nWidth + 1) * nHeight);
			pIdx[(m_nWidth * 2 + 4) * nHeight + 1 + (nWidth * 2)] = (nWidth + 0 + (m_nWidth + 1) * nHeight);
		}
	}
	// 重複する頂点情報のインデックスを設定
	for (int nDup = 0; nDup < m_nHeight - 1; nDup++)
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
void CMeshWall::Uninit(void)
{
	CScene3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMeshWall::Update(void)
{
	CScene3D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshWall::Draw(void)
{
	CScene3D::Draw();
}
//=============================================================================
// 壁を生成
//=============================================================================
CMeshWall *CMeshWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nWidth, int nHeight, int nType)
{
	CMeshWall *pMeshWall;
	pMeshWall = new CMeshWall;

	if (pMeshWall != NULL)
	{
		pMeshWall->m_nType = nType;
		pMeshWall->SetPosition(pos);	// 位置を設定
		pMeshWall->SetRotation(rot);	// 向きを設定
		pMeshWall->m_size = size;		// 壁の大きさ
		pMeshWall->m_nWidth = nWidth;	// 幅
		pMeshWall->m_nHeight = nHeight;	// 高さ
		pMeshWall->SetNumVtx((nWidth + 1) * (nHeight + 1));	// 頂点数
		pMeshWall->SetNumIdx(((nWidth + 1) * 2) * nHeight + (nHeight - 1) * 2);			// インデックス数：((幅 + 1) * 2) * 高さ + (高さ - 1) * 2
		pMeshWall->SetNumPrimitive(((nWidth + 1) * 2) * nHeight + (nHeight - 1) * 2);	// プリミティブ(三角形の面)数
		pMeshWall->Init();				// 初期化処理
	}

	return pMeshWall;
}
//=============================================================================
// 当たり判定
//=============================================================================
bool CMeshWall::Collision(CMeshWall *pMeshWall, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float& BackPos)
{
	if (pMeshWall != NULL)
	{
		D3DXVECTOR3 pos = pMeshWall->GetPosition();
		D3DXVECTOR3 size = pMeshWall->GetSize();

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
