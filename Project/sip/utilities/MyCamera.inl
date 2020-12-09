#include "MyCamera.h"
namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="position">�ݒ肷����W</param>
	/// <returns>this</returns>
	/// <created>���̂���,2020/11/17</created>
	/// <changed>���̂���,2020/11/17</changed>
	// ********************************************************************************
	inline CMyCamera& CMyCamera::SetPosition(const Vector3 & position)
	{
		m_Position = position;
		return UpdateCamera();
	}

	// ********************************************************************************
	/// <summary>
	/// �^�[�Q�b�g�̐ݒ�
	/// </summary>
	/// <param name="target">�ݒ肷��^�[�Q�b�g</param>
	/// <returns>this</returns>
	/// <created>���̂���,2020/11/17</created>
	/// <changed>���̂���,2020/11/17</changed>
	// ********************************************************************************
	inline CMyCamera& CMyCamera::SetTarget(const Vector3 & target)
	{
		m_Target = target;
		return UpdateCamera();
	}

	// ********************************************************************************
	/// <summary>
	/// ����x�N�g���̐ݒ�
	/// </summary>
	/// <param name="up">�ݒ肷�����x�N�g��</param>
	/// <returns>this</returns>
	/// <created>���̂���,2020/11/17</created>
	/// <changed>���̂���,2020/11/17</changed>
	// ********************************************************************************
	inline CMyCamera& CMyCamera::SetUpVector(const Vector3 & up)
	{
		m_UpVector = up;
		return UpdateCamera();
	}

	// ********************************************************************************
	/// <summary>
	/// ����̐ݒ�
	/// </summary>
	/// <param name="fov">�ݒ肷�鎋��</param>
	/// <returns>this</returns>
	/// <created>���̂���,2020/11/18</created>
	/// <changed>���̂���,2020/11/18</changed>
	// ********************************************************************************
	inline CMyCamera & CMyCamera::SetFov(const MofFloat & fov)
	{
		m_Fov = fov;
		return UpdatePerspectiveFov();
	}

	// ********************************************************************************
	/// <summary>
	/// �A�X�y�N�g�̐ݒ�
	/// </summary>
	/// <param name="aspect">�ݒ肷��A�X�y�N�g</param>
	/// <returns>this</returns>
	/// <created>���̂���,2020/11/18</created>
	/// <changed>���̂���,2020/11/18</changed>
	// ********************************************************************************
	inline CMyCamera & CMyCamera::SetAspect(const Vector2 & aspect)
	{
		m_Aspect = aspect;
		return UpdatePerspectiveFov();
	}

	// ********************************************************************************
	/// <summary>
	/// �ŋߒl�ƍŉ��l�̐ݒ�
	/// </summary>
	/// <param name="Near">�ݒ肷��ŋߒl</param>
	/// <param name="Far">�ݒ肷��ŉ��l</param>
	/// <returns>this</returns>
	/// <created>���̂���,2020/11/18</created>
	/// <changed>���̂���,2020/11/18</changed>
	// ********************************************************************************
	inline CMyCamera & CMyCamera::SetNearFar(const MofFloat & Near, const MofFloat & Far)
	{
		m_NearFar = Vector2{ Near, Far };
		return UpdatePerspectiveFov();
	}

	// ********************************************************************************
	/// <summary>
	/// ���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	/// <created>���̂���,2020/11/17</created>
	/// <changed>���̂���,2020/11/17</changed>
	// ********************************************************************************
	inline Vector3 CMyCamera::GetPosition(void) const
	{
		return m_Camera.GetViewPosition();
	}

	// ********************************************************************************
	/// <summary>
	/// �����_�̎擾
	/// </summary>
	/// <returns>�����_</returns>
	/// <created>���̂���,2020/11/17</created>
	/// <changed>���̂���,2020/11/17</changed>
	// ********************************************************************************
	inline Vector3 CMyCamera::GetTarget(void) const
	{
		return m_Camera.GetTargetPosition();
	}

	// ********************************************************************************
	/// <summary>
	/// ����x�N�g���̎擾
	/// </summary>
	/// <returns>����x�N�g��</returns>
	/// <created>���̂���,2020/11/17</created>
	/// <changed>���̂���,2020/11/17</changed>
	// ********************************************************************************
	inline Vector3 CMyCamera::GetUpVector(void) const
	{
		return m_Camera.GetViewUp();
	}

	// ********************************************************************************
	/// <summary>
	/// ����̎擾
	/// </summary>
	/// <returns>����</returns>
	/// <created>���̂���,2020/11/18</created>
	/// <changed>���̂���,2020/11/18</changed>
	// ********************************************************************************
	inline MofFloat CMyCamera::GetFov(void) const
	{
		return m_Camera.GetProjectionInfo().Fov;
	}

	// ********************************************************************************
	/// <summary>
	/// �A�X�y�N�g�̎擾
	/// </summary>
	/// <returns>�A�X�y�N�g</returns>
	/// <created>���̂���,2020/11/18</created>
	/// <changed>���̂���,2020/11/18</changed>
	// ********************************************************************************
	inline MofFloat CMyCamera::GetAspect(void) const
	{
		return m_Camera.GetProjectionInfo().Aspect;
	}

	// ********************************************************************************
	/// <summary>
	/// �ŋߒl�̎擾
	/// </summary>
	/// <returns>�ŋߒl</returns>
	/// <created>���̂���,2020/11/18</created>
	/// <changed>���̂���,2020/11/18</changed>
	// ********************************************************************************
	inline MofFloat CMyCamera::GetNear(void) const
	{
		return m_Camera.GetProjectionInfo().Near;
	}

	// ********************************************************************************
	/// <summary>
	/// �ŉ��l�̎擾
	/// </summary>
	/// <returns>�ŉ��l</returns>
	/// <created>���̂���,2020/11/18</created>
	/// <changed>���̂���,2020/11/18</changed>
	// ********************************************************************************
	inline MofFloat CMyCamera::GetFar(void) const
	{
		return m_Camera.GetProjectionInfo().Far;
	}

	// ********************************************************************************
	/// <summary>
	/// �J�����̎擾
	/// </summary>
	/// <returns>�J�����̃|�C���^</returns>
	/// <created>���̂���,2020/11/17</created>
	/// <changed>���̂���,2020/11/17</changed>
	// ********************************************************************************
	inline LPCamera CMyCamera::GetCamera(void)
	{
		return &m_Camera;
	}

	// ********************************************************************************
	/// <summary>
	/// �J�������̍X�V
	/// </summary>
	/// <returns>this</returns>
	/// <created>���̂���,2020/11/17</created>
	/// <changed>���̂���,2020/11/18</changed>
	// ********************************************************************************
	inline CMyCamera& CMyCamera::UpdateCamera(void)
	{
		//�J�����̍Đݒ�
		m_Camera.LookAt(m_Position, m_Target, m_UpVector);
		m_Camera.Update();
		return *this;
	}

	// ********************************************************************************
	/// <summary>
	/// �J�����̔䗦�A����X�V
	/// </summary>
	/// <returns>this</returns>
	/// <created>���̂���,2020/11/18</created>
	/// <changed>���̂���,2020/11/18</changed>
	// ********************************************************************************
	inline CMyCamera & CMyCamera::UpdatePerspectiveFov(void)
	{
		//�J�����̍Đݒ�
		m_Camera.PerspectiveFov(m_Fov, m_Aspect.x / m_Aspect.y, m_NearFar[0], m_NearFar[1]);
		m_Camera.Update();
		return *this;
	}
}