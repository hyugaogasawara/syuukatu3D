//=============================================================================
//
//	マウスクラス [mouse.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//ヘッダファイルのインクルード
//=============================================================================
#include "mouse.h"
#include "input.h"
//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CMouse::CMouse()
{
	// 変数をクリア
	m_pDevice = NULL;
	ZeroMemory(&m_MouseState, sizeof(DIMOUSESTATE));	
	ZeroMemory(&m_MouseStateTrigger, sizeof(DIMOUSESTATE));
	ZeroMemory(&m_MouseStateRelease, sizeof(DIMOUSESTATE));
	m_bMouse = false;
}
//=============================================================================
// デストラクタ
//=============================================================================
CMouse::~CMouse()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInitオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	//入力デバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//カーソル非表示
	//ShowCursor(FALSE);

	//処理を同期させる
	m_pDevice->Poll();

	// マウスへのアクセス権を獲得(入力制御開始)
	m_pDevice->Acquire();
	m_bMouse = true;

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CMouse::Uninit(void)
{
	CInput::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CMouse::Update(void)
{
	DIMOUSESTATE aMouseState;	// 入力情報保存変数

	//入力デバイスからデータを取得する
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aMouseState), &aMouseState)))
	{
		for (int nCntButton = 0; nCntButton < DIM_MAX; nCntButton++)
		{
			m_MouseStateTrigger.rgbButtons[nCntButton] = m_MouseState.rgbButtons[nCntButton] ^ aMouseState.rgbButtons[nCntButton] & aMouseState.rgbButtons[nCntButton];
			m_MouseStateRelease.rgbButtons[nCntButton] = (m_MouseState.rgbButtons[nCntButton] ^ aMouseState.rgbButtons[nCntButton]) & m_MouseState.rgbButtons[nCntButton];
			m_MouseState.rgbButtons[nCntButton] = aMouseState.rgbButtons[nCntButton];	//マウスの入力情報保存
		}
		m_MouseState.lX = aMouseState.lX;	// X軸情報保存
		m_MouseState.lY = aMouseState.lY;	// Y軸情報保存
		m_MouseState.lZ = aMouseState.lZ;	// Z軸情報保存
	}
	else
	{
		m_pDevice->Acquire();	// マウスへのアクセス権を獲得
	}
}
//=============================================================================
// マウスの入力情報を取得
//=============================================================================
bool CMouse::GetPress(MouseButton Button)
{
	return (m_MouseState.rgbButtons[Button] & 0x80) ? true : false;
}
//=============================================================================
// トリガー情報を取得
//=============================================================================
bool CMouse::GetTrigger(MouseButton Button)
{
	return (m_MouseStateTrigger.rgbButtons[Button] & 0x80) ? true : false;

}
//=============================================================================
// リリース情報を取得
//=============================================================================
bool CMouse::GetRelease(MouseButton Button)
{
	return (m_MouseStateRelease.rgbButtons[Button] & 0x80) ? true : false;
}
//=============================================================================
// マウスのX軸情報(右：＋　左：ー)
//=============================================================================
float CMouse::MouseX(void)
{
	return (float)m_MouseState.lX;
}
//=============================================================================
// マウスのY軸情報(上：ー　下：＋)
//=============================================================================
float CMouse::MouseY(void)
{
	return (float)m_MouseState.lY;
}
//=============================================================================
// マウスのホイール(上方向：＋　下方向：ー)
//=============================================================================
float CMouse::MouseZ(void)
{
	return (float)m_MouseState.lZ;
}
//=============================================================================
// マウスの使用状況
//=============================================================================
bool CMouse::Mouse(void)
{
	return m_bMouse;
}
//=============================================================================
// ボタンの列挙情報に対応したボタン操作
//=============================================================================
bool CMouse::GetMouseButton(MouseButton Button)
{
	if ((m_MouseStateTrigger.rgbButtons[Button] & 0x80) != 0 && (m_MouseStateRelease.rgbButtons[Button] & 0x80) == 0)
	{
		return true;
	}
	return false;
}
