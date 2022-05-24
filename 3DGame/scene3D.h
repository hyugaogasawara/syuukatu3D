//=============================================================================
//
// 3D�|���S���N���X [scene3D.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_VERTEX_3D	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// 3D ���_�t�H�[�}�b�g
#define NUM_VERTEX		4					// ���_��

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos; // ���_���W
	D3DXVECTOR3 nor; // �@���x�N�g��
	D3DCOLOR    col; // ���_�J���[
	D3DXVECTOR2 tex; // �e�N�X�`�����W
} VERTEX_3D;

//*****************************************************************************
//	3D�|���S���N���X
//*****************************************************************************
class CScene3D : public CScene
{
public:
	CScene3D(int nPriority = PRIORITY_NONE);		// �R���X�g���N�^
	virtual ~CScene3D();		// �f�X�g���N�^
	virtual HRESULT Init(void);	// ����������
	virtual void Uninit(void);	// �I������
	virtual void Update(void);	// �X�V����
	virtual void Draw(void);	// �`�揈��

	// �擾����
	LPDIRECT3DVERTEXBUFFER9 *GetVtxBuff(void) { return &m_pVtxBuff; }	// ���_�o�b�t�@�̃A�h���X
	LPDIRECT3DINDEXBUFFER9 *GetIdxBuff(void) { return &m_pIdxBuff; }	// �C���f�b�N�X�o�b�t�@�̃A�h���X
	int GetNumVtx(void) { return m_nNumVtx; }				// ���_��
	int GetNumIdx(void) { return m_nNumIdx; }				// �C���f�b�N�X��
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			// �ʒu
	D3DXVECTOR3 GetRotation(void) { return m_rot; }			// ����

	// �ݒ菈��
	void BindTexture(int nType) { m_pTexture = CTexture::SetTexture(nType); } // �e�N�X�`���̊��蓖��
	void SetNumVtx(int nNumVtx) { m_nNumVtx = nNumVtx; }	// ���_��
	void SetNumIdx(int nNumIdx) { m_nNumIdx = nNumIdx; }	// �C���f�b�N�X��
	void SetNumPrimitive(int nNumPrimitive) { m_nNumPrimitve = nNumPrimitive; }	// �v���~�e�B�u��
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		// �ʒu
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }		// ����

private:
	LPDIRECT3DTEXTURE9		m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;	// ���b�V���t�B�[���h�̃C���f�b�N�X�ւ̃|�C���^
	D3DXMATRIX				m_mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3				m_pos;		// �ʒu
	D3DXVECTOR3				m_rot;		// ����
	D3DXVECTOR3				m_size;		// �T�C�Y
	int						m_nNumVtx;	// ���_��
	int						m_nNumIdx;	// �C���f�b�N�X��
	int						m_nNumPrimitve;	// �v���~�e�B�u��(�O�p�`�|���S����)
};
#endif //!_SCENE3D_H_