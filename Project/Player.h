#pragma once

#include	"Character.h"

class CPlayer : public CCharacter {
private:
public:
	CPlayer();
	virtual ~CPlayer();
	virtual void Update();
};