#include "FreeCamera.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// �X�V
	/// </summary>
	/// <created>���̂���,2020/11/23</created>
	/// <changed>���̂���,2020/11/23</changed>
	// ********************************************************************************
	void CFreeCamera::Update(void)
	{
		Vector3 view{ GetPosition() };
		Vector3 target{ GetTarget() };

		bool bMove = false;

		if (g_pInput->IsKeyHold(MOFKEY_LEFT))
		{
			CVector3 vv = view - target;
			vv.RotationY(0.01f);
			view = target + vv;
			bMove = true;
		}
		else if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
		{
			CVector3 vv = view - target;
			vv.RotationY(-0.01f);
			view = target + vv;
			bMove = true;
		}
		if (g_pInput->IsKeyHold(MOFKEY_UP))
		{
			CVector3 vv = view - target;
			float d = sqrt(vv.x * vv.x + vv.z * vv.z);
			MofFloat sina = MOF_SIN(-0.01f);
			MofFloat cosa = MOF_COS(-0.01f);
			MofFloat tmpy = vv.y * cosa + d * -sina;
			MofFloat tmpxz = vv.y * sina + d * cosa;
			vv.y = tmpy;
			vv.x = (vv.x / d) * tmpxz;
			vv.z = (vv.z / d) * tmpxz;
			view = target + vv;
			bMove = true;
		}
		else if (g_pInput->IsKeyHold(MOFKEY_DOWN))
		{
			CVector3 vv = view - target;
			float d = sqrt(vv.x * vv.x + vv.z * vv.z);
			MofFloat sina = MOF_SIN(0.01f);
			MofFloat cosa = MOF_COS(0.01f);
			MofFloat tmpy = vv.y * cosa + d * -sina;
			MofFloat tmpxz = vv.y * sina + d * cosa;
			vv.y = tmpy;
			vv.x = (vv.x / d) * tmpxz;
			vv.z = (vv.z / d) * tmpxz;
			view = target + vv;
			bMove = true;
		}

		//�}�E�X���͂ŃJ��������
		CVector3 mv;
		g_pInput->GetMouseMove(mv);
		//�z�C�[���ɂ��J�����̃Y�[������
		if (mv.z != 0)
		{
			CVector3 vv = view - target;
			vv *= 1.0f - mv.z * 0.0001f;
			view = target + vv;
			bMove = true;
		}
		else if (g_pInput->IsMouseKeyHold(2))
		{
			CVector3 vv = view - target;
			vv *= 1.0f + mv.y * 0.01f;
			view = target + vv;
			bMove = true;
		}
		//���N���b�N�ɂ��J�����ړ�
		if (g_pInput->IsMouseKeyHold(MOFMOUSE_LBUTTON))
		{
			CVector3 sv;
			CVector3 uv;
			CVector3 vv = target - view;
			vv.Normal(vv);
			vv.Cross(Vector3(0, 1, 0), sv);
			sv.Normal(sv);
			view += sv * mv.x * 0.01f;
			target += sv * mv.x * 0.01f;
			sv.Cross(vv, uv);
			uv.Normal(uv);
			view += uv * mv.y * 0.01f;
			target += uv * mv.y * 0.01f;
			bMove = true;
		}
		//�E�N���b�N�ɂ��J������]
		if (g_pInput->IsMouseKeyHold(MOFMOUSE_RBUTTON))
		{
			CVector3 vv = view - target;
			vv.RotationY(mv.x * 0.01f);
			float d = sqrt(vv.x * vv.x + vv.z * vv.z);
			MofFloat sina = MOF_SIN(-mv.y * 0.01f);
			MofFloat cosa = MOF_COS(-mv.y * 0.01f);
			MofFloat tmpy = vv.y * cosa + d * -sina;
			MofFloat tmpxz = vv.y * sina + d * cosa;
			vv.y = tmpy;
			vv.x = (vv.x / d) * tmpxz;
			vv.z = (vv.z / d) * tmpxz;
			view = target + vv;
			bMove = true;
		}

		if (bMove)
		{
			SetPosition(view);
			SetTarget(target);
		}
	}
}
