#include "detector.hpp"

cv::Ptr<Detector> createHoughDetector() {return cv::Ptr<Detector>();}
//Other detectors

cv::Ptr<Detector> createDetector(const std::string &impl_name)
{
    if (impl_name == "Hough")
        return createHoughDetector();
    return 0;
}
