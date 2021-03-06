#include "detector.hpp"

cv::Ptr<Detector> createDetectorHough();
//Other detectors

cv::Ptr<Detector> detectorCreation(const std::string &impl_name)
{
    if (impl_name == "Hough")
        return createDetectorHough();
    return 0;
}
