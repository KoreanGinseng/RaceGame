#include "MyCamera.h"
namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position">設定する座標</param>
	/// <returns>this</returns>
	/// <created>いのうえ,2020/11/17</created>
	/// <changed>いのうえ,2020/11/17</changed>
	// ********************************************************************************
	inline CMyCamera& CMyCamera::SetPosition(const Vector3 & position)
	{
		m_Position = position;
		return UpdateCamera();
	}

	// ********************************************************************************
	/// <summary>
	/// ターゲットの設定
	/// </summary>
	/// <param name="target">設定するターゲット</param>
	/// <returns>this</returns>
	/// <created>いのうえ,2020/11/17</created>
	/// <changed>いのうえ,2020/11/17</changed>
	// ********************************************************************************
	inline CMyCamera& CMyCamera::SetTarget(const Vector3 & target)
	{
		m_Target = target;
		return UpdateCamera();
	}

	// ********************************************************************************
	/// <summary>
	/// 上方ベクトルの設定
	/// </summary>
	/// <param name="up">設定する上方ベクトル</param>
	/// <returns>this</returns>
	/// <created>いのうえ,2020/11/17</created>
	/// <changed>いのうえ,2020/11/17</changed>
	// ********************************************************************************
	inline CMyCamera& CMyCamera::SetUpVector(const Vector3 & up)
	{
		m_UpVector = up;
		return UpdateCamera();
	}

	// ********************************************************************************
	/// <summary>
	/// 視野の設定
	/// </summary>
	/// <param name="fov">設定する視野</param>
	/// <returns>this</returns>
	/// <created>いのうえ,2020/11/18</created>
	/// <changed>いのうえ,2020/11/18</changed>
	// ********************************************************************************
	inline CMyCamera & CMyCamera::SetFov(const MofFloat & fov)
	{
		m_Fov = fov;
		return UpdatePerspectiveFov();
	}

	// ********************************************************************************
	/// <summary>
	/// アスペクトの設定
	/// </summary>
	/// <param name="aspect">設定するアスペクト</param>
	/// <returns>this</returns>
	/// <created>いのうえ,2020/11/18</created>
	/// <changed>いのうえ,2020/11/18</changed>
	// ********************************************************************************
	inline CMyCamera & CMyCamera::SetAspect(const Vector2 & aspect)
	{
		m_Aspect = aspect;
		return UpdatePerspectiveFov();
	}

	// ********************************************************************************
	/// <summary>
	/// 最近値と最遠値の設定
	/// </summary>
	/// <param name="Near">設定する最近値</param>
	/// <param name="Far">設定する最遠値</param>
	/// <returns>this</returns>
	/// <created>いのうえ,2020/11/18</created>
	/// <changed>いのうえ,2020/11/18</changed>
	// ********************************************************************************
	inline CMyCamera & CMyCamera::SetNearFar(const MofFloat & Near, const MofFloat & Far)
	{
		m_NearFar = Vector2{ Near, Far };
		return UpdatePerspectiveFov();
	}

	// ********************************************************************************
	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	/// <created>いのうえ,2020/11/17</created>
	/// <changed>いのうえ,2020/11/17</changed>
	// ********************************************************************************
	inline Vector3 CMyCamera::GetPosition(void) const
	{
		return m_Camera.GetViewPosition();
	}

	// ********************************************************************************
	/// <summary>
	/// 注視点の取得
	/// </summary>
	/// <returns>注視点</returns>
	/// <created>いのうえ,2020/11/17</created>
	/// <changed>いのうえ,2020/11/17</changed>
	// ********************************************************************************
	inline Vector3 CMyCamera::GetTarget(void) const
	{
		return m_Camera.GetTargetPosition();
	}

	// ********************************************************************************
	/// <summary>
	/// 上方ベクトルの取得
	/// </summary>
	/// <returns>上方ベクトル</returns>
	/// <created>いのうえ,2020/11/17</created>
	/// <changed>いのうえ,2020/11/17</changed>
	// ********************************************************************************
	inline Vector3 CMyCamera::GetUpVector(void) const
	{
		return m_Camera.GetViewUp();
	}

	// ********************************************************************************
	/// <summary>
	/// 視野の取得
	/// </summary>
	/// <returns>視野</returns>
	/// <created>いのうえ,2020/11/18</created>
	/// <changed>いのうえ,2020/11/18</changed>
	// ********************************************************************************
	inline MofFloat CMyCamera::GetFov(void) const
	{
		return m_Camera.GetProjectionInfo().Fov;
	}

	// ********************************************************************************
	/// <summary>
	/// アスペクトの取得
	/// </summary>
	/// <returns>アスペクト</returns>
	/// <created>いのうえ,2020/11/18</created>
	/// <changed>いのうえ,2020/11/18</changed>
	// ********************************************************************************
	inline MofFloat CMyCamera::GetAspect(void) const
	{
		return m_Camera.GetProjectionInfo().Aspect;
	}

	// ********************************************************************************
	/// <summary>
	/// 最近値の取得
	/// </summary>
	/// <returns>最近値</returns>
	/// <created>いのうえ,2020/11/18</created>
	/// <changed>いのうえ,2020/11/18</changed>
	// ********************************************************************************
	inline MofFloat CMyCamera::GetNear(void) const
	{
		return m_Camera.GetProjectionInfo().Near;
	}

	// ********************************************************************************
	/// <summary>
	/// 最遠値の取得
	/// </summary>
	/// <returns>最遠値</returns>
	/// <created>いのうえ,2020/11/18</created>
	/// <changed>いのうえ,2020/11/18</changed>
	// ********************************************************************************
	inline MofFloat CMyCamera::GetFar(void) const
	{
		return m_Camera.GetProjectionInfo().Far;
	}

	// ********************************************************************************
	/// <summary>
	/// カメラの取得
	/// </summary>
	/// <returns>カメラのポインタ</returns>
	/// <created>いのうえ,2020/11/17</created>
	/// <changed>いのうえ,2020/11/17</changed>
	// ********************************************************************************
	inline LPCamera CMyCamera::GetCamera(void)
	{
		return &m_Camera;
	}

	// ********************************************************************************
	/// <summary>
	/// カメラ情報の更新
	/// </summary>
	/// <returns>this</returns>
	/// <created>いのうえ,2020/11/17</created>
	/// <changed>いのうえ,2020/11/18</changed>
	// ********************************************************************************
	inline CMyCamera& CMyCamera::UpdateCamera(void)
	{
		//カメラの再設定
		m_Camera.LookAt(m_Position, m_Target, m_UpVector);
		m_Camera.Update();
		return *this;
	}

	// ********************************************************************************
	/// <summary>
	/// カメラの比率、視野更新
	/// </summary>
	/// <returns>this</returns>
	/// <created>いのうえ,2020/11/18</created>
	/// <changed>いのうえ,2020/11/18</changed>
	// ********************************************************************************
	inline CMyCamera & CMyCamera::UpdatePerspectiveFov(void)
	{
		//カメラの再設定
		m_Camera.PerspectiveFov(m_Fov, m_Aspect.x / m_Aspect.y, m_NearFar[0], m_NearFar[1]);
		m_Camera.Update();
		return *this;
	}
}