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
#define SPEED 3.0f
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
	CSight(int nPriority = PRIORITY_MODEL);	// �f�t�H���g�R���X�g���N�^
	~CSight();			// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	static CSight *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType);

private:
	void Move(void);

	D3DXVECTOR3	m_pos;		// �ʒu
	D3DXVECTOR3	m_rot;		// ����
	D3DXVECTOR3	m_size;		// �傫��
	D3DXVECTOR3	m_move;		// �ړ���
	int			m_nLife;	// ����
	bool		m_bUninit;
	CBullet		*m_pBullet;
	CInputKeyboard *m_pKeyboard;
	CMouse			*m_pMouse;
};
#endif //!_SIGHT_H_