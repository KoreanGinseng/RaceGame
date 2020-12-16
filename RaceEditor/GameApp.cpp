/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"

#define BUFF_SIZE (260)

//コースメッシュ
CMeshContainer				gCourceMesh;
//地面当たり判定メッシュ
CMeshContainer				gGroundMesh;

//グリッド表示フラグ
bool						gGridVisible = true;
//当たり判定表示フラグ
bool						gCollisionVisible = false;
//背景色
Vector3						gBGColor(0.0f, 0.0f, 1.0f);

// エディタ編集モード
Flags8					    gEditMode;

//カメラ
CFreeCamera                 gCamera;
//カメラ位置
CVector3					gCPos(0, 0, -5);
//カメラ注視点位置
CVector3					gTPos(0, 0, 0);
//カメラの上方ベクトル
CVector3					gCUp(0, 1, 0);

//光源
CDirectionalLight			gLight;

//プレイヤー最大数
#define                     MAXCHARACTER (6)
//スタート地点配置番号
int                         gStartPosNo = 0;
//スタート地点
CVector3                    gStartPos[MAXCHARACTER];

//設定パス
std::vector<CVector3>       gPath;

/**
 * ダイアログのアイテムにVector3を設定
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
 * ダイアログのアイテムからVector3を取得
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
 * 親ダイアログプロシージャ
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
 * 背景色設定ダイアログプロシージャ
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
 * メッシュ読み込み
 *
 * 引数
 * [in]			hWnd				ウインドウハンドル
 */
bool LoadCourceMesh(HWND hWnd) {
	//ファイル選択ダイアログを表示
	char path[MAX_PATH];
	char Filter[] = "メッシュファイル\0*.mom\0すべてのファイル(*.*)\0*.*\0\0";
	char DefExt[] = "mom";
	bool bMulti;
	if (!CFileDialog::Open(hWnd, CFileDialog::Mode::Open, "メッシュファイルを開く", Filter, DefExt, path, bMulti))
	{
		return false;
	}
	//前のメッシュを解放
	gCourceMesh.Release();
	//選んだファイルを開く
	if (!gCourceMesh.Load(path))
	{
		return false;
	}
	return true;
}

/**
 * メッシュ読み込み
 *
 * 引数
 * [in]			hWnd				ウインドウハンドル
 */
bool LoadGroundMesh(HWND hWnd) {
	//ファイル選択ダイアログを表示
	char path[MAX_PATH];
	char Filter[] = "メッシュファイル\0*.mom\0すべてのファイル(*.*)\0*.*\0\0";
	char DefExt[] = "mom";
	bool bMulti;
	if (!CFileDialog::Open(hWnd, CFileDialog::Mode::Open, "メッシュファイルを開く", Filter, DefExt, path, bMulti))
	{
		return false;
	}
	//前のメッシュを解放
	gGroundMesh.Release();
	//選んだファイルを開く
	if (!gGroundMesh.Load(path))
	{
		return false;
	}
	return true;
}
/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {
	//リソース配置ディレクトリの設定
	CUtilities::SetCurrentDirectory("Resource");

	gEditMode.Set(MODE_CAMERA);

	//カメラの設定
	gCamera.Initialize();

	gCamera
		.SetPosition(gCPos)
		.SetTarget(gTPos)
		.SetUpVector(gCUp)
		.SetNearFar(0.01f, 3000.0f);

	CGraphicsUtilities::SetCamera(gCamera.GetCamera());

	//基本光源の設定
	gLight.SetDirection(Vector3(-1, -1, 1));
	gLight.SetDiffuse(MOF_COLOR_WHITE);
	gLight.SetAmbient(MOF_COLOR_HWHITE);
	CGraphicsUtilities::SetDirectionalLight(&gLight);

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの更新
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void) {
	//キーの更新
	g_pInput->RefreshKey();

	//キー入力でモード変更
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

	//キー入力でカメラ操作
	if (gEditMode.Check(MODE_CAMERA))
	{
		gCamera.Update();
	}
	else if (gEditMode.Check(MODE_START))
	{
		//マウス左クリックで接触判定
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			//マウス座標を３D空間上のレイに変換する
			Vector2 mp;
			g_pInput->GetMousePos(mp);
			Vector3 cv;
			gCamera.GetCamera()->ScreenToWorld(mp, cv);
			//カメラ位置からクリック方向のレイ
			CRay3D cray(gCamera.GetPosition(), cv);
			//配置済みのスタート地点のクリック判定
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
				//レイと地面で当たり判定
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
		//マウス左クリックで接触判定
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			//マウス座標を３D空間上のレイに変換する
			Vector2 mp;
			g_pInput->GetMousePos(mp);
			Vector3 cv;
			gCamera.GetCamera()->ScreenToWorld(mp, cv);
			//カメラ位置からクリック方向のレイ
			CRay3D cray(gCamera.GetPosition(), cv);
			//レイと地面で当たり判定
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
		@brief			アプリケーションの描画
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void) {
	//描画開始
	g_pGraphics->RenderStart();
	//画面のクリア
	g_pGraphics->ClearTarget(gBGColor.x, gBGColor.y, gBGColor.z, 0.0f, 1.0f, 0);

	//深度バッファを有効にする
	g_pGraphics->SetDepthEnable(TRUE);

	//グリッドを描画する
	if (gGridVisible)
	{
		CGraphicsUtilities::RenderGrid(2, 20, MOF_COLOR_WHITE, PLANEAXIS_ALL);
	}

	// ワールド行列作成
	CMatrix44 matWorld;
	// メッシュの描画
	gCourceMesh.Render(matWorld);
	if (gCollisionVisible)
	{
		gGroundMesh.Render(matWorld);
	}

	//開始地点描画
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

	//パス地点描画
	for (std::vector<CVector3>::iterator it = gPath.begin(); it != gPath.end(); ++it)
	{
		HSV hsv(CMyTime::Time() * 180.0f, 255, 255);
		Vector4 col = CHSVUtilities::ToVector4(hsv);
		col.w = 0.5f;
		CSphere gsp(*it, 3.0f);
		CGraphicsUtilities::RenderSphere(gsp, col);
		//次の点と線でつなぐ
		std::vector<CVector3>::iterator nit = it + 1;
		if (nit != gPath.end())
		{
			CGraphicsUtilities::RenderLine(*it, *nit, CHSVUtilities::ToRGB(hsv));
		}
	}

	//深度バッファを無効にする
	g_pGraphics->SetDepthEnable(FALSE);
	CGraphicsUtilities::RenderString(4, 4, MOF_COLOR_WHITE, "F1: カメラ操作, F2: 開始地点設定, F3: パス設定");

	//描画の終了
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの解放
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Release(void) {
	gCourceMesh.Release();
	gGroundMesh.Release();
	gPath.clear();
	return TRUE;
}