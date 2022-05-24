//=============================================================================
//
// �r���{�[�h�N���X [billboard.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"
#include "scene3D.h"

//*****************************************************************************
//	�r���{�[�h�N���X
//*****************************************************************************
class CBillboard : public CScene
{
public:
	CBillboard(int nPriority = PRIORITY_NONE);	// �f�t�H���g�R���X�g���N�^
	~CBillboard();		// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	static CBillboard *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType);

	// �ݒ菈��
	void BindTexture(int nType) { m_pTexture = CTexture::SetTexture(nType); } // �e�N�X�`���̊��蓖��
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		// �ʒu
	void SetSize(D3DXVECTOR3 size) { m_size = size; }		// �傫��
	void SetColValue(D3DCOLORVALUE col) { m_color = col; }	// �J���[

	// �擾����
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	D3DXMATRIX				m_mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3		m_pos;		// �ʒu
	D3DXVECTOR3		m_rot;		// ����
	D3DXVECTOR3		m_size;		// �傫��
	D3DXVECTOR3		m_move;		// �ړ���
	D3DCOLORVALUE	m_color;	// �J���[
};
#endif //!_BILLBOARD_H_