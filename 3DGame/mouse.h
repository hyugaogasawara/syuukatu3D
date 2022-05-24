//=============================================================================
//
//	�}�E�X�N���X [mouse.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _MOUSE_H_
#define _MOUSE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_KEY_MAX (256) //�L�[�̍ő吔

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "input.h"

//*****************************************************************************
//	�}�E�X�N���X
//*****************************************************************************
class CMouse : public CInput
{
public:
	// �}�E�X�̃{�^����
	typedef enum
	{
		DIM_L = 0,	// ���N���b�N
		DIM_R,		// �E�N���b�N
		DIM_W,		// �z�C�[���{�^��
		DIM_MAX		// �{�^���ő吔
	} MouseButton;

	CMouse();	// �f�t�H���g�R���X�g���N�^
	~CMouse();	// �f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ����������
	void Uninit();									// �I������
	void Update();									// �X�V����

	// �擾����
	bool GetPress(MouseButton Button);		// �v���X���
	bool GetTrigger(MouseButton Button);		// �g���K�[���
	bool GetRelease(MouseButton Button);		// �����[�X���
	float MouseX(void);	// �}�E�X��X��
	float MouseY(void);	// �}�E�X��Y��
	float MouseZ(void);	// �}�E�X��Z��(�}�E�X�z�C�[���̎����)
	bool Mouse(void);		// �}�E�X�̎g�p��
	bool GetMouseButton(MouseButton Button);	// ���͏��
	DIMOUSESTATE GetMousePos(void) { return m_MouseState; }	// �}�E�X�̓��͏��擾


private:
	DIMOUSESTATE	m_MouseState;			// �}�E�X�̓��͏��(�v���X���)
	DIMOUSESTATE	m_MouseStateTrigger;	// �}�E�X�̓��͏��(�g���K�[���)
	DIMOUSESTATE	m_MouseStateRelease;	// �}�E�X�̓��͏��(�����[�X���)
	bool			m_bMouse;				// �}�E�X�̎g�p��					
};
#endif //!_MOUSE_H_