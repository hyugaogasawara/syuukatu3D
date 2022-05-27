//=============================================================================
//
// �}�l�[�W�� [manager.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//*****************************************************************************
//�w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"
#include "keyboard.h"
#include "mouse.h"
//#include "xinput_pad.h"
//#include "sound.h"
//#include "loadData.h"
//
#include "title.h"
//#include "menu.h"
//#include "tutorial.h"
#include "select.h"
#include "game.h"
//#include "result.h"
#include "fade.h"

#include "light.h"
#include "camera.h"
#include "texture.h"
#include "Xload.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_FILE "data/LOADFILE/texture.txt"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CManager		*CManager::m_pInstance = NULL;
CRenderer		*CManager::m_pRenderer = NULL;
CInputKeyboard	*CManager::m_pKeyboard = NULL;
CMouse			*CManager::m_pMouse = NULL;
CXinputPad		*CManager::m_pXinputPad = NULL;
CSound			*CManager::m_pSound = NULL;

CTitle			*CManager::m_pTitle = NULL;
CMenu			*CManager::m_pMenu = NULL;
CTutorial		*CManager::m_pTutorial = NULL;
CSelect			*CManager::m_pSelect = NULL;
CGame			*CManager::m_pGame = NULL;
CResult			*CManager::m_pResult = NULL;
CRanking		*CManager::m_pRanking = NULL;

CFade			*CManager::m_pFade = NULL;
CTexture		*CManager::m_pTexture = NULL;
CModel			*CManager::m_pModel = NULL;
CXload			*CManager::m_pXload = NULL;
CLoadData		*CManager::m_pLoadData = NULL;
CCamera			*CManager::m_pCamera = NULL;
CLight			*CManager::m_apLight[MAX_LIGHT] = {};
CManager::MODE	CManager::m_mode = MODE_GAME;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CManager::CManager()
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �����_���[�̐�
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;

		// �����_���[����������
		if (m_pRenderer != NULL)
		{
			m_pRenderer->Init(hWnd, bWindow);
		}
	}
	// �L�[�{�[�h����
	if (m_pKeyboard == NULL)
	{
		m_pKeyboard = new CInputKeyboard;

		// �L�[�{�[�h����������
		if (m_pKeyboard != NULL)
		{
			m_pKeyboard->Init(hInstance, hWnd);
		}
	}
	// �}�E�X����
	if (m_pMouse == NULL)
	{
		m_pMouse = new CMouse;

		// �}�E�X����������
		if (m_pMouse != NULL)
		{
			m_pMouse->Init(hInstance, hWnd);
		}
	}
#if 0 
	// �Q�[���p�b�h����
	if (m_pXinputPad == NULL)
	{
		m_pXinputPad = new CXinputPad;

		// �Q�[���p�b�h����������
		if (m_pXinputPad != NULL)
		{
			m_pXinputPad->Init(hInstance, hWnd);
		}
	}
	// �T�E���h����
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;

		if (m_pSound != NULL)
		{
			// �T�E���h����������
			m_pSound->Init(hWnd);
		}
	}
	// �ǂݍ��݃f�[�^�N���X����
	if (m_pLoadData == NULL)
	{
		m_pLoadData = new CLoadData;

		if (m_pLoadData != NULL)
		{
			// �e�N�X�`������������
			m_pLoadData->Init();
		}
	}
#endif	// �Q�[���p�b�h,�T�E���h,�ǂݍ��݃N���X
	// �e�N�X�`������
	if (m_pTexture == NULL)
	{
		m_pTexture = new CTexture;

		if (m_pTexture != NULL)
		{
			// �e�N�X�`������������
			m_pTexture->Init();
		}
	}
	if (m_pXload == NULL)
	{
		m_pXload = new CXload;

		if (m_pXload != NULL)
		{
			// �e�N�X�`������������
			m_pXload->Init();
		}
	}

	// �t�F�[�h�̐���
	m_pFade = CFade::Create(m_mode);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	// �S�ẴI�u�W�F�N�g�N���X��j��
	CScene::ReleaseAll();

	// �L�[�{�[�h���j��
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Uninit();

		// �L�[�{�[�h�̊J��
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}
	// �}�E�X���j��
	if (m_pMouse != NULL)
	{
		m_pMouse->Uninit();

		// �}�E�X�̊J��
		delete m_pMouse;
		m_pMouse = NULL;
	}
#if 0
	// Xinput�Q�[���p�b�h���j��
	if (m_pXinputPad != NULL)
	{
		m_pXinputPad->Uninit();

		// Xinput�Q�[���p�b�h�̊J��
		delete m_pXinputPad;
		m_pXinputPad = NULL;
	}
	// �T�E���h���j��
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();

		// �T�E���h�̊J��
		delete m_pSound;
		m_pSound = NULL;
	}
#endif	// �Q�[���p�b�h,�T�E���h�N���X

	// �J�������j��
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	// ���C�g�̔j��
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		if (m_apLight[nCntLight] != NULL)
		{
			m_apLight[nCntLight]->Uninit();
			delete m_apLight[nCntLight];
			m_apLight[nCntLight] = NULL;
		}
	}
	// �e�N�X�`�����j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Uninit();

		// �e�N�X�`���̊J��
		delete m_pTexture;
		m_pTexture = NULL;
	}
	// ���f�����j��
	if (m_pXload != NULL)
	{
		m_pXload->Uninit();

		// �e�N�X�`���̊J��
		delete m_pXload;
		m_pXload = NULL;
	}

	// �����_���[���j��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();

		// �����_���[�̊J��
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	// �L�[�{�[�h�̍X�V����
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Update();
	}
	// �}�E�X�̍X�V����
	if (m_pMouse != NULL)
	{
		m_pMouse->Update();
	}
	// �Q�[���p�b�h�̍X�V����
#if 0
	if (m_pXinputPad != NULL)
	{
		m_pXinputPad->Update();
	}
#endif	// �Q�[���p�b�h

	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}
	// �����_���[�̍X�V����
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	// �����_���[�̕`�揈��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();	

		// �J�����̐ݒ�
		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			if (m_pCamera)	// null�`�F�b�N
			{
				m_pCamera->SetCamera();
			}
		}


	}

}
//=============================================================================
// ���[�h�̐ݒ�
//=============================================================================
void CManager::SetMode(CManager::MODE mode)
{
	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;
	case MODE_MENU:
		//if (m_pMenu != NULL)
		//{
		//	m_pMenu->Uninit();
		//	m_pMenu = NULL;
		//}
		break;
	case MODE_TUTORIAL:
		//if (m_pTutorial != NULL)
		//{
		//	m_pTutorial->Uninit();
		//	m_pTutorial = NULL;
		//}
		break;
	case MODE_SELECT:
		if (m_pSelect != NULL)
		{
			m_pSelect->Uninit();
			m_pSelect = NULL;
		}
		break;
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			//�J�����̔j��
			if (m_pCamera != NULL)
			{
				//�I������
				m_pCamera->Uninit();

				//�������̊J��
				delete m_pCamera;
				m_pCamera = NULL;
			}

			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;
	case MODE_RESULT:
		//if (m_pResult != NULL)
		//{
		//	m_pResult->Uninit();
		//	delete m_pResult;
		//	m_pResult = NULL;
		//}
		break;
	default:
		break;
	}

	// �S�ẴI�u�W�F�N�g�N���X��j��
	CScene::ReleaseAll();

	switch (mode)
	{
	case MODE_TITLE:
		m_pTitle = CTitle::Create();
		break;
	case MODE_MENU:
		//m_pMenu = CMenu::Create();
		break;
	case MODE_TUTORIAL:
		//m_pTutorial = CTutorial::Create();
		break;
	case MODE_SELECT:
		m_pSelect = CSelect::Create();
		break;
	case MODE_GAME:
		// �J�����̐���
		if (!m_pCamera)
		{
			m_pCamera = CCamera::Create();
		}
		// ���C�e�B���O�̐���
		m_apLight[0] = CLight::Create(D3DXVECTOR3(0.2f, -0.8f, 0.4f), D3DXVECTOR3(400.0f, 800.0f, -400.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
		m_apLight[1] = CLight::Create(D3DXVECTOR3(-0.2f, 0.8f, -0.4f), D3DXVECTOR3(-100.0f, 0.0f, 100.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1);
		m_apLight[2] = CLight::Create(D3DXVECTOR3(0.4f, -0.1f, 0.4f), D3DXVECTOR3(100.0f, 0.0f, -200.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2);

		if (!m_pGame)
		{
			m_pGame = CGame::Create();
		}
		break;
	case MODE_RESULT:
		//m_pResult = CResult::Create();
		break;
	default:
		break;
	}

	m_mode = mode;
}