//=============================================================================
//
// プレイヤークラス [player.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CModel;
class CInputKeyboard;
class CGamePad;
class CXLoad;
//*****************************************************************************
//	プレイヤークラス
//*****************************************************************************
class CPlayer : public CScene
{
public:
	CPlayer(int nPriority = PRIORITY_PLAYER);	// コンストラクタ
	~CPlayer();			// デストラクタ

	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	// 生成処理
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	
	
	// 取得処理
	D3DXVECTOR3	GetPosition(void) { return m_pos; }		// 位置
	D3DXVECTOR3	GetPositionOld(void) { return m_posOld; }	// 1フレーム前の位置
	D3DXVECTOR3	GetRotation(void) { return m_rot; }		// 向き
	D3DXVECTOR3	GetMovement(void) { return m_move; }	// 移動量

	// 設定処理
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	// 位置
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }	// 向き
private:
	void Move(void);		// 移動処理
	void Attack(void);		// 攻撃処理
	void Collision(void);	// 当たり判定

	D3DXMATRIX		m_mtxWorld;		// ワールドマトリックス
	D3DXVECTOR3		m_pos;			// 位置
	D3DXVECTOR3		m_posOld;		// 1フレーム前の位置
	D3DXVECTOR3		m_rot;			// 向き
	D3DXVECTOR3		m_size;			// 大きさ
	D3DXVECTOR3		m_move;			// 移動量
	CModel			*m_pModel[32];	// モデルへのポインタ
	CXLoad			*m_pXload;
	CInputKeyboard	*m_pKeyboard;	// キーボード入力情報
	int				m_nNumModel;	// モデルの総数
};
#endif //!_PLAYER_H_