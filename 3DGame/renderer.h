//=============================================================================
//
// �����_�����O���� [renderer.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//	�����_�����O�N���X
//*****************************************************************************
class CRenderer
{
public:
	CRenderer();		// �f�t�H���g�R���X�g���N�^
	~CRenderer();		// �f�X�g���N�^

	HRESULT Init(HWND hWnd, BOOL bWindow);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	// �擾����
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	// �f�o�C�X���擾
	LPD3DXFONT GetFont(void) { return m_pFont; }				// �t�H���g���擾
private:
#ifdef _DEBUG
	void DrawFPS(void);	// FPS�̕`�揈��
	void DrawTXT(void);
#endif

	LPDIRECT3D9				m_pD3D;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	LPD3DXFONT				m_pFont;		// �t�H���g�ւ̃|�C���^
};
#endif //!_RENDERER_H_