//=============================================================================
//
// ���b�V���V�����_�[�N���X�@�F�@�~�� [meshcylinder.h]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "meshcylinder.h"
#include "keyboard.h"
#include "game.h"
#include "texture.h"
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CMeshCylinder::CMeshCylinder(int nPriority) : CScene3D(nPriority)
{
	// �����o�ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nSide = 0;
	m_nVertical = 0;
	m_bOutSide = false;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshCylinder::~CMeshCylinder()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshCylinder::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CScene3D::BindTexture(m_nType);	//�e�N�X�`���̊��蓖��
	int nNumVtx = GetNumVtx();		// ���_�����擾
	int nNumIdx = GetNumIdx();		// �C���f�b�N�X�����擾
	float fAngle = atan2f(m_size.x, m_size.z);		// �p�x�����߂�
	float fAddValue = (D3DX_PI / (m_nSide / 2.0f));	// ���Z����p�x�̒l
	float fAddAngle = 0;			// ���Z����p�x

	LPDIRECT3DVERTEXBUFFER9	*pVtxBuff = GetVtxBuff();	// ���_�o�b�t�@�̃|�C���^��Scene3D����Q�Ƃ��Ď擾

	// ���_�o�b�t�@�̐���					  
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * nNumVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&(*pVtxBuff),
		NULL);

	VERTEX_3D *pVtx; //���_�o�b�t�@�ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	(*pVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);

	// ���_��
	int nCntVtx = 0;

	m_fRadius = 100.0f;

	// �c�̕�����
	for (int nVertical = 0; nVertical < m_nVertical + 1; nVertical++)
	{	// ���̕�����
		for (int nSide = 0; nSide < m_nSide + 1; nSide++, nCntVtx++)
		{
			// ���_���W�̐ݒ�
			pVtx[nCntVtx].pos = D3DXVECTOR3(
				(-m_size.x / 2) * cosf(fAngle - fAddAngle),
				m_size.y - (nVertical * (m_size.y / m_nVertical)),
				(-m_size.z / 2) * sinf(fAngle - fAddAngle));

			// ���_���d�����Ȃ��Ƃ��Ɋp�x�����Z����
			if (nSide != m_nSide)
			{
				if (m_bOutSide == false)
				{	// �V�����_�[�̓����ɕ`��
					fAddAngle += fAddValue;
				}
				else
				{	// �V�����_�[�̊O���ɕ`��
					fAddAngle -= fAddValue;
				}
			}

			// �@���x�N�g���̐ݒ�
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[nCntVtx].col = D3DCOLOR_RGBA(255, 255, 255, 255);;

			// �e�N�X�`�����W	  ���̕����� * 1.0f, �c�̕����� * 1.0f
			pVtx[nCntVtx].tex = D3DXVECTOR2(0.0f + (nSide * 1.0f), 0.0f + (nVertical * 1.0f));
		}
	}

	//���_�o�b�t�@���A�����b�N����
	(*pVtxBuff)->Unlock();

	LPDIRECT3DINDEXBUFFER9	*pIdxBuff = GetIdxBuff();	// �C���f�b�N�X�ւ̃|�C���^��Scene3D����Q�Ƃ��Ď擾

	//�C���f�b�N�X�o�b�t�@�̐���			 
	pDevice->CreateIndexBuffer(sizeof(WORD) * nNumIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&(*pIdxBuff),
		NULL);

	WORD *pIdx;		//�C���f�b�N�X���ւ̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	(*pIdxBuff)->Lock(0, 0, (void**)&pIdx, 0);

	// �k�ރ|���S���̔ԍ��f�[�^��ݒ�
	for (int nVertical = 0; nVertical < m_nVertical + 1; nVertical++)
	{
		for (int nSide = 0; nSide < m_nSide + 1; nSide++)
		{
			// �d�����Ȃ����_���̃C���f�b�N�X��ݒ�
			pIdx[(m_nSide * 2 + 4) * nVertical + 0 + (nSide * 2)] = (nSide + (m_nSide + 1) + (m_nSide + 1) * nVertical);
			pIdx[(m_nSide * 2 + 4) * nVertical + 1 + (nSide * 2)] = (nSide + 0             + (m_nSide + 1) * nVertical);
		}
	}
	// �d�����钸�_���̃C���f�b�N�X��ݒ�
	for (int nVertical = 0; nVertical < m_nVertical - 1; nVertical++)
	{
		pIdx[(m_nSide * 2 + 2) + 0 + nVertical * (m_nSide * 2 + 4)] = (m_nSide           + (m_nSide + 1) * nVertical);
		pIdx[(m_nSide * 2 + 2) + 1 + nVertical * (m_nSide * 2 + 4)] = ((m_nSide * 2 + 2) + (m_nSide + 1) * nVertical);
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	(*pIdxBuff)->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeshCylinder::Uninit(void)
{
	CScene3D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMeshCylinder::Update(void)
{
	CScene3D::Update();

	m_rot.y += m_fRotateSpeed;

	// ������3.14����-3.14�̒l�͈͓̔��Ɏ��߂�
	if (m_rot.y >= D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}

	SetRotation(m_rot);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshCylinder::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �J�����O��L���ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	CScene3D::Draw();

	// �J�����O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}
//=============================================================================
// ��������
//=============================================================================
CMeshCylinder *CMeshCylinder::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nVertical, int nSide, int nType, float fRotateSpeed)
{
	CMeshCylinder *pMeshCylinder;
	pMeshCylinder = new CMeshCylinder;

	if (pMeshCylinder != NULL)
	{
		pMeshCylinder->m_nType = nType;			// �e�N�X�`���̎�ނ�ݒ�
		pMeshCylinder->SetPosition(pos);		// �ʒu��ݒ�
		pMeshCylinder->m_rot = rot;				// ������ݒ�
		pMeshCylinder->m_size = size;			// �~���̑傫��
		pMeshCylinder->m_nVertical = nVertical;	// �c�̒��_��
		pMeshCylinder->m_nSide = nSide;			// ���̒��_��
		pMeshCylinder->SetNumVtx((nSide + 1) * (nVertical + 1));	// ���_��
		pMeshCylinder->SetRotateSpeed(fRotateSpeed);
		pMeshCylinder->SetNumIdx(((nSide * nVertical * 2) + (nVertical * 4)));	// �C���f�b�N�X���F(���̕����� * �c�̕����� * 2) + (�c�̕����� * 4)
		pMeshCylinder->SetNumPrimitive(((nSide * nVertical * 2) + (nVertical * 4)));
		pMeshCylinder->m_bOutSide = true;		// �O���ɕ`�悷�邩�ǂ���
		pMeshCylinder->Init();					// ����������
	}

	return pMeshCylinder;
}
