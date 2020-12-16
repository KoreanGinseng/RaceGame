/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"

#define BUFF_SIZE (260)

//�R�[�X���b�V��
CMeshContainer				gCourceMesh;
//�n�ʓ����蔻�胁�b�V��
CMeshContainer				gGroundMesh;

//�O���b�h�\���t���O
bool						gGridVisible = true;
//�����蔻��\���t���O
bool						gCollisionVisible = false;
//�w�i�F
Vector3						gBGColor(0.0f, 0.0f, 1.0f);

// �G�f�B�^�ҏW���[�h
Flags8					    gEditMode;

//�J����
CFreeCamera                 gCamera;
//�J�����ʒu
CVector3					gCPos(0, 0, -5);
//�J���������_�ʒu
CVector3					gTPos(0, 0, 0);
//�J�����̏���x�N�g��
CVector3					gCUp(0, 1, 0);

//����
CDirectionalLight			gLight;

//�v���C���[�ő吔
#define                     MAXCHARACTER (6)
//�X�^�[�g�n�_�z�u�ԍ�
int                         gStartPosNo = 0;
//�X�^�[�g�n�_
CVector3                    gStartPos[MAXCHARACTER];

//�ݒ�p�X
std::vector<CVector3>       gPath;

/**
 * �_�C�A���O�̃A�C�e����Vector3��ݒ�
 */
void SetDlgItemVector3(HWND hWnd, int idX, int idY, int idZ, const Vector3* vec) {
	char str[BUFF_SIZE];
	sprintf_s(str, "%f", vec->x);
	SetDlgItemText(hWnd, idX, str);
	sprintf_s(str, "%f", vec->y);
	SetDlgItemText(hWnd, idY, str);
	sprintf_s(str, "%f", vec->z);
	SetDlgItemText(hWnd, idZ, str);
}
/**
 * �_�C�A���O�̃A�C�e������Vector3���擾
 */
void GetDlgItemVector3(HWND hWnd, int idX, int idY, int idZ, Vector3* vec) {
	char str[BUFF_SIZE];
	GetDlgItemText(hWnd, idX, str, BUFF_SIZE);
	vec->x = (float)atof(str);
	GetDlgItemText(hWnd, idY, str, BUFF_SIZE);
	vec->y = (float)atof(str);
	GetDlgItemText(hWnd, idZ, str, BUFF_SIZE);
	vec->z = (float)atof(str);
}

/**
 * �e�_�C�A���O�v���V�[�W��
 */
LRESULT CALLBACK ParentDlgProc(HWND hWnd, UINT msg, WPARAM wpar, LPARAM lpar) {
	switch (msg)
	{
	case WM_INITDIALOG:
		break;
	default:
		return 0;
	}
	return TRUE;
}

/**
 * �w�i�F�ݒ�_�C�A���O�v���V�[�W��
 */
LRESULT CALLBACK BGColorDlgProc(HWND hWnd, UINT msg, WPARAM wpar, LPARAM lpar) {
	switch (msg)
	{
	case WM_INITDIALOG:
		SetDlgItemVector3(hWnd, IDC_BGCOLOR_R, IDC_BGCOLOR_G, IDC_BGCOLOR_B, &gBGColor);
		break;
	case WM_COMMAND:
		switch (LOWORD(wpar))
		{
		case IDOK:
			GetDlgItemVector3(hWnd, IDC_BGCOLOR_R, IDC_BGCOLOR_G, IDC_BGCOLOR_B, &gBGColor);
			EndDialog(hWnd, 0);
			break;
		case IDCANCEL:
			EndDialog(hWnd, 0);
			break;
		default:
			return FALSE;
		}
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

/**
 * ���b�V���ǂݍ���
 *
 * ����
 * [in]			hWnd				�E�C���h�E�n���h��
 */
bool LoadCourceMesh(HWND hWnd) {
	//�t�@�C���I���_�C�A���O��\��
	char path[MAX_PATH];
	char Filter[] = "���b�V���t�@�C��\0*.mom\0���ׂẴt�@�C��(*.*)\0*.*\0\0";
	char DefExt[] = "mom";
	bool bMulti;
	if (!CFileDialog::Open(hWnd, CFileDialog::Mode::Open, "���b�V���t�@�C�����J��", Filter, DefExt, path, bMulti))
	{
		return false;
	}
	//�O�̃��b�V�������
	gCourceMesh.Release();
	//�I�񂾃t�@�C�����J��
	if (!gCourceMesh.Load(path))
	{
		return false;
	}
	return true;
}

/**
 * ���b�V���ǂݍ���
 *
 * ����
 * [in]			hWnd				�E�C���h�E�n���h��
 */
bool LoadGroundMesh(HWND hWnd) {
	//�t�@�C���I���_�C�A���O��\��
	char path[MAX_PATH];
	char Filter[] = "���b�V���t�@�C��\0*.mom\0���ׂẴt�@�C��(*.*)\0*.*\0\0";
	char DefExt[] = "mom";
	bool bMulti;
	if (!CFileDialog::Open(hWnd, CFileDialog::Mode::Open, "���b�V���t�@�C�����J��", Filter, DefExt, path, bMulti))
	{
		return false;
	}
	//�O�̃��b�V�������
	gGroundMesh.Release();
	//�I�񂾃t�@�C�����J��
	if (!gGroundMesh.Load(path))
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
MofBool CGameApp::Initialize(void) {
	//���\�[�X�z�u�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");

	gEditMode.Set(MODE_CAMERA);

	//�J�����̐ݒ�
	gCamera.Initialize();

	gCamera
		.SetPosition(gCPos)
		.SetTarget(gTPos)
		.SetUpVector(gCUp)
		.SetNearFar(0.01f, 3000.0f);

	CGraphicsUtilities::SetCamera(gCamera.GetCamera());

	//��{�����̐ݒ�
	gLight.SetDirection(Vector3(-1, -1, 1));
	gLight.SetDiffuse(MOF_COLOR_WHITE);
	gLight.SetAmbient(MOF_COLOR_HWHITE);
	CGraphicsUtilities::SetDirectionalLight(&gLight);

	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̍X�V
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void) {
	//�L�[�̍X�V
	g_pInput->RefreshKey();

	//�L�[���͂Ń��[�h�ύX
	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		SendMessage(g_pFramework->GetWindow()->GetWindowHandle(), WM_COMMAND, ID_EDITCAMERA, 0);
	}
	if (g_pInput->IsKeyPush(MOFKEY_F2))
	{
		SendMessage(g_pFramework->GetWindow()->GetWindowHandle(), WM_COMMAND, ID_EDITSTART, 0);
	}
	if (g_pInput->IsKeyPush(MOFKEY_F3))
	{
		SendMessage(g_pFramework->GetWindow()->GetWindowHandle(), WM_COMMAND, ID_EDITPATH, 0);
	}

	//�L�[���͂ŃJ��������
	if (gEditMode.Check(MODE_CAMERA))
	{
		gCamera.Update();
	}
	else if (gEditMode.Check(MODE_START))
	{
		//�}�E�X���N���b�N�ŐڐG����
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			//�}�E�X���W���RD��ԏ�̃��C�ɕϊ�����
			Vector2 mp;
			g_pInput->GetMousePos(mp);
			Vector3 cv;
			gCamera.GetCamera()->ScreenToWorld(mp, cv);
			//�J�����ʒu����N���b�N�����̃��C
			CRay3D cray(gCamera.GetPosition(), cv);
			//�z�u�ς݂̃X�^�[�g�n�_�̃N���b�N����
			bool bsphit = false;
			float sphit = 0.0f;
			for (int i = 0; i < MAXCHARACTER; i++)
			{
				CSphere gsp(gStartPos[i], 3.0f);
				if (cray.CollisionSphere(gsp, sphit))
				{
					gStartPosNo = i;
					bsphit = true;
					break;
				}
			}
			if (!bsphit)
			{
				//���C�ƒn�ʂœ����蔻��
				COLLISIONOUTGEOMETRY gout;
				if (cray.CollisionMesh(&gGroundMesh, gout))
				{
					gStartPos[gStartPosNo++] = cray.Position + cray.Direction * gout.d;
					if (gStartPosNo >= MAXCHARACTER)
					{
						gStartPosNo = 0;
					}
				}
			}
		}
	}
	else if (gEditMode.Check(MODE_PATH))
	{
		//�}�E�X���N���b�N�ŐڐG����
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			//�}�E�X���W���RD��ԏ�̃��C�ɕϊ�����
			Vector2 mp;
			g_pInput->GetMousePos(mp);
			Vector3 cv;
			gCamera.GetCamera()->ScreenToWorld(mp, cv);
			//�J�����ʒu����N���b�N�����̃��C
			CRay3D cray(gCamera.GetPosition(), cv);
			//���C�ƒn�ʂœ����蔻��
			COLLISIONOUTGEOMETRY gout;
			if (cray.CollisionMesh(&gGroundMesh, gout))
			{
				CVector3 pos = cray.Position + cray.Direction * gout.d;
				gPath.push_back(pos);
			}
		}
	}

	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̕`��
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void) {
	//�`��J�n
	g_pGraphics->RenderStart();
	//��ʂ̃N���A
	g_pGraphics->ClearTarget(gBGColor.x, gBGColor.y, gBGColor.z, 0.0f, 1.0f, 0);

	//�[�x�o�b�t�@��L���ɂ���
	g_pGraphics->SetDepthEnable(TRUE);

	//�O���b�h��`�悷��
	if (gGridVisible)
	{
		CGraphicsUtilities::RenderGrid(2, 20, MOF_COLOR_WHITE, PLANEAXIS_ALL);
	}

	// ���[���h�s��쐬
	CMatrix44 matWorld;
	// ���b�V���̕`��
	gCourceMesh.Render(matWorld);
	if (gCollisionVisible)
	{
		gGroundMesh.Render(matWorld);
	}

	//�J�n�n�_�`��
	for (int i = 0; i < MAXCHARACTER; i++)
	{
		CSphere gsp(gStartPos[i], 3.0f);

		HSV hsv(CMyTime::Time() * 60.0f, 255, 255);
		Vector4 col = CHSVUtilities::ToVector4(hsv);
		col.w = 0.5f;

		if (i == gStartPosNo && gEditMode.Check(MODE_START))
		{
			CGraphicsUtilities::RenderLineSphere(gsp, col);
		}
		else
		{
			CGraphicsUtilities::RenderSphere(gsp, col);
		}
	}

	//�p�X�n�_�`��
	for (std::vector<CVector3>::iterator it = gPath.begin(); it != gPath.end(); ++it)
	{
		HSV hsv(CMyTime::Time() * 180.0f, 255, 255);
		Vector4 col = CHSVUtilities::ToVector4(hsv);
		col.w = 0.5f;
		CSphere gsp(*it, 3.0f);
		CGraphicsUtilities::RenderSphere(gsp, col);
		//���̓_�Ɛ��łȂ�
		std::vector<CVector3>::iterator nit = it + 1;
		if (nit != gPath.end())
		{
			CGraphicsUtilities::RenderLine(*it, *nit, CHSVUtilities::ToRGB(hsv));
		}
	}

	//�[�x�o�b�t�@�𖳌��ɂ���
	g_pGraphics->SetDepthEnable(FALSE);
	CGraphicsUtilities::RenderString(4, 4, MOF_COLOR_WHITE, "F1: �J��������, F2: �J�n�n�_�ݒ�, F3: �p�X�ݒ�");

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
MofBool CGameApp::Release(void) {
	gCourceMesh.Release();
	gGroundMesh.Release();
	gPath.clear();
	return TRUE;
}