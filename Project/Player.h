#pragma once

#include	"Character.h"

class CPlayer : public CCharacter {
private:
public:
	CPlayer();
	virtual ~CPlayer();
	virtual void Update(CMeshPtr pGMesh, CMeshPtr pWMesh, CVector3 * path, int cnt);
};