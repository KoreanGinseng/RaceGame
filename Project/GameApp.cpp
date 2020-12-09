/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	"Player.h"
#include	"Stage.h"
#include    "Cpu.h"

//キャラクタの宣言
CCharacter*  			gCharacter[MAXCHARACTER] = 
{
	new CPlayer(),
	new CCpu(),
	new CCpu(),
	new CCpu(),
	new CCpu(),
	new CCpu(),
};
//ステージの宣言
CStage					gStage;
// デバッグ表示フラグ
bool					gbDebug = false;
// カメラ操作フラグ
bool					gbCamera = false;

//カメラ
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
		@brief			アプリケーションの初期化
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	//リソース配置ディレクトリの設定
	CUtilities::SetCurrentDirectory("Resource");

	//カメラの設定
	gFreeCamera.Initialize();
	CGraphicsUtilities::SetCamera(gFreeCamera.GetCamera());

	//キャラクタの読み込み
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
	//ステージの読み込み
	CUtilities::SetCurrentDirectory("Stage");
	if (!LoadStage())
	{
		return FALSE;
	}
	gStage.Load();
	CUtilities::SetCurrentDirectory("../");

	//初期化
	for (int i = 0; i < MAXCHARACTER; i++)
	{
		gCharacter[i]->Initialize(gStage.GetStartPos(i), gStage.GetPath());
	}
	gStage.Initialize();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの更新
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//キーの更新
	g_pInput->RefreshKey();

	//キー入力でカメラ操作
	if (gbCamera)
	{
		gFreeCamera.Update();
	}
	else
	{
		//キャラクタの更新
		for (int i = 0; i < MAXCHARACTER; i++)
		{
			gCharacter[i]->Update(gStage.GetCollisionGroundMesh(), gStage.GetCollisionWallMesh(),
				gStage.GetPath(), gStage.GetPathCount());
			//パスの判定
			gCharacter[i]->CalculatePathNo(gStage.GetPath(), gStage.GetPathCount());
		}
		gCharacter[0]->UpdateRank(&(gCharacter[1]), MAXCHARACTER - 1, gStage.GetPath(), gStage.GetPathCount());
	}
	
	//ステージの更新
	gStage.Update();

	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		gbCamera = !gbCamera;
	}

	// デバッグ表示の切り替え
	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		gbDebug = !gbDebug;
	}
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの描画
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//描画開始
	g_pGraphics->RenderStart();
	//画面のクリア
	g_pGraphics->ClearTarget(0.0f,0.0f,1.0f,0.0f,1.0f,0);

	//深度バッファを有効にする
	g_pGraphics->SetDepthEnable(TRUE);
	if (gbCamera)
	{
		CGraphicsUtilities::SetCamera(gFreeCamera.GetCamera());
	}
	else
	{
		//プレイヤーのカメラを有効にする
		gCharacter[0]->SetCameraEnable();
	}

	//ステージの描画
	gStage.Render();

	//キャラクタの描画
	for (int i = 0; i < MAXCHARACTER; i++)
	{
		gCharacter[i]->Render();
	}
	
	//グリッドを描画する
	if (gbDebug)
	{
		CGraphicsUtilities::RenderGrid(2, 100, MOF_COLOR_WHITE, PLANEAXIS_ALL);
		gStage.RenderDebug();
	}

	// 深度バッファ無効化
	g_pGraphics->SetDepthEnable(FALSE);

	// 2Dデバッグ描画
	if (gbDebug)
	{
		//FPS描画
		CGraphicsUtilities::RenderString(10, 10, MOF_COLOR_WHITE, "%d", CUtilities::GetFPS());
		// プレイヤーのデバッグ文字描画
		gCharacter[0]->RenderDebugText();
	}

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
MofBool CGameApp::Release(void){
	//キャラクタの解放
	gStage.Release();

	for (int i = 0; i < MAXCHARACTER; i++)
	{
		MOF_SAFE_DELETE(gCharacter[i]);
	}

	CMeshAsset::Release();
	return TRUE;
}