//=============================================================================
//
//	�}�E�X�N���X [mouse.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "mouse.h"
#include "input.h"
//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CMouse::CMouse()
{
	// �ϐ����N���A
	m_pDevice = NULL;
	ZeroMemory(&m_MouseState, sizeof(DIMOUSESTATE));	
	ZeroMemory(&m_MouseStateTrigger, sizeof(DIMOUSESTATE));
	ZeroMemory(&m_MouseStateRelease, sizeof(DIMOUSESTATE));
	m_bMouse = false;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMouse::~CMouse()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInit�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	//���̓f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�J�[�\����\��
	//ShowCursor(FALSE);

	//�����𓯊�������
	m_pDevice->Poll();

	// �}�E�X�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();
	m_bMouse = true;

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CMouse::Uninit(void)
{
	CInput::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CMouse::Update(void)
{
	DIMOUSESTATE aMouseState;	// ���͏��ۑ��ϐ�

	//���̓f�o�C�X����f�[�^���擾����
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aMouseState), &aMouseState)))
	{
		for (int nCntButton = 0; nCntButton < DIM_MAX; nCntButton++)
		{
			m_MouseStateTrigger.rgbButtons[nCntButton] = m_MouseState.rgbButtons[nCntButton] ^ aMouseState.rgbButtons[nCntButton] & aMouseState.rgbButtons[nCntButton];
			m_MouseStateRelease.rgbButtons[nCntButton] = (m_MouseState.rgbButtons[nCntButton] ^ aMouseState.rgbButtons[nCntButton]) & m_MouseState.rgbButtons[nCntButton];
			m_MouseState.rgbButtons[nCntButton] = aMouseState.rgbButtons[nCntButton];	//�}�E�X�̓��͏��ۑ�
		}
		m_MouseState.lX = aMouseState.lX;	// X�����ۑ�
		m_MouseState.lY = aMouseState.lY;	// Y�����ۑ�
		m_MouseState.lZ = aMouseState.lZ;	// Z�����ۑ�
	}
	else
	{
		m_pDevice->Acquire();	// �}�E�X�ւ̃A�N�Z�X�����l��
	}
}
//=============================================================================
// �}�E�X�̓��͏����擾
//=============================================================================
bool CMouse::GetPress(MouseButton Button)
{
	return (m_MouseState.rgbButtons[Button] & 0x80) ? true : false;
}
//=============================================================================
// �g���K�[�����擾
//=============================================================================
bool CMouse::GetTrigger(MouseButton Button)
{
	return (m_MouseStateTrigger.rgbButtons[Button] & 0x80) ? true : false;

}
//=============================================================================
// �����[�X�����擾
//=============================================================================
bool CMouse::GetRelease(MouseButton Button)
{
	return (m_MouseStateRelease.rgbButtons[Button] & 0x80) ? true : false;
}
//=============================================================================
// �}�E�X��X�����(�E�F�{�@���F�[)
//=============================================================================
float CMouse::MouseX(void)
{
	return (float)m_MouseState.lX;
}
//=============================================================================
// �}�E�X��Y�����(��F�[�@���F�{)
//=============================================================================
float CMouse::MouseY(void)
{
	return (float)m_MouseState.lY;
}
//=============================================================================
// �}�E�X�̃z�C�[��(������F�{�@�������F�[)
//=============================================================================
float CMouse::MouseZ(void)
{
	return (float)m_MouseState.lZ;
}
//=============================================================================
// �}�E�X�̎g�p��
//=============================================================================
bool CMouse::Mouse(void)
{
	return m_bMouse;
}
//=============================================================================
// �{�^���̗񋓏��ɑΉ������{�^������
//=============================================================================
bool CMouse::GetMouseButton(MouseButton Button)
{
	if ((m_MouseStateTrigger.rgbButtons[Button] & 0x80) != 0 && (m_MouseStateRelease.rgbButtons[Button] & 0x80) == 0)
	{
		return true;
	}
	return false;
}
