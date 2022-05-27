//=============================================================================
//
// �X�R�A�N���X [score.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "score.h"
#include "polygon.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScore::CScore(int nPriority) : CScene(nPriority)
{
	// �����o�ϐ��̃N���A
	memset(&m_apNumber[0], NULL, sizeof(CPolygon));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nScore = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScore::~CScore()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CScore::Init(void)
{
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		m_apNumber[nCntNum] = CPolygon::Create(D3DXVECTOR3(m_pos.x + 45.0f * nCntNum, m_pos.y, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), 6);
	}
	SetObjType(OBJTYPE_UI);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScore::Uninit(void)
{
	//FILE *pFile;
	//pFile = fopen("data/SAVEDATA/currentscore.txt", "w");
	//if (pFile != NULL)
	//{
	//	fprintf(pFile, "%d", m_nScore);
	//}
	//else
	//{
	//	printf("�t�@�C�����J���܂���ł���\n");
	//}
	//fclose(pFile);


	// �������j��
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		if (m_apNumber[nCntNum] != NULL)
		{
			m_apNumber[nCntNum]->Uninit();
			delete m_apNumber[nCntNum];
			m_apNumber[nCntNum] = NULL;
		}
	}

	// �I�u�W�F�N�g�̊J��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScore::Update(void)
{
	// ���Z���ꂽ�X�R�A�̏�����]�Z�Ōv�Z����
	// �|���S��1�����Ɍv�Z���ꂽ�������i�[
	m_apNumber[0]->SetNumber(m_nScore / (int)pow(10, 6));
	m_apNumber[1]->SetNumber(m_nScore % (int)pow(10, 5) / (int)pow(10, 4));
	m_apNumber[2]->SetNumber(m_nScore % (int)pow(10, 4) / (int)pow(10, 3));
	m_apNumber[3]->SetNumber(m_nScore % (int)pow(10, 3) / (int)pow(10, 2));
	m_apNumber[4]->SetNumber(m_nScore % (int)pow(10, 2) / (int)pow(10, 1));
	m_apNumber[5]->SetNumber(m_nScore % (int)pow(10, 1));

}

//=============================================================================
// �`�揈��
//=============================================================================
void CScore::Draw(void)
{
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		m_apNumber[nCntNum]->Draw();
	}
}
//=============================================================================
// �X�R�A�̐���
//=============================================================================
CScore *CScore::Create(D3DXVECTOR3 pos)
{
	CScore *pScore = nullptr;
	if (pScore == nullptr)
	{
		pScore = new CScore;

		if (pScore != nullptr)
		{
			pScore->m_pos = pos;
			pScore->Init();
		}
	}
	return pScore;
}
