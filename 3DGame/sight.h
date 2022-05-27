//=============================================================================
//
// �Ə��N���X [sight.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _SIGHT_H_
#define _SIGHT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"
#include "billboard.h"

//*****************************************************************************
//	�}�N����`
//*****************************************************************************
#define SPEED 2.5f
//*****************************************************************************
//	�O���錾
//*****************************************************************************
class CInputKeyboard;
class CMouse;
class CBullet;
//*****************************************************************************
//	�e�N���X
//*****************************************************************************
class CSight : public CBillboard
{
public:
	CSight(int nPriority = PRIORITY_SIGHT);	// �R���X�g���N�^
	~CSight();			// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	// ��������
	static CSight *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType);

private:
	void Move(void);	// �ړ�����

	D3DXVECTOR3	m_pos;		// �ʒu
	D3DXVECTOR3	m_rot;		// ����
	D3DXVECTOR3	m_size;		// �傫��
	D3DXVECTOR3	m_move;		// �ړ���
	int			m_nLife;	// ����
	bool		m_bUninit;	// �j��
	CBullet		*m_pBullet;	// �e�N���X�̃|�C���^
	CInputKeyboard	*m_pKeyboard;	// �L�[�{�[�h�N���X�̃|�C���^
	CMouse			*m_pMouse;		// �}�E�X�N���X�̃|�C���^
};
#endif //!_SIGHT_H_