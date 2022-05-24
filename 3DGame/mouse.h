//=============================================================================
//
//	マウスクラス [mouse.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _MOUSE_H_
#define _MOUSE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_KEY_MAX (256) //キーの最大数

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "input.h"

//*****************************************************************************
//	マウスクラス
//*****************************************************************************
class CMouse : public CInput
{
public:
	// マウスのボタン列挙
	typedef enum
	{
		DIM_L = 0,	// 左クリック
		DIM_R,		// 右クリック
		DIM_W,		// ホイールボタン
		DIM_MAX		// ボタン最大数
	} MouseButton;

	CMouse();	// デフォルトコンストラクタ
	~CMouse();	// デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化処理
	void Uninit();									// 終了処理
	void Update();									// 更新処理

	// 取得処理
	bool GetPress(MouseButton Button);		// プレス情報
	bool GetTrigger(MouseButton Button);		// トリガー情報
	bool GetRelease(MouseButton Button);		// リリース情報
	float MouseX(void);	// マウスのX軸
	float MouseY(void);	// マウスのY軸
	float MouseZ(void);	// マウスのZ軸(マウスホイールの軸情報)
	bool Mouse(void);		// マウスの使用状況
	bool GetMouseButton(MouseButton Button);	// 入力情報
	DIMOUSESTATE GetMousePos(void) { return m_MouseState; }	// マウスの入力情報取得


private:
	DIMOUSESTATE	m_MouseState;			// マウスの入力情報(プレス情報)
	DIMOUSESTATE	m_MouseStateTrigger;	// マウスの入力情報(トリガー情報)
	DIMOUSESTATE	m_MouseStateRelease;	// マウスの入力情報(リリース情報)
	bool			m_bMouse;				// マウスの使用状況					
};
#endif //!_MOUSE_H_