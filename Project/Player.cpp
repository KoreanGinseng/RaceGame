#include	"Player.h"

/**
 * コンストラクタ
 */
CPlayer::CPlayer() :
CCharacter() 
{
}

/**
 * デストラクタ
 */
CPlayer::~CPlayer()
{
	Release();
}

/**
 * 更新
 */
void CPlayer::Update(CMeshPtr pGMesh, CMeshPtr pWMesh, CVector3 * path, int cnt)
{
	//キー入力で移動
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