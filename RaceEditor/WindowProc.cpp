#include	"WindowProc.h"

extern bool   gGridVisible;
extern bool   gCollisionVisible;
extern Flags8 gEditMode;

/**
 * コンストラクタ
 *
 */
CWindowProc::CWindowProc() :
	CDefWindowProc() {
}

/**
 * デストラクタ
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
 * ウインドウプロシージャ
 *
 * 引数
 * [in]			hWnd				ウインドウハンドル
 * [in]			msg					メッセージ
 * [in]			wpar				パラメーター１
 * [in]			lpar				パラメーター２
 */
MofProcResult CWindowProc::WindowProc(MofWindowHandle hWnd, MofUInt msg, MofProcParamW wpar, MofProcParamL lpar) {
	//---------------------------
	////メッセージ処理
	//---------------------------
	switch (msg)
	{
	case WM_CREATE:
	{
		//メニューを設定
		SetMenu(hWnd, LoadMenu(NULL, MAKEINTRESOURCE(IDR_MENU1)));
		int w = 1024 + GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
		int h = 768 + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU);
		SetWindowPos(hWnd, NULL, 0, 0, w, h, SWP_NOZORDER | SWP_NOMOVE);

		// ダイアログ作成
		HWND hDlg = CreateDialog(CUtilities::GetInstanceHandle(), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)ParentDlgProc);
		RECT rect;
		GetWindowRect(hWnd, &rect);
		SetWindowPos(hDlg, NULL, rect.right, rect.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		ShowWindow(hDlg, SW_SHOW);
		break;
	}
	case WM_COMMAND:
		//メニュー選択
		switch (LOWORD(wpar))
		{
		case ID_LOADMESH:						//メッシュ読み込み
			LoadCourceMesh(hWnd);
			break;
		case ID_LOADCOLMESH:					//当たり判定メッシュ読み込み
			LoadGroundMesh(hWnd);
			break;

		case ID_QUIT:
			PostQuitMessage(0);					//終了
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
	default:									//デフォルト処理
		return CDefWindowProc::WindowProc(hWnd, msg, wpar, lpar);
	}
	return DefWindowProc(hWnd, msg, wpar, lpar);
}