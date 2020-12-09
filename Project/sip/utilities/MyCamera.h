#pragma once
#include "Mof.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// ラップカメラクラス
	/// </summary>
	// ********************************************************************************
	class CMyCamera
	{
	protected:

		Vector3 m_Position{ 0.0f, 2.0f, -10.0f };  //! カメラの座標
		Vector3 m_Target  { 0.0f, 0.0f,   0.0f };  //! 注視点の座標
		Vector3 m_UpVector{ 0.0f, 1.0f,   0.0f };  //! 上方ベクトル

		Vector2 m_Aspect  { 1024.0f,  768.0f };    //! アスペクト
		Vector2 m_NearFar {   0.01f, 2000.0f };    //! x = NEAR, y = FAR

		float   m_Fov     { MOF_ToRadian(60.0f) }; //! 視野

		CCamera m_Camera;                          //! カメラ

	public:

		// ********************************************************************************
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <created>いのうえ,2020/11/17</created>
		/// <changed>いのうえ,2020/11/17</changed>
		// ********************************************************************************
		explicit CMyCamera(void) = default;

		// ********************************************************************************
		/// <summary>
		/// デストラクタ
		/// </summary>
		/// <created>いのうえ,2020/11/17</created>
		/// <changed>いのうえ,2020/11/17</changed>
		// ********************************************************************************
		virtual ~CMyCamera(void) = default;

		// ********************************************************************************
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pCam">初期化データポインタ</param>
		/// <created>いのうえ,2020/11/17</created>
		/// <changed>いのうえ,2020/11/23</changed>
		// ********************************************************************************
		virtual void Initialize(CMyCamera* pCam = nullptr);

		// ********************************************************************************
		/// <summary>
		/// 座標の設定
		/// </summary>
		/// <param name="position">設定する座標</param>
		/// <returns>this</returns>
		/// <created>いのうえ,2020/11/17</created>
		/// <changed>いのうえ,2020/11/18</changed>
		// ********************************************************************************
		inline virtual CMyCamera& SetPosition(const Vector3& position);

		// ********************************************************************************
		/// <summary>
		/// ターゲットの設定
		/// </summary>
		/// <param name="target">設定するターゲット</param>
		/// <returns>this</returns>
		/// <created>いのうえ,2020/11/17</created>
		/// <changed>いのうえ,2020/11/18</changed>
		// ********************************************************************************
		inline virtual CMyCamera& SetTarget(const Vector3& target);

		// ********************************************************************************
		/// <summary>
		/// 上方ベクトルの設定
		/// </summary>
		/// <param name="up">設定する上方ベクトル</param>
		/// <returns>this</returns>
		/// <created>いのうえ,2020/11/17</created>
		/// <changed>いのうえ,2020/11/18</changed>
		// ********************************************************************************
		inline virtual CMyCamera& SetUpVector(const Vector3& up);

		// ********************************************************************************
		/// <summary>
		/// 視野の設定
		/// </summary>
		/// <param name="fov">設定する視野</param>
		/// <returns>this</returns>
		/// <created>いのうえ,2020/11/18</created>
		/// <changed>いのうえ,2020/11/18</changed>
		// ********************************************************************************
		inline virtual CMyCamera& SetFov(const MofFloat& fov);

		// ********************************************************************************
		/// <summary>
		/// アスペクトの設定
		/// </summary>
		/// <param name="aspect">設定するアスペクト</param>
		/// <returns>this</returns>
		/// <created>いのうえ,2020/11/18</created>
		/// <changed>いのうえ,2020/11/18</changed>
		// ********************************************************************************
		inline virtual CMyCamera& SetAspect(const Vector2& aspect);
		
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
		inline virtual CMyCamera& SetNearFar(const MofFloat& Near, const MofFloat& Far);

		// ********************************************************************************
		/// <summary>
		/// 座標の取得
		/// </summary>
		/// <returns>座標</returns>
		/// <created>いのうえ,2020/11/17</created>
		/// <changed>いのうえ,2020/11/17</changed>
		// ********************************************************************************
		inline virtual Vector3 GetPosition(void) const;

		// ********************************************************************************
		/// <summary>
		/// 注視点の取得
		/// </summary>
		/// <returns>注視点</returns>
		/// <created>いのうえ,2020/11/17</created>
		/// <changed>いのうえ,2020/11/17</changed>
		// ********************************************************************************
		inline virtual Vector3 GetTarget(void) const;
		
		// ********************************************************************************
		/// <summary>
		/// 上方ベクトルの取得
		/// </summary>
		/// <returns>上方ベクトル</returns>
		/// <created>いのうえ,2020/11/17</created>
		/// <changed>いのうえ,2020/11/17</changed>
		// ********************************************************************************
		inline virtual Vector3 GetUpVector(void) const;

		// ********************************************************************************
		/// <summary>
		/// 視野の取得
		/// </summary>
		/// <returns>視野</returns>
		/// <created>いのうえ,2020/11/18</created>
		/// <changed>いのうえ,2020/11/18</changed>
		// ********************************************************************************
		inline virtual MofFloat GetFov(void) const;

		// ********************************************************************************
		/// <summary>
		/// アスペクトの取得
		/// </summary>
		/// <returns>アスペクト</returns>
		/// <created>いのうえ,2020/11/18</created>
		/// <changed>いのうえ,2020/11/18</changed>
		// ********************************************************************************
		inline virtual MofFloat GetAspect(void) const;

		// ********************************************************************************
		/// <summary>
		/// 最近値の取得
		/// </summary>
		/// <returns>最近値</returns>
		/// <created>いのうえ,2020/11/18</created>
		/// <changed>いのうえ,2020/11/18</changed>
		// ********************************************************************************
		inline virtual MofFloat GetNear(void) const;

		// ********************************************************************************
		/// <summary>
		/// 最遠値の取得
		/// </summary>
		/// <returns>最遠値</returns>
		/// <created>いのうえ,2020/11/18</created>
		/// <changed>いのうえ,2020/11/18</changed>
		// ********************************************************************************
		inline virtual MofFloat GetFar(void) const;

		// ********************************************************************************
		/// <summary>
		/// カメラの取得
		/// </summary>
		/// <returns>カメラのポインタ</returns>
		/// <created>いのうえ,2020/11/17</created>
		/// <changed>いのうえ,2020/11/17</changed>
		// ********************************************************************************
		inline virtual LPCamera GetCamera(void);

	protected:

		// ********************************************************************************
		/// <summary>
		/// カメラ情報の更新
		/// </summary>
		/// <returns>this</returns>
		/// <created>いのうえ,2020/11/17</created>
		/// <changed>いのうえ,2020/11/18</changed>
		// ********************************************************************************
		inline virtual CMyCamera& UpdateCamera(void);

		// ********************************************************************************
		/// <summary>
		/// カメラの比率、視野更新
		/// </summary>
		/// <returns>this</returns>
		/// <created>いのうえ,2020/11/18</created>
		/// <changed>いのうえ,2020/11/18</changed>
		// ********************************************************************************
		inline virtual CMyCamera& UpdatePerspectiveFov(void);
	};
}

#include "MyCamera.inl"