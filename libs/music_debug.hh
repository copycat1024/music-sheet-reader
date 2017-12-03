/* CC Music Reader Debugger header
 *
 * Contain the object used to debug the result.
 *
 * Status: Locked
 *
 */

#ifndef CC_MUSIC_DEBUG
#define CC_MUSIC_DEBUG

#include <opencv2/core/core.hpp>
#include <string>
#include <vector>

namespace cc{

enum class Error;
class Locator;

class Debugger{
public:
	void debug(Locator&, Error);
private:
};

}

#endif
