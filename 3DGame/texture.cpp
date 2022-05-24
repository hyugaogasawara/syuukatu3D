//=============================================================================
//
// �e�N�X�`���N���X [texture.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "texture.h"
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::m_apTexture[MAX_TEXTURE] = {};	// �e�N�X�`���ւ̃|�C���^
int CTexture::m_nType = 0;									// �e�N�X�`���̎�ސ�

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{
	// �����o�ϐ��̃N���A
	m_nType = 0;			// ��ސ�
	m_nNumTexture = 0;		// ��ނ̑���
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CTexture::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �t�@�C�����J��
	FILE *pFile = fopen(FILENAME_TEXTURE, "r");

	char aFile[256];	// �t�@�C���̕�����ۑ�

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "NUM_TEXTURE") == 0)
			{
				// �e�N�X�`����
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nNumTexture);
			}
			if (strcmp(&aFile[0], "TEXTURE_FILENAME") == 0)
			{
				// �e�N�X�`���̃p�X
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);

				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice, &aFile[0], &m_apTexture[m_nType]);
				m_nType++;
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0)
			{
				// �I��
				break;
			}
		}
		fclose(pFile);
	}
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CTexture::Uninit(void)
{
	// �e�N�X�`���̎�ސ��j��
	for (int nCntTex = 0; nCntTex < m_nType; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}
