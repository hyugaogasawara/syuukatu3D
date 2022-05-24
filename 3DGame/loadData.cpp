//=============================================================================
//
// 読み込みクラス　[loadData.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "loadData.h"
#include "model.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CModel *CLoadData::m_pModel[32] = {};
int CLoadData::m_nNumModel = 0;
//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CLoadData::CLoadData()
{
	// メンバ変数のクリア
}
//=============================================================================
// デストラクタ
//=============================================================================
CLoadData::~CLoadData()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLoadData::Init(void)
{
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CLoadData::Uninit(void)
{
}
//=============================================================================
// モデルファイル読み込み
//=============================================================================
void CLoadData::LoadModel(const char *pPathName)
{
	FILE *pFile = fopen(pPathName, "r");	// テキストファイル開放
	char aFile[512];	// 文字列保存
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 rot;	// 向き
	int nIndex = 0;		// 番号
	int nParent = 0;	// 親子関係
	int nCntModel = 0;	// モデル数カウント
	bool bCharacter = false;	// キャラクター設定
	bool bParts = false;		// パーツ設定
	bool bMotion = false;		// モーション設定
	bool bKeyParts = false;		// パーツキー設定
	bool bKeyMotion = false;	// モーションキー設定
	CModel *apModel[32];		// モデルのポインタ

	if (pFile != NULL)
	{
		while (true)
		{	// 文字列を読み込む
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "NUM_MODEL") == 0)
			{// モデル数
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nNumModel);
			}
			if (strcmp(&aFile[0], "MODEL_FILENAME") == 0)
			{// 読み込んだパスでモデルを生成
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				apModel[nCntModel] = CModel::Create(&aFile[0]);
				nCntModel++;
			}
			if (strcmp(&aFile[0], "CHARACTERSET") == 0)
			{// キャラクター設定
				nCntModel = 0;
				bCharacter = true;
			}
			if (strcmp(&aFile[0], "END_CHARACTERSET") == 0)
			{// キャラクター設定終了
				bCharacter = false;
			}
			if (bCharacter == true)
			{
				if (strcmp(&aFile[0], "PARTSSET") == 0)
				{// パーツ設定
					bParts = true;
				}
				if (strcmp(&aFile[0], "END_PARTSSET") == 0)
				{// パーツ設定終了
					bParts = false;
					nCntModel++;
				}
				if (bParts == true)
				{
					if (strcmp(&aFile[0], "INDEX") == 0)
					{// 読み込んだモデルファイルから呼び出すモデルの番号を設定
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nIndex);
						m_pModel[nCntModel] = apModel[nIndex];
					}
					if (strcmp(&aFile[0], "PARENT") == 0)
					{// 親子関係設定
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nParent);

						// 親子関係が-1の場合、親モデルを設定
						if (nParent != -1)
						{
							m_pModel[nCntModel]->SetParent(m_pModel[nParent]);
						}
					}
					if (strcmp(&aFile[0], "POS") == 0)
					{// 位置
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
						m_pModel[nCntModel]->SetPosition(pos);
					}
					if (strcmp(&aFile[0], "ROT") == 0)
					{// 向き
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
						m_pModel[nCntModel]->SetRotation(rot);
					}
				}// パーツ設定
			}// キャラクター設定

			if (strcmp(&aFile[0], "END_SCRIPT") == 0)
			{// 読み込み終了
				break;
			}
		}
		fclose(pFile);	// ファイルを閉じる
	}
}

