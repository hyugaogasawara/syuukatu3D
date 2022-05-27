//=============================================================================
//
// モデルクラス [modelsingle.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//ヘッダファイルのインクルード
//=============================================================================
#include "modelsingle.h"
#include "Xload.h"
#include "game.h"
#include "bullet.h"
#include "score.h"
//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CModelSingle::CModelSingle(int nPriority) : CScene(nPriority)
{
	// メンバ変数のクリア
	memset(m_pTexture, NULL, sizeof(m_pTexture));	// テクスチャのポインタ
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向き
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 大きさ
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 各頂点の最小値
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 各頂点の最大値
	m_pMesh = NULL;									// メッシュ（頂点情報）へのポインタ
	m_pBuffMat = NULL;								// マテリアル（材質情報）へのポインタ
	m_nNumMat = 0;									// マテリアル数
	m_pXload = CManager::GetXLoad();				// Xファイルのデータ取得
}
//=============================================================================
// デストラクタ
//=============================================================================
CModelSingle::~CModelSingle()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CModelSingle::Init(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	// オブジェクトの種類
	SetObjType(OBJTYPE_MODEL);

	// Xファイルのデータを取得
	m_pBuffMat = m_pXload->GetBuffMat(m_nModelType);
	m_nNumMat = m_pXload->GetNumMat(m_nModelType);
	m_pMesh = m_pXload->GetMesh(m_nModelType);

	// Xファイルの読み込み
	//D3DXLoadMeshFromX("data/MODEL/target.x", D3DXMESH_SYSTEMMEM,
	//	pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);

	// マテリアルデータへのポインタ
	D3DXMATERIAL	*pMat;
	int nCntTex = 0;

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_pTexture[nCntTex]);
			nCntTex++;
		}
	}

	// 頂点情報の取得
	int nNumVtx;		// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;		// 頂点バッファへのポインタ

	// 頂点数を取得
	nNumVtx = m_pMesh->GetNumVertices();

	// 頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	// 頂点バッファをロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		// 頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		// 全ての頂点を比較して最大値と最小値を抜き出す
		// 最大値
		if (vtx.x >= m_vtxMax.x)
		{
			m_vtxMax.x = vtx.x;
		}
		if (vtx.y >= m_vtxMax.y)
		{
			m_vtxMax.y = vtx.y;
		}
		if (vtx.z >= m_vtxMax.z)
		{
			m_vtxMax.z = vtx.z;
		}
		// 最小値
		if (vtx.x <= m_vtxMin.x)
		{
			m_vtxMin.x = vtx.x;
		}
		if (vtx.y <= m_vtxMin.y)
		{
			m_vtxMin.y = vtx.y;
		}
		if (vtx.z <= m_vtxMin.z)
		{
			m_vtxMin.z = vtx.z;
		}
		// 頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}
	// 最大値と最小値を引いた値がモデルの大きさ
	m_size.x = m_vtxMax.x - m_vtxMin.x;
	m_size.y = m_vtxMax.y - m_vtxMin.y;
	m_size.z = m_vtxMax.z - m_vtxMin.z;

	// 頂点設定
	// 正面の頂点
	m_vtx[0].x = m_vtxMin.x;
	m_vtx[0].y = m_vtxMax.y;
	m_vtx[0].z = m_vtxMin.z;
	m_vtx[1].x = m_vtxMax.x;
	m_vtx[1].y = m_vtxMax.y;
	m_vtx[1].z = m_vtxMin.z;
	m_vtx[2].x = m_vtxMin.x;
	m_vtx[2].y = m_vtxMin.y;
	m_vtx[2].z = m_vtxMin.z;
	m_vtx[3].x = m_vtxMax.x;
	m_vtx[3].y = m_vtxMin.y;
	m_vtx[3].z = m_vtxMin.z;
	// 背面の頂点
	m_vtx[4].x = m_vtxMin.x;
	m_vtx[4].y = m_vtxMax.y;
	m_vtx[4].z = m_vtxMax.z;
	m_vtx[5].x = m_vtxMax.x;
	m_vtx[5].y = m_vtxMax.y;
	m_vtx[5].z = m_vtxMax.z;
	m_vtx[6].x = m_vtxMin.x;
	m_vtx[6].y = m_vtxMin.y;
	m_vtx[6].z = m_vtxMax.z;
	m_vtx[7].x = m_vtxMax.x;
	m_vtx[7].y = m_vtxMin.y;
	m_vtx[7].z = m_vtxMax.z;

	// 頂点バッファをアンロック
	m_pMesh->UnlockVertexBuffer();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CModelSingle::Uninit(void)
{
	// オブジェクトの開放
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CModelSingle::Update(void)
{
	if (m_nModelType == 0)
	{
		// 当たり判定
		CModelSingle::Collision();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CModelSingle::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX	mtxRot, mtxTrans;	// 計算用マトリックス
	D3DMATERIAL9		matDef;		// 現在のマテリアル保存用
	D3DXMATERIAL		*pMat;		// マテリアルデータへのポインタ
	int					nCntTex = 0;// テクスチャ数カウント

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// 各パーツのワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// マテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	if (m_pBuffMat != NULL)
	{
		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			if (pMat->pTextureFilename)
			{	// テクスチャの設定
				pDevice->SetTexture(0, m_pTexture[nCntTex]);
				nCntTex++;
			}
			else
			{	// テクスチャの設定
				pDevice->SetTexture(0, NULL);
			}
			// モデル（パーツ）の描画	
			m_pMesh->DrawSubset(nCntMat);
		}
		// 保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}

	D3DXMATRIX vtxTrans,vtxParent;

	// 8頂点分のワールド座標を保存
	for (int nCnt = 0; nCnt < MODEL_VTX; nCnt++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_aMtxWorld[nCnt]);

		// 位置を反映
		D3DXMatrixTranslation(&vtxTrans, m_vtx[nCnt].x, m_vtx[nCnt].y, m_vtx[nCnt].z);
		D3DXMatrixMultiply(&m_aMtxWorld[nCnt], &m_aMtxWorld[nCnt], &vtxTrans);

		if (m_mtxWorld)
		{
			vtxParent = m_mtxWorld;
		}
		else
		{
			pDevice->GetTransform(D3DTS_WORLD, &vtxParent);
		}

		// 親子関係を掛け合わせる
		D3DXMatrixMultiply(&m_aMtxWorld[nCnt], &vtxParent, &m_aMtxWorld[nCnt]);

		// 各パーツのワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_aMtxWorld[nCnt]);

		// ワールド座標を保存
		m_aSaveMtxWorld[nCnt].x = m_aMtxWorld[nCnt]._41;
		m_aSaveMtxWorld[nCnt].y = m_aMtxWorld[nCnt]._42;
		m_aSaveMtxWorld[nCnt].z = m_aMtxWorld[nCnt]._43;
	}
}
//=============================================================================
// 生成処理
//=============================================================================
CModelSingle *CModelSingle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	CModelSingle *pModelSingle = nullptr;
	if (pModelSingle == nullptr)
	{
		pModelSingle = new CModelSingle;

		if (pModelSingle != nullptr)
		{
			pModelSingle->SetPosition(pos);		// 位置
			pModelSingle->SetRotation(rot);		// 向き
			pModelSingle->SetModelType(nType);	// 種類
			pModelSingle->Init();				// 初期化処理
		}
	}
	return pModelSingle;
}
//=============================================================================
// 当たり判定
//=============================================================================
bool CModelSingle::Collision(void)
{
	// オブジェクト情報初期化
	CScene *pThisObj = nullptr;
	CScene *pSaveObj = nullptr;

	// 先頭オブジェクトの優先順位を取得
	pThisObj = pThisObj->GetTopObj(PRIORITY_BULLET);

	while (pThisObj)
	{
		// 現在のオブジェクトの情報保存
		pSaveObj = pThisObj;

		// オブジェクトの種類を取得
		if (pThisObj->GetObjType() == OBJTYPE_BULLET)
		{
			// 変数初期化
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// 位置を取得
			pos = pThisObj->GetPosition();

			// 4頂点から対象に向かって伸びるベクトルを算出
			D3DXVECTOR3 vec[MODEL_SURFACE_VTX];
			vec[0] = m_aSaveMtxWorld[0] - pos;
			vec[1] = m_aSaveMtxWorld[1] - pos;
			vec[2] = m_aSaveMtxWorld[2] - pos;
			vec[3] = m_aSaveMtxWorld[3] - pos;

			// 右回りのベクトルを算出
			D3DXVECTOR3 vec2[MODEL_SURFACE_VTX];
			vec2[0] = m_aSaveMtxWorld[1] - m_aSaveMtxWorld[0];
			vec2[1] = m_aSaveMtxWorld[3] - m_aSaveMtxWorld[1];
			vec2[2] = m_aSaveMtxWorld[2] - m_aSaveMtxWorld[3];
			vec2[3] = m_aSaveMtxWorld[0] - m_aSaveMtxWorld[2];

			// 外積を求める
			float fVecCross[MODEL_SURFACE_VTX];
			fVecCross[0] = (vec[0].x * vec2[0].y) - (vec2[0].x * vec[0].y);
			fVecCross[1] = (vec[1].x * vec2[1].y) - (vec2[1].x * vec[1].y);
			fVecCross[2] = (vec[3].x * vec2[2].y) - (vec2[2].x * vec[3].y);
			fVecCross[3] = (vec[2].x * vec2[3].y) - (vec2[3].x * vec[2].y);

			// 範囲内の判定
			if (fVecCross[0] < 0.0f && fVecCross[1] < 0.0f && fVecCross[2] < 0.0f && fVecCross[3] < 0.0f)
			{
				// 法線を求める
				D3DXVECTOR3 Normal;
				D3DXVECTOR3 vec1_3D;
				D3DXVECTOR3 vec2_3D;
				vec1_3D = vec2[1] - vec2[0];
				vec2_3D = vec2[2] - vec2[0];

				// 法線の計算(外積)
				D3DXVec3Cross(&Normal, &vec1_3D, &vec2_3D);

				// 正規化
				D3DXVec3Normalize(&Normal, &Normal);

				// 内積
				float fVecDot;
				fVecDot = -D3DXVec3Dot(&Normal, &vec[0]);

				// 求めた値が鋭角(90 ～ 180°)の場合はマイナス
				if (fVecDot < 0.0f)
				{
					CScore *pScore = CGame::GetScore();
					pScore->AddScore(100);

					// 当たり判定
					CBullet *pBullet;
					pBullet = (CBullet*)pThisObj;
					pBullet->SetUninit(true);
					this->Uninit();
					return true;
				}
			}

		}
		// 次のオブジェクトを取得
		pThisObj = pSaveObj->GetNextObj(pThisObj);
	}
	return false;
}
