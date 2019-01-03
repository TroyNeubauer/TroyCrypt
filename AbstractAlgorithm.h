#include "TroyCrypt.h"

#pragma once
class AbstractAlgorithm
{
private:
	u8* m_State;
	u32 m_StateSize;

public:
	AbstractAlgorithm(u32 stateSize);
	~AbstractAlgorithm();
};

