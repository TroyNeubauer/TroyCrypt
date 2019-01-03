#pragma once

#include "TroyCrypt.h"
#include <map>
#include <string>

typedef std::map<std::string, u64>& StageData;
class AbstractStage
{
public:
	virtual void operate(u8* input, u8* output, u32 length, StageData data) = delete;
	virtual ~AbstractStage();
};
