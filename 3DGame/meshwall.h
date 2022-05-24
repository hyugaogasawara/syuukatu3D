//
// ���b�V���E�H�[���N���X [meshwall.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"
#include "scene3D.h"

//*****************************************************************************
//	���b�V���E�H�[���N���X
//*****************************************************************************
class CMeshWall : public CScene3D
{
public:
	CMeshWall(int nPriority = PRIORITY_NONE);	// �f�t�H���g�R���X�g���N�^
	~CMeshWall();								// �f�X�g���N�^

	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	static CMeshWall *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nWidth, int nDepth, int nType);	// ��������

	// �ݒ菈��
	void BindTexture(int nType) { m_nType = nType; }	// �e�N�X�`���̊��蓖��

	// �擾����
	D3DXVECTOR3 GetPosition(void) { return m_pos; }		// �ʒu�̎擾
	D3DXVECTOR3 GetSize(void) { return m_size; }		// �傫���̎擾
	bool Collision(CMeshWall *pMeshField, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float& BackPos);

private:
	D3DXMATRIX	m_mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3	m_pos;		// �ʒu
	D3DXVECTOR3	m_rot;		// ����
	D3DXVECTOR3	m_size;		// �傫��
	bool		m_bUninit;	// �j��
	int			m_nWidth;	// ���̕�����
	int			m_nHeight;	// �����̕�����
	int			m_nType;	// �e�N�X�`���̎��
};
#endif //!_MESHWALL_H_