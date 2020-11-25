#pragma once

#include	"GameDefine.h"

class CStage {
private:
	
	CMeshPtr                    m_pMesh   { nullptr };
	CMeshPtr                    m_pSkyMesh{ nullptr };

	CMeshPtr                    m_pCollisionWallMesh  { nullptr };
	CMeshPtr                    m_pCollisionGroundMesh{ nullptr };

	CDirectionalLight			m_Light;

public:
	CStage();
	virtual ~CStage();
	bool Load();
	void Initialize();
	void Update();
	void Render();
	void RenderDebugText();
	void Release();

	CMeshPtr GetCollisionGroundMesh(void);
	CMeshPtr GetCollisionWallMesh(void);
};