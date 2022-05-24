//=============================================================================
//
// �v���C���[�N���X [player.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CModel;
class CInputKeyboard;
class CGamePad;
class CXLoad;
//*****************************************************************************
//	�v���C���[�N���X
//*****************************************************************************
class CPlayer : public CScene
{
public:
	CPlayer(int nPriority = PRIORITY_PLAYER);	// �R���X�g���N�^
	~CPlayer();			// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	// ��������
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	
	
	// �擾����
	D3DXVECTOR3	GetPosition(void) { return m_pos; }		// �ʒu
	D3DXVECTOR3	GetPositionOld(void) { return m_posOld; }	// 1�t���[���O�̈ʒu
	D3DXVECTOR3	GetRotation(void) { return m_rot; }		// ����
	D3DXVECTOR3	GetMovement(void) { return m_move; }	// �ړ���

	// �ݒ菈��
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	// �ʒu
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }	// ����
private:
	void Move(void);		// �ړ�����
	void Attack(void);		// �U������
	void Collision(void);	// �����蔻��

	D3DXMATRIX		m_mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3		m_pos;			// �ʒu
	D3DXVECTOR3		m_posOld;		// 1�t���[���O�̈ʒu
	D3DXVECTOR3		m_rot;			// ����
	D3DXVECTOR3		m_size;			// �傫��
	D3DXVECTOR3		m_move;			// �ړ���
	CModel			*m_pModel[32];	// ���f���ւ̃|�C���^
	CXLoad			*m_pXload;
	CInputKeyboard	*m_pKeyboard;	// �L�[�{�[�h���͏��
	int				m_nNumModel;	// ���f���̑���
};
#endif //!_PLAYER_H_