#pragma once

#include	"GameDefine.h"

//ÉvÉåÉCÉÑÅ[ç≈ëÂêî
#define MAXCHARACTER (6)

class CStage {
private:
	
	CMeshPtr                    m_pMesh   { nullptr };
	CMeshPtr                    m_pSkyMesh{ nullptr };

	CMeshPtr                    m_pCollisionWallMesh  { nullptr };
	CMeshPtr                    m_pCollisionGroundMesh{ nullptr };

	CDirectionalLight			m_Light;

	CVector3                    m_StartPos[MAXCHARACTER]{ Vector3() };
	int                         m_PathCount{ 0 };
	CVector3*                   m_PathArray{ nullptr };

public:
	CStage();
	virtual ~CStage();
	bool Load();
	void Initialize();
	void Update();
	void Render();
	void RenderDebug();
	void RenderDebugText();
	void Release();

	const CVector3& GetStartPos(int no) const;
	CVector3* GetPath(void);
	int GetPathCount(void);

	CMeshPtr GetCollisionGroundMesh(void);
	CMeshPtr GetCollisionWallMesh(void);
};