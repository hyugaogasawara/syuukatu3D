//=============================================================================
//
// �I�u�W�F�N�g�N���X [scene.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CScene *CScene::m_pTop[PRIORITY_MAX] = {};	// �擪�I�u�W�F�N�g
CScene *CScene::m_pCur[PRIORITY_MAX] = {};	// ����(�Ō��)�̃I�u�W�F�N�g

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	m_nPriority = nPriority;	// �`��̗D�揇�ʂ�ݒ�

	// �擪�ƍŌ���̃I�u�W�F�N�g���Ȃ��ꍇ
	if (m_pTop[m_nPriority] == NULL && m_pCur[m_nPriority] == NULL)
	{
		m_pTop[m_nPriority] = this;			// ���̃I�u�W�F�N�g��擪����
		m_pCur[m_nPriority] = this;			// �Ō���̃I�u�W�F�N�g
		m_pPrev = NULL;
		m_pNext = NULL;
	}
	else
	{
		m_pPrev = m_pCur[m_nPriority];		// "���̃I�u�W�F�N�g�̑O��"�Ō���̃I�u�W�F�N�g
		m_pCur[m_nPriority]->m_pNext = this;	// ���̃I�u�W�F�N�g��"���̃I�u�W�F�N�g"
		m_pCur[m_nPriority] = this;			// ����(�Ō��)�̃I�u�W�F�N�g��"���̃I�u�W�F�N�g"
		m_pNext = NULL;						// ����(�Ō��)�̃I�u�W�F�N�g�ɂ͎��̃I�u�W�F�N�g���Ȃ��̂�NULL�ɂ���
	}
	m_bDeath = false;			// ���S�t���O�𗧂ĂȂ�
	m_objType = OBJTYPE::OBJTYPE_NONE;	// �I�u�W�F�N�g�̎�ނ�������

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
	if (m_pTop[m_nPriority] != this && m_pCur[m_nPriority] != this)
	{// ���̃I�u�W�F�N�g���擪�ł�����(�Ō��)�̃I�u�W�F�N�g�ł��Ȃ��ꍇ
		m_pNext->m_pPrev = m_pNext;
		m_pPrev->m_pNext = m_pPrev;
	}
	if (m_pTop[m_nPriority] == this)
	{//	���̃I�u�W�F�N�g���擪�������ꍇ�A���̃I�u�W�F�N�g��擪�ɂ���
		m_pTop[m_nPriority] = m_pNext;

		if (m_pNext != NULL)
		{// ���̃I�u�W�F�N�g�����݂���ꍇ�A�O�̃I�u�W�F�N�g����NULL�ɂ���
			m_pNext->m_pPrev = NULL;
		}
	}
	if (m_pCur[m_nPriority] == this)
	{//	���̃I�u�W�F�N�g������(�Ō��)�̃I�u�W�F�N�g�������ꍇ�A�O�̃I�u�W�F�N�g���Ō���ɂ���
		m_pCur[m_nPriority] = m_pPrev;

		if (m_pPrev != NULL)
		{// �O�̃I�u�W�F�N�g�����݂���ꍇ�A���̃I�u�W�F�N�g����NULL�ɂ���
			m_pPrev->m_pNext = NULL;
		}
	}
}
//=============================================================================
// �S�ẴI�u�W�F�N�g���J��
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		if (nCntPriority != PRIORITY_FADE)
		{
			// �擪�I�u�W�F�N�g�̃|�C���^����
			CScene *pScene = m_pTop[nCntPriority];

			while (pScene != NULL)
			{// ���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�����
				CScene *pSceneNext = pScene->m_pNext;

				// ���݂̃I�u�W�F�N�g�̎��S�t���O�𗧂Ă�
				if (pScene->m_bDeath == true)
				{// ���S�t���O�������Ă�����I�u�W�F�N�g��j��
					pScene->Uninit();
					delete pScene;
					pScene = NULL;
				}
				// �I�u�W�F�N�g�����X�V
				pScene = pSceneNext;
			}
		}
	}
}
//=============================================================================
// �S�ẴI�u�W�F�N�g���X�V
//=============================================================================
void CScene::UpdateAll(void)
{
	CScene *pScene = NULL;		// ���݂̃I�u�W�F�N�g����ۑ�
	CScene *pSceneNext = NULL;	// ���̃I�u�W�F�N�g����ۑ�

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{// �擪�I�u�W�F�N�g�̃|�C���^����
		pScene = m_pTop[nCntPriority];

		while (pScene != NULL)
		{// ���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�����
			pSceneNext = pScene->m_pNext;

			// ���݂̃I�u�W�F�N�g���X�V
			pScene->Update();

			// �I�u�W�F�N�g�����X�V
			pScene = pSceneNext;
		}
	}

	// ���݂̃I�u�W�F�N�g����������
	pSceneNext = NULL;

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{// �擪�I�u�W�F�N�g�̃|�C���^����
		pScene = m_pTop[nCntPriority];

		while (pScene != NULL)
		{
			pSceneNext = pScene->m_pNext;

			if (pScene->m_bDeath == true)
			{// ���S�t���O�������Ă�����I�u�W�F�N�g��j��
				delete pScene;
				pScene = NULL;
			}
			pScene = pSceneNext;
		}
	}
}
//=============================================================================
// �S�ẴI�u�W�F�N�g��`��
//=============================================================================
void CScene::DrawAll(void)
{	
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		// �擪�I�u�W�F�N�g�̃|�C���^����
		CScene *pScene = m_pTop[nCntPriority];

		while (pScene != NULL)
		{
			// ���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�����
			CScene *pSceneNext = pScene->m_pNext;

			// ���݂̃I�u�W�F�N�g��`��
			pScene->Draw();

			// �I�u�W�F�N�g�����X�V
			pScene = pSceneNext;
		}
	}
}