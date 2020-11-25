#include	"Stage.h"

/**
* �R���X�g���N�^
*/
CStage::CStage()
{
}

/**
* �f�X�g���N�^
*/
CStage::~CStage()
{
}

/**
* �ǂݍ���
*/
bool CStage::Load(void)
{
	// ���b�V���̓ǂݍ���
	m_pMesh    = MeshAsset("Course1");
	m_pSkyMesh = MeshAsset("Course1_sky");
	m_pCollisionWallMesh   = MeshAsset("Course1WallHit");
	m_pCollisionGroundMesh = MeshAsset("Course1GroundHit");
	if (!m_pMesh || !m_pSkyMesh || !m_pCollisionWallMesh || !m_pCollisionGroundMesh)
	{
		return false;
	}
	return true;
}

/**
* ������
*/
void CStage::Initialize(void)
{
	//�X�e�[�W�̌����̐ݒ�
	m_Light.SetDirection(Vector3(-1, -1, 1));
	m_Light.SetDiffuse(MOF_COLOR_WHITE);
	m_Light.SetAmbient(MOF_COLOR_HWHITE);
	CGraphicsUtilities::SetDirectionalLight(&m_Light);
}

/**
* �X�V
*/
void CStage::Update(void)
{
}

/**
* �`��
*/
void CStage::Render(void)
{
	// ���[���h�s��쐬
	CMatrix44 matWorld;
	//�V�����b�V���̕`��
	m_pSkyMesh->Render(matWorld);
	// ���b�V���̕`��
	m_pMesh->Render(matWorld);
}

/**
* �f�o�b�O�����`��
*/
void CStage::RenderDebugText(void)
{
}

/**
* ���
*/
void CStage::Release(void)
{
	m_pMesh = nullptr;
	m_pSkyMesh = nullptr;
	m_pCollisionWallMesh = nullptr;
	m_pCollisionGroundMesh = nullptr;
}

CMeshPtr CStage::GetCollisionGroundMesh(void)
{
	return m_pCollisionGroundMesh;
}

CMeshPtr CStage::GetCollisionWallMesh(void)
{
	return m_pCollisionWallMesh;
}
