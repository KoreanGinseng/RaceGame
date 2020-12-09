#include "MyCamera.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pCam">�������f�[�^�|�C���^</param>
	/// <created>���̂���,2020/11/17</created>
	/// <changed>���̂���,2020/11/23</changed>
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