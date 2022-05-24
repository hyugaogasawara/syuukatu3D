//=============================================================================
//
// ���C�g�N���X [light.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
//	���C�g�N���X
//*****************************************************************************
class CLight
{
public:
	CLight();			// �f�t�H���g�R���X�g���N�^
	~CLight();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 vecDir, D3DXVECTOR3 pos, D3DXCOLOR col, int nCntLight);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����

	static CLight *Create(D3DXVECTOR3 vecDir, D3DXVECTOR3 pos, D3DXCOLOR col, int nCntLight);	// ��������

private:
	D3DLIGHT9		m_aLight[MAX_LIGHT];	// ���C�g���
	D3DXVECTOR3		m_vecDir;		// �ݒ�p�����x�N�g��
	D3DXVECTOR3		m_vecDirection;	// �g�U���̕���
	D3DLIGHTTYPE	m_type;			// ���
	D3DXCOLOR		m_color;		// �F
	static int		m_nNumLight;	// �ԍ�
	int				m_nCntLight;	// ��������ۑ�

};
#endif //!_LIGHT_H_