#pragma once
#include "Character.h"

class CCpu : public CCharacter
{
private:

public:
	CCpu(void) : CCharacter() {}
	virtual ~CCpu(void) { Release(); }

	virtual void Update(CMeshPtr pGMesh, CMeshPtr pWMesh, CVector3* path, int cnt);
};

