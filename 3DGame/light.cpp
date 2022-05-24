//=============================================================================
//
// ���C�g�N���X [light.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "light.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
int CLight::m_nNumLight = 0;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CLight::CLight()
{
	// �����o�ϐ��̃N���A
	ZeroMemory(&m_aLight[0], sizeof(D3DLIGHT9));

	// ���C�g�̔ԍ���ۑ�����
	m_nCntLight = m_nNumLight;
	m_nNumLight++;

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLight::~CLight()
{
	// ���C�g�̑��������炷
	m_nNumLight--;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CLight::Init(D3DXVECTOR3 vecDir, D3DXVECTOR3 pos, D3DXCOLOR col, int nCntLight)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���C�g�̎�ނ�ݒ�
	m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;
	
	// �g�U���̐ݒ�
	m_aLight[nCntLight].Diffuse = col;	

	// �ʒu�ݒ�
	m_aLight[nCntLight].Position = pos;

	// �����x�N�g����ݒ�
	m_vecDir = vecDir;
	D3DXVec3Normalize(&m_vecDir, &m_vecDir);	// ���K������

	// ������ݒ�
	m_aLight[nCntLight].Direction = m_vecDir;

	// ���C�g��ݒ�
	pDevice->SetLight(m_nCntLight, &m_aLight[nCntLight]);

	// ���C�g��L���ɂ���
	pDevice->LightEnable(m_nCntLight, TRUE);

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CLight::Uninit(void)
{
}
//=============================================================================
// �X�V����
//=============================================================================
void CLight::Update(void)
{
}
//=============================================================================
// ��������
//=============================================================================
CLight *CLight::Create(D3DXVECTOR3 vecDir, D3DXVECTOR3 pos, D3DXCOLOR col, int nCntLight)
{
	CLight *pLight;
	pLight = new CLight;

	if (pLight != NULL)
	{
		pLight->Init(vecDir, pos, col, nCntLight);	// ����������
	}

	return pLight;
}