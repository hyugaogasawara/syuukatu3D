//=============================================================================
//
// �Q�[����� [game.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "game.h"
#include "keyboard.h"
#include "fade.h"
#include "meshfield.h"
#include "meshwall.h"
#include "meshcylinder.h"
#include "meshsphere.h"
#include "player.h"
#include "bullet.h"
#include "effect.h"
#include "modelsingle.h"
#include "sight.h"
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CPlayer *CGame::m_pPlayer = nullptr;		// �v���C���[
CMeshField *CGame::m_pMeshField = nullptr;	// ���b�V���t�B�[���h
CMeshSphere *CGame::m_pMeshSphere = nullptr;// ���b�V���X�t�B�A
CModelSingle *CGame::m_pModelSingle = nullptr;	// ���f��
CSight *CGame::m_pSight = nullptr;				// �Ə�

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CGame::CGame(int nPriority) : CScene(nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGame::Init(void)
{
	// ��
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 500.0f), 2, 2, 0);

	// ��
	//CMeshWall::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), 5, 5, 0);

	// �~��
	//CMeshCylinder::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 50.0f, 100.0f), 1, 16, 0, 0.001f);

	// ��/����
	m_pMeshSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1000.0f, 12, 3, 2);

	// �v���C���[
	//m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	// ���f��
	m_pModelSingle = CModelSingle::Create(D3DXVECTOR3(0.0f, 100.0f, 30.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), 0);

	// �Ə�
	m_pSight = CSight::Create(D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 4);

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Uninit();
		m_pMeshField = nullptr;
	}

	// �I�u�W�F�N�g�̊J��
	Release();
}
//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	// �t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	// �G�t�F�N�g
	//if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true)
	//{
	//	CEffect::Create(50.0f, 50.0f, 50.0f, D3DXVECTOR3(5.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(255, 255, 255, 255), D3DXCOLOR(0, 0, 0, 0), 120, 3);
	//}

	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		if (CManager::GetInputKeyboard()->GetTrigger(DIK_SPACE) == true)
		{
			pFade->SetFade(CManager::MODE_TITLE);
		}
	}

}
//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{
}
//=============================================================================
// �Q�[����ʂ̐���
//=============================================================================
CGame *CGame::Create(void)
{
	CGame *pGame;
	pGame = new CGame;

	if (pGame != NULL)
	{
		pGame->Init();
	}

	return pGame;
}