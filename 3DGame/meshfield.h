//=============================================================================
//
// ���b�V���t�B�[���h�N���X [meshfield.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"
#include "scene3D.h"

//*****************************************************************************
//	���b�V���t�B�[���h�N���X
//*****************************************************************************
class CMeshField : public CScene3D
{
public:
	CMeshField(int nPriority = PRIORITY_FIELD);	// �f�t�H���g�R���X�g���N�^
	~CMeshField();				// �f�X�g���N�^

	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

	// ��������
	static CMeshField *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nWidth, int nDepth, int nType);

	// �擾����
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// �ʒu
	D3DXVECTOR3 GetSize(void) {return m_size; }		// �傫��

	// �����蔻��
	bool Collision(CMeshField *pMeshField, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float& BackPos);

private:
	D3DXMATRIX	m_mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3	m_pos;		// �ʒu
	D3DXVECTOR3	m_rot;		// ����
	D3DXVECTOR3	m_size;		// �傫��
	bool		m_bUninit;	// �j��
	int			m_nWidth;	// ���̕�����
	int			m_nDepth;	// ���s�̕�����
	int			m_nType;		// �e�N�X�`���̎��
};
#endif //!_MESHFIELD_H_