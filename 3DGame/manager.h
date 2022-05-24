//=============================================================================
//
// マネージャ [manager.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_LIGHT 3	// ライトの最大数
#define MAX_CAMERA 1	// カメラの個体数
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CRenderer;
class CInputKeyboard;
class CMouse;
class CXinputPad;
class CSound;

class CTitle;
class CMenu;
class CTutorial;
class CSelect;
class CGame;
class CResult;
class CRanking;
class CFade;
class CLight;
class CCamera;
class CTexture;
class CLoadData;
class CModel;
class CXload;
//*****************************************************************************
//	マネージャクラス
//*****************************************************************************
class CManager
{
public:
	// モードの種類
	typedef enum
	{
		MODE_TITLE = 0,	// タイトル
		MODE_MENU,		// 選択
		MODE_TUTORIAL,	// チュートリアル
		MODE_SELECT,	// 武器セレクト
		MODE_GAME,		// ゲーム
		MODE_RESULT,	// リザルト
		MODE_MAX		// 最大数
	} MODE;

	CManager();		// デフォルトコンストラクタ
	~CManager();	// デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);	// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理

	// 取得処理
	static CManager			*GetInstance(void) { return m_pInstance; }				// インスタンス取得
	static CRenderer		*GetRenderer(void) { return m_pRenderer; }				// レンダラーを取得
	static CInputKeyboard	*GetInputKeyboard(void) { return m_pKeyboard; }			// キーボードを取得
	static CMouse			*GetMouse(void) { return m_pMouse; }					// マウスを取得
	static CXinputPad		*GetXinputPad(void) { return m_pXinputPad; }			// ゲームパッド取得
	static CSound			*GetSound(void) { return m_pSound; }					// サウンドを取得
	static CTitle			*GetTitle(void) { return m_pTitle; }					// タイトルのインスタンス
	static CMenu			*GetMenu(void) { return m_pMenu; }						// メニューのインスタンス
	static CTutorial		*GetTutorial(void) { return m_pTutorial; }				// チュートリアルのインスタンス
	static CSelect			*GetSelect(void) { return m_pSelect; }					// セレクトのインスタンス
	static CGame			*GetGame(void) { return m_pGame; }						// ゲームのインスタンス
	static CResult			*GetResult(void) { return m_pResult; }					// リザルトのインスタンス
	static CRanking			*GetRanking(void) { return m_pRanking; }				// ランキングのインスタンス
	static CFade			*GetFade(void) { return m_pFade; }						// フェードを取得
	static CLight			*GetLight(void) { return m_apLight[0]; }				// ライトを取得
	static CCamera			*GetCamera(void) { return m_pCamera; }			// カメラを取得
	static CTexture			*GetTexture(void) { return m_pTexture; }				// テクスチャを取得
	static CLoadData		*GetLoadData(void) { return m_pLoadData; }				// 読み込みデータクラスを取得
	static CModel			*GetModel(void) { return m_pModel; }					// モデルを取得
	static CXload			*GetXLoad(void) { return m_pXload; }				// プレイデータを取得

	// 設定処理
	static void SetMode(MODE mode);					// モードの設定
	static MODE GetMode(void) { return m_mode; }	// モードを取得

private:
	static CManager			*m_pInstance;			// 管理クラスのインスタンス
	static CRenderer		*m_pRenderer;			// レンダラーのインスタンス
	static CInputKeyboard	*m_pKeyboard;			// キーボードのインスタンス
	static CMouse			*m_pMouse;				// マウスのインスタンス
	static CXinputPad		*m_pXinputPad;			// ゲームパッドのインスタンス
	static CSound			*m_pSound;				// サウンドのインスタンス
	static CTitle			*m_pTitle;				// タイトルのインスタンス
	static CMenu			*m_pMenu;				// メニューのインスタンス
	static CTutorial		*m_pTutorial;			// チュートリアルのインスタンス
	static CSelect			*m_pSelect;				// セレクトのインスタンス
	static CGame			*m_pGame;				// ゲームのインスタンス
	static CResult			*m_pResult;				// リザルトのインスタンス
	static CRanking			*m_pRanking;			// ランキングのインスタンス
	static CFade			*m_pFade;				// フェードのインスタンス
	static CLight			*m_apLight[MAX_LIGHT];	// ライトのインスタンス
	static CCamera			*m_pCamera;				// カメラのインスタンス
	static CTexture			*m_pTexture;			// テクスチャのインスタンス
	static CLoadData		*m_pLoadData;			// 読み込みデータクラスのインスタンス
	static CModel			*m_pModel;				// モデルのインスタンス
	static CXload			*m_pXload;			// Xファイルデータのインスタンス

	static MODE				m_mode;					// 画面のモード

};
#endif //!_MANAGER_H_