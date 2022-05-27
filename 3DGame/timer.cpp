//=============================================================================
//
// �^�C�}�[�N���X [timer.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "timer.h"
#include "polygon.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTimer::CTimer(int nPriority) : CScene(nPriority)
{
	// �����o�ϐ��̃N���A
	memset(&m_apNumber[0], NULL, sizeof(CPolygon));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nTimer = 0;
	m_nFrame = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTimer::~CTimer()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CTimer::Init(void)
{
	// �|���S���̐�������
	for (int nCntNum = 0; nCntNum < TIME_DIGIT; nCntNum++)
	{
		m_apNumber[nCntNum] = CPolygon::Create(D3DXVECTOR3(m_pos.x + 45.0f * nCntNum, m_pos.y, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), 6);
	}
	// �I�u�W�F�N�g�̎�ސݒ�
	SetObjType(OBJTYPE_UI);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTimer::Uninit(void)
{
	//FILE *pFile;
	//pFile = fopen("data/SAVEDATA/currentscore.txt", "w");
	//if (pFile != NULL)
	//{
	//	fprintf(pFile, "%d", m_nTimer);
	//}
	//else
	//{
	//	printf("�t�@�C�����J���܂���ł���\n");
	//}
	//fclose(pFile);


	// �������j��
	for (int nCntNum = 0; nCntNum < TIME_DIGIT; nCntNum++)
	{
		if (m_apNumber[nCntNum] != NULL)
		{
			// �|���S���̏I������
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
void CTimer::Update(void)
{
	// ���Z���ꂽ�X�R�A�̏�����]�Z�Ōv�Z����
	// �|���S��1�����Ɍv�Z���ꂽ�������i�[
	m_apNumber[0]->SetNumber(m_nTimer % (int)pow(10, 2) / (int)pow(10, 1));
	m_apNumber[1]->SetNumber(m_nTimer % (int)pow(10, 1));

	// �t���[�����J�E���g
	m_nFrame++;

	if (m_nFrame == 60)
	{
		m_nTimer--;		// �J�E���g�_�E��
		m_nFrame = 0;	// �t���[�������Z�b�g

		if (m_nTimer <= 0)
		{
			m_nTimer = 0;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTimer::Draw(void)
{
	// �|���S���̕`�揈��
	for (int nCntNum = 0; nCntNum < TIME_DIGIT; nCntNum++)
	{
		m_apNumber[nCntNum]->Draw();
	}
}
//=============================================================================
// �X�R�A�̐���
//=============================================================================
CTimer *CTimer::Create(D3DXVECTOR3 pos, int nTime)
{
	CTimer *pTimer = nullptr;
	if (pTimer == nullptr)
	{
		pTimer = new CTimer;

		if (pTimer != nullptr)
		{
			pTimer->m_pos = pos;		// �ʒu
			pTimer->m_nTimer = nTime;	// ����
			pTimer->Init();				// ����������
		}
	}
	return pTimer;
}
