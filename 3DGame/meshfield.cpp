//=============================================================================
//
// ���b�V���t�B�[���h�N���X�@�F�@���� [meshfield.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "meshfield.h"
#include "keyboard.h"
#include "game.h"
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CMeshField::CMeshField(int nPriority) : CScene3D(nPriority)
{
	// �����o�ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshField::~CMeshField()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshField::Init(void)
{
	SetObjType(OBJTYPE_FIELD);

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	CScene3D::BindTexture(m_nType);	// �e�N�X�`���̊��蓖��
	int nNumVtx = GetNumVtx();		// ���_�����擾
	int nNumIdx = GetNumIdx();		// �C���f�b�N�X�����擾

	LPDIRECT3DVERTEXBUFFER9	*pVtxBuff = GetVtxBuff();	// ���_�o�b�t�@�̃|�C���^��Scene3D����Q�Ƃ��Ď擾
	
	// ���_�o�b�t�@�̐���					  
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * nNumVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&(*pVtxBuff),
		NULL);

	VERTEX_3D *pVtx; // ���_�o�b�t�@�ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	(*pVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);

	// ���_��
	int nCntVtx = 0;

	// ���s�̕�����
	for (int nDepth = 0; nDepth < m_nDepth + 1; nDepth++)
	{	// ���̕����� 
		for (int nWidth = 0; nWidth < m_nWidth + 1; nWidth++, nCntVtx++)
		{
			// �ʒu�̐ݒ�				   (�傫�� / 2.0f) + (������ * (�傫�� / �ݒ肵��������))
			pVtx[nCntVtx].pos = D3DXVECTOR3((-m_size.x / 2.0f) + (nWidth * (m_size.x / m_nWidth)),
				m_pos.y,
				(m_size.z / 2.0f) - (nDepth * (m_size.z / m_nDepth)));

			// �@���x�N�g���̐ݒ�
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[nCntVtx].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// �e�N�X�`�����W	  ���̕����� * 1.0f, ���s�̕����� * 1.0f
			pVtx[nCntVtx].tex = D3DXVECTOR2(nWidth * 1.0f, nDepth * 1.0f);
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	(*pVtxBuff)->Unlock();

	LPDIRECT3DINDEXBUFFER9	*pIdxBuff = GetIdxBuff();	// �C���f�b�N�X�ւ̃|�C���^��Scene3D����Q�Ƃ��Ď擾

	// �C���f�b�N�X�o�b�t�@�̐���			 
	pDevice->CreateIndexBuffer(sizeof(WORD) * nNumIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&(*pIdxBuff),
		NULL);

	WORD *pIdx;		// �C���f�b�N�X���ւ̃|�C���^

	// �C���f�b�N�X�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	(*pIdxBuff)->Lock(0, 0, (void**)&pIdx, 0);

	// �k�ރ|���S���̔ԍ��f�[�^��ݒ�
	for (int nDepth = 0; nDepth < m_nDepth + 1; nDepth++)
	{
		for (int nWidth = 0; nWidth < m_nWidth + 1; nWidth++)
		{
			// �d�����Ȃ����_���̃C���f�b�N�X��ݒ�
			pIdx[(m_nWidth * 2 + 4) * nDepth + 0 + (nWidth * 2)] = (nWidth + (m_nWidth + 1) + (m_nWidth + 1) * nDepth);
			pIdx[(m_nWidth * 2 + 4) * nDepth + 1 + (nWidth * 2)] = (nWidth + 0 + (m_nWidth + 1) * nDepth);
		}
	}
	// �d�����钸�_���̃C���f�b�N�X��ݒ�
	for (int nDup = 0; nDup < m_nDepth - 1; nDup++)
	{
		pIdx[(m_nWidth * 2 + 2) + 0 + nDup * (m_nWidth * 2 + 4)] = (m_nWidth + (m_nWidth + 1) * nDup);
		pIdx[(m_nWidth * 2 + 2) + 1 + nDup * (m_nWidth * 2 + 4)] = ((m_nWidth * 2 + 2) + (m_nWidth + 1) * nDup);
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	(*pIdxBuff)->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeshField::Uninit(void)
{
	CScene3D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMeshField::Update(void)
{
	CScene3D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshField::Draw(void)
{
	CScene3D::Draw();
}
//=============================================================================
// ��������
//=============================================================================
CMeshField *CMeshField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nWidth, int nDepth, int nType)
{
	CMeshField *pMeshField;
	pMeshField = new CMeshField;

	if (pMeshField != NULL)
	{
		pMeshField->m_nType = nType;	// �e�N�X�`���̎�ނ�ݒ�
		pMeshField->SetPosition(pos);	// �ʒu��ݒ�
		pMeshField->m_size = size;		// ���̑傫��
		pMeshField->m_nWidth = nWidth;	// ���̕�����
		pMeshField->m_nDepth = nDepth;	// ���s�̕�����
		pMeshField->SetNumVtx((nWidth + 1) * (nDepth + 1));	// ���_��
		pMeshField->SetNumIdx((nWidth + 1) * (nDepth + 1) + ((nWidth + 3) * (nDepth - 1)));	// �C���f�b�N�X���F(���_��) + (���̕����� + 3) * (���s�̕����� - 1)
		pMeshField->SetNumPrimitive((nWidth + 1) * (nDepth + 1) + ((nWidth + 3) * (nDepth - 1)));
		pMeshField->Init();				// ����������
	}

	return pMeshField;
}
//=============================================================================
// �����蔻��
//=============================================================================
bool CMeshField::Collision(CMeshField *pMeshField, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float& BackPos)
{
	if (pMeshField != NULL)
	{
		D3DXVECTOR3 pos = pMeshField->GetPosition();
		D3DXVECTOR3 size = pMeshField->GetSize();

		if (pPos->y <= pos.y && pPosOld->y >= pos.y)
		{
			if (pPos->x >= pos.x - m_size.x + 10.0f && pPos->z <= pos.z + m_size.z + 10.0f &&
				pPos->x <= pos.x + m_size.x + 10.0f && pPos->z >= pos.z - m_size.z + 10.0f)
			{
				pPos->y = pos.y;
				BackPos = pos.y;
				return true;
			}
		}
	}
	return false;
}
