//=============================================================================
//
// �X�R�A�N���X [score.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_DIGIT	6		// �ő包��

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPolygon;
class CScene2D;
//*****************************************************************************
//	�X�R�A�N���X
//*****************************************************************************
class CScore : public CScene
{
public:
	CScore(int nPriority = PRIORITY_UI);	// �R���X�g���N�^
	~CScore();				// �f�X�g���N�^

	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	// ��������
	static CScore *Create(D3DXVECTOR3 pos);

	// �擾����
	int GetScore(void) { return m_nScore; }							// �X�R�A�̎擾
	CPolygon *GetNumber(int nNumber) { return m_apNumber[nNumber]; }// �����N���X�擾

	// �ݒ菈��
	void SetScore(int nScore) { m_nScore = nScore; }			// �X�R�A�̐ݒ�
	void AddScore(int nValue) { m_nScore += nValue; }			// �X�R�A�̉��Z

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;				// ���L�e�N�X�`���̃|�C���^
	CPolygon					*m_apNumber[MAX_DIGIT];	// �ő包�����̐���
	D3DXVECTOR3					m_pos;					// �ʒu
	int							m_nScore;				// �X�R�A�̒l
	int							m_nValue;				// �����l
};
#endif //!_SCORE_H_