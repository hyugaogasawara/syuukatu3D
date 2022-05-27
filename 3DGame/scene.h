//=============================================================================
//
// オブジェクトクラス [scene.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//	オブジェクトクラス
//*****************************************************************************
class CScene
{
public:
	// オブジェクトの種類
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_SPHERE,		// 床
		OBJTYPE_FIELD,		// 床
		OBJTYPE_MODEL,
		OBJTYPE_PLAYER,		// プレイヤー
		OBJTYPE_BULLET,		// 弾
		OBJTYPE_EFFECT,		// エフェクト
		OBJTYPE_SIGHT,		// 照準
		OBJTYPE_UI,			// UI
		OBJTYPE_MAX			// 最大数
	} OBJTYPE;

	// 描画の優先順位
	typedef enum
	{
		PRIORITY_NONE = 0,
		PRIORITY_BG,		// 背景
		PRIORITY_SPHERE,	// 球
		PRIORITY_FIELD,		// 床
		PRIORITY_MODEL,		// モデル
		PRIORITY_PLAYER,	// プレイヤー
		PRIORITY_BULLET,	// 弾
		PRIORITY_EFFECT,	// エフェクト
		PRIORITY_SIGHT,		// 照準
		PRIORITY_UI,		// UI
		PRIORITY_FADE,		// フェード
		PRIORITY_MAX		// 最大数
	} PRIORITY;

	CScene(int nPriority = PRIORITY_NONE);			// 引数を持つコンストラクタ
	virtual ~CScene();				// デストラクタ

	virtual HRESULT Init(void) = 0;	// 初期化処理
	virtual void Uninit(void) = 0;	// 終了処理
	virtual void Update(void) = 0;	// 更新処理
	virtual void Draw(void) = 0;	// 描画処理

	static void ReleaseAll(void);	// 全てのオブジェクトの破棄
	static void UpdateAll(void);	// 全てのオブジェクトの更新処理
	static void DrawAll(void);		// 全てのオブジェクトの描画処理

	// 取得処理
	static CScene *GetTopObj(int nPriority) { return m_pTop[nPriority]; }	// 先頭オブジェクト取得
	CScene *GetNextObj(CScene *pScene) { return pScene->m_pNext; }			// 次のオブジェクト情報取得
	OBJTYPE GetObjType(void) { return m_objType; }							// オブジェクトの種類を取得
	D3DXVECTOR3 GetPosition(void) { return m_pos; }							// 位置
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }						// 1フレーム前の位置
	D3DXVECTOR3 GetSize(void) { return m_size; }							// 大きさ

	// 設定処理
	void SetObjType(OBJTYPE objType) { m_objType = objType; }	// オブジェクトの種類
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }			// 位置
	void SetPosOld(D3DXVECTOR3 posOld) { m_posOld = posOld; }	// 位置
	void SetSize(D3DXVECTOR3 size) { m_size = size; }			// 大きさ

protected:
	void Release(void) { m_bDeath = true; }	// オブジェクトの開放

private:
	// リスト構造
	static CScene *m_pTop[PRIORITY_MAX];	// 先頭オブジェクト
	static CScene *m_pCur[PRIORITY_MAX];	// 現在(最後尾)のオブジェクト
	CScene	*m_pPrev;		// 前のオブジェクトへのポインタ
	CScene	*m_pNext;		// 次のオブジェクトへのポインタ
	bool	m_bDeath;		// 死亡フラグ

	OBJTYPE m_objType;		// オブジェクトの種類
	int		m_nPriority;	// 描画の優先順位

	// 当たり判定関連
	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_posOld;	// 1フレーム前の位置
	D3DXVECTOR3 m_size;		// 大きさ
};

#endif //!_SCENE_H_