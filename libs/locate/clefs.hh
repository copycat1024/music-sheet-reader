/* CC Music Reader Clef header
 *
 * Contain the base object for clefs locating.
 *
 * Status: Open
 *
 */

#ifndef CC_MUSIC_CLEFS
#define CC_MUSIC_CLEFS

#include <opencv2/core/core.hpp>
#include <vector>
#include "symbols.hh"

namespace cc {

class ClefsLocator : SymbolsLocator {
public:
	void locateFrom(cv::Mat, double);
	std::vector<cv::Vec4i> GClefs;
private:

};

}
#endif
