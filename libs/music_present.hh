/* CC Music Reader Presenter header
 *
 * Contain the object used to present the result.
 *
 * Status: Locked
 *
 */

#ifndef CC_MUSIC_PRESENT
#define CC_MUSIC_PRESENT

#include <opencv2/core/core.hpp>
#include <string>
#include <vector>
#include "music_locate.hh"

namespace cc{

class Presenter{
public:
	// present results
	void presentResults(const Locator&, const cv::Mat&);

private:
	void _presentStavesAndLines(const Locator&, const cv::Mat&);
};

}

#endif
