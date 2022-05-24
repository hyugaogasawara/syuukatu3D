//=============================================================================
//
// 2D�I�u�W�F�N�g�N���X [scene2D.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene2D.h"
#include "manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene2D::CScene2D(int nPriority) : CScene(nPriority)
{
	// �����o�ϐ����N���A
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CScene2D::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX2D,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,											// ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_2D,												// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,											// ���\�[�X�̃o�b�t�@��ێ����郁����
		&m_pVtxBuff,												// ���_�o�b�t�@�ւ̃|�C���^
		NULL);														// NULL�ɐݒ�

	VERTEX_2D *pVtx; //���_�o�b�t�@�ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W��ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CScene2D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene2D::Update(void)
{
	VERTEX_2D *pVtx; //���_�o�b�t�@�ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), m_pos.z);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene2D::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}
//=============================================================================
// ��������
//=============================================================================
CScene2D * CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType)
{
	CScene2D *pScene2D = NULL;
	pScene2D = new CScene2D;

	if (pScene2D != NULL)
	{
		pScene2D->SetPosition(pos);
		pScene2D->SetSize(size);
		pScene2D->Init();
	}

	return pScene2D;
}
//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void CScene2D::SetVtxTexture(int nPatteernAnimU, float fAnimU, int nPatteernAnimV, float fAnimV, float fTexU, float fTexV)
{
	VERTEX_2D *pVtx; //���_�o�b�t�@�ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W��ݒ�
	pVtx[0].tex = D3DXVECTOR2((nPatteernAnimU * fAnimU) + 0.0f,  (nPatteernAnimV * fAnimV) + 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nPatteernAnimU * fAnimU) + fTexU, (nPatteernAnimV * fAnimV) + 0.0f);
	pVtx[2].tex = D3DXVECTOR2((nPatteernAnimU * fAnimU) + 0.0f,  (nPatteernAnimV * fAnimV) + fTexV);
	pVtx[3].tex = D3DXVECTOR2((nPatteernAnimU * fAnimU) + fTexU, (nPatteernAnimV * fAnimV) + fTexV);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �e�N�X�`���p�^�[���ݒ�
//=============================================================================
void CScene2D::SetTexPattern(int nPattern, float fTexU)
{
	VERTEX_2D *pVtx; //���_�o�b�t�@�ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].tex = D3DXVECTOR2(nPattern * fTexU, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nPattern * fTexU + fTexU, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nPattern * fTexU, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nPattern * fTexU + fTexU, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// ��]����ݒ�
//=============================================================================
void CScene2D::SetRotate(float fAngleX, float fAngleY, float fVec)
{
	VERTEX_2D *pVtx; //���_�o�b�t�@�ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - sinf(fAngleX), m_pos.y - cosf(fAngleY), m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + cosf(fAngleX), m_pos.y - sinf(fAngleY), m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - cosf(fAngleX), m_pos.y + sinf(fAngleY), m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(fAngleX), m_pos.y + cosf(fAngleY), m_pos.z);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}
//=============================================================================
// ���_�J���[��ݒ�
//=============================================================================
void CScene2D::SetColor(D3DCOLORVALUE color)
{
	m_color = color;

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�ݒ�
	pVtx[0].col = D3DCOLOR_RGBA((int)m_color.r, (int)m_color.g, (int)m_color.b, (int)m_color.a);
	pVtx[1].col = D3DCOLOR_RGBA((int)m_color.r, (int)m_color.g, (int)m_color.b, (int)m_color.a);
	pVtx[2].col = D3DCOLOR_RGBA((int)m_color.r, (int)m_color.g, (int)m_color.b, (int)m_color.a);
	pVtx[3].col = D3DCOLOR_RGBA((int)m_color.r, (int)m_color.g, (int)m_color.b, (int)m_color.a);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

}
//=============================================================================
// ���_�J���[��ݒ�
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR color)
{

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�ݒ�
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

}
//=============================================================================
// �X�N���[���ݒ�
//=============================================================================
void CScene2D::SetScrollTex(float fTexU, float fTexV)
{
	m_fTexU = fTexU;
	m_fMoveTexV += fTexV;

	if (m_fMoveTexV >= 1.0f)
	{
		m_fMoveTexV -= 1.0f;
	}
	else if (m_fMoveTexV < 0.0f)
	{
		m_fMoveTexV += 1.0f;
	}

	if (m_fTexU >= 1.0f)
	{
		m_fTexU -= 1.0f;
	}
	else if (m_fTexU < 0.0f)
	{
		m_fTexU += 1.0f;
	}

	VERTEX_2D *pVtx;// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`����UV�ݒ�
	pVtx[0].tex = D3DXVECTOR2(m_fTexU,			m_fMoveTexV);
	pVtx[1].tex = D3DXVECTOR2(m_fTexU + 1.0f,	m_fMoveTexV);
	pVtx[2].tex = D3DXVECTOR2(m_fTexU,			m_fMoveTexV + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_fTexU + 1.0f,	m_fMoveTexV + 1.0f);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �e�N�X�`�����W��ݒ�
//=============================================================================
void CScene2D::SetNumber(int nNumber)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nNumber * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nNumber * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 1.0f);

	m_pVtxBuff->Unlock();
}
