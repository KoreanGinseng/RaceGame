#include	"Player.h"

/**
 * �R���X�g���N�^
 */
CPlayer::CPlayer() :
CCharacter() 
{
}

/**
 * �f�X�g���N�^
 */
CPlayer::~CPlayer()
{
	Release();
}

/**
 * �X�V
 */
void CPlayer::Update(CMeshPtr pGMesh, CMeshPtr pWMesh, CVector3 * path, int cnt)
{
	//�L�[���͂ňړ�
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		m_Angle.y -= CHARACTER_ROTATIONSPEED;
		MOF_NORMALIZE_RADIANANGLE(m_Angle.y);
	}
	else if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		m_Angle.y += CHARACTER_ROTATIONSPEED;
		MOF_NORMALIZE_RADIANANGLE(m_Angle.y);
	}
	if (g_pInput->IsKeyHold(MOFKEY_UP))
	{
		m_bAccele = true;
	}
	if (g_pInput->IsKeyHold(MOFKEY_DOWN))
	{
		m_bBrake = true;
	}

	CCharacter::Update(pGMesh, pWMesh, path, cnt);
}