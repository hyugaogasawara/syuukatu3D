//=============================================================================
//
// ���f���N���X [modelsingle.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "modelsingle.h"
#include "Xload.h"
#include "game.h"
#include "bullet.h"
#include "score.h"
//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CModelSingle::CModelSingle(int nPriority) : CScene(nPriority)
{
	// �����o�ϐ��̃N���A
	memset(m_pTexture, NULL, sizeof(m_pTexture));	// �e�N�X�`���̃|�C���^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �傫��
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �e���_�̍ŏ��l
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �e���_�̍ő�l
	m_pMesh = NULL;									// ���b�V���i���_���j�ւ̃|�C���^
	m_pBuffMat = NULL;								// �}�e���A���i�ގ����j�ւ̃|�C���^
	m_nNumMat = 0;									// �}�e���A����
	m_pXload = CManager::GetXLoad();				// X�t�@�C���̃f�[�^�擾
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModelSingle::~CModelSingle()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CModelSingle::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �I�u�W�F�N�g�̎��
	SetObjType(OBJTYPE_MODEL);

	// X�t�@�C���̃f�[�^���擾
	m_pBuffMat = m_pXload->GetBuffMat(m_nModelType);
	m_nNumMat = m_pXload->GetNumMat(m_nModelType);
	m_pMesh = m_pXload->GetMesh(m_nModelType);

	// X�t�@�C���̓ǂݍ���
	//D3DXLoadMeshFromX("data/MODEL/target.x", D3DXMESH_SYSTEMMEM,
	//	pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL	*pMat;
	int nCntTex = 0;

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_pTexture[nCntTex]);
			nCntTex++;
		}
	}

	// ���_���̎擾
	int nNumVtx;		// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

	// ���_�����擾
	nNumVtx = m_pMesh->GetNumVertices();

	// ���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	// ���_�o�b�t�@�����b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		// ���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		// �S�Ă̒��_���r���čő�l�ƍŏ��l�𔲂��o��
		// �ő�l
		if (vtx.x >= m_vtxMax.x)
		{
			m_vtxMax.x = vtx.x;
		}
		if (vtx.y >= m_vtxMax.y)
		{
			m_vtxMax.y = vtx.y;
		}
		if (vtx.z >= m_vtxMax.z)
		{
			m_vtxMax.z = vtx.z;
		}
		// �ŏ��l
		if (vtx.x <= m_vtxMin.x)
		{
			m_vtxMin.x = vtx.x;
		}
		if (vtx.y <= m_vtxMin.y)
		{
			m_vtxMin.y = vtx.y;
		}
		if (vtx.z <= m_vtxMin.z)
		{
			m_vtxMin.z = vtx.z;
		}
		// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}
	// �ő�l�ƍŏ��l���������l�����f���̑傫��
	m_size.x = m_vtxMax.x - m_vtxMin.x;
	m_size.y = m_vtxMax.y - m_vtxMin.y;
	m_size.z = m_vtxMax.z - m_vtxMin.z;

	// ���_�ݒ�
	// ���ʂ̒��_
	m_vtx[0].x = m_vtxMin.x;
	m_vtx[0].y = m_vtxMax.y;
	m_vtx[0].z = m_vtxMin.z;
	m_vtx[1].x = m_vtxMax.x;
	m_vtx[1].y = m_vtxMax.y;
	m_vtx[1].z = m_vtxMin.z;
	m_vtx[2].x = m_vtxMin.x;
	m_vtx[2].y = m_vtxMin.y;
	m_vtx[2].z = m_vtxMin.z;
	m_vtx[3].x = m_vtxMax.x;
	m_vtx[3].y = m_vtxMin.y;
	m_vtx[3].z = m_vtxMin.z;
	// �w�ʂ̒��_
	m_vtx[4].x = m_vtxMin.x;
	m_vtx[4].y = m_vtxMax.y;
	m_vtx[4].z = m_vtxMax.z;
	m_vtx[5].x = m_vtxMax.x;
	m_vtx[5].y = m_vtxMax.y;
	m_vtx[5].z = m_vtxMax.z;
	m_vtx[6].x = m_vtxMin.x;
	m_vtx[6].y = m_vtxMin.y;
	m_vtx[6].z = m_vtxMax.z;
	m_vtx[7].x = m_vtxMax.x;
	m_vtx[7].y = m_vtxMin.y;
	m_vtx[7].z = m_vtxMax.z;

	// ���_�o�b�t�@���A�����b�N
	m_pMesh->UnlockVertexBuffer();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CModelSingle::Uninit(void)
{
	// �I�u�W�F�N�g�̊J��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CModelSingle::Update(void)
{
	if (m_nModelType == 0)
	{
		// �����蔻��
		CModelSingle::Collision();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CModelSingle::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX	mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9		matDef;		// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL		*pMat;		// �}�e���A���f�[�^�ւ̃|�C���^
	int					nCntTex = 0;// �e�N�X�`�����J�E���g

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// �e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	if (m_pBuffMat != NULL)
	{
		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			if (pMat->pTextureFilename)
			{	// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, m_pTexture[nCntTex]);
				nCntTex++;
			}
			else
			{	// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);
			}
			// ���f���i�p�[�c�j�̕`��	
			m_pMesh->DrawSubset(nCntMat);
		}
		// �ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}

	D3DXMATRIX vtxTrans,vtxParent;

	// 8���_���̃��[���h���W��ۑ�
	for (int nCnt = 0; nCnt < MODEL_VTX; nCnt++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_aMtxWorld[nCnt]);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&vtxTrans, m_vtx[nCnt].x, m_vtx[nCnt].y, m_vtx[nCnt].z);
		D3DXMatrixMultiply(&m_aMtxWorld[nCnt], &m_aMtxWorld[nCnt], &vtxTrans);

		if (m_mtxWorld)
		{
			vtxParent = m_mtxWorld;
		}
		else
		{
			pDevice->GetTransform(D3DTS_WORLD, &vtxParent);
		}

		// �e�q�֌W���|�����킹��
		D3DXMatrixMultiply(&m_aMtxWorld[nCnt], &vtxParent, &m_aMtxWorld[nCnt]);

		// �e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_aMtxWorld[nCnt]);

		// ���[���h���W��ۑ�
		m_aSaveMtxWorld[nCnt].x = m_aMtxWorld[nCnt]._41;
		m_aSaveMtxWorld[nCnt].y = m_aMtxWorld[nCnt]._42;
		m_aSaveMtxWorld[nCnt].z = m_aMtxWorld[nCnt]._43;
	}
}
//=============================================================================
// ��������
//=============================================================================
CModelSingle *CModelSingle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	CModelSingle *pModelSingle = nullptr;
	if (pModelSingle == nullptr)
	{
		pModelSingle = new CModelSingle;

		if (pModelSingle != nullptr)
		{
			pModelSingle->SetPosition(pos);		// �ʒu
			pModelSingle->SetRotation(rot);		// ����
			pModelSingle->SetModelType(nType);	// ���
			pModelSingle->Init();				// ����������
		}
	}
	return pModelSingle;
}
//=============================================================================
// �����蔻��
//=============================================================================
bool CModelSingle::Collision(void)
{
	// �I�u�W�F�N�g��񏉊���
	CScene *pThisObj = nullptr;
	CScene *pSaveObj = nullptr;

	// �擪�I�u�W�F�N�g�̗D�揇�ʂ��擾
	pThisObj = pThisObj->GetTopObj(PRIORITY_BULLET);

	while (pThisObj)
	{
		// ���݂̃I�u�W�F�N�g�̏��ۑ�
		pSaveObj = pThisObj;

		// �I�u�W�F�N�g�̎�ނ��擾
		if (pThisObj->GetObjType() == OBJTYPE_BULLET)
		{
			// �ϐ�������
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// �ʒu���擾
			pos = pThisObj->GetPosition();

			// 4���_����ΏۂɌ������ĐL�т�x�N�g�����Z�o
			D3DXVECTOR3 vec[MODEL_SURFACE_VTX];
			vec[0] = m_aSaveMtxWorld[0] - pos;
			vec[1] = m_aSaveMtxWorld[1] - pos;
			vec[2] = m_aSaveMtxWorld[2] - pos;
			vec[3] = m_aSaveMtxWorld[3] - pos;

			// �E���̃x�N�g�����Z�o
			D3DXVECTOR3 vec2[MODEL_SURFACE_VTX];
			vec2[0] = m_aSaveMtxWorld[1] - m_aSaveMtxWorld[0];
			vec2[1] = m_aSaveMtxWorld[3] - m_aSaveMtxWorld[1];
			vec2[2] = m_aSaveMtxWorld[2] - m_aSaveMtxWorld[3];
			vec2[3] = m_aSaveMtxWorld[0] - m_aSaveMtxWorld[2];

			// �O�ς����߂�
			float fVecCross[MODEL_SURFACE_VTX];
			fVecCross[0] = (vec[0].x * vec2[0].y) - (vec2[0].x * vec[0].y);
			fVecCross[1] = (vec[1].x * vec2[1].y) - (vec2[1].x * vec[1].y);
			fVecCross[2] = (vec[3].x * vec2[2].y) - (vec2[2].x * vec[3].y);
			fVecCross[3] = (vec[2].x * vec2[3].y) - (vec2[3].x * vec[2].y);

			// �͈͓��̔���
			if (fVecCross[0] < 0.0f && fVecCross[1] < 0.0f && fVecCross[2] < 0.0f && fVecCross[3] < 0.0f)
			{
				// �@�������߂�
				D3DXVECTOR3 Normal;
				D3DXVECTOR3 vec1_3D;
				D3DXVECTOR3 vec2_3D;
				vec1_3D = vec2[1] - vec2[0];
				vec2_3D = vec2[2] - vec2[0];

				// �@���̌v�Z(�O��)
				D3DXVec3Cross(&Normal, &vec1_3D, &vec2_3D);

				// ���K��
				D3DXVec3Normalize(&Normal, &Normal);

				// ����
				float fVecDot;
				fVecDot = -D3DXVec3Dot(&Normal, &vec[0]);

				// ���߂��l���s�p(90 �` 180��)�̏ꍇ�̓}�C�i�X
				if (fVecDot < 0.0f)
				{
					CScore *pScore = CGame::GetScore();
					pScore->AddScore(100);

					// �����蔻��
					CBullet *pBullet;
					pBullet = (CBullet*)pThisObj;
					pBullet->SetUninit(true);
					this->Uninit();
					return true;
				}
			}

		}
		// ���̃I�u�W�F�N�g���擾
		pThisObj = pSaveObj->GetNextObj(pThisObj);
	}
	return false;
}
