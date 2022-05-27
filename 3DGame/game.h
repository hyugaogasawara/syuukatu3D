//=============================================================================
//
// �Q�[���N���X [game.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPlayer;
class CMeshSphere;
class CMeshField;
class CModelSingle;
class CSight;
class CScore;

//*****************************************************************************
//	�Q�[���N���X
//*****************************************************************************
class CGame : public CScene
{
public:
	CGame(int nPriority = PRIORITY_NONE);	// �f�t�H���g�R���X�g���N�^
	~CGame();			// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	// ��������
	static CGame *Create(void);

	// �擾����
	static CPlayer *GetPlayer(void) { return m_pPlayer; }	// �v���C���[
	static CSight *GetSight(void) { return m_pSight; }		// �Ə�
	static CModelSingle *GetModelSingle(void) { return m_pModelSingle; }	// ���f���P��
	static CScore *GetScore(void) { return m_pScore; }
private:
	static CPlayer		*m_pPlayer;		// �v���C���[
	static CMeshSphere	*m_pMeshSphere;	// ���b�V���X�t�B�A
	static CMeshField	*m_pMeshField;	// ���b�V���t�B�[���h
	static CModelSingle *m_pModelSingle;// ���f���P��
	static CSight		*m_pSight;		// �Ə�
	static CScore		*m_pScore;
};
#endif //!_GAME_H_