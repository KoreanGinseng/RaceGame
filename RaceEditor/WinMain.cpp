#include	"GameApp.h"
#include	"WindowProc.h"

int WINAPI _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	sip::LPSipFrameworkThread pSipThread = new sip::CSipFrameworkThread();
	Mof::LPFramework pFrame = new Mof::CDX11GameFramework(); 
	Mof::WINDOWSGAMEFRAMEWORKINITIALIZEINFO Info;
	Info.pApplication = new CGameApp();
	Info.Flag = MOF_FRAMEWORK_GRAPHICSINITIALIZE | MOF_FRAMEWORK_INPUTINITIALIZE | MOF_FRAMEWORK_APPLICATIONINITIALIZE;
	
	//ウインドウプロシージャーの設定
	Info.WindowCreateInfo.pProc = new CWindowProc();
	
	if ( pFrame->Initialize(&Info) )
	{
		pFrame->Run();
	}
	
	MOF_SAFE_DELETE(pFrame);
	MOF_SAFE_DELETE(pSipThread);
	return 0;
}