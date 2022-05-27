//=============================================================================
//
// テクスチャクラス [texture.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "texture.h"
//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::m_apTexture[MAX_TEXTURE] = {};	// テクスチャへのポインタ
int CTexture::m_nType = 0;									// テクスチャの種類数

//=============================================================================
// コンストラクタ
//=============================================================================
CTexture::CTexture()
{
	// メンバ変数のクリア
	m_nType = 0;			// 種類数
	m_nNumTexture = 0;		// 種類の総数
}
//=============================================================================
// デストラクタ
//=============================================================================
CTexture::~CTexture()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTexture::Init(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ファイルを開く
	FILE *pFile = fopen(FILENAME_TEXTURE, "r");

	char aFile[256];	// ファイルの文字列保存

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "NUM_TEXTURE") == 0)
			{
				// テクスチャ数
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nNumTexture);
			}
			if (strcmp(&aFile[0], "TEXTURE_FILENAME") == 0)
			{
				// テクスチャのパス
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);

				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice, &aFile[0], &m_apTexture[m_nType]);
				m_nType++;
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0)
			{
				// 終了
				break;
			}
		}
		fclose(pFile);
	}
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CTexture::Uninit(void)
{
	// テクスチャの種類数破棄
	for (int nCntTex = 0; nCntTex < m_nNumTexture; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}
