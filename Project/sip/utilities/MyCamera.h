#pragma once
#include "Mof.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// ���b�v�J�����N���X
	/// </summary>
	// ********************************************************************************
	class CMyCamera
	{
	protected:

		Vector3 m_Position{ 0.0f, 2.0f, -10.0f };  //! �J�����̍��W
		Vector3 m_Target  { 0.0f, 0.0f,   0.0f };  //! �����_�̍��W
		Vector3 m_UpVector{ 0.0f, 1.0f,   0.0f };  //! ����x�N�g��

		Vector2 m_Aspect  { 1024.0f,  768.0f };    //! �A�X�y�N�g
		Vector2 m_NearFar {   0.01f, 2000.0f };    //! x = NEAR, y = FAR

		float   m_Fov     { MOF_ToRadian(60.0f) }; //! ����

		CCamera m_Camera;                          //! �J����

	public:

		// ********************************************************************************
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <created>���̂���,2020/11/17</created>
		/// <changed>���̂���,2020/11/17</changed>
		// ********************************************************************************
		explicit CMyCamera(void) = default;

		// ********************************************************************************
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		/// <created>���̂���,2020/11/17</created>
		/// <changed>���̂���,2020/11/17</changed>
		// ********************************************************************************
		virtual ~CMyCamera(void) = default;

		// ********************************************************************************
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="pCam">�������f�[�^�|�C���^</param>
		/// <created>���̂���,2020/11/17</created>
		/// <changed>���̂���,2020/11/23</changed>
		// ********************************************************************************
		virtual void Initialize(CMyCamera* pCam = nullptr);

		// ********************************************************************************
		/// <summary>
		/// ���W�̐ݒ�
		/// </summary>
		/// <param name="position">�ݒ肷����W</param>
		/// <returns>this</returns>
		/// <created>���̂���,2020/11/17</created>
		/// <changed>���̂���,2020/11/18</changed>
		// ********************************************************************************
		inline virtual CMyCamera& SetPosition(const Vector3& position);

		// ********************************************************************************
		/// <summary>
		/// �^�[�Q�b�g�̐ݒ�
		/// </summary>
		/// <param name="target">�ݒ肷��^�[�Q�b�g</param>
		/// <returns>this</returns>
		/// <created>���̂���,2020/11/17</created>
		/// <changed>���̂���,2020/11/18</changed>
		// ********************************************************************************
		inline virtual CMyCamera& SetTarget(const Vector3& target);

		// ********************************************************************************
		/// <summary>
		/// ����x�N�g���̐ݒ�
		/// </summary>
		/// <param name="up">�ݒ肷�����x�N�g��</param>
		/// <returns>this</returns>
		/// <created>���̂���,2020/11/17</created>
		/// <changed>���̂���,2020/11/18</changed>
		// ********************************************************************************
		inline virtual CMyCamera& SetUpVector(const Vector3& up);

		// ********************************************************************************
		/// <summary>
		/// ����̐ݒ�
		/// </summary>
		/// <param name="fov">�ݒ肷�鎋��</param>
		/// <returns>this</returns>
		/// <created>���̂���,2020/11/18</created>
		/// <changed>���̂���,2020/11/18</changed>
		// ********************************************************************************
		inline virtual CMyCamera& SetFov(const MofFloat& fov);

		// ********************************************************************************
		/// <summary>
		/// �A�X�y�N�g�̐ݒ�
		/// </summary>
		/// <param name="aspect">�ݒ肷��A�X�y�N�g</param>
		/// <returns>this</returns>
		/// <created>���̂���,2020/11/18</created>
		/// <changed>���̂���,2020/11/18</changed>
		// ********************************************************************************
		inline virtual CMyCamera& SetAspect(const Vector2& aspect);
		
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
		inline virtual CMyCamera& SetNearFar(const MofFloat& Near, const MofFloat& Far);

		// ********************************************************************************
		/// <summary>
		/// ���W�̎擾
		/// </summary>
		/// <returns>���W</returns>
		/// <created>���̂���,2020/11/17</created>
		/// <changed>���̂���,2020/11/17</changed>
		// ********************************************************************************
		inline virtual Vector3 GetPosition(void) const;

		// ********************************************************************************
		/// <summary>
		/// �����_�̎擾
		/// </summary>
		/// <returns>�����_</returns>
		/// <created>���̂���,2020/11/17</created>
		/// <changed>���̂���,2020/11/17</changed>
		// ********************************************************************************
		inline virtual Vector3 GetTarget(void) const;
		
		// ********************************************************************************
		/// <summary>
		/// ����x�N�g���̎擾
		/// </summary>
		/// <returns>����x�N�g��</returns>
		/// <created>���̂���,2020/11/17</created>
		/// <changed>���̂���,2020/11/17</changed>
		// ********************************************************************************
		inline virtual Vector3 GetUpVector(void) const;

		// ********************************************************************************
		/// <summary>
		/// ����̎擾
		/// </summary>
		/// <returns>����</returns>
		/// <created>���̂���,2020/11/18</created>
		/// <changed>���̂���,2020/11/18</changed>
		// ********************************************************************************
		inline virtual MofFloat GetFov(void) const;

		// ********************************************************************************
		/// <summary>
		/// �A�X�y�N�g�̎擾
		/// </summary>
		/// <returns>�A�X�y�N�g</returns>
		/// <created>���̂���,2020/11/18</created>
		/// <changed>���̂���,2020/11/18</changed>
		// ********************************************************************************
		inline virtual MofFloat GetAspect(void) const;

		// ********************************************************************************
		/// <summary>
		/// �ŋߒl�̎擾
		/// </summary>
		/// <returns>�ŋߒl</returns>
		/// <created>���̂���,2020/11/18</created>
		/// <changed>���̂���,2020/11/18</changed>
		// ********************************************************************************
		inline virtual MofFloat GetNear(void) const;

		// ********************************************************************************
		/// <summary>
		/// �ŉ��l�̎擾
		/// </summary>
		/// <returns>�ŉ��l</returns>
		/// <created>���̂���,2020/11/18</created>
		/// <changed>���̂���,2020/11/18</changed>
		// ********************************************************************************
		inline virtual MofFloat GetFar(void) const;

		// ********************************************************************************
		/// <summary>
		/// �J�����̎擾
		/// </summary>
		/// <returns>�J�����̃|�C���^</returns>
		/// <created>���̂���,2020/11/17</created>
		/// <changed>���̂���,2020/11/17</changed>
		// ********************************************************************************
		inline virtual LPCamera GetCamera(void);

	protected:

		// ********************************************************************************
		/// <summary>
		/// �J�������̍X�V
		/// </summary>
		/// <returns>this</returns>
		/// <created>���̂���,2020/11/17</created>
		/// <changed>���̂���,2020/11/18</changed>
		// ********************************************************************************
		inline virtual CMyCamera& UpdateCamera(void);

		// ********************************************************************************
		/// <summary>
		/// �J�����̔䗦�A����X�V
		/// </summary>
		/// <returns>this</returns>
		/// <created>���̂���,2020/11/18</created>
		/// <changed>���̂���,2020/11/18</changed>
		// ********************************************************************************
		inline virtual CMyCamera& UpdatePerspectiveFov(void);
	};
}

#include "MyCamera.inl"