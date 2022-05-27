//=============================================================================
//
// 照準クラス [sight.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//ヘッダファイルのインクルード
//=============================================================================
#include "sight.h"
#include "keyboard.h"
#include "mouse.h"
#include "bullet.h"
#include "modelsingle.h"
#include "game.h"
#include "effect.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define WIDTH_MOVE_LIMIT	120	// 移動幅制限
#define UP_MOVE_LIMIT		170	// 上移動制限
#define DOWN_MOVE_LIMIT		70	// 下移動制限
//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CSight::CSight(int nPriority) : CBillboard(nPriority)
{
	// メンバ変数のクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 大きさ
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量
	m_pKeyboard = CManager::GetInputKeyboard();	// キーボード情報取得
	m_pMouse = CManager::GetMouse();			// マウス情報取得
}
//=============================================================================
// デストラクタ
//=============================================================================
CSight::~CSight()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSight::Init(void)
{
	// オブジェクトの種類設定
	SetObjType(OBJTYPE_SIGHT);

	CBillboard::Init();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSight::Uninit(void)
{
	CBillboard::Uninit();

	// オブジェクトを開放
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CSight::Update(void)
{
	// 位置を取得
	m_pos = CBillboard::GetPosition();
	
	// 移動量更新
	m_pos += m_move;

	// 破棄
	if (m_bUninit == true)
	{
		Uninit();
	}

	// 移動処理
	Move();

	// マウス左ボタン
	if (m_pMouse->GetTrigger(CMouse::DIM_L) == true)
	{
		// 弾を生成
		//CEffect::Create(m_pos.x, m_pos.y, -20.0f, D3DXVECTOR3(3.5f, 3.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 5.0f), D3DXCOLOR(255, 255, 255, 255), D3DXCOLOR(0, 0, 0, 0), 120, 3);
		m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, -60.0f), D3DXVECTOR3(3.5f, 3.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 5.0f), 120, 1);

	}

	// 位置を設定
	CBillboard::SetPosition(m_pos);
	CBillboard::Update();

}

//=============================================================================
// 描画処理
//=============================================================================
void CSight::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Zテスト
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// 継承元の描画処理
	CBillboard::Draw();

	// Zテストを元に戻す
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);


	// ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//=============================================================================
// 生成処理
//=============================================================================
CSight *CSight::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType)
{
	CSight *pSight = nullptr;
	if (pSight == nullptr)
	{
		pSight = new CSight;

		if (pSight != nullptr)
		{
			pSight->m_pos = pos;		// 位置
			pSight->SetSize(size);		// 大きさ
			pSight->SetPosition(pos);	// 位置
			pSight->BindTexture(nType);	// テクスチャの種類
			pSight->Init();				// 初期化処理
		}
	}
	return pSight;
}
//=============================================================================
// 移動処理
//=============================================================================
void CSight::Move(void)
{
	// 移動速度
	float fSpeed = SPEED;
	
	// 上
	if (m_pKeyboard->GetPress(DIK_W) == true)
	{
		if (m_pKeyboard->GetPress(DIK_A) == true)
		{
			m_rot.y = (D3DX_PI * 7) / 4;
			m_pos.x += sinf(m_rot.y) * fSpeed / 2;
			m_pos.y += cosf(m_rot.y) * fSpeed / 2;
		}
		else if (m_pKeyboard->GetPress(DIK_D) == true)
		{
			m_rot.y = (D3DX_PI * 7) / 4;
			m_pos.x += sinf(-m_rot.y) * fSpeed / 2;
			m_pos.y += cosf(-m_rot.y) * fSpeed / 2;
		}
		else
		{
			m_rot.y = 0.0f;
			m_pos.x += sinf(m_rot.y) * fSpeed;
			m_pos.y += cosf(m_rot.y) * fSpeed;
		}
	}
	// 下
	if (m_pKeyboard->GetPress(DIK_S) == true)
	{
		if (m_pKeyboard->GetPress(DIK_A) == true)
		{
			m_rot.y = (D3DX_PI * 3) / 4;
			m_pos.x += sinf(-m_rot.y) * fSpeed / 2;
			m_pos.y += cosf(-m_rot.y) * fSpeed / 2;
		}
		else if (m_pKeyboard->GetPress(DIK_D) == true)
		{
			m_rot.y = (D3DX_PI * 3) / 4;
			m_pos.x += sinf(m_rot.y) * fSpeed / 2;
			m_pos.y += cosf(m_rot.y) * fSpeed / 2;
		}
		else
		{
			m_rot.y = D3DX_PI;
			m_pos.x += sinf(m_rot.y) * fSpeed;
			m_pos.y += cosf(m_rot.y) * fSpeed;
		}
	}

	// 左
	if (m_pKeyboard->GetPress(DIK_A) == true)
	{
		m_rot.y = D3DX_PI / 2;
		m_pos.x += sinf(-m_rot.y) * fSpeed;
		m_pos.z += cosf(-m_rot.y) * fSpeed;
	}
	// 右
	if (m_pKeyboard->GetPress(DIK_D) == true)
	{
		m_rot.y = D3DX_PI / 2;
		m_pos.x += sinf(m_rot.y) * fSpeed;
		m_pos.z += cosf(m_rot.y) * fSpeed;
	}

	//=========================================================================
	// 移動制限
	//=========================================================================
	// 右
	if (m_pos.x >= WIDTH_MOVE_LIMIT - m_size.x / 2.0f)
	{
		m_pos.x = WIDTH_MOVE_LIMIT - m_size.x / 2.0f;
		m_move.x *= -1;
	}
	// 左
	else if (m_pos.x <= -WIDTH_MOVE_LIMIT + m_size.x)
	{
		m_pos.x = -WIDTH_MOVE_LIMIT + m_size.x;
		m_move.x *= -1;
	}
	// 上
	if (m_pos.y >= UP_MOVE_LIMIT - m_size.y / 2.0f)
	{
		m_pos.y = UP_MOVE_LIMIT - m_size.y / 2.0f;
		m_move.y *= -1;
	}
	// 下
	else if (m_pos.y <= DOWN_MOVE_LIMIT + m_size.y / 2.0f)
	{
		m_pos.y = DOWN_MOVE_LIMIT + m_size.y / 2.0f;
		m_move.y *= -1;
	}

}
