//=============================================================================
//
// �^�C�}�[�N���X [timer.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TIME_DIGIT	2		// �^�C�}�[�̌���

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPolygon;

//*****************************************************************************
//	�X�R�A�N���X
//*****************************************************************************
class CTimer : public CScene
{
public:
	CTimer(int nPriority = PRIORITY_UI);	// �R���X�g���N�^
	~CTimer();				// �f�X�g���N�^

	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	// ��������
	static CTimer *Create(D3DXVECTOR3 pos, int nTime);

	void SetScore(int nScore) { m_nTimer = nScore; }	// �X�R�A�̐ݒ�
	void AddScore(int nValue) { m_nTimer += nValue; }	// �X�R�A�̉��Z
	int GetScore(void) { return m_nTimer; }				// �X�R�A�̎擾
	CPolygon *GetNumber(int nNumber) { return m_apNumber[nNumber]; }// �����N���X�擾

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;				// ���L�e�N�X�`���̃|�C���^
	CPolygon					*m_apNumber[TIME_DIGIT];// �ő包�����̐���
	D3DXVECTOR3					m_pos;					// �ʒu
	int							m_nTimer;				// �X�R�A�̒l
	int							m_nFrame;				// �t���[��
	int							m_nValue;				// �����l
};
#endif //!_TIMER_H_