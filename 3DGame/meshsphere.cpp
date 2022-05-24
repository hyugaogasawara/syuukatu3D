//=============================================================================
//
// ���b�V���X�t�B�A�N���X�@�F�@�� [meshsphere.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "meshsphere.h"
#include "keyboard.h"
#include "game.h"
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMeshSphere::CMeshSphere(int nPriority) : CScene3D(nPriority)
{
	// �����o�ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nType = 0;
	m_nLine = 0;
	m_nVertical = 0;
	m_fRadius = 0.0f;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshSphere::~CMeshSphere()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshSphere::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(OBJTYPE_SPHERE);

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	CScene3D::BindTexture(m_nType);	// �e�N�X�`���̊��蓖��
	int nNumVtx = GetNumVtx();		// ���_�����擾
	int nNumIdx = GetNumIdx();		// �C���f�b�N�X�����擾

	// ���_�o�b�t�@�̃|�C���^��Scene3D����擾
	LPDIRECT3DVERTEXBUFFER9	*pVtxBuff = GetVtxBuff();

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

	// �c�̕�����
	for (int nVertical = 0; nVertical < m_nVertical + 1; nVertical++)
	{	// ���̕����� 
		for (int nLine = 0; nLine < m_nLine + 1; nLine++, nCntVtx++)
		{	// ���_���W�̊p�x���Z�o
			float fPhi = (D3DX_PI * 2) / m_nVertical * nVertical;
			float ftheta = (D3DX_PI * 2) / m_nVertical * nLine;

			// ���_���W�̐ݒ�
			pVtx[nCntVtx].pos = D3DXVECTOR3(
				m_fRadius * sinf(ftheta) * cosf(fPhi),
				m_fRadius * sinf(ftheta + D3DX_PI / 2),
				m_fRadius * sinf(ftheta) * sinf(fPhi));

			// �@���x�N�g���̐ݒ�
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[nCntVtx].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// �e�N�X�`�����W			�e�N�X�`���̕��� / ���̕�����, 1.0f / �c�̕�����
			pVtx[nCntVtx].tex = D3DXVECTOR2((0.2f / m_nLine * nLine), (1.0f / m_nVertical * nVertical));
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	(*pVtxBuff)->Unlock();

	// �C���f�b�N�X�ւ̃|�C���^��Scene3D����擾
	LPDIRECT3DINDEXBUFFER9	*pIdxBuff = GetIdxBuff();

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
	for (int nVertical = 0; nVertical < m_nVertical + 1; nVertical++)
	{
		for (int nLine = 0; nLine < m_nLine + 1; nLine++)
		{
			// �d�����Ȃ����_���̃C���f�b�N�X��ݒ�
			pIdx[(m_nLine * 2 + 4) * nVertical + 0 + (nLine * 2)] = (nLine + (m_nLine + 1) + (m_nLine + 1) * nVertical);
			pIdx[(m_nLine * 2 + 4) * nVertical + 1 + (nLine * 2)] = (nLine + 0 + (m_nLine + 1) * nVertical);
		}
	}
	// �d�����钸�_���̃C���f�b�N�X��ݒ�
	for (int nDup = 0; nDup < m_nVertical - 1; nDup++)
	{
		pIdx[(m_nLine * 2 + 2) + 0 + nDup * (m_nLine * 2 + 4)] = (m_nLine + (m_nLine + 1) * nDup);
		pIdx[(m_nLine * 2 + 2) + 1 + nDup * (m_nLine * 2 + 4)] = ((m_nLine * 2 + 2) + (m_nLine + 1) * nDup);
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	(*pIdxBuff)->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeshSphere::Uninit(void)
{
	// �p�����̏I������
	CScene3D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMeshSphere::Update(void)
{
	// ��]���x
	m_rot.y += 0.0001f;

	// �p�x����
	if (m_rot.y >= D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}

	// ������ݒ�
	CScene3D::SetRotation(m_rot);

}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshSphere::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �J�����O��L���ɂ���
	if (m_bCalling == true)
	{
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	}

	// �p�����̕`�揈��
	CScene3D::Draw();

	// �J�����O�𖳌��ɂ���
	if (m_bCalling == true)
	{
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	}

	// ���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//=============================================================================
// ��������
//=============================================================================
CMeshSphere *CMeshSphere::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, int nVertical, int nLine, int nType)
{
	CMeshSphere *pMeshSphere;
	pMeshSphere = new CMeshSphere;

	if (pMeshSphere != NULL)
	{
		pMeshSphere->m_bCalling = false;		// �J�����O�̏��
		pMeshSphere->m_nType = nType;			// �e�N�X�`���̎�ނ�ݒ�
		pMeshSphere->m_fRadius = fRadius;		// ���̑傫��
		pMeshSphere->m_nLine = nLine;			// ���̕�����
		pMeshSphere->m_nVertical = nVertical;	// �c�̕�����
		pMeshSphere->SetPosition(pos);			// �ʒu��ݒ�
		pMeshSphere->SetRotation(rot);			// ������ݒ�
		pMeshSphere->SetNumVtx((nLine + 1) * (nVertical + 1));	// ���_��
		pMeshSphere->SetNumIdx((2 * nLine * (nVertical * 2)));	// �C���f�b�N�X��
		pMeshSphere->SetNumPrimitive(2 * nLine * nVertical + (nVertical * 4) - 2);	// �v���~�e�B�u(�O�p�`�̖�)��
		pMeshSphere->Init();					// ����������
	}

	return pMeshSphere;
}
