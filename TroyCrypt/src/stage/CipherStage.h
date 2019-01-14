#pragma once

#include "../TroyCrypt.h"
#include "../TroyContext.h"

namespace TroyCrypt {
class CipherStage
{
	virtual void operate(TroyContext* context) = 0;
	virtual void inverse(TroyContext* context) = 0;
};

}
