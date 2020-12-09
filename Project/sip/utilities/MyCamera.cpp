#include "MyCamera.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pCam">初期化データポインタ</param>
	/// <created>いのうえ,2020/11/17</created>
	/// <changed>いのうえ,2020/11/23</changed>
	// ********************************************************************************
	void CMyCamera::Initialize(CMyCamera* pCam)
	{
		if (pCam == nullptr)
		{
			*this = CMyCamera();
		}
		UpdatePerspectiveFov();
		UpdateCamera();
	}
}