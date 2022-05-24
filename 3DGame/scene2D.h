//=============================================================================
//
// 2D�I�u�W�F�N�g�N���X [scene2D.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// ���_�t�H�[�}�b�g
#define NUM_VERTEX2D		4										// ���_��

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	float		rhw; //1.0f�ŌŒ�
	D3DCOLOR    col; //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
} VERTEX_2D;

//*****************************************************************************
//	2D�I�u�W�F�N�g�N���X
//*****************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority = PRIORITY_NONE);	// �R���X�g���N�^
	~CScene2D();				// �f�X�g���N�^

	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

	// ��������
	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType);

	// �擾����
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// �ʒu���擾
	D3DXVECTOR3 GetSize(void) { return m_size; }	// �T�C�Y���擾

	// �ݒ菈��
	void BindTexture(int nType) { m_pTexture = CTexture::SetTexture(nType); }	// �e�N�X�`���̊��蓖��
	void SetVtxTexture(int nPatternAnimU, float fAnimU, int nPatternAnimV, float fAnimV, float fTexU, float fTexV);	// �e�N�X�`�����W�̐ݒ�
	void SetTexPattern(int nPattern, float fTexU);								// �e�N�X�`���p�^�[��
	void SetRotate(float fAngleX, float fAngleY, float fVec);					// ��]���
	void SetColor(D3DCOLORVALUE colval);										// ���_�J���[
	void SetColor(D3DXCOLOR color);				
	void SetScrollTex(float fTexU, float fTexV);								// �e�N�X�`���X�N���[��
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; CScene::SetPosition(pos); }// �ʒu
	void SetSize(D3DXVECTOR3 size) { m_size = size; CScene::SetSize(size); }	// �傫��
	void SetNumber(int nNum);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				m_pos;			// �ʒu
	D3DXVECTOR3				m_size;			// �T�C�Y
	D3DXCOLOR				m_color;		// ���_�J���[
	D3DCOLORVALUE			m_colval;		// ���_�J���[
	float					m_fTexU;
	float					m_fTexV;
	float					m_fMoveTexV;
};
#endif //!_SCENE2D_H_
