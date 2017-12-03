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
#include "cc_music_symbols.hh"

namespace cc {

class ClefsLocator : SymbolsLocator {
public:
	void locateClefsFrom(cv::Mat);
	std::vector<cv::Vec4i> GClefs;
private:

};

}
#endif