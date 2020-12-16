#pragma once

#include	"Mof.h"
#include	"GameApp.h"

class CWindowProc : public CDefWindowProc {
public:
	CWindowProc();
	virtual ~CWindowProc();
	void SetEditMode(MofWindowHandle hWnd, MofU8 mode, UINT id);
	virtual MofProcResult WindowProc(MofWindowHandle hWnd,MofUInt msg,MofProcParamW wpar,MofProcParamL lpar);
};