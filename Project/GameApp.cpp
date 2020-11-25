/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	"Player.h"
#include	"Stage.h"

//�L�����N�^�̐錾
CPlayer					gPlayer;
//�X�e�[�W�̐錾
CStage					gStage;
// �f�o�b�O�\���t���O
bool					gbDebug = false;
// �J��������t���O
bool					gbCamera = false;

//�J����
CCamera					gCamera;
//�J�����ʒu
CVector3				gCPos(0, 0, -5);
//�J���������_�ʒu
CVector3				gTPos(0, 0, 0);
//�J�����̏���x�N�g��
CVector3				gCUp(0, 1, 0);
/**
 * �J�����X�V
 */
void UpdateCamera(){
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		CVector3 vv = gCPos - gTPos;
		vv.RotationY(0.01f);
		gCPos = gTPos + vv;
		gCamera.LookAt(gCPos, gTPos, Vector3(0, 1, 0));
		gCamera.Update();
	}
	else if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		CVector3 vv = gCPos - gTPos;
		vv.RotationY(-0.01f);
		gCPos = gTPos + vv;
		gCamera.LookAt(gCPos, gTPos, Vector3(0, 1, 0));
		gCamera.Update();
	}
	if (g_pInput->IsKeyHold(MOFKEY_UP))
	{
		CVector3 vv = gCPos - gTPos;
		float d = sqrt(vv.x * vv.x + vv.z * vv.z);
		MofFloat sina = MOF_SIN(-0.01f);
		MofFloat cosa = MOF_COS(-0.01f);
		MofFloat tmpy = vv.y * cosa + d * -sina;
		MofFloat tmpxz = vv.y * sina + d * cosa;
		vv.y = tmpy;
		vv.x = (vv.x / d) * tmpxz;
		vv.z = (vv.z / d) * tmpxz;
		gCPos = gTPos + vv;
		gCamera.LookAt(gCPos, gTPos, Vector3(0, 1, 0));
		gCamera.Update();
	}
	else if (g_pInput->IsKeyHold(MOFKEY_DOWN))
	{
		CVector3 vv = gCPos - gTPos;
		float d = sqrt(vv.x * vv.x + vv.z * vv.z);
		MofFloat sina = MOF_SIN(0.01f);
		MofFloat cosa = MOF_COS(0.01f);
		MofFloat tmpy = vv.y * cosa + d * -sina;
		MofFloat tmpxz = vv.y * sina + d * cosa;
		vv.y = tmpy;
		vv.x = (vv.x / d) * tmpxz;
		vv.z = (vv.z / d) * tmpxz;
		gCPos = gTPos + vv;
		gCamera.LookAt(gCPos, gTPos, Vector3(0, 1, 0));
		gCamera.Update();
	}

	//�}�E�X���͂ŃJ��������
	CVector3 mv;
	g_pInput->GetMouseMove(mv);
	//�z�C�[���ɂ��J�����̃Y�[������
	if (mv.z != 0)
	{
		CVector3 vv = gCPos - gTPos;
		vv *= 1.0f - mv.z * 0.0001f;
		gCPos = gTPos + vv;
		gCamera.LookAt(gCPos, gTPos, Vector3(0, 1, 0));
		gCamera.Update();
	}
	else if (g_pInput->IsMouseKeyHold(2))
	{
		CVector3 vv = gCPos - gTPos;
		vv *= 1.0f + mv.y * 0.01f;
		gCPos = gTPos + vv;
		gCamera.LookAt(gCPos, gTPos, Vector3(0, 1, 0));
		gCamera.Update();
	}
	//���N���b�N�ɂ��J�����ړ�
	if (g_pInput->IsMouseKeyHold(MOFMOUSE_LBUTTON))
	{
		CVector3 sv;
		CVector3 uv;
		CVector3 vv = gTPos - gCPos;
		vv.Normal(vv);
		vv.Cross(gCUp, sv);
		sv.Normal(sv);
		gCPos += sv * mv.x * 0.01f;
		gTPos += sv * mv.x * 0.01f;
		sv.Cross(vv, uv);
		uv.Normal(uv);
		gCPos += uv * mv.y * 0.01f;
		gTPos += uv * mv.y * 0.01f;
		gCamera.LookAt(gCPos, gTPos, Vector3(0, 1, 0));
		gCamera.Update();
	}
	//�E�N���b�N�ɂ��J������]
	if (g_pInput->IsMouseKeyHold(MOFMOUSE_RBUTTON))
	{
		CVector3 vv = gCPos - gTPos;
		vv.RotationY(mv.x * 0.01f);
		float d = sqrt(vv.x * vv.x + vv.z * vv.z);
		MofFloat sina = MOF_SIN(-mv.y * 0.01f);
		MofFloat cosa = MOF_COS(-mv.y * 0.01f);
		MofFloat tmpy = vv.y * cosa + d * -sina;
		MofFloat tmpxz = vv.y * sina + d * cosa;
		vv.y = tmpy;
		vv.x = (vv.x / d) * tmpxz;
		vv.z = (vv.z / d) * tmpxz;
		gCPos = gTPos + vv;
		gCamera.LookAt(gCPos, gTPos, Vector3(0, 1, 0));
		gCamera.Update();
	}
}

/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	//���\�[�X�z�u�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");

	//�J�����̐ݒ�
	gCamera.SetViewPort();
	gCamera.LookAt(gCPos, gTPos, gCUp);
	gCamera.PerspectiveFov(MOF_ToRadian(60.0f), 1024.0f / 768.0f, 0.01f, 2000.0f);
	gCamera.Update();
	CGraphicsUtilities::SetCamera(&gCamera);

	//�L�����N�^�̓ǂݍ���
	CUtilities::SetCurrentDirectory("Chara");
	gPlayer.Load();
	CUtilities::SetCurrentDirectory("../");
	//�X�e�[�W�̓ǂݍ���
	CUtilities::SetCurrentDirectory("Stage");
	gStage.Load();
	CUtilities::SetCurrentDirectory("../");

	//������
	gPlayer.Initialize();
	gStage.Initialize();
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̍X�V
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//�L�[�̍X�V
	g_pInput->RefreshKey();

	//�L�[���͂ŃJ��������
	if (gbCamera)
	{
		UpdateCamera();
	}
	else
	{
		//�L�����N�^�̍X�V
		gPlayer.Update();
	}
	//�X�e�[�W�̍X�V
	gStage.Update();
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		gbCamera = ((gbCamera) ? false : true);
	}

	// �f�o�b�O�\���̐؂�ւ�
	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		gbDebug = ((gbDebug) ? false : true);
	}
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̕`��
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//�`��J�n
	g_pGraphics->RenderStart();
	//��ʂ̃N���A
	g_pGraphics->ClearTarget(0.0f,0.0f,1.0f,0.0f,1.0f,0);

	//�[�x�o�b�t�@��L���ɂ���
	g_pGraphics->SetDepthEnable(TRUE);
	if (gbCamera)
	{
		CGraphicsUtilities::SetCamera(&gCamera);
	}
	else
	{
		//�v���C���[�̃J������L���ɂ���
		gPlayer.SetCameraEnable();
	}

	//�X�e�[�W�̕`��
	gStage.Render();
	//�L�����N�^�̕`��
	gPlayer.Render();
	//�O���b�h��`�悷��
	if (gbDebug)
	{
		CGraphicsUtilities::RenderGrid(2, 100, MOF_COLOR_WHITE, PLANEAXIS_ALL);
	}

	// �[�x�o�b�t�@������
	g_pGraphics->SetDepthEnable(FALSE);

	// 2D�f�o�b�O�`��
	if (gbDebug)
	{
		//FPS�`��
		CGraphicsUtilities::RenderString(10, 10, MOF_COLOR_WHITE, "%d", CUtilities::GetFPS());
		// �v���C���[�̃f�o�b�O�����`��
		gPlayer.RenderDebugText();
	}

	//�`��̏I��
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̉��
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Release(void){
	//�L�����N�^�̉��
	gStage.Release();
	gPlayer.Release();
	return TRUE;
}