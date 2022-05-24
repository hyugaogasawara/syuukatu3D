//=============================================================================
//
// ���b�V���X�t�B�A�N���X �F�@���@[meshsphere.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _MESHSPHERE_H_
#define _MESHSPHERE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"
#include "scene3D.h"

//*****************************************************************************
//	���b�V���X�t�B�A�N���X
//*****************************************************************************
class CMeshSphere : public CScene3D
{
public:
	CMeshSphere(int nPriority = PRIORITY_SPHERE);	// �R���X�g���N�^
	~CMeshSphere();		// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	// ��������
	static CMeshSphere *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, int nVertical, int nLine, int nType);

	// �擾����
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// �ʒu
private:
	D3DXMATRIX	m_mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3	m_pos;		// �ʒu
	D3DXVECTOR3	m_rot;		// ����
	bool		m_bUninit;	// �j��
	bool		m_bCalling;	// �J�����O�̏��
	int			m_nVertical;// �c�̕�����
	int			m_nLine;	// ���̕�����
	int			m_nType;	// �e�N�X�`���̎��
	float		m_fRadius;	// ���a
};
#endif //!_MESHSPHERE_H_