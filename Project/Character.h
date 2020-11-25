#pragma once

#include	"GameDefine.h"

// �ړ����x
#define		CHARACTER_MOVESPEED			(0.01f)
#define		CHARACTER_DECELERATIONSPEED	(0.005f)
#define		CHARACTER_BRAKESPEED		(0.02f)
#define		CHARACTER_MOVESPEEDMAX		(1.0f)
// ��]���x
#define		CHARACTER_ROTATIONSPEED		(0.04f)
// �{�[�����a
#define     CHARACTER_BALLRADIUS        (1.35f)
// �{�[���~��
#define     CHARACTER_BALLCIRCUMFRENCE  (2.0f * CHARACTER_BALLRADIUS * MOF_MATH_PI)

class CCharacter {
protected:
	CMeshPtr                    m_pMesh  { nullptr };
	LPMeshMotionController      m_pMotion{ nullptr };
	CVector3                    m_Pos    { 0.0f, 0.0f, 0.0f };
	CVector3                    m_Move   { 0.0f, 0.0f, 0.0f };
	CVector3                    m_Angle  { 0.0f, 0.0f, 0.0f };

	CMyCamera                   m_Camera;

	bool                        m_bAccele{ false };
	bool                        m_bBrake { false };

	float                       m_Gravity{ 0.0f };
	bool                        m_bGround{ false };
	bool                        m_bStage { false };

	CVector3                    m_GroundNormal{ 0.0f, 0.0f, 0.0f };
	CVector3                    m_GroundAxis  { 0.0f, 0.0f, 0.0f };
	float                       m_GroundSlant { 0.0f };

	CQuaternion                 m_GroundRotationQ { 0.0f, 0.0f, 0.0f, 0.0f };

	CMeshPtr                    m_pBallMesh{ nullptr };
	CMatrix33                   m_BallRotation{ Matrix33() };

public:

	CCharacter();
	virtual ~CCharacter();
	virtual bool Load();
	virtual void Initialize();
	virtual void Update(CMeshPtr pGMesh, CMeshPtr pWMesh);
	virtual void UpdateMove();
	virtual void UpdateCamera();
	virtual void SetCameraEnable();
	virtual void Render();
	virtual void RenderDebugText();
	virtual void Release();

	virtual void CollisionStage(CMeshPtr pGMesh, CMeshPtr pWMesh);
};