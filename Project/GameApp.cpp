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
#include    "Cpu.h"

//�L�����N�^�̐錾
CCharacter*  			gCharacter[MAXCHARACTER] = 
{
	new CPlayer(),
	new CCpu(),
	new CCpu(),
	new CCpu(),
	new CCpu(),
	new CCpu(),
};
//�X�e�[�W�̐錾
CStage					gStage;
// �f�o�b�O�\���t���O
bool					gbDebug = false;
// �J��������t���O
bool					gbCamera = false;

//�J����
CFreeCamera				gFreeCamera;

bool LoadCharacter(void)
{
	if (!CMeshAsset::Load("Neko", "Neko.mom"))
	{
		return false;
	}
	if (!CMeshAsset::Load("Ball01", "Ball01.mom"))
	{
		return false;
	}
	if (!CMeshAsset::Load("Shadow", "Shadow.mom"))
	{
		return false;
	}
	return true;
}

bool LoadStage(void)
{
	if (!CMeshAsset::Load("Course1", "Course1.mom"))
	{
		return false;
	}
	if (!CMeshAsset::Load("Course1_sky", "Course1_sky.mom"))
	{
		return false;
	}
	if (!CMeshAsset::Load("Course1WallHit", "Course1WallHit.mom"))
	{
		return false;
	}
	if (!CMeshAsset::Load("Course1GroundHit", "Course1GroundHit.mom"))
	{
		return false;
	}
	return true;
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
	gFreeCamera.Initialize();
	CGraphicsUtilities::SetCamera(gFreeCamera.GetCamera());

	//�L�����N�^�̓ǂݍ���
	CUtilities::SetCurrentDirectory("Chara");
	if (!LoadCharacter())
	{
		return FALSE;
	}
	for (int i = 0; i < MAXCHARACTER; i++)
	{
		gCharacter[i]->Load();
	}
	CUtilities::SetCurrentDirectory("../");
	//�X�e�[�W�̓ǂݍ���
	CUtilities::SetCurrentDirectory("Stage");
	if (!LoadStage())
	{
		return FALSE;
	}
	gStage.Load();
	CUtilities::SetCurrentDirectory("../");

	//������
	for (int i = 0; i < MAXCHARACTER; i++)
	{
		gCharacter[i]->Initialize(gStage.GetStartPos(i), gStage.GetPath());
	}
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
		gFreeCamera.Update();
	}
	else
	{
		//�L�����N�^�̍X�V
		for (int i = 0; i < MAXCHARACTER; i++)
		{
			gCharacter[i]->Update(gStage.GetCollisionGroundMesh(), gStage.GetCollisionWallMesh(),
				gStage.GetPath(), gStage.GetPathCount());
			//�p�X�̔���
			gCharacter[i]->CalculatePathNo(gStage.GetPath(), gStage.GetPathCount());
		}
		gCharacter[0]->UpdateRank(&(gCharacter[1]), MAXCHARACTER - 1, gStage.GetPath(), gStage.GetPathCount());
	}
	
	//�X�e�[�W�̍X�V
	gStage.Update();

	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		gbCamera = !gbCamera;
	}

	// �f�o�b�O�\���̐؂�ւ�
	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		gbDebug = !gbDebug;
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
		CGraphicsUtilities::SetCamera(gFreeCamera.GetCamera());
	}
	else
	{
		//�v���C���[�̃J������L���ɂ���
		gCharacter[0]->SetCameraEnable();
	}

	//�X�e�[�W�̕`��
	gStage.Render();

	//�L�����N�^�̕`��
	for (int i = 0; i < MAXCHARACTER; i++)
	{
		gCharacter[i]->Render();
	}
	
	//�O���b�h��`�悷��
	if (gbDebug)
	{
		CGraphicsUtilities::RenderGrid(2, 100, MOF_COLOR_WHITE, PLANEAXIS_ALL);
		gStage.RenderDebug();
	}

	// �[�x�o�b�t�@������
	g_pGraphics->SetDepthEnable(FALSE);

	// 2D�f�o�b�O�`��
	if (gbDebug)
	{
		//FPS�`��
		CGraphicsUtilities::RenderString(10, 10, MOF_COLOR_WHITE, "%d", CUtilities::GetFPS());
		// �v���C���[�̃f�o�b�O�����`��
		gCharacter[0]->RenderDebugText();
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

	for (int i = 0; i < MAXCHARACTER; i++)
	{
		MOF_SAFE_DELETE(gCharacter[i]);
	}

	CMeshAsset::Release();
	return TRUE;
}