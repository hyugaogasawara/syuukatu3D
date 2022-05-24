//=============================================================================
//
// �ǂݍ��݃N���X�@[loadData.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "loadData.h"
#include "model.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CModel *CLoadData::m_pModel[32] = {};
int CLoadData::m_nNumModel = 0;
//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CLoadData::CLoadData()
{
	// �����o�ϐ��̃N���A
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLoadData::~CLoadData()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CLoadData::Init(void)
{
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CLoadData::Uninit(void)
{
}
//=============================================================================
// ���f���t�@�C���ǂݍ���
//=============================================================================
void CLoadData::LoadModel(const char *pPathName)
{
	FILE *pFile = fopen(pPathName, "r");	// �e�L�X�g�t�@�C���J��
	char aFile[512];	// ������ۑ�
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 rot;	// ����
	int nIndex = 0;		// �ԍ�
	int nParent = 0;	// �e�q�֌W
	int nCntModel = 0;	// ���f�����J�E���g
	bool bCharacter = false;	// �L�����N�^�[�ݒ�
	bool bParts = false;		// �p�[�c�ݒ�
	bool bMotion = false;		// ���[�V�����ݒ�
	bool bKeyParts = false;		// �p�[�c�L�[�ݒ�
	bool bKeyMotion = false;	// ���[�V�����L�[�ݒ�
	CModel *apModel[32];		// ���f���̃|�C���^

	if (pFile != NULL)
	{
		while (true)
		{	// �������ǂݍ���
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "NUM_MODEL") == 0)
			{// ���f����
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nNumModel);
			}
			if (strcmp(&aFile[0], "MODEL_FILENAME") == 0)
			{// �ǂݍ��񂾃p�X�Ń��f���𐶐�
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				apModel[nCntModel] = CModel::Create(&aFile[0]);
				nCntModel++;
			}
			if (strcmp(&aFile[0], "CHARACTERSET") == 0)
			{// �L�����N�^�[�ݒ�
				nCntModel = 0;
				bCharacter = true;
			}
			if (strcmp(&aFile[0], "END_CHARACTERSET") == 0)
			{// �L�����N�^�[�ݒ�I��
				bCharacter = false;
			}
			if (bCharacter == true)
			{
				if (strcmp(&aFile[0], "PARTSSET") == 0)
				{// �p�[�c�ݒ�
					bParts = true;
				}
				if (strcmp(&aFile[0], "END_PARTSSET") == 0)
				{// �p�[�c�ݒ�I��
					bParts = false;
					nCntModel++;
				}
				if (bParts == true)
				{
					if (strcmp(&aFile[0], "INDEX") == 0)
					{// �ǂݍ��񂾃��f���t�@�C������Ăяo�����f���̔ԍ���ݒ�
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nIndex);
						m_pModel[nCntModel] = apModel[nIndex];
					}
					if (strcmp(&aFile[0], "PARENT") == 0)
					{// �e�q�֌W�ݒ�
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nParent);

						// �e�q�֌W��-1�̏ꍇ�A�e���f����ݒ�
						if (nParent != -1)
						{
							m_pModel[nCntModel]->SetParent(m_pModel[nParent]);
						}
					}
					if (strcmp(&aFile[0], "POS") == 0)
					{// �ʒu
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
						m_pModel[nCntModel]->SetPosition(pos);
					}
					if (strcmp(&aFile[0], "ROT") == 0)
					{// ����
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
						m_pModel[nCntModel]->SetRotation(rot);
					}
				}// �p�[�c�ݒ�
			}// �L�����N�^�[�ݒ�

			if (strcmp(&aFile[0], "END_SCRIPT") == 0)
			{// �ǂݍ��ݏI��
				break;
			}
		}
		fclose(pFile);	// �t�@�C�������
	}
}

