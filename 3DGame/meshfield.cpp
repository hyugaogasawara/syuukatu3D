//=============================================================================
//
// ���b�V���t�B�[���h�N���X [meshfield.h]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "meshfield.h"
#include "keyboard.h"
#include "game.h"
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CMeshField::m_pTexture = NULL;	// �e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMeshField::CMeshField(int nPriority) : CScene3D(nPriority)
{
	// �����o�ϐ��̃N���A
	memset(m_pos, 0, sizeof(m_pos));			// �ʒu
	memset(m_rot, 0, sizeof(m_rot));			// �ʒu
	memset(m_move, 0, sizeof(m_move));			// �ړ���
	memset(m_size, 0, sizeof(m_size));		// �傫��

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
	SetObjType(OBJTYPE_MODEL);

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (m_nWidth + 1) * (m_nDepth + 1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx; //���_�o�b�t�@�ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y, m_pos.z + m_size.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x,			  m_pos.y, m_pos.z + m_size.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y, m_pos.z + m_size.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y, m_pos.z);
	pVtx[4].pos = D3DXVECTOR3(m_pos.x,			  m_pos.y, m_pos.z);
	pVtx[5].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y, m_pos.z);

	pVtx[6].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y, m_pos.z - m_size.z);
	pVtx[7].pos = D3DXVECTOR3(m_pos.x,			  m_pos.y, m_pos.z - m_size.z);
	pVtx[8].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y, m_pos.z - m_size.z);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(5.0f, 5.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 5.0f);
	pVtx[2].tex = D3DXVECTOR2(5.0f, 5.0f);

	pVtx[3].tex = D3DXVECTOR2(5.0f, 0.0f);
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(5.0f, 0.0f);

	pVtx[6].tex = D3DXVECTOR2(5.0f, 5.0f);
	pVtx[7].tex = D3DXVECTOR2(0.0f, 5.0f);
	pVtx[8].tex = D3DXVECTOR2(5.0f, 5.0f);


	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * ((m_nWidth + 1) * (m_nDepth + 1) * 2) - 4,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	WORD *pIdx;		//�C���f�b�N�X���ւ̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//�ԍ��f�[�^�̐ݒ�
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;

	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;

	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;

	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;


	//���_�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeshField::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CMeshField::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshField::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

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

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S���̕`��
	pDevice->SetTexture(0, m_pTexture);

	// �C���f�b�N�X�̃v���~�e�B�u
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (m_nWidth + 1) * (m_nDepth + 1), 0, 12);
}
//=============================================================================
// �v���C���[�̐���
//=============================================================================
CMeshField *CMeshField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nWidth, int nDepth, int nType)
{
	CMeshField *pMeshField;
	pMeshField = new CMeshField;

	if (pMeshField != NULL)
	{
		pMeshField->m_pos = pos;
		pMeshField->m_size = size;
		pMeshField->m_nWidth = nWidth;
		pMeshField->m_nDepth = nDepth;
		pMeshField->Init();
		pMeshField->BindTexture(nType);
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
			if (pPos->x >= pos.x - size.x + 10.0f && pPos->z <= pos.z + size.z + 10.0f&&
				pPos->x <= pos.x + size.x + 10.0f && pPos->z >= pos.z - size.z + 10.0f)
			{
				pPos->y = pos.y;
				BackPos = pos.y;
				return true;
			}
		}
	}
	return false;
}
