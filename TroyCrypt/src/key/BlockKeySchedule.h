
#include "../TroyContext.h"

namespace TroyCrypt {

	class BlockKeySchedule {
	public:
		virtual void nextKey(BlockContext* context) = 0;
	};
}
