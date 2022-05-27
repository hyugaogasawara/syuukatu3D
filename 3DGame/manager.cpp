//=============================================================================
//
// マネージャ [manager.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//*****************************************************************************
//ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"
#include "keyboard.h"
#include "mouse.h"
//#include "xinput_pad.h"
//#include "sound.h"
//#include "loadData.h"
//
#include "title.h"
//#include "menu.h"
//#include "tutorial.h"
#include "select.h"
#include "game.h"
//#include "result.h"
#include "fade.h"

#include "light.h"
#include "camera.h"
#include "texture.h"
#include "Xload.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTURE_FILE "data/LOADFILE/texture.txt"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CManager		*CManager::m_pInstance = NULL;
CRenderer		*CManager::m_pRenderer = NULL;
CInputKeyboard	*CManager::m_pKeyboard = NULL;
CMouse			*CManager::m_pMouse = NULL;
CXinputPad		*CManager::m_pXinputPad = NULL;
CSound			*CManager::m_pSound = NULL;

CTitle			*CManager::m_pTitle = NULL;
CMenu			*CManager::m_pMenu = NULL;
CTutorial		*CManager::m_pTutorial = NULL;
CSelect			*CManager::m_pSelect = NULL;
CGame			*CManager::m_pGame = NULL;
CResult			*CManager::m_pResult = NULL;
CRanking		*CManager::m_pRanking = NULL;

CFade			*CManager::m_pFade = NULL;
CTexture		*CManager::m_pTexture = NULL;
CModel			*CManager::m_pModel = NULL;
CXload			*CManager::m_pXload = NULL;
CLoadData		*CManager::m_pLoadData = NULL;
CCamera			*CManager::m_pCamera = NULL;
CLight			*CManager::m_apLight[MAX_LIGHT] = {};
CManager::MODE	CManager::m_mode = MODE_GAME;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CManager::CManager()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// レンダラーの成
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;

		// レンダラー初期化処理
		if (m_pRenderer != NULL)
		{
			m_pRenderer->Init(hWnd, bWindow);
		}
	}
	// キーボード生成
	if (m_pKeyboard == NULL)
	{
		m_pKeyboard = new CInputKeyboard;

		// キーボード初期化処理
		if (m_pKeyboard != NULL)
		{
			m_pKeyboard->Init(hInstance, hWnd);
		}
	}
	// マウス生成
	if (m_pMouse == NULL)
	{
		m_pMouse = new CMouse;

		// マウス初期化処理
		if (m_pMouse != NULL)
		{
			m_pMouse->Init(hInstance, hWnd);
		}
	}
#if 0 
	// ゲームパッド生成
	if (m_pXinputPad == NULL)
	{
		m_pXinputPad = new CXinputPad;

		// ゲームパッド初期化処理
		if (m_pXinputPad != NULL)
		{
			m_pXinputPad->Init(hInstance, hWnd);
		}
	}
	// サウンド生成
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;

		if (m_pSound != NULL)
		{
			// サウンド初期化処理
			m_pSound->Init(hWnd);
		}
	}
	// 読み込みデータクラス生成
	if (m_pLoadData == NULL)
	{
		m_pLoadData = new CLoadData;

		if (m_pLoadData != NULL)
		{
			// テクスチャ初期化処理
			m_pLoadData->Init();
		}
	}
#endif	// ゲームパッド,サウンド,読み込みクラス
	// テクスチャ生成
	if (m_pTexture == NULL)
	{
		m_pTexture = new CTexture;

		if (m_pTexture != NULL)
		{
			// テクスチャ初期化処理
			m_pTexture->Init();
		}
	}
	if (m_pXload == NULL)
	{
		m_pXload = new CXload;

		if (m_pXload != NULL)
		{
			// テクスチャ初期化処理
			m_pXload->Init();
		}
	}

	// フェードの生成
	m_pFade = CFade::Create(m_mode);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{
	// 全てのオブジェクトクラスを破棄
	CScene::ReleaseAll();

	// キーボード情報破棄
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Uninit();

		// キーボードの開放
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}
	// マウス情報破棄
	if (m_pMouse != NULL)
	{
		m_pMouse->Uninit();

		// マウスの開放
		delete m_pMouse;
		m_pMouse = NULL;
	}
#if 0
	// Xinputゲームパッド情報破棄
	if (m_pXinputPad != NULL)
	{
		m_pXinputPad->Uninit();

		// Xinputゲームパッドの開放
		delete m_pXinputPad;
		m_pXinputPad = NULL;
	}
	// サウンド情報破棄
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();

		// サウンドの開放
		delete m_pSound;
		m_pSound = NULL;
	}
#endif	// ゲームパッド,サウンドクラス

	// カメラ情報破棄
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	// ライトの破棄
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		if (m_apLight[nCntLight] != NULL)
		{
			m_apLight[nCntLight]->Uninit();
			delete m_apLight[nCntLight];
			m_apLight[nCntLight] = NULL;
		}
	}
	// テクスチャ情報破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Uninit();

		// テクスチャの開放
		delete m_pTexture;
		m_pTexture = NULL;
	}
	// モデル情報破棄
	if (m_pXload != NULL)
	{
		m_pXload->Uninit();

		// テクスチャの開放
		delete m_pXload;
		m_pXload = NULL;
	}

	// レンダラー情報破棄
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();

		// レンダラーの開放
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	// キーボードの更新処理
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Update();
	}
	// マウスの更新処理
	if (m_pMouse != NULL)
	{
		m_pMouse->Update();
	}
	// ゲームパッドの更新処理
#if 0
	if (m_pXinputPad != NULL)
	{
		m_pXinputPad->Update();
	}
#endif	// ゲームパッド

	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}
	// レンダラーの更新処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	// レンダラーの描画処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();	

		// カメラの設定
		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			if (m_pCamera)	// nullチェック
			{
				m_pCamera->SetCamera();
			}
		}
	}

}
//=============================================================================
// モードの設定
//=============================================================================
void CManager::SetMode(CManager::MODE mode)
{
	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;
	case MODE_MENU:
		//if (m_pMenu != NULL)
		//{
		//	m_pMenu->Uninit();
		//	m_pMenu = NULL;
		//}
		break;
	case MODE_TUTORIAL:
		//if (m_pTutorial != NULL)
		//{
		//	m_pTutorial->Uninit();
		//	m_pTutorial = NULL;
		//}
		break;
	case MODE_SELECT:
		if (m_pSelect != NULL)
		{
			m_pSelect->Uninit();
			m_pSelect = NULL;
		}
		break;
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			//カメラの破棄
			if (m_pCamera != NULL)
			{
				//終了処理
				m_pCamera->Uninit();

				//メモリの開放
				delete m_pCamera;
				m_pCamera = NULL;
			}

			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;
	case MODE_RESULT:
		//if (m_pResult != NULL)
		//{
		//	m_pResult->Uninit();
		//	delete m_pResult;
		//	m_pResult = NULL;
		//}
		break;
	default:
		break;
	}

	// 全てのオブジェクトクラスを破棄
	CScene::ReleaseAll();

	switch (mode)
	{
	case MODE_TITLE:
		m_pTitle = CTitle::Create();
		break;
	case MODE_MENU:
		//m_pMenu = CMenu::Create();
		break;
	case MODE_TUTORIAL:
		//m_pTutorial = CTutorial::Create();
		break;
	case MODE_SELECT:
		m_pSelect = CSelect::Create();
		break;
	case MODE_GAME:
		// カメラの生成
		if (!m_pCamera)
		{
			m_pCamera = CCamera::Create();
		}
		// ライティングの生成
		m_apLight[0] = CLight::Create(D3DXVECTOR3(0.2f, -0.8f, 0.4f), D3DXVECTOR3(400.0f, 800.0f, -400.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
		m_apLight[1] = CLight::Create(D3DXVECTOR3(-0.2f, 0.8f, -0.4f), D3DXVECTOR3(-100.0f, 0.0f, 100.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1);
		m_apLight[2] = CLight::Create(D3DXVECTOR3(0.4f, -0.1f, 0.4f), D3DXVECTOR3(100.0f, 0.0f, -200.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2);

		if (!m_pGame)
		{
			m_pGame = CGame::Create();
		}
		break;
	case MODE_RESULT:
		//m_pResult = CResult::Create();
		break;
	default:
		break;
	}

	m_mode = mode;
}