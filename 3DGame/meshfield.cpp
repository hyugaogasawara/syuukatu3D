//=============================================================================
//
// メッシュフィールドクラス [meshfield.h]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "meshfield.h"
#include "keyboard.h"
#include "game.h"
//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CMeshField::m_pTexture = NULL;	// テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CMeshField::CMeshField(int nPriority) : CScene3D(nPriority)
{
	// メンバ変数のクリア
	memset(m_pos, 0, sizeof(m_pos));			// 位置
	memset(m_rot, 0, sizeof(m_rot));			// 位置
	memset(m_move, 0, sizeof(m_move));			// 移動量
	memset(m_size, 0, sizeof(m_size));		// 大きさ

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
	SetObjType(OBJTYPE_MODEL);

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (m_nWidth + 1) * (m_nDepth + 1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx; //頂点バッファへのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y, m_pos.z + m_size.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x,			  m_pos.y, m_pos.z + m_size.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y, m_pos.z + m_size.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y, m_pos.z);
	pVtx[4].pos = D3DXVECTOR3(m_pos.x,			  m_pos.y, m_pos.z);
	pVtx[5].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y, m_pos.z);

	pVtx[6].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y, m_pos.z - m_size.z);
	pVtx[7].pos = D3DXVECTOR3(m_pos.x,			  m_pos.y, m_pos.z - m_size.z);
	pVtx[8].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y, m_pos.z - m_size.z);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(5.0f, 5.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 5.0f);
	pVtx[2].tex = D3DXVECTOR2(5.0f, 5.0f);

	pVtx[3].tex = D3DXVECTOR2(5.0f, 0.0f);
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(5.0f, 0.0f);

	pVtx[6].tex = D3DXVECTOR2(5.0f, 5.0f);
	pVtx[7].tex = D3DXVECTOR2(0.0f, 5.0f);
	pVtx[8].tex = D3DXVECTOR2(5.0f, 5.0f);


	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * ((m_nWidth + 1) * (m_nDepth + 1) * 2) - 4,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	WORD *pIdx;		//インデックス情報へのポインタ

	//インデックスバッファをロックし、頂点データへのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//番号データの設定
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;

	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;

	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;

	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;


	//頂点バッファをアンロックする
	m_pIdxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMeshField::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//インデックスバッファの破棄
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CMeshField::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshField::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ポリゴンの描画
	pDevice->SetTexture(0, m_pTexture);

	// インデックスのプリミティブ
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (m_nWidth + 1) * (m_nDepth + 1), 0, 12);
}
//=============================================================================
// プレイヤーの生成
//=============================================================================
CMeshField *CMeshField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nWidth, int nDepth, int nType)
{
	CMeshField *pMeshField;
	pMeshField = new CMeshField;

	if (pMeshField != NULL)
	{
		pMeshField->m_pos = pos;
		pMeshField->m_size = size;
		pMeshField->m_nWidth = nWidth;
		pMeshField->m_nDepth = nDepth;
		pMeshField->Init();
		pMeshField->BindTexture(nType);
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
			if (pPos->x >= pos.x - size.x + 10.0f && pPos->z <= pos.z + size.z + 10.0f&&
				pPos->x <= pos.x + size.x + 10.0f && pPos->z >= pos.z - size.z + 10.0f)
			{
				pPos->y = pos.y;
				BackPos = pos.y;
				return true;
			}
		}
	}
	return false;
}
