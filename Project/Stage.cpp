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

	//�e�L�X�g�t�@�C�����J��
	FILE* fp = fopen("path.txt", "rt");
	if (fp == NULL)
	{
		return false;
	}

	//�X�^�[�g�n�_�ǂݍ���
	for (int i = 0; i < MAXCHARACTER; i++)
	{
		fscanf(fp, "%f,%f,%f\n", &m_StartPos[i].x, &m_StartPos[i].y, &m_StartPos[i].z);
	}
	//�p�X�ǂݍ���
	fscanf(fp, "%d\n", &m_PathCount);
	m_PathArray = new CVector3[m_PathCount];
	for (int i = 0; i < m_PathCount; i++)
	{
		fscanf(fp, "%f,%f,%f\n", &m_PathArray[i].x, &m_PathArray[i].y, &m_PathArray[i].z);
	}
	//�t�@�C�������
	fclose(fp);

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
* �f�o�b�O�`��
*/
void CStage::RenderDebug(void)
{
	//�p�X�n�_�`��
	for (int i = 0; i < m_PathCount; i++)
	{
		CSphere gsp{ m_PathArray[i], 3.0f };
		CGraphicsUtilities::RenderSphere(gsp, CVector4{ 0, 1, 0, 0.5f });
		//���̓_�Ƃ���łȂ�
		if (i != m_PathCount - 1)
		{
			CGraphicsUtilities::RenderLine(m_PathArray[i], m_PathArray[i + 1], MOF_COLOR_GREEN);
		}
	}
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
	m_pMesh                = nullptr;
	m_pSkyMesh             = nullptr;
	m_pCollisionWallMesh   = nullptr;
	m_pCollisionGroundMesh = nullptr;
	MOF_SAFE_DELETE_ARRAY(m_PathArray);
}

const CVector3 & CStage::GetStartPos(int no) const
{
	return m_StartPos[no];
}

CVector3 * CStage::GetPath(void)
{
	return m_PathArray;
}

int CStage::GetPathCount(void)
{
	return m_PathCount;
}

CMeshPtr CStage::GetCollisionGroundMesh(void)
{
	return m_pCollisionGroundMesh;
}

CMeshPtr CStage::GetCollisionWallMesh(void)
{
	return m_pCollisionWallMesh;
}
