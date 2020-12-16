#include	"WindowProc.h"

extern bool   gGridVisible;
extern bool   gCollisionVisible;
extern Flags8 gEditMode;

/**
 * �R���X�g���N�^
 *
 */
CWindowProc::CWindowProc() :
	CDefWindowProc() {
}

/**
 * �f�X�g���N�^
 *
 */
CWindowProc::~CWindowProc() {
}

void CWindowProc::SetEditMode(MofWindowHandle hWnd, MofU8 mode, UINT id)
{
	gEditMode.Reset(MODE_MAX);
	gEditMode.Set(mode);

	HMENU hMenu = GetMenu(hWnd);
	CheckMenuItem(hMenu, ID_EDITCAMERA, ((id == ID_EDITCAMERA) ? MFS_CHECKED : MF_UNCHECKED));
	CheckMenuItem(hMenu, ID_EDITSTART , ((id == ID_EDITSTART ) ? MFS_CHECKED : MF_UNCHECKED));
	CheckMenuItem(hMenu, ID_EDITPATH  , ((id == ID_EDITPATH  ) ? MFS_CHECKED : MF_UNCHECKED));
}

/**
 * �E�C���h�E�v���V�[�W��
 *
 * ����
 * [in]			hWnd				�E�C���h�E�n���h��
 * [in]			msg					���b�Z�[�W
 * [in]			wpar				�p�����[�^�[�P
 * [in]			lpar				�p�����[�^�[�Q
 */
MofProcResult CWindowProc::WindowProc(MofWindowHandle hWnd, MofUInt msg, MofProcParamW wpar, MofProcParamL lpar) {
	//---------------------------
	////���b�Z�[�W����
	//---------------------------
	switch (msg)
	{
	case WM_CREATE:
	{
		//���j���[��ݒ�
		SetMenu(hWnd, LoadMenu(NULL, MAKEINTRESOURCE(IDR_MENU1)));
		int w = 1024 + GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
		int h = 768 + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU);
		SetWindowPos(hWnd, NULL, 0, 0, w, h, SWP_NOZORDER | SWP_NOMOVE);

		// �_�C�A���O�쐬
		HWND hDlg = CreateDialog(CUtilities::GetInstanceHandle(), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)ParentDlgProc);
		RECT rect;
		GetWindowRect(hWnd, &rect);
		SetWindowPos(hDlg, NULL, rect.right, rect.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		ShowWindow(hDlg, SW_SHOW);
		break;
	}
	case WM_COMMAND:
		//���j���[�I��
		switch (LOWORD(wpar))
		{
		case ID_LOADMESH:						//���b�V���ǂݍ���
			LoadCourceMesh(hWnd);
			break;
		case ID_LOADCOLMESH:					//�����蔻�胁�b�V���ǂݍ���
			LoadGroundMesh(hWnd);
			break;

		case ID_QUIT:
			PostQuitMessage(0);					//�I��
			break;

		case ID_GRIDVISIBLE:
		{
			HMENU hMenu = GetMenu(hWnd);
			MENUITEMINFO mii;
			mii.cbSize = sizeof(mii);
			mii.fMask = MIIM_STATE;
			GetMenuItemInfo(hMenu, ID_GRIDVISIBLE, FALSE, &mii);
			gGridVisible = (mii.fState & MFS_CHECKED) == 0;
			mii.fState = gGridVisible ? (mii.fState | MFS_CHECKED) : (mii.fState & ~MFS_CHECKED);
			SetMenuItemInfo(hMenu, ID_GRIDVISIBLE, FALSE, &mii);
		}
		break;
		case ID_COLLISIONVISIBLE:
		{
			HMENU hMenu = GetMenu(hWnd);
			MENUITEMINFO mii;
			mii.cbSize = sizeof(mii);
			mii.fMask = MIIM_STATE;
			GetMenuItemInfo(hMenu, ID_COLLISIONVISIBLE, FALSE, &mii);
			gCollisionVisible = (mii.fState & MFS_CHECKED) == 0;
			mii.fState = gCollisionVisible ? (mii.fState | MFS_CHECKED) : (mii.fState & ~MFS_CHECKED);
			SetMenuItemInfo(hMenu, ID_COLLISIONVISIBLE, FALSE, &mii);
		}
		break;
		case ID_BGCOLOR:
			DialogBox(CUtilities::GetInstanceHandle(), MAKEINTRESOURCE(IDD_BGCOLOR), hWnd, (DLGPROC)BGColorDlgProc);
			break;

		case ID_EDITCAMERA:
			SetEditMode(hWnd, MODE_CAMERA, ID_EDITCAMERA);
			break;
		case ID_EDITSTART:
			SetEditMode(hWnd, MODE_START, ID_EDITSTART);
			break;
		case ID_EDITPATH:
			SetEditMode(hWnd, MODE_PATH, ID_EDITPATH);
			break;

		}
		break;
	default:									//�f�t�H���g����
		return CDefWindowProc::WindowProc(hWnd, msg, wpar, lpar);
	}
	return DefWindowProc(hWnd, msg, wpar, lpar);
}