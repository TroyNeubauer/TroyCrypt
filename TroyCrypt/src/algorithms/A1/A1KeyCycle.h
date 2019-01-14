
#include "../../key/BlockKeySchedule.h"


namespace TroyCrypt {

class A1KeyCycle : public BlockKeySchedule {
public:
	void nextKey(BlockContext* context);
};
}