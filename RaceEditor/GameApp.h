/*************************************************************************//*!
					
					@file	GameApp.h
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

#pragma once

//INCLUDE
#include	"MofSip.h"
#include	"Resource.h"

//エディタ用関数プロトタイプ宣言
LRESULT CALLBACK ParentDlgProc(HWND hWnd, UINT msg, WPARAM wpar, LPARAM lpar);
LRESULT CALLBACK BGColorDlgProc(HWND hWnd, UINT msg, WPARAM wpar, LPARAM lpar);
bool LoadCourceMesh(HWND hWnd);
bool LoadGroundMesh(HWND hWnd);

//エディタ操作
enum EDITMODE : MofU8
{
	MODE_CAMERA = (1 << 0),
	MODE_START  = (1 << 1),
	MODE_PATH   = (1 << 2),

	MODE_MAX    = 0xFF,
};

/*******************************//*!
@brief	基本ゲームアプリ。

@author	濱田　享
*//********************************/
class CGameApp : public CSingleGameApplication {
public:
	/*************************************************************************//*!
			@brief			コンストラクタ
			@param			None

			@return			None
	*//**************************************************************************/
	CGameApp(){}
	/*************************************************************************//*!
			@brief			デストラクタ
			@param			None

			@return			None
	*//**************************************************************************/
	virtual ~CGameApp(){	Release();	}
	/*************************************************************************//*!
			@brief			アプリケーションの初期化
			@param			None
				
			@return			TRUE		成功<br>
							それ以外	失敗、エラーコードが戻り値となる
	*//**************************************************************************/
	virtual MofBool Initialize(void);
	/*************************************************************************//*!
			@brief			アプリケーションの更新
			@param			None
				
			@return			TRUE		成功<br>
							それ以外	失敗、エラーコードが戻り値となる
	*//**************************************************************************/
	virtual MofBool Update(void);
	/*************************************************************************//*!
			@brief			アプリケーションの描画
			@param			None
				
			@return			TRUE		成功<br>
							それ以外	失敗、エラーコードが戻り値となる
	*//**************************************************************************/
	virtual MofBool Render(void);
	/*************************************************************************//*!
			@brief			アプリケーションの解放
			@param			None
				
			@return			TRUE		成功<br>
							それ以外	失敗、エラーコードが戻り値となる
	*//**************************************************************************/
	virtual MofBool Release(void);
};
