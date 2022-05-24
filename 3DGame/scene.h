//=============================================================================
//
// �I�u�W�F�N�g�N���X [scene.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//	�I�u�W�F�N�g�N���X
//*****************************************************************************
class CScene
{
public:
	// �I�u�W�F�N�g�̎��
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_SPHERE,		// ��
		OBJTYPE_FIELD,		// ��
		OBJTYPE_MODEL,
		OBJTYPE_PLAYER,		// �v���C���[
		OBJTYPE_BULLET,		// �e
		OBJTYPE_EFFECT,		// �G�t�F�N�g
		OBJTYPE_SIGHT,		// �Ə�
		OBJTYPE_UI,			// UI
		OBJTYPE_MAX			// �ő吔
	} OBJTYPE;

	// �`��̗D�揇��
	typedef enum
	{
		PRIORITY_NONE = 0,
		PRIORITY_BG,		// �w�i
		PRIORITY_SPHERE,	// ��
		PRIORITY_FIELD,		// ��
		PRIORITY_MODEL,		// ���f��
		PRIORITY_PLAYER,	// �v���C���[
		PRIORITY_BULLET,	// �e
		PRIORITY_EFFECT,	// �G�t�F�N�g
		PRIORITY_UI,		// UI
		PRIORITY_FADE,		// �t�F�[�h
		PRIORITY_MAX		// �ő吔
	} PRIORITY;

	CScene(int nPriority = PRIORITY_NONE);			// ���������R���X�g���N�^
	virtual ~CScene();				// �f�X�g���N�^

	virtual HRESULT Init(void) = 0;	// ����������
	virtual void Uninit(void) = 0;	// �I������
	virtual void Update(void) = 0;	// �X�V����
	virtual void Draw(void) = 0;	// �`�揈��

	static void ReleaseAll(void);	// �S�ẴI�u�W�F�N�g�̔j��
	static void UpdateAll(void);	// �S�ẴI�u�W�F�N�g�̍X�V����
	static void DrawAll(void);		// �S�ẴI�u�W�F�N�g�̕`�揈��

	// �擾����
	static CScene *GetTopObj(int nPriority) { return m_pTop[nPriority]; }	// �擪�I�u�W�F�N�g�擾
	CScene *GetNextObj(CScene *pScene) { return pScene->m_pNext; }			// ���̃I�u�W�F�N�g���擾
	OBJTYPE GetObjType(void) { return m_objType; }							// �I�u�W�F�N�g�̎�ނ��擾
	D3DXVECTOR3 GetPosition(void) { return m_pos; }							// �ʒu
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }						// 1�t���[���O�̈ʒu
	D3DXVECTOR3 GetSize(void) { return m_size; }							// �傫��

	// �ݒ菈��
	void SetObjType(OBJTYPE objType) { m_objType = objType; }	// �I�u�W�F�N�g�̎��
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }			// �ʒu
	void SetPosOld(D3DXVECTOR3 posOld) { m_posOld = posOld; }	// �ʒu
	void SetSize(D3DXVECTOR3 size) { m_size = size; }			// �傫��

protected:
	void Release(void) { m_bDeath = true; }	// �I�u�W�F�N�g�̊J��

private:
	// ���X�g�\��
	static CScene *m_pTop[PRIORITY_MAX];	// �擪�I�u�W�F�N�g
	static CScene *m_pCur[PRIORITY_MAX];	// ����(�Ō��)�̃I�u�W�F�N�g
	CScene	*m_pPrev;		// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene	*m_pNext;		// ���̃I�u�W�F�N�g�ւ̃|�C���^
	bool	m_bDeath;		// ���S�t���O

	OBJTYPE m_objType;		// �I�u�W�F�N�g�̎��
	int		m_nPriority;	// �`��̗D�揇��

	// �����蔻��֘A
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_posOld;	// 1�t���[���O�̈ʒu
	D3DXVECTOR3 m_size;		// �傫��
};

#endif //!_SCENE_H_