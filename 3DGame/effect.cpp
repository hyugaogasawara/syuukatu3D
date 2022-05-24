//=============================================================================
//
// �G�t�F�N�g�N���X [effect.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "effect.h"
//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CEffect::CEffect(int nPriority) : CBillboard(nPriority)
{
	// �����o�ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �傫��
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CEffect::Init(void)
{
	// �I�u�W�F�N�g�̎�ސݒ�
	SetObjType(OBJTYPE_BULLET);

	CBillboard::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEffect::Uninit(void)
{
	CBillboard::Uninit();

	// �I�u�W�F�N�g���J��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEffect::Update(void)
{
	// �ʒu���擾
	D3DXVECTOR3 pos = CBillboard::GetPosition();

	// �ړ��ʍX�V
	pos += m_move;

	// ��������
	m_nLife--;

	// �J���[
	m_color.r += m_Subcolor.r;
	m_color.g += m_Subcolor.g;
	m_color.b += m_Subcolor.b;
	m_color.a += m_Subcolor.a;

	// �ʒu��ݒ�
	CBillboard::SetPosition(pos);
	CBillboard::SetColValue(m_color);
	CBillboard::Update();

	// 0�ȉ��ō폜
	if (m_nLife <= 0)
	{
		m_bUninit = true;
	}


	// �j��
	if (m_bUninit == true)
	{
		Uninit();
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void CEffect::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �J�����O��L���ɂ���
	if (m_bCalling == true)
	{
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	}

	// �p�����̕`�揈��
	CBillboard::Draw();

	// �J�����O�𖳌��ɂ���
	if (m_bCalling == true)
	{
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	}

	// ���u�����f�B���O��ʏ퍇���ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//=============================================================================
// �G�t�F�N�g�̐���
//=============================================================================
CEffect *CEffect::Create(float fPosX, float fPosY, float fPosZ, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLORVALUE col, D3DCOLORVALUE subcol, int nLife, int nType)
{
	CEffect *pEffect;
	pEffect = new CEffect;

	if (pEffect != NULL)
	{
		pEffect->m_move = move;			// �ړ���
		pEffect->m_nLife = nLife;		// ����
		pEffect->m_color = col;			// �J���[
		pEffect->m_Subcolor = subcol;	// �J���[����
		pEffect->SetSize(size);			// �傫��
		pEffect->SetPosition({ fPosX, fPosY, fPosZ });	// �ʒu
		pEffect->BindTexture(nType);	// �e�N�X�`���̎��
		pEffect->Init();				// ����������
	}

	return pEffect;
}
