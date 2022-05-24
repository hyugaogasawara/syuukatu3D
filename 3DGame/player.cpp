//=============================================================================
//
// �v���C���[�N���X [player.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "player.h"
#include "keyboard.h"
#include "loadData.h"
#include "model.h"
#include "camera.h"
#include "modelsingle.h"
#include "game.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define FILENAME_PLAYER "data/LOADFILE/model.txt"
#define SPEED 2.0f
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene(nPriority)
{
	// �����o�ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 1�t���[���O�̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �傫��
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
	m_pKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h���擾

	// ���f������
	CLoadData::LoadModel(FILENAME_PLAYER);		// ���f���f�[�^�̓ǂݍ���
	m_nNumModel = CLoadData::GetNumModel();		// �p�[�c���擾

	// �p�[�c�̐������f�������擾
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		m_pModel[nCntModel] = CLoadData::GetModel(nCntModel);	// �p�[�c������ǂݍ��񂾃f�[�^����擾
	}

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	// �I�u�W�F�N�g�̎�ސݒ�
	SetObjType(OBJTYPE_PLAYER);	

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	// ���f����j��
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel]->Uninit();
		}
	}

	// �I�u�W�F�N�g���J��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{

	// �ړ��ʍX�V
	m_pos += m_move;

	m_posOld = m_pos;

	// �ړ�����
	Move();

	// �ʒu��ݒ�
	CScene::SetPosOld(m_posOld);
	CScene::SetPosition(m_pos);
	CScene::SetSize(m_size);

	CModelSingle *pModelSingle = CGame::GetModelSingle();

	if (pModelSingle->Collision() == true)
	{

	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX	mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���f���̕`��
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel]->Draw();
		}
	}
}
//=============================================================================
// �v���C���[�̐���
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer *pPlayer = nullptr;
	if (pPlayer == nullptr)
	{
		pPlayer = new CPlayer;

		if (pPlayer != nullptr)
		{
			pPlayer->Init();		//����������
			pPlayer->m_pos = pos;	// �ʒu
			pPlayer->m_rot = rot;	// ����
		}
	}
	return pPlayer;
}
//=============================================================================
// �ړ�����
//=============================================================================
void CPlayer::Move(void)
{
	//-----------------------------------------------------
	//					�L�[�{�[�h����
	//-----------------------------------------------------
	//�@�J�����̏��擾
	CCamera *pCamera = CManager::GetCamera();

	// �J�����̌������擾
	float fCameraRotY = pCamera->GetRot().y;

	// �ړ����x
	float fSpeed = SPEED;

	if (m_pKeyboard->GetPress(DIK_W) == true)
	{
		if (m_pKeyboard->GetPress(DIK_A) == true)
		{
			m_rot.y = (D3DX_PI * 3) / 4;
			m_move.x = sinf(fCameraRotY + (D3DX_PI * 3) / 4) * -fSpeed;
			m_move.z = cosf(fCameraRotY + (D3DX_PI * 3) / 4) * -fSpeed;
		}
		else if (m_pKeyboard->GetPress(DIK_D) == true)
		{
			m_rot.y = -(D3DX_PI * 3) / 4;
			m_move.x = sinf(fCameraRotY - (D3DX_PI * 3) / 4) * -fSpeed;
			m_move.z = cosf(fCameraRotY - (D3DX_PI * 3) / 4) * -fSpeed;
		}
		else
		{
			m_rot.y = D3DX_PI;
			m_move.x = sinf(fCameraRotY) * fSpeed;
			m_move.z = cosf(fCameraRotY) * fSpeed;
		}
	}
	else if (m_pKeyboard->GetPress(DIK_S) == true)
	{
		if (m_pKeyboard->GetPress(DIK_A) == true)
		{
			m_rot.y = -(D3DX_PI * 7) / 4;
			m_move.x = sinf(fCameraRotY - (D3DX_PI * 7) / 4) * -fSpeed;
			m_move.z = cosf(fCameraRotY - (D3DX_PI * 7) / 4) * -fSpeed;
		}
		else if (m_pKeyboard->GetPress(DIK_D) == true)
		{
			m_rot.y = (D3DX_PI * 7) / 4;
			m_move.x = sinf(fCameraRotY + (D3DX_PI * 7) / 4) * -fSpeed;
			m_move.z = cosf(fCameraRotY + (D3DX_PI * 7) / 4) * -fSpeed;
		}
		else
		{
			m_rot.y = fCameraRotY;
			m_move.x = sinf(fCameraRotY) * fSpeed;
			m_move.z = cosf(fCameraRotY) * -fSpeed;
		}
	}
	else if (m_pKeyboard->GetPress(DIK_A) == true)
	{
		m_rot.y = D3DX_PI / 2;
		m_move.x = cosf(fCameraRotY) * -fSpeed;
		m_move.z = sinf(fCameraRotY) * -fSpeed;
	}
	else if (m_pKeyboard->GetPress(DIK_D) == true)
	{
		m_rot.y = -D3DX_PI / 2;
		m_move.x = cosf(fCameraRotY) * fSpeed;
		m_move.z = sinf(fCameraRotY) * fSpeed;
	}

	// ������ݒ�
	m_move.x *= 0.8f;
	m_move.z *= 0.8f;

	// �ړ��ʂ��ݒ肵���l�͈̔͂ɂȂ������~
	if (m_move.x <= 0.1f && m_move.x >= -0.1f)
	{
		m_move.x = 0.0f;
	}
	if (m_move.z <= 0.1f && m_move.z >= -0.1f)
	{
		m_move.z = 0.0f;
	}

	//-----------------------------------------------------
	//					�Q�[���p�b�h����
	//-----------------------------------------------------

}
