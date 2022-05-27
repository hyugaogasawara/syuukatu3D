//=============================================================================
//
// ���f���N���X [modelsingle.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _MODELSINGLE_H_
#define _MODELSINGLE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_VTX			8	// ���_
#define MODEL_SURFACE_VTX	4	// �ʂ̒��_
#define MODEL_TEX			5
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CXload;

//*****************************************************************************
//	���f���N���X
//*****************************************************************************
class CModelSingle : public CScene
{
public:
	CModelSingle(int nPriority = PRIORITY_MODEL);	// �R���X�g���N�^
	~CModelSingle();	// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	// ��������
	static CModelSingle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);

	// �擾����
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }		// ���[���h�}�g���b�N�X
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			// �p�[�c�̈ʒu
	D3DXVECTOR3 GetRotation(void) { return m_rot; }			// �p�[�c�̌���
	D3DXVECTOR3 GetSize(void) { return m_size; }			// �p�[�c�̑傫��

	// �ݒ菈��
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		// �p�[�c�̈ʒu
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }		// �p�[�c�̌���
	void SetModelType(int nType) { m_nModelType = nType; }	// ���f���̎��

	// �����蔻��
	bool Collision(void);
private:
	LPDIRECT3DTEXTURE9	m_pTexture[MODEL_TEX];	// �e�N�X�`���̃|�C���^
	LPD3DXMESH			m_pMesh;				// ���b�V���i���_���j�ւ̃|�C���^
	LPD3DXBUFFER		m_pBuffMat;				// �}�e���A���i�ގ����j�ւ̃|�C���^
	DWORD				m_nNumMat;				// �}�g���b�N�X��
	D3DXMATRIX			m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3			m_pos;					// �ʒu
	D3DXVECTOR3			m_posOld;				// 1�t���[���O�̈ʒu
	D3DXVECTOR3			m_rot;					// ����
	D3DXVECTOR3			m_size;					// �傫��
	D3DXVECTOR3			m_vtxMin, m_vtxMax;		// ���_�̍ŏ��l�A�ő�l
	D3DXVECTOR3			m_vtx[MODEL_VTX];		// ���_�̃��[�J�����W
	D3DXMATRIX			m_aMtxWorld[MODEL_VTX];	// 8���_���̃��[���h�}�g���b�N�X
	D3DXVECTOR3			m_aSaveMtxWorld[MODEL_VTX];	// ���_�̃��[���h�}�g���b�N�X�ۑ�
	CXload				*m_pXload;					// X�t�@�C���̏��
	int					m_nModelType;				// ���f���̎��

};
#endif //!_MODELSINGLE_H_