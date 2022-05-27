//=============================================================================
//
// �ėp�|���S���N���X [polygon.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"
#include "scene2D.h"
#include "texture.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// ���_�t�H�[�}�b�g
#define NUM_VERTEX		4											// ���_��

//*****************************************************************************
//	�ėp�|���S���N���X
//*****************************************************************************
class CPolygon
{
public:
	CPolygon();		// �R���X�g���N�^
	~CPolygon();		// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType);		// �����̐���
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }	// �e�N�X�`���̊��蓖��
	void SetNumber(int nNumber);							// �e�N�X�`�����W��ݒ�

private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;			// �ʒu
	D3DXVECTOR3				m_size;			// �傫��
	int						m_nType;		// �e�N�X�`���̎��
};
#endif //!_POLYGON_H_