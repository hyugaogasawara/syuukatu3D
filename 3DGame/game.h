//=============================================================================
//
// ゲームクラス [game.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPlayer;
class CMeshSphere;
class CMeshField;
class CModelSingle;
class CSight;
//*****************************************************************************
//	ゲームクラス
//*****************************************************************************
class CGame : public CScene
{
public:
	CGame(int nPriority = PRIORITY_NONE);	// デフォルトコンストラクタ
	~CGame();			// デストラクタ

	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	// 生成処理
	static CGame *Create(void);

	// 取得処理
	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CSight *GetSight(void) { return m_pSight; }
	static CModelSingle *GetModelSingle(void) { return m_pModelSingle; }

private:
	static CPlayer *m_pPlayer;
	static CMeshSphere *m_pMeshSphere;
	static CMeshField *m_pMeshField;
	static CModelSingle *m_pModelSingle;
	static CSight *m_pSight;
};
#endif //!_GAME_H_