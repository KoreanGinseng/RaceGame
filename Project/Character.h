#pragma once

#include	"GameDefine.h"

// ˆÚ“®‘¬“x
#define		CHARACTER_MOVESPEED			(0.01f)
#define		CHARACTER_DECELERATIONSPEED	(0.005f)
#define		CHARACTER_BRAKESPEED		(0.02f)
#define		CHARACTER_MOVESPEEDMAX		(1.0f)
// ‰ñ“]‘¬“x
#define		CHARACTER_ROTATIONSPEED		(0.04f)

class CCharacter {
protected:
	CMeshContainer				m_Mesh;
	LPMeshMotionController		m_pMotion;
	CVector3					m_Pos;
	CVector3					m_Move;
	CVector3					m_Angle;

	CCamera						m_Camera;

	bool						m_bAccele;
	bool						m_bBrake;
public:
	CCharacter();
	virtual ~CCharacter();
	virtual bool Load();
	virtual void Initialize();
	virtual void Update();
	virtual void UpdateMove();
	virtual void UpdateCamera();
	virtual void SetCameraEnable();
	virtual void Render();
	virtual void RenderDebugText();
	virtual void Release();
};