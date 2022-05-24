//=============================================================================
//
// �e�N�X�`���N���X [texture.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FILENAME_TEXTURE "data/LOADFILE/texture.txt"
#define MAX_TEXTURE 30
//*****************************************************************************
//	�e�N�X�`���N���X
//*****************************************************************************
class CTexture
{
public:
	//�e�N�X�`���̎��
	typedef enum
	{
		TYPE_FIELD = 0,	// �t�B�[���h
		TYPE_MAX		// �e�N�X�`���̍ő吔
	} TEXTURE;

	CTexture();			// �R���X�g���N�^
	~CTexture();		// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������

	static LPDIRECT3DTEXTURE9 SetTexture(int nType) {return m_apTexture[nType]; }	// �e�N�X�`���̎�ނ�ݒ�

private:
	static LPDIRECT3DTEXTURE9	m_apTexture[MAX_TEXTURE];	// �e�N�X�`���̃|�C���^
	static int					m_nType;				// ��ސ�
	int							m_nNumTexture;			// ��ނ̑���
};
#endif //!_TEXTURE_H_