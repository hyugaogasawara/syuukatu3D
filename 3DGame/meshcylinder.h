//
// ���b�V���V�����_�[�N���X�F�~�� [meshcylinder.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"
#include "scene3D.h"

//*****************************************************************************
//	���b�V���t�B�[���h�N���X
//*****************************************************************************
class CMeshCylinder : public CScene3D
{
public:
	CMeshCylinder(int nPriority = PRIORITY_NONE);	// �f�t�H���g�R���X�g���N�^
	~CMeshCylinder();								// �f�X�g���N�^

	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

	static CMeshCylinder *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nVertical, int nSide, int ntype, float fRotateSpeed);	// ��������

	// �擾����
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// �ʒu�̎擾
	D3DXVECTOR3 GetSize(void) { return m_size; }	// �傫���̎擾

	// �ݒ菈��
	void SetRotateSpeed(float fSpeed) { m_fRotateSpeed = fSpeed; }
private:
	D3DXVECTOR3	m_pos;			// �ʒu
	D3DXVECTOR3	m_rot;			// ����
	D3DXVECTOR3	m_size;			// �傫��
	D3DXCOLOR	m_col;			// �F
	bool		m_bUninit;		// �j��
	bool		m_bOutSide;		// �O�����ǂ���
	int			m_nVertical;	// �c�̕�����
	int			m_nSide;		// ���̕�����
	float		m_fRotateSpeed;	// ��]���x
	float		m_fRadius;		// ���a
	int			m_nType;		// �e�N�X�`���̎��
};
#endif //!_MESHCYLINDER_H_