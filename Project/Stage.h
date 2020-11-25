#pragma once

#include	"GameDefine.h"

class CStage {
private:
	CMeshContainer				m_Mesh;
	CMeshContainer				m_SkyMesh;
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
};