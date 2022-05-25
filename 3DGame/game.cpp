//=============================================================================
//
// ゲーム画面 [game.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//ヘッダファイルのインクルード
//=============================================================================
#include "game.h"
#include "keyboard.h"
#include "fade.h"
#include "meshfield.h"
#include "meshwall.h"
#include "meshcylinder.h"
#include "meshsphere.h"
#include "player.h"
#include "bullet.h"
#include "effect.h"
#include "modelsingle.h"
#include "sight.h"
//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CPlayer *CGame::m_pPlayer = nullptr;		// プレイヤー
CMeshField *CGame::m_pMeshField = nullptr;	// メッシュフィールド
CMeshSphere *CGame::m_pMeshSphere = nullptr;// メッシュスフィア
CModelSingle *CGame::m_pModelSingle = nullptr;	// モデル
CSight *CGame::m_pSight = nullptr;				// 照準

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CGame::CGame(int nPriority) : CScene(nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGame::Init(void)
{
	// 床
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 500.0f), 2, 2, 0);

	// 壁
	//CMeshWall::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), 5, 5, 0);

	// 円柱
	//CMeshCylinder::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 50.0f, 100.0f), 1, 16, 0, 0.001f);

	// 球/半球
	m_pMeshSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1000.0f, 12, 3, 2);

	// プレイヤー
	//m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	// モデル
	m_pModelSingle = CModelSingle::Create(D3DXVECTOR3(0.0f, 100.0f, 30.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), 0);

	// 照準
	m_pSight = CSight::Create(D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 4);

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Uninit();
		m_pMeshField = nullptr;
	}

	// オブジェクトの開放
	Release();
}
//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	// フェードの取得
	CFade *pFade = CManager::GetFade();

	// エフェクト
	//if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true)
	//{
	//	CEffect::Create(50.0f, 50.0f, 50.0f, D3DXVECTOR3(5.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(255, 255, 255, 255), D3DXCOLOR(0, 0, 0, 0), 120, 3);
	//}

	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		if (CManager::GetInputKeyboard()->GetTrigger(DIK_SPACE) == true)
		{
			pFade->SetFade(CManager::MODE_TITLE);
		}
	}

}
//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{
}
//=============================================================================
// ゲーム画面の生成
//=============================================================================
CGame *CGame::Create(void)
{
	CGame *pGame;
	pGame = new CGame;

	if (pGame != NULL)
	{
		pGame->Init();
	}

	return pGame;
}