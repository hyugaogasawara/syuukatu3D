//=============================================================================
//
// プレイヤークラス [player.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//ヘッダファイルのインクルード
//=============================================================================
#include "player.h"
#include "keyboard.h"
#include "loadData.h"
#include "model.h"
#include "camera.h"
#include "modelsingle.h"
#include "game.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define FILENAME_PLAYER "data/LOADFILE/model.txt"
#define SPEED 2.0f
//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene(nPriority)
{
	// メンバ変数のクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 1フレーム前の位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 大きさ
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量
	m_pKeyboard = CManager::GetInputKeyboard();	// キーボード情報取得

	// モデル生成
	CLoadData::LoadModel(FILENAME_PLAYER);		// モデルデータの読み込み
	m_nNumModel = CLoadData::GetNumModel();		// パーツ数取得

	// パーツの数分モデル情報を取得
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		m_pModel[nCntModel] = CLoadData::GetModel(nCntModel);	// パーツ数分を読み込んだデータから取得
	}

}
//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(void)
{
	// オブジェクトの種類設定
	SetObjType(OBJTYPE_PLAYER);	

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	// モデルを破棄
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel]->Uninit();
		}
	}

	// オブジェクトを開放
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{

	// 移動量更新
	m_pos += m_move;

	m_posOld = m_pos;

	// 移動処理
	Move();

	// 位置を設定
	CScene::SetPosOld(m_posOld);
	CScene::SetPosition(m_pos);
	CScene::SetSize(m_size);

	CModelSingle *pModelSingle = CGame::GetModelSingle();

	if (pModelSingle->Collision() == true)
	{

	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 計算用マトリックス
	D3DXMATRIX	mtxRot, mtxTrans;

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

	// モデルの描画
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel]->Draw();
		}
	}
}
//=============================================================================
// プレイヤーの生成
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer *pPlayer = nullptr;
	if (pPlayer == nullptr)
	{
		pPlayer = new CPlayer;

		if (pPlayer != nullptr)
		{
			pPlayer->Init();		//初期化処理
			pPlayer->m_pos = pos;	// 位置
			pPlayer->m_rot = rot;	// 向き
		}
	}
	return pPlayer;
}
//=============================================================================
// 移動処理
//=============================================================================
void CPlayer::Move(void)
{
	//-----------------------------------------------------
	//					キーボード操作
	//-----------------------------------------------------
	//　カメラの情報取得
	CCamera *pCamera = CManager::GetCamera();

	// カメラの向きを取得
	float fCameraRotY = pCamera->GetRot().y;

	// 移動速度
	float fSpeed = SPEED;

	if (m_pKeyboard->GetPress(DIK_W) == true)
	{
		if (m_pKeyboard->GetPress(DIK_A) == true)
		{
			m_rot.y = (D3DX_PI * 3) / 4;
			m_move.x = sinf(fCameraRotY + (D3DX_PI * 3) / 4) * -fSpeed;
			m_move.z = cosf(fCameraRotY + (D3DX_PI * 3) / 4) * -fSpeed;
		}
		else if (m_pKeyboard->GetPress(DIK_D) == true)
		{
			m_rot.y = -(D3DX_PI * 3) / 4;
			m_move.x = sinf(fCameraRotY - (D3DX_PI * 3) / 4) * -fSpeed;
			m_move.z = cosf(fCameraRotY - (D3DX_PI * 3) / 4) * -fSpeed;
		}
		else
		{
			m_rot.y = D3DX_PI;
			m_move.x = sinf(fCameraRotY) * fSpeed;
			m_move.z = cosf(fCameraRotY) * fSpeed;
		}
	}
	else if (m_pKeyboard->GetPress(DIK_S) == true)
	{
		if (m_pKeyboard->GetPress(DIK_A) == true)
		{
			m_rot.y = -(D3DX_PI * 7) / 4;
			m_move.x = sinf(fCameraRotY - (D3DX_PI * 7) / 4) * -fSpeed;
			m_move.z = cosf(fCameraRotY - (D3DX_PI * 7) / 4) * -fSpeed;
		}
		else if (m_pKeyboard->GetPress(DIK_D) == true)
		{
			m_rot.y = (D3DX_PI * 7) / 4;
			m_move.x = sinf(fCameraRotY + (D3DX_PI * 7) / 4) * -fSpeed;
			m_move.z = cosf(fCameraRotY + (D3DX_PI * 7) / 4) * -fSpeed;
		}
		else
		{
			m_rot.y = fCameraRotY;
			m_move.x = sinf(fCameraRotY) * fSpeed;
			m_move.z = cosf(fCameraRotY) * -fSpeed;
		}
	}
	else if (m_pKeyboard->GetPress(DIK_A) == true)
	{
		m_rot.y = D3DX_PI / 2;
		m_move.x = cosf(fCameraRotY) * -fSpeed;
		m_move.z = sinf(fCameraRotY) * -fSpeed;
	}
	else if (m_pKeyboard->GetPress(DIK_D) == true)
	{
		m_rot.y = -D3DX_PI / 2;
		m_move.x = cosf(fCameraRotY) * fSpeed;
		m_move.z = sinf(fCameraRotY) * fSpeed;
	}

	// 慣性を設定
	m_move.x *= 0.8f;
	m_move.z *= 0.8f;

	// 移動量が設定した値の範囲になったら停止
	if (m_move.x <= 0.1f && m_move.x >= -0.1f)
	{
		m_move.x = 0.0f;
	}
	if (m_move.z <= 0.1f && m_move.z >= -0.1f)
	{
		m_move.z = 0.0f;
	}

	//-----------------------------------------------------
	//					ゲームパッド操作
	//-----------------------------------------------------

}
