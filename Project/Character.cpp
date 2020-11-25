#include	"Character.h"

/**
 * �R���X�g���N�^
 */
CCharacter::CCharacter() :
m_Mesh() ,
m_pMotion(NULL) ,
m_Pos() ,
m_Move() ,
m_Angle() ,
m_Camera() ,
m_bAccele(false),
m_bBrake(false) {
}

/**
 * �f�X�g���N�^
 */
CCharacter::~CCharacter(){
}

/**
 * �ǂݍ���
 */
bool CCharacter::Load(void){
	// ���b�V���̓ǂݍ���
	if(!m_Mesh.Load("Neko.mom"))
	{
		return false;
	}
	m_pMotion = m_Mesh.CreateMotionController();
	return true;
}

/**
 * ������
 */
void CCharacter::Initialize(void){
	m_Pos = Vector3(0.0f,0.0f,0.0f);
	m_pMotion->ChangeMotionByName("Stop_Ball", 1.0f, TRUE);

	//�J�����̐ݒ�
	m_Camera.SetViewPort();
	m_Camera.PerspectiveFov(MOF_ToRadian(60.0f), 1024.0f / 768.0f, 0.01f, 2000.0f);
	UpdateCamera();
}

/**
 * �X�V
 */
void CCharacter::Update(void){
	//�ړ��X�V
	UpdateMove();

	//���W�X�V
	m_Pos += m_Move;

	//�A�j���[�V�����̎��Ԃ�i�߂�
	m_pMotion->AddTimer(GAMEFRAMETIME);

	//�J�����X�V
	UpdateCamera();
}

/**
 * �ړ��X�V
 */
void CCharacter::UpdateMove(void){
	//�u���[�L

	//�A�N�Z��

	//���͂Ȃ��̏ꍇ

}

/**
 * �J�����X�V
 */
void CCharacter::UpdateCamera(){
	//�J�����̐ݒ�
	CVector3 cpos = m_Pos;
	CVector3 tpos = m_Pos;
	CVector3 fvec(0, 0, -1);
	fvec.RotationY(m_Angle.y);
	cpos.y += 2.0f;
	cpos -= fvec * 5.0f;
	tpos.y += 2.0f;
	m_Camera.LookAt(cpos, tpos, CVector3(0, 1, 0));
	m_Camera.Update();
}

/**
 * �J������L���ɂ���
 */
void CCharacter::SetCameraEnable(){
	CGraphicsUtilities::SetCamera(&m_Camera);
}

/**
 * �`��
 */
void CCharacter::Render(void){
	// ���[���h�s��쐬
	CMatrix44 matWorld;
	matWorld.RotationZXY(m_Angle);
	matWorld.SetTranslation(m_Pos);
	//�A�j���[�V�����Ƀ��[���h�}�g���N�X��K�p
	m_pMotion->RefreshBoneMatrix(matWorld);
	// ���b�V���̕`��
	m_Mesh.Render(m_pMotion);
}

/**
 * �f�o�b�O�����`��
 */
void CCharacter::RenderDebugText(void){
	// �ʒu�̕`��
	CGraphicsUtilities::RenderString(10,40,MOF_COLOR_WHITE,
			"�v���C���[�ʒu X : %.1f , Y : %.1f , Z : %.1f",m_Pos.x,m_Pos.y,m_Pos.z);
}

/**
 * ���
 */
void CCharacter::Release(void){
	MOF_SAFE_DELETE(m_pMotion);
	m_Mesh.Release();
}