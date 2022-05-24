//=============================================================================
//
// �G�t�F�N�g�N���X [effect.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"
#include "billboard.h"

//*****************************************************************************
//	�e�N���X
//*****************************************************************************
class CEffect : public CBillboard
{
public:
	CEffect(int nPriority = PRIORITY_EFFECT);	// �f�t�H���g�R���X�g���N�^
	~CEffect();			// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	// ��������
	static CEffect *Create(float fPosX, float fPosY, float fPosZ, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLORVALUE col, D3DCOLORVALUE subcol, int nLife, int nType);

protected:
	bool		m_bCalling;		// �J�����O�̏��
	int			m_nLife;		// ����

private:
	D3DXVECTOR3		m_pos;		// �ʒu
	D3DXVECTOR3		m_rot;		// ����
	D3DXVECTOR3		m_size;		// �傫��
	D3DXVECTOR3		m_move;		// �ړ���
	D3DCOLORVALUE	m_color;	// �J���[
	D3DCOLORVALUE	m_Subcolor;	// �J���[
	bool			m_bUninit;	// �j��
};
#endif //!_EFFECT_H_