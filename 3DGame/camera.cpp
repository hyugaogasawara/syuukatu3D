//=============================================================================
//
// カメラクラス [camea.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//ヘッダファイルのインクルード
//=============================================================================
#include "camera.h"
#include "keyboard.h"
#include "mouse.h"
#include "player.h"
#include "game.h"
//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CCamera::CCamera()
{
	// 変数をクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		
}
//=============================================================================
// デストラクタ
//=============================================================================
CCamera::~CCamera()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCamera::Init(void)
{
	m_fViewDepth = VIEW_Z;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posV = D3DXVECTOR3(0.0f, VIEW_Y, -m_fViewDepth);	// 視点
	m_posR = D3DXVECTOR3(0.0f, GAZE_Y, -GAZE_Z);		// 注視点
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				// 法線ベクトル
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// カメラの向き
	m_size = D3DXVECTOR3(100.0f ,0.0f ,100.0f);			// 大きさ

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CCamera::Uninit(void)
{
}
//=============================================================================
// 更新処理
//=============================================================================
void CCamera::Update(void)
{
	// キーボード情報取得
	CInputKeyboard *pKeyboard = NULL;
	pKeyboard = CManager::GetInputKeyboard();

	// マウス情報取得
	CMouse *pMouse = NULL;
	pMouse = CManager::GetMouse();

	// ゲームパッド情報取得
	CXinputPad *pXinputPad = NULL;
	pXinputPad = CManager::GetXinputPad();

	//KeyboardControl(pKeyboard);	// キーボード操作

	//MouseControl(pMouse);			// マウス操作

	//GamePadXControl(pXinputPad);		// ゲームパッド操作

	// プレイヤー情報取得
	CPlayer *pPlayer = CGame::GetPlayer();

	if (pPlayer != NULL)
	{
		// 追従
		D3DXVECTOR3 posR = pPlayer->GetMovement();
		D3DXVECTOR3 posV = pPlayer->GetMovement();
		m_posR += posR;
		m_posV += posV;
		//m_posR.x += posR.x;
		//m_posV.x += posV.x;
		//m_posR.z += posR.z;
		//m_posV.z += posV.z;
	}
	//m_posV.y = VIEW_Y;	// 視点
	//m_posR.y = GAZE_Y;	// 注視点

}
//=============================================================================
// 設定処理
//=============================================================================
void CCamera::SetCamera(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),						// 画角 360度
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	// 画面比率
		10.0f,										// 手前の位置
		4000.0f);									// 奥の位置	数値変更で描画範囲を広くする

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
//=============================================================================
// 生成処理
//=============================================================================
CCamera *CCamera::Create(void)
{
	CCamera *pCamera = nullptr;
	if (pCamera == nullptr)
	{
		pCamera = new CCamera;

		if (pCamera != nullptr)
		{
			pCamera->Init();
		}
	}
	return pCamera;
}
//=============================================================================
// キーボード操作
//=============================================================================
void CCamera::KeyboardControl(CInputKeyboard * pKeyboard)
{
	//=============================================
	//				カメラの移動処理
	//=============================================
	if (pKeyboard->GetPress(DIK_UP) == true)
	{// 前移動
		m_posV.x += sinf(m_rot.y) * (4.0f);
		m_posV.z += cosf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);	// sinf X軸の決定
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);	// cosf Z軸の決定
	}
	else if (pKeyboard->GetPress(DIK_DOWN) == true)
	{// 後移動
		m_posV.x -= sinf(m_rot.y) * (4.0f);
		m_posV.z -= cosf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);
	}
	else if (pKeyboard->GetPress(DIK_LEFT) == true)
	{// 左移動
		m_posV.x -= cosf(m_rot.y) * (4.0f);
		m_posV.z += sinf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);
	}
	else if (pKeyboard->GetPress(DIK_RIGHT) == true)
	{// 右移動
		m_posV.x += cosf(m_rot.y) * (4.0f);
		m_posV.z -= sinf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);
	}
	if (pKeyboard->GetPress(DIK_U) == true)
	{// 視点と注視点の距離
		m_posV.z += 4.0f;
	}
	if (pKeyboard->GetPress(DIK_M) == true)
	{// 視点と注視点の距離
		m_posV.z -= 4.0f;
	}

	//=============================================
	//					視点操作
	//=============================================
	if (pKeyboard->GetPress(DIK_Y) == true)
	{// 上移動
		m_posV.y += 4.0f;

		//if (m_posV.y >= 900.0f)
		//{
		//	m_posV.y = 900.0f;
		//}

	}
	else if (pKeyboard->GetPress(DIK_N) == true)
	{// 下移動
		m_posV.y -= 4.0f;

		//if (m_posV.y <= 200.0f)
		//{
		//	m_posV.y = 200.0f;
		//}

	}
	if (pKeyboard->GetPress(DIK_C) == true)
	{// 左旋回
		if (m_rot.y < D3DX_PI)
		{// -3.14fより小さくなったときに値を3.14fにする
			m_rot.y += D3DX_PI * 2.0f;
		}
		m_rot.y -= 0.03f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * VIEW_Z;
		m_posV.z = m_posR.z - cosf(m_rot.y) * VIEW_Z;
	}
	else if (pKeyboard->GetPress(DIK_Z) == true)
	{// 右旋回
		if (m_rot.y > D3DX_PI)
		{// 3.14fより大きくなったときに値を-3.14fにする
			m_rot.y -= D3DX_PI * 2.0f;
		}
		m_rot.y += 0.03f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * VIEW_Z;
		m_posV.z = m_posR.z - cosf(m_rot.y) * VIEW_Z;
	}

	//=============================================
	//					注視点操作
	//=============================================
	if (pKeyboard->GetPress(DIK_T) == true)
	{// 上移動
		m_posR.y += 2.0f;
	}
	else if (pKeyboard->GetPress(DIK_B) == true)
	{// 下移動
		m_posR.y -= 2.0f;
	}
	else if (pKeyboard->GetPress(DIK_Q) == true)
	{// 左旋回
		if (m_rot.y < D3DX_PI)
		{// -3.14fより小さくなったとき3.14fにする
			m_rot.y += D3DX_PI * 2.0f;
		}
		m_rot.y -= 0.03f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * VIEW_Z;
		m_posR.z = m_posV.z + cosf(m_rot.y) * VIEW_Z;
	}
	else if (pKeyboard->GetPress(DIK_E) == true)
	{// 右旋回
		if (m_rot.y > D3DX_PI)
		{// 3.14fより大きくなったとき-3.14fにする
			m_rot.y -= D3DX_PI * 2.0f;
		}
		m_rot.y += 0.03f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * VIEW_Z;
		m_posR.z = m_posV.z + cosf(m_rot.y) * VIEW_Z;
	}
}
//=============================================================================
// マウス操作
//=============================================================================
void CCamera::MouseControl(CMouse *pMouse)
{
#if 1
	// マウスの左ボタン
	if (pMouse->GetTrigger(CMouse::DIM_L) == true)
	{// マウス座標を取得
		GetCursorPos(&m_Cursol);
	}
	else if (pMouse->GetPress(CMouse::DIM_L) == true)
	{
		SetCursorPos(m_Cursol.x, m_Cursol.y);

		m_rot.y += pMouse->GetMousePos().lX * 0.01f;
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y = -D3DX_PI;
		}
		m_posV.y += pMouse->GetMousePos().lY * -0.1f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fViewDepth;
		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fViewDepth;
	}

	// マウスの右ボタン
	if (pMouse->GetTrigger(CMouse::DIM_R) == true)
	{// マウス座標を取得
		GetCursorPos(&m_Cursol);
	}
	else if (pMouse->GetPress(CMouse::DIM_R) == true)
	{
		SetCursorPos(m_Cursol.x, m_Cursol.y);

		m_rot.y -= pMouse->GetMousePos().lX * 0.001f;
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y = -D3DX_PI;
		}
		m_posR.y += pMouse->GetMousePos().lY * -0.1f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fViewDepth;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fViewDepth;

		//m_posR.y = m_fViewDepth * sinf(m_rot.x) * sinf(m_rot.y);
		//m_posR.x = m_fViewDepth * sinf(m_rot.x) * cosf(m_rot.y);
		//m_posR.z = m_fViewDepth * cosf(m_rot.x);
	}
#else
	// マウスの右ボタン
	if (pMouse->GetTrigger(CMouse::DIM_L) == true)
	{// マウス座標を取得
		GetCursorPos(&m_Cursol);
	}
	else if (pMouse->GetPress(CMouse::DIM_L) == true)
	{
		SetCursorPos(m_Cursol.x, m_Cursol.y);

		m_rot.x -= pMouse->GetMousePos().lX * 0.001f;
		m_rot.y += pMouse->GetMousePos().lY * -0.1f;
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y = -D3DX_PI;
		}

		//m_posR.x = m_posV.x + sinf(m_rot.y) * m_fViewDepth;
		//m_posR.z = m_posV.z + cosf(m_rot.y) * m_fViewDepth;

		m_posR.y = m_fViewDepth * sinf(m_rot.y) * cosf(m_rot.x);
		m_posR.x = m_fViewDepth * sinf(m_rot.y) * sinf(m_rot.x); 
		m_posR.z = m_fViewDepth * cosf(m_rot.y);
	}
#endif
}
//=============================================================================
// ゲームパッド操作：XInput
//=============================================================================
#if 0
void CCamera::GamePadXControl(CXinputPad *pGamePad)
{
	//=============================================
	//				カメラの移動処理
	//=============================================
	if (pGamePad->GetRightStick(CXinputPad::STICKTYPE_UP) == true)
	{// 前移動
		m_posV.x += sinf(m_rot.y) * (4.0f);
		m_posV.z += cosf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);	// sinf X軸の決定
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);	// cosf Z軸の決定
	}
	else if (pGamePad->GetRightStick(CXinputPad::STICKTYPE_DOWN) == true)
	{// 後移動
		m_posV.x -= sinf(m_rot.y) * (4.0f);
		m_posV.z -= cosf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);
	}
	else if (pGamePad->GetRightStick(CXinputPad::STICKTYPE_LEFT) == true)
	{// 左移動
		m_posV.x -= cosf(m_rot.y) * (4.0f);
		m_posV.z += sinf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);
	}
	else if (pGamePad->GetRightStick(CXinputPad::STICKTYPE_RIGHT) == true)
	{// 右移動
		m_posV.x += cosf(m_rot.y) * (4.0f);
		m_posV.z -= sinf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);
	}
	if (pGamePad->GetShoulder(CXinputPad::SHOULDERTYPE_RIGHT) == true)
	{// 視点と注視点の距離
		m_posV.z += 4.0f;
	}
	if (pGamePad->GetShoulder(CXinputPad::SHOULDERTYPE_LEFT) == true)
	{// 視点と注視点の距離
		m_posV.z -= 4.0f;
	}

	//=============================================
	//					視点操作
	//=============================================
	if (pGamePad->GetButtonPress(XINPUT_GAMEPAD_DPAD_UP) == true)
	{// 上移動
		m_posV.y += 4.0f;

		//if (m_posV.y >= 900.0f)
		//{
		//	m_posV.y = 900.0f;
		//}

	}
	if (pGamePad->GetButtonPress(XINPUT_GAMEPAD_DPAD_DOWN) == true)
	{// 下移動
		m_posV.y -= 4.0f;

		//if (m_posV.y <= 200.0f)
		//{
		//	m_posV.y = 200.0f;
		//}

	}
	if (pGamePad->GetButtonPress(XINPUT_GAMEPAD_DPAD_LEFT) == true)
	{// 左旋回
		if (m_rot.y < D3DX_PI)
		{// -3.14fより小さくなったときに値を3.14fにする
			m_rot.y += D3DX_PI * 2.0f;
		}
		m_rot.y -= 0.03f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * VIEW_Z;
		m_posV.z = m_posR.z - cosf(m_rot.y) * VIEW_Z;
	}
	if (pGamePad->GetButtonPress(XINPUT_GAMEPAD_DPAD_RIGHT) == true)
	{// 右旋回
		if (m_rot.y > D3DX_PI)
		{// 3.14fより大きくなったときに値を-3.14fにする
			m_rot.y -= D3DX_PI * 2.0f;
		}
		m_rot.y += 0.03f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * VIEW_Z;
		m_posV.z = m_posR.z - cosf(m_rot.y) * VIEW_Z;
	}

	//=============================================
	//					注視点操作
	//=============================================
	if (pGamePad->GetLeftStick(CXinputPad::STICKTYPE_UP) == true)
	{// 上移動
		m_posR.y += 2.0f;
	}
	if (pGamePad->GetLeftStick(CXinputPad::STICKTYPE_DOWN) == true)
	{// 下移動
		m_posR.y -= 2.0f;
	}
	if (pGamePad->GetLeftStick(CXinputPad::STICKTYPE_LEFT) == true)
	{// 左旋回
		if (m_rot.y < D3DX_PI)
		{// -3.14fより小さくなったとき3.14fにする
			m_rot.y += D3DX_PI * 2.0f;
		}
		m_rot.y -= 0.03f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * VIEW_Z;
		m_posR.z = m_posV.z + cosf(m_rot.y) * VIEW_Z;
	}
	if (pGamePad->GetLeftStick(CXinputPad::STICKTYPE_RIGHT) == true)
	{// 右旋回
		if (m_rot.y > D3DX_PI)
		{// 3.14fより大きくなったとき-3.14fにする
			m_rot.y -= D3DX_PI * 2.0f;
		}
		m_rot.y += 0.03f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * VIEW_Z;
		m_posR.z = m_posV.z + cosf(m_rot.y) * VIEW_Z;
	}

}
#endif