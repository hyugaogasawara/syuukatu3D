//=============================================================================
//
// �Ə��N���X [sight.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "sight.h"
#include "keyboard.h"
#include "mouse.h"
#include "bullet.h"
#include "modelsingle.h"
#include "game.h"
#include "effect.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define WIDTH_MOVE_LIMIT	170	// �ړ�������
#define UP_MOVE_LIMIT		190	// ��ړ�����
#define DOWN_MOVE_LIMIT		70	// ���ړ�����
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CSight::CSight(int nPriority) : CBillboard(nPriority)
{
	// �����o�ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �傫��
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
	m_pKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h���擾
	m_pMouse = CManager::GetMouse();			// �}�E�X���擾
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSight::~CSight()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CSight::Init(void)
{
	// �I�u�W�F�N�g�̎�ސݒ�
	SetObjType(OBJTYPE_SIGHT);

	CBillboard::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSight::Uninit(void)
{
	CBillboard::Uninit();

	// �I�u�W�F�N�g���J��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CSight::Update(void)
{
	// �ʒu���擾
	m_pos = CBillboard::GetPosition();
	
	// �ړ��ʍX�V
	m_pos += m_move;

	// �j��
	if (m_bUninit == true)
	{
		Uninit();
	}

	// �ړ�����
	Move();

	if (m_pMouse->GetTrigger(CMouse::DIM_L) == true)
	{
		// �e�𐶐�
		//CEffect::Create(m_pos.x, m_pos.y, -20.0f, D3DXVECTOR3(3.5f, 3.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 5.0f), D3DXCOLOR(255, 255, 255, 255), D3DXCOLOR(0, 0, 0, 0), 120, 3);
		m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, -20.0f), D3DXVECTOR3(3.5f, 3.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 5.0f), 120, 1);

	}

	// �ʒu��ݒ�
	CBillboard::SetPosition(m_pos);
	CBillboard::Update();

}

//=============================================================================
// �`�揈��
//=============================================================================
void CSight::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Z�e�X�g
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// �p�����̕`�揈��
	CBillboard::Draw();

	// Z�e�X�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);


	// ���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//=============================================================================
// �Ə��̐���
//=============================================================================
CSight *CSight::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType)
{
	CSight *pSight = nullptr;
	if (pSight == nullptr)
	{
		pSight = new CSight;

		if (pSight != nullptr)
		{
			pSight->m_pos = pos;		// �ʒu
			pSight->SetSize(size);		// �傫��
			pSight->SetPosition(pos);	// �ʒu
			pSight->BindTexture(nType);	// �e�N�X�`���̎��
			pSight->Init();				// ����������
		}
	}
	return pSight;
}
//=============================================================================
// �ړ�����
//=============================================================================
void CSight::Move(void)
{
	float fSpeed = SPEED;
	
	// ��
	if (m_pKeyboard->GetPress(DIK_W) == true)
	{
		if (m_pKeyboard->GetPress(DIK_A) == true)
		{
			m_rot.y = (D3DX_PI * 7) / 4;
			m_pos.x += sinf(m_rot.y) * fSpeed / 2;
			m_pos.y += cosf(m_rot.y) * fSpeed / 2;
		}
		else if (m_pKeyboard->GetPress(DIK_D) == true)
		{
			m_rot.y = (D3DX_PI * 7) / 4;
			m_pos.x += sinf(-m_rot.y) * fSpeed / 2;
			m_pos.y += cosf(-m_rot.y) * fSpeed / 2;
		}
		else
		{
			m_rot.y = 0.0f;
			m_pos.x += sinf(m_rot.y) * fSpeed;
			m_pos.y += cosf(m_rot.y) * fSpeed;
		}
	}
	// ��
	if (m_pKeyboard->GetPress(DIK_S) == true)
	{
		if (m_pKeyboard->GetPress(DIK_A) == true)
		{
			m_rot.y = (D3DX_PI * 3) / 4;
			m_pos.x += sinf(-m_rot.y) * fSpeed / 2;
			m_pos.y += cosf(-m_rot.y) * fSpeed / 2;
		}
		else if (m_pKeyboard->GetPress(DIK_D) == true)
		{
			m_rot.y = (D3DX_PI * 3) / 4;
			m_pos.x += sinf(m_rot.y) * fSpeed / 2;
			m_pos.y += cosf(m_rot.y) * fSpeed / 2;
		}
		else
		{
			m_rot.y = D3DX_PI;
			m_pos.x += sinf(m_rot.y) * fSpeed;
			m_pos.y += cosf(m_rot.y) * fSpeed;
		}
	}

	// ��
	if (m_pKeyboard->GetPress(DIK_A) == true)
	{
		m_rot.y = D3DX_PI / 2;
		m_pos.x += sinf(-m_rot.y) * fSpeed;
		m_pos.z += cosf(-m_rot.y) * fSpeed;
	}
	// �E
	if (m_pKeyboard->GetPress(DIK_D) == true)
	{
		m_rot.y = D3DX_PI / 2;
		m_pos.x += sinf(m_rot.y) * fSpeed;
		m_pos.z += cosf(m_rot.y) * fSpeed;
	}

	//=========================================================================
	// �ړ�����
	//=========================================================================
	// �E
	if (m_pos.x >= WIDTH_MOVE_LIMIT - m_size.x / 2.0f)
	{
		m_pos.x = WIDTH_MOVE_LIMIT - m_size.x / 2.0f;
		m_move.x *= -1;
	}
	// ��
	else if (m_pos.x <= -WIDTH_MOVE_LIMIT + m_size.x)
	{
		m_pos.x = -WIDTH_MOVE_LIMIT + m_size.x;
		m_move.x *= -1;
	}
	// ��
	if (m_pos.y >= UP_MOVE_LIMIT - m_size.y / 2.0f)
	{
		m_pos.y = UP_MOVE_LIMIT - m_size.y / 2.0f;
		m_move.y *= -1;
	}
	// ��
	else if (m_pos.y <= DOWN_MOVE_LIMIT + m_size.y / 2.0f)
	{
		m_pos.y = DOWN_MOVE_LIMIT + m_size.y / 2.0f;
		m_move.y *= -1;
	}

}
