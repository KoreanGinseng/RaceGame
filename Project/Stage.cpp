#include	"Stage.h"

/**
* �R���X�g���N�^
*/
CStage::CStage() :
m_Mesh() ,
m_SkyMesh() ,
m_Light() {
}

/**
* �f�X�g���N�^
*/
CStage::~CStage(){
}

/**
* �ǂݍ���
*/
bool CStage::Load(void){
	// ���b�V���̓ǂݍ���
	if (!m_Mesh.Load("Course1.mom"))
	{
		return false;
	}
	if (!m_SkyMesh.Load("Course1_sky.mom"))
	{
		return false;
	}
	return true;
}

/**
* ������
*/
void CStage::Initialize(void){
	//�X�e�[�W�̌����̐ݒ�
	m_Light.SetDirection(Vector3(-1, -1, 1));
	m_Light.SetDiffuse(MOF_COLOR_WHITE);
	m_Light.SetAmbient(MOF_COLOR_HWHITE);
	CGraphicsUtilities::SetDirectionalLight(&m_Light);
}

/**
* �X�V
*/
void CStage::Update(void){
}

/**
* �`��
*/
void CStage::Render(void){
	// ���[���h�s��쐬
	CMatrix44 matWorld;
	//�V�����b�V���̕`��
	m_SkyMesh.Render(matWorld);
	// ���b�V���̕`��
	m_Mesh.Render(matWorld);
}

/**
* �f�o�b�O�����`��
*/
void CStage::RenderDebugText(void){
}

/**
* ���
*/
void CStage::Release(void){
	m_Mesh.Release();
	m_SkyMesh.Release();
}