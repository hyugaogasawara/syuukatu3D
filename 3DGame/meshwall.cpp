//=============================================================================
//
// ���b�V���E�H�[���N���X�@�F�@�� [meshwall.h]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "meshwall.h"
#include "keyboard.h"
#include "game.h"
#include "texture.h"
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CMeshWall::CMeshWall(int nPriority) : CScene3D(nPriority)
{
	// �����o�ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshWall::~CMeshWall()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshWall::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CScene3D::BindTexture(m_nType);		// �e�N�X�`���̊��蓖��
	int nNumVtx = GetNumVtx();	// ���_�����擾
	int nNumIdx = GetNumIdx();	// �C���f�b�N�X�����擾

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
	for (int nHeight = 0; nHeight < m_nHeight + 1; nHeight++)
	{	// ���̕����� 
		for (int nWidth = 0; nWidth < m_nWidth + 1; nWidth++, nCntVtx++)
		{
			// �ʒu�̐ݒ�
			pVtx[nCntVtx].pos = D3DXVECTOR3(
				(-m_size.x / 2.0f) + (nWidth * (m_size.x / m_nWidth)),
				(m_size.y / 2.0f) - (nHeight * (m_size.y / m_nHeight)) + m_pos.y,
				m_pos.z);

			// �@���x�N�g���̐ݒ�
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[nCntVtx].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// �e�N�X�`�����W	  ���̕����� * 1.0f, �����̕����� * 1.0f
			pVtx[nCntVtx].tex = D3DXVECTOR2(nWidth * 1.0f, nHeight * 1.0f);
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
	for (int nHeight = 0; nHeight < m_nHeight + 1; nHeight++)
	{
		for (int nWidth = 0; nWidth < m_nWidth + 1; nWidth++, nNumVtx++)
		{
			// �d�����Ȃ����_���̃C���f�b�N�X��ݒ�
			pIdx[(m_nWidth * 2 + 4) * nHeight + 0 + (nWidth * 2)] = (nWidth + (m_nWidth + 1) + (m_nWidth + 1) * nHeight);
			pIdx[(m_nWidth * 2 + 4) * nHeight + 1 + (nWidth * 2)] = (nWidth + 0 + (m_nWidth + 1) * nHeight);
		}
	}
	// �d�����钸�_���̃C���f�b�N�X��ݒ�
	for (int nDup = 0; nDup < m_nHeight - 1; nDup++)
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
void CMeshWall::Uninit(void)
{
	CScene3D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMeshWall::Update(void)
{
	CScene3D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshWall::Draw(void)
{
	CScene3D::Draw();
}
//=============================================================================
// �ǂ𐶐�
//=============================================================================
CMeshWall *CMeshWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nWidth, int nHeight, int nType)
{
	CMeshWall *pMeshWall;
	pMeshWall = new CMeshWall;

	if (pMeshWall != NULL)
	{
		pMeshWall->m_nType = nType;
		pMeshWall->SetPosition(pos);	// �ʒu��ݒ�
		pMeshWall->SetRotation(rot);	// ������ݒ�
		pMeshWall->m_size = size;		// �ǂ̑傫��
		pMeshWall->m_nWidth = nWidth;	// ��
		pMeshWall->m_nHeight = nHeight;	// ����
		pMeshWall->SetNumVtx((nWidth + 1) * (nHeight + 1));	// ���_��
		pMeshWall->SetNumIdx(((nWidth + 1) * 2) * nHeight + (nHeight - 1) * 2);			// �C���f�b�N�X���F((�� + 1) * 2) * ���� + (���� - 1) * 2
		pMeshWall->SetNumPrimitive(((nWidth + 1) * 2) * nHeight + (nHeight - 1) * 2);	// �v���~�e�B�u(�O�p�`�̖�)��
		pMeshWall->Init();				// ����������
	}

	return pMeshWall;
}
//=============================================================================
// �����蔻��
//=============================================================================
bool CMeshWall::Collision(CMeshWall *pMeshWall, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float& BackPos)
{
	if (pMeshWall != NULL)
	{
		D3DXVECTOR3 pos = pMeshWall->GetPosition();
		D3DXVECTOR3 size = pMeshWall->GetSize();

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
