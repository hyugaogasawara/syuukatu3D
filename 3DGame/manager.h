//=============================================================================
//
// �}�l�[�W�� [manager.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LIGHT 3	// ���C�g�̍ő吔
#define MAX_CAMERA 1	// �J�����̌̐�
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CRenderer;
class CInputKeyboard;
class CMouse;
class CXinputPad;
class CSound;

class CTitle;
class CMenu;
class CTutorial;
class CSelect;
class CGame;
class CResult;
class CRanking;
class CFade;
class CLight;
class CCamera;
class CTexture;
class CLoadData;
class CModel;
class CXload;
//*****************************************************************************
//	�}�l�[�W���N���X
//*****************************************************************************
class CManager
{
public:
	// ���[�h�̎��
	typedef enum
	{
		MODE_TITLE = 0,	// �^�C�g��
		MODE_MENU,		// �I��
		MODE_TUTORIAL,	// �`���[�g���A��
		MODE_SELECT,	// ����Z���N�g
		MODE_GAME,		// �Q�[��
		MODE_RESULT,	// ���U���g
		MODE_MAX		// �ő吔
	} MODE;

	CManager();		// �f�t�H���g�R���X�g���N�^
	~CManager();	// �f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);	// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	// �擾����
	static CManager			*GetInstance(void) { return m_pInstance; }				// �C���X�^���X�擾
	static CRenderer		*GetRenderer(void) { return m_pRenderer; }				// �����_���[���擾
	static CInputKeyboard	*GetInputKeyboard(void) { return m_pKeyboard; }			// �L�[�{�[�h���擾
	static CMouse			*GetMouse(void) { return m_pMouse; }					// �}�E�X���擾
	static CXinputPad		*GetXinputPad(void) { return m_pXinputPad; }			// �Q�[���p�b�h�擾
	static CSound			*GetSound(void) { return m_pSound; }					// �T�E���h���擾
	static CTitle			*GetTitle(void) { return m_pTitle; }					// �^�C�g���̃C���X�^���X
	static CMenu			*GetMenu(void) { return m_pMenu; }						// ���j���[�̃C���X�^���X
	static CTutorial		*GetTutorial(void) { return m_pTutorial; }				// �`���[�g���A���̃C���X�^���X
	static CSelect			*GetSelect(void) { return m_pSelect; }					// �Z���N�g�̃C���X�^���X
	static CGame			*GetGame(void) { return m_pGame; }						// �Q�[���̃C���X�^���X
	static CResult			*GetResult(void) { return m_pResult; }					// ���U���g�̃C���X�^���X
	static CRanking			*GetRanking(void) { return m_pRanking; }				// �����L���O�̃C���X�^���X
	static CFade			*GetFade(void) { return m_pFade; }						// �t�F�[�h���擾
	static CLight			*GetLight(void) { return m_apLight[0]; }				// ���C�g���擾
	static CCamera			*GetCamera(void) { return m_pCamera; }			// �J�������擾
	static CTexture			*GetTexture(void) { return m_pTexture; }				// �e�N�X�`�����擾
	static CLoadData		*GetLoadData(void) { return m_pLoadData; }				// �ǂݍ��݃f�[�^�N���X���擾
	static CModel			*GetModel(void) { return m_pModel; }					// ���f�����擾
	static CXload			*GetXLoad(void) { return m_pXload; }				// �v���C�f�[�^���擾

	// �ݒ菈��
	static void SetMode(MODE mode);					// ���[�h�̐ݒ�
	static MODE GetMode(void) { return m_mode; }	// ���[�h���擾

private:
	static CManager			*m_pInstance;			// �Ǘ��N���X�̃C���X�^���X
	static CRenderer		*m_pRenderer;			// �����_���[�̃C���X�^���X
	static CInputKeyboard	*m_pKeyboard;			// �L�[�{�[�h�̃C���X�^���X
	static CMouse			*m_pMouse;				// �}�E�X�̃C���X�^���X
	static CXinputPad		*m_pXinputPad;			// �Q�[���p�b�h�̃C���X�^���X
	static CSound			*m_pSound;				// �T�E���h�̃C���X�^���X
	static CTitle			*m_pTitle;				// �^�C�g���̃C���X�^���X
	static CMenu			*m_pMenu;				// ���j���[�̃C���X�^���X
	static CTutorial		*m_pTutorial;			// �`���[�g���A���̃C���X�^���X
	static CSelect			*m_pSelect;				// �Z���N�g�̃C���X�^���X
	static CGame			*m_pGame;				// �Q�[���̃C���X�^���X
	static CResult			*m_pResult;				// ���U���g�̃C���X�^���X
	static CRanking			*m_pRanking;			// �����L���O�̃C���X�^���X
	static CFade			*m_pFade;				// �t�F�[�h�̃C���X�^���X
	static CLight			*m_apLight[MAX_LIGHT];	// ���C�g�̃C���X�^���X
	static CCamera			*m_pCamera;				// �J�����̃C���X�^���X
	static CTexture			*m_pTexture;			// �e�N�X�`���̃C���X�^���X
	static CLoadData		*m_pLoadData;			// �ǂݍ��݃f�[�^�N���X�̃C���X�^���X
	static CModel			*m_pModel;				// ���f���̃C���X�^���X
	static CXload			*m_pXload;			// X�t�@�C���f�[�^�̃C���X�^���X

	static MODE				m_mode;					// ��ʂ̃��[�h

};
#endif //!_MANAGER_H_