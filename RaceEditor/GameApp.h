/*************************************************************************//*!
					
					@file	GameApp.h
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

#pragma once

//INCLUDE
#include	"MofSip.h"
#include	"Resource.h"

//�G�f�B�^�p�֐��v���g�^�C�v�錾
LRESULT CALLBACK ParentDlgProc(HWND hWnd, UINT msg, WPARAM wpar, LPARAM lpar);
LRESULT CALLBACK BGColorDlgProc(HWND hWnd, UINT msg, WPARAM wpar, LPARAM lpar);
bool LoadCourceMesh(HWND hWnd);
bool LoadGroundMesh(HWND hWnd);

//�G�f�B�^����
enum EDITMODE : MofU8
{
	MODE_CAMERA = (1 << 0),
	MODE_START  = (1 << 1),
	MODE_PATH   = (1 << 2),

	MODE_MAX    = 0xFF,
};

/*******************************//*!
@brief	��{�Q�[���A�v���B

@author	�_�c�@��
*//********************************/
class CGameApp : public CSingleGameApplication {
public:
	/*************************************************************************//*!
			@brief			�R���X�g���N�^
			@param			None

			@return			None
	*//**************************************************************************/
	CGameApp(){}
	/*************************************************************************//*!
			@brief			�f�X�g���N�^
			@param			None

			@return			None
	*//**************************************************************************/
	virtual ~CGameApp(){	Release();	}
	/*************************************************************************//*!
			@brief			�A�v���P�[�V�����̏�����
			@param			None
				
			@return			TRUE		����<br>
							����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
	*//**************************************************************************/
	virtual MofBool Initialize(void);
	/*************************************************************************//*!
			@brief			�A�v���P�[�V�����̍X�V
			@param			None
				
			@return			TRUE		����<br>
							����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
	*//**************************************************************************/
	virtual MofBool Update(void);
	/*************************************************************************//*!
			@brief			�A�v���P�[�V�����̕`��
			@param			None
				
			@return			TRUE		����<br>
							����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
	*//**************************************************************************/
	virtual MofBool Render(void);
	/*************************************************************************//*!
			@brief			�A�v���P�[�V�����̉��
			@param			None
				
			@return			TRUE		����<br>
							����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
	*//**************************************************************************/
	virtual MofBool Release(void);
};
