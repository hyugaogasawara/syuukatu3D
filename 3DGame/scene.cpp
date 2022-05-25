//=============================================================================
//
// オブジェクトクラス [scene.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CScene *CScene::m_pTop[PRIORITY_MAX] = {};	// 先頭オブジェクト
CScene *CScene::m_pCur[PRIORITY_MAX] = {};	// 現在(最後尾)のオブジェクト

//=============================================================================
// コンストラクタ
//=============================================================================
CScene::CScene(int nPriority)
{
	// 先頭と最後尾のオブジェクトがない場合
	if (m_pTop[nPriority] == NULL && m_pCur[nPriority] == NULL)
	{
		m_pTop[nPriority] = this;			// このオブジェクトを先頭且つ
		m_pCur[nPriority] = this;			// 最後尾のオブジェクト
		m_pPrev = NULL;
		m_pNext = NULL;
	}
	else
	{
		m_pPrev = m_pCur[nPriority];		// "このオブジェクトの前は"最後尾のオブジェクト
		m_pCur[nPriority]->m_pNext = this;	// 次のオブジェクトは"このオブジェクト"
		m_pCur[nPriority] = this;			// 現在(最後尾)のオブジェクトは"このオブジェクト"
		m_pNext = NULL;						// 現在(最後尾)のオブジェクトには次のオブジェクトがないのでNULLにする
	}

	m_nPriority = nPriority;	// 描画の優先順位を設定
	m_bDeath = false;			// 死亡フラグを立てない
	m_objType = OBJTYPE::OBJTYPE_NONE;	// オブジェクトの種類を初期化

}
//=============================================================================
// デストラクタ
//=============================================================================
CScene::~CScene()
{
#if 0
	if (m_pTop[m_nPriority] != this && m_pCur[m_nPriority] != this)
	{// このオブジェクトが先頭でも現在(最後尾)のオブジェクトでもない場合
		m_pNext->m_pPrev = m_pNext;
		m_pPrev->m_pNext = m_pPrev;
	}
	if (m_pTop[m_nPriority] == this)
	{//	このオブジェクトが先頭だった場合、次のオブジェクトを先頭にする
		m_pTop[m_nPriority] = m_pNext;

		if (m_pNext != NULL)
		{// 次のオブジェクトが存在する場合、前のオブジェクト情報をNULLにする
			m_pNext->m_pPrev = NULL;
		}
	}
	if (m_pCur[m_nPriority] == this)
	{//	このオブジェクトが現在(最後尾)のオブジェクトだった場合、前のオブジェクトを最後尾にする
		m_pCur[m_nPriority] = m_pPrev;

		if (m_pPrev != NULL)
		{// 前のオブジェクトが存在する場合、次のオブジェクト情報をNULLにする
			m_pPrev->m_pNext = NULL;
		}
	}
#else
	if (m_pTop[m_nPriority] == this && m_pCur[m_nPriority] == this)
	{
		m_pTop[m_nPriority] = NULL;
		m_pCur[m_nPriority] = NULL;
		m_pNext = NULL;
		m_pPrev = NULL;
	}
	else if (m_pTop[m_nPriority] == this)
	{
		m_pNext->m_pPrev = NULL;
		m_pTop[m_nPriority] = m_pNext;
	}
	else if (m_pCur[m_nPriority] == this)
	{
		m_pPrev->m_pNext = NULL;
		m_pCur[m_nPriority] = m_pPrev;
	}
	else
	{
		m_pPrev->m_pNext = m_pNext;
		m_pNext->m_pPrev = m_pPrev;
	}
#endif

}
//=============================================================================
// 全てのオブジェクトを開放
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		if (nCntPriority != PRIORITY_FADE)
		{
			// 先頭オブジェクトのポインタを代入
			CScene *pScene = m_pTop[nCntPriority];

			while (pScene != NULL)
			{// 現在のオブジェクトのポインタを保存する
				CScene *pSceneNext = pScene->m_pNext;

				pScene->Uninit();
				delete pScene;
				pScene = NULL;
				// オブジェクト情報を更新
				pScene = pSceneNext;
			}
		}
	}
}
//=============================================================================
// 全てのオブジェクトを更新
//=============================================================================
void CScene::UpdateAll(void)
{
	CScene *pScene = NULL;		// 現在のオブジェクト情報を保存
	CScene *pSceneNext = NULL;	// 次のオブジェクト情報を保存

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{// 先頭オブジェクトのポインタを代入
		pScene = m_pTop[nCntPriority];

		while (pScene != NULL)
		{// 現在のオブジェクトのポインタを保存する
			pSceneNext = pScene->m_pNext;

			// 現在のオブジェクトを更新
			pScene->Update();

			// オブジェクト情報を更新
			pScene = pSceneNext;
		}
	}

	// 現在のオブジェクト情報を初期化
	pSceneNext = NULL;

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{// 先頭オブジェクトのポインタを代入
		pScene = m_pTop[nCntPriority];

		while (pScene != NULL)
		{
			pSceneNext = pScene->m_pNext;

			if (pScene->m_bDeath == true)
			{// 死亡フラグが立っていたらオブジェクトを破棄
				delete pScene;
				pScene = NULL;
			}
			pScene = pSceneNext;
		}
	}
}
//=============================================================================
// 全てのオブジェクトを描画
//=============================================================================
void CScene::DrawAll(void)
{	
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		// 先頭オブジェクトのポインタを代入
		CScene *pScene = m_pTop[nCntPriority];

		while (pScene != NULL)
		{
			// 現在のオブジェクトのポインタを保存する
			CScene *pSceneNext = pScene->m_pNext;

			// 現在のオブジェクトを描画
			pScene->Draw();

			// オブジェクト情報を更新
			pScene = pSceneNext;
		}
	}
}