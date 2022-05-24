//=============================================================================
//
// �e�N���X [bullet.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"
#include "billboard.h"

//*****************************************************************************
//	�e�N���X
//*****************************************************************************
class CBullet : public CBillboard
{
public:
	CBullet(int nPriority = PRIORITY_BULLET);	// �f�t�H���g�R���X�g���N�^
	~CBullet();			// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, int nLife, int nType);

	// �ݒ菈��
	void SetUninit(bool bUninit) { m_bUninit = bUninit; }

private:
	D3DXVECTOR3	m_pos;		// �ʒu
	D3DXVECTOR3	m_rot;		// ����
	D3DXVECTOR3	m_size;		// �傫��
	D3DXVECTOR3	m_move;		// �ړ���
	int			m_nLife;	// ����
	bool		m_bUninit;	// �I����������
};
#endif //!_BULLET_H_