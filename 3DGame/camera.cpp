//=============================================================================
//
// �J�����N���X [camea.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "camera.h"
#include "keyboard.h"
#include "mouse.h"
#include "player.h"
#include "game.h"
//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	// �ϐ����N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CCamera::Init(void)
{
	m_fViewDepth = VIEW_Z;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posV = D3DXVECTOR3(0.0f, VIEW_Y, -m_fViewDepth);	// ���_
	m_posR = D3DXVECTOR3(0.0f, GAZE_Y, -GAZE_Z);		// �����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				// �@���x�N�g��
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �J�����̌���
	m_size = D3DXVECTOR3(100.0f ,0.0f ,100.0f);			// �傫��

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CCamera::Uninit(void)
{
}
//=============================================================================
// �X�V����
//=============================================================================
void CCamera::Update(void)
{
	// �L�[�{�[�h���擾
	CInputKeyboard *pKeyboard = NULL;
	pKeyboard = CManager::GetInputKeyboard();

	// �}�E�X���擾
	CMouse *pMouse = NULL;
	pMouse = CManager::GetMouse();

	// �Q�[���p�b�h���擾
	CXinputPad *pXinputPad = NULL;
	pXinputPad = CManager::GetXinputPad();

	//KeyboardControl(pKeyboard);	// �L�[�{�[�h����

	//MouseControl(pMouse);			// �}�E�X����

	//GamePadXControl(pXinputPad);		// �Q�[���p�b�h����

	// �v���C���[���擾
#if 0
	CPlayer *pPlayer = CGame::GetPlayer();

	if (pPlayer != NULL)
	{
		// �Ǐ]
		D3DXVECTOR3 posR = pPlayer->GetMovement();
		D3DXVECTOR3 posV = pPlayer->GetMovement();
		m_posR += posR;
		m_posV += posV;
		//m_posR.x += posR.x;
		//m_posV.x += posV.x;
		//m_posR.z += posR.z;
		//m_posV.z += posV.z;
	}
#endif
	//m_posV.y = VIEW_Y;	// ���_
	//m_posR.y = GAZE_Y;	// �����_

}
//=============================================================================
// �ݒ菈��
//=============================================================================
void CCamera::SetCamera(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),						// ��p 360�x
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	// ��ʔ䗦
		10.0f,										// ��O�̈ʒu
		4000.0f);									// ���̈ʒu	���l�ύX�ŕ`��͈͂��L������

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
//=============================================================================
// ��������
//=============================================================================
CCamera *CCamera::Create(void)
{
	CCamera *pCamera = nullptr;
	if (pCamera == nullptr)
	{
		pCamera = new CCamera;

		if (pCamera != nullptr)
		{
			pCamera->Init();
		}
	}
	return pCamera;
}
//=============================================================================
// �L�[�{�[�h����
//=============================================================================
void CCamera::KeyboardControl(CInputKeyboard * pKeyboard)
{
	//=============================================
	//				�J�����̈ړ�����
	//=============================================
	if (pKeyboard->GetPress(DIK_UP) == true)
	{// �O�ړ�
		m_posV.x += sinf(m_rot.y) * (4.0f);
		m_posV.z += cosf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);	// sinf X���̌���
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);	// cosf Z���̌���
	}
	else if (pKeyboard->GetPress(DIK_DOWN) == true)
	{// ��ړ�
		m_posV.x -= sinf(m_rot.y) * (4.0f);
		m_posV.z -= cosf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);
	}
	else if (pKeyboard->GetPress(DIK_LEFT) == true)
	{// ���ړ�
		m_posV.x -= cosf(m_rot.y) * (4.0f);
		m_posV.z += sinf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);
	}
	else if (pKeyboard->GetPress(DIK_RIGHT) == true)
	{// �E�ړ�
		m_posV.x += cosf(m_rot.y) * (4.0f);
		m_posV.z -= sinf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);
	}
	if (pKeyboard->GetPress(DIK_U) == true)
	{// ���_�ƒ����_�̋���
		m_posV.z += 4.0f;
	}
	if (pKeyboard->GetPress(DIK_M) == true)
	{// ���_�ƒ����_�̋���
		m_posV.z -= 4.0f;
	}

	//=============================================
	//					���_����
	//=============================================
	if (pKeyboard->GetPress(DIK_Y) == true)
	{// ��ړ�
		m_posV.y += 4.0f;

		//if (m_posV.y >= 900.0f)
		//{
		//	m_posV.y = 900.0f;
		//}

	}
	else if (pKeyboard->GetPress(DIK_N) == true)
	{// ���ړ�
		m_posV.y -= 4.0f;

		//if (m_posV.y <= 200.0f)
		//{
		//	m_posV.y = 200.0f;
		//}

	}
	if (pKeyboard->GetPress(DIK_C) == true)
	{// ������
		if (m_rot.y < D3DX_PI)
		{// -3.14f��菬�����Ȃ����Ƃ��ɒl��3.14f�ɂ���
			m_rot.y += D3DX_PI * 2.0f;
		}
		m_rot.y -= 0.03f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * VIEW_Z;
		m_posV.z = m_posR.z - cosf(m_rot.y) * VIEW_Z;
	}
	else if (pKeyboard->GetPress(DIK_Z) == true)
	{// �E����
		if (m_rot.y > D3DX_PI)
		{// 3.14f���傫���Ȃ����Ƃ��ɒl��-3.14f�ɂ���
			m_rot.y -= D3DX_PI * 2.0f;
		}
		m_rot.y += 0.03f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * VIEW_Z;
		m_posV.z = m_posR.z - cosf(m_rot.y) * VIEW_Z;
	}

	//=============================================
	//					�����_����
	//=============================================
	if (pKeyboard->GetPress(DIK_T) == true)
	{// ��ړ�
		m_posR.y += 2.0f;
	}
	else if (pKeyboard->GetPress(DIK_B) == true)
	{// ���ړ�
		m_posR.y -= 2.0f;
	}
	else if (pKeyboard->GetPress(DIK_Q) == true)
	{// ������
		if (m_rot.y < D3DX_PI)
		{// -3.14f��菬�����Ȃ����Ƃ�3.14f�ɂ���
			m_rot.y += D3DX_PI * 2.0f;
		}
		m_rot.y -= 0.03f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * VIEW_Z;
		m_posR.z = m_posV.z + cosf(m_rot.y) * VIEW_Z;
	}
	else if (pKeyboard->GetPress(DIK_E) == true)
	{// �E����
		if (m_rot.y > D3DX_PI)
		{// 3.14f���傫���Ȃ����Ƃ�-3.14f�ɂ���
			m_rot.y -= D3DX_PI * 2.0f;
		}
		m_rot.y += 0.03f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * VIEW_Z;
		m_posR.z = m_posV.z + cosf(m_rot.y) * VIEW_Z;
	}
}
//=============================================================================
// �}�E�X����
//=============================================================================
void CCamera::MouseControl(CMouse *pMouse)
{
#if 1
	// �}�E�X�̍��{�^��
	if (pMouse->GetTrigger(CMouse::DIM_L) == true)
	{// �}�E�X���W���擾
		GetCursorPos(&m_Cursol);
	}
	else if (pMouse->GetPress(CMouse::DIM_L) == true)
	{
		SetCursorPos(m_Cursol.x, m_Cursol.y);

		m_rot.y += pMouse->GetMousePos().lX * 0.01f;
		if (m_rot.y > D3DX_PI / 4)
		{
			m_rot.y = -D3DX_PI / 4;
		}
		m_posV.y += pMouse->GetMousePos().lY * -0.1f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fViewDepth;
		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fViewDepth;
	}

	// �}�E�X�̉E�{�^��
	if (pMouse->GetTrigger(CMouse::DIM_R) == true)
	{// �}�E�X���W���擾
		GetCursorPos(&m_Cursol);
	}
	else if (pMouse->GetPress(CMouse::DIM_R) == true)
	{
		SetCursorPos(m_Cursol.x, m_Cursol.y);

		m_rot.y -= pMouse->GetMousePos().lX * 0.001f;
		if (m_rot.y > D3DX_PI / 4)
		{
			m_rot.y = -D3DX_PI / 4;
		}
		m_posR.y += pMouse->GetMousePos().lY * -0.1f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fViewDepth;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fViewDepth;

		//m_posR.y = m_fViewDepth * sinf(m_rot.x) * sinf(m_rot.y);
		//m_posR.x = m_fViewDepth * sinf(m_rot.x) * cosf(m_rot.y);
		//m_posR.z = m_fViewDepth * cosf(m_rot.x);
	}
#else
	// �}�E�X�̉E�{�^��
	if (pMouse->GetTrigger(CMouse::DIM_L) == true)
	{// �}�E�X���W���擾
		GetCursorPos(&m_Cursol);
	}
	else if (pMouse->GetPress(CMouse::DIM_L) == true)
	{
		SetCursorPos(m_Cursol.x, m_Cursol.y);

		m_rot.x -= pMouse->GetMousePos().lX * 0.001f;
		m_rot.y += pMouse->GetMousePos().lY * -0.1f;
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y = -D3DX_PI;
		}

		//m_posR.x = m_posV.x + sinf(m_rot.y) * m_fViewDepth;
		//m_posR.z = m_posV.z + cosf(m_rot.y) * m_fViewDepth;

		m_posR.y = m_fViewDepth * sinf(m_rot.y) * cosf(m_rot.x);
		m_posR.x = m_fViewDepth * sinf(m_rot.y) * sinf(m_rot.x); 
		m_posR.z = m_fViewDepth * cosf(m_rot.y);
	}
#endif
}
//=============================================================================
// �Q�[���p�b�h����FXInput
//=============================================================================
#if 0
void CCamera::GamePadXControl(CXinputPad *pGamePad)
{
	//=============================================
	//				�J�����̈ړ�����
	//=============================================
	if (pGamePad->GetRightStick(CXinputPad::STICKTYPE_UP) == true)
	{// �O�ړ�
		m_posV.x += sinf(m_rot.y) * (4.0f);
		m_posV.z += cosf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);	// sinf X���̌���
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);	// cosf Z���̌���
	}
	else if (pGamePad->GetRightStick(CXinputPad::STICKTYPE_DOWN) == true)
	{// ��ړ�
		m_posV.x -= sinf(m_rot.y) * (4.0f);
		m_posV.z -= cosf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);
	}
	else if (pGamePad->GetRightStick(CXinputPad::STICKTYPE_LEFT) == true)
	{// ���ړ�
		m_posV.x -= cosf(m_rot.y) * (4.0f);
		m_posV.z += sinf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);
	}
	else if (pGamePad->GetRightStick(CXinputPad::STICKTYPE_RIGHT) == true)
	{// �E�ړ�
		m_posV.x += cosf(m_rot.y) * (4.0f);
		m_posV.z -= sinf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);
	}
	if (pGamePad->GetShoulder(CXinputPad::SHOULDERTYPE_RIGHT) == true)
	{// ���_�ƒ����_�̋���
		m_posV.z += 4.0f;
	}
	if (pGamePad->GetShoulder(CXinputPad::SHOULDERTYPE_LEFT) == true)
	{// ���_�ƒ����_�̋���
		m_posV.z -= 4.0f;
	}

	//=============================================
	//					���_����
	//=============================================
	if (pGamePad->GetButtonPress(XINPUT_GAMEPAD_DPAD_UP) == true)
	{// ��ړ�
		m_posV.y += 4.0f;

		//if (m_posV.y >= 900.0f)
		//{
		//	m_posV.y = 900.0f;
		//}

	}
	if (pGamePad->GetButtonPress(XINPUT_GAMEPAD_DPAD_DOWN) == true)
	{// ���ړ�
		m_posV.y -= 4.0f;

		//if (m_posV.y <= 200.0f)
		//{
		//	m_posV.y = 200.0f;
		//}

	}
	if (pGamePad->GetButtonPress(XINPUT_GAMEPAD_DPAD_LEFT) == true)
	{// ������
		if (m_rot.y < D3DX_PI)
		{// -3.14f��菬�����Ȃ����Ƃ��ɒl��3.14f�ɂ���
			m_rot.y += D3DX_PI * 2.0f;
		}
		m_rot.y -= 0.03f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * VIEW_Z;
		m_posV.z = m_posR.z - cosf(m_rot.y) * VIEW_Z;
	}
	if (pGamePad->GetButtonPress(XINPUT_GAMEPAD_DPAD_RIGHT) == true)
	{// �E����
		if (m_rot.y > D3DX_PI)
		{// 3.14f���傫���Ȃ����Ƃ��ɒl��-3.14f�ɂ���
			m_rot.y -= D3DX_PI * 2.0f;
		}
		m_rot.y += 0.03f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * VIEW_Z;
		m_posV.z = m_posR.z - cosf(m_rot.y) * VIEW_Z;
	}

	//=============================================
	//					�����_����
	//=============================================
	if (pGamePad->GetLeftStick(CXinputPad::STICKTYPE_UP) == true)
	{// ��ړ�
		m_posR.y += 2.0f;
	}
	if (pGamePad->GetLeftStick(CXinputPad::STICKTYPE_DOWN) == true)
	{// ���ړ�
		m_posR.y -= 2.0f;
	}
	if (pGamePad->GetLeftStick(CXinputPad::STICKTYPE_LEFT) == true)
	{// ������
		if (m_rot.y < D3DX_PI)
		{// -3.14f��菬�����Ȃ����Ƃ�3.14f�ɂ���
			m_rot.y += D3DX_PI * 2.0f;
		}
		m_rot.y -= 0.03f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * VIEW_Z;
		m_posR.z = m_posV.z + cosf(m_rot.y) * VIEW_Z;
	}
	if (pGamePad->GetLeftStick(CXinputPad::STICKTYPE_RIGHT) == true)
	{// �E����
		if (m_rot.y > D3DX_PI)
		{// 3.14f���傫���Ȃ����Ƃ�-3.14f�ɂ���
			m_rot.y -= D3DX_PI * 2.0f;
		}
		m_rot.y += 0.03f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * VIEW_Z;
		m_posR.z = m_posV.z + cosf(m_rot.y) * VIEW_Z;
	}

}
#endif