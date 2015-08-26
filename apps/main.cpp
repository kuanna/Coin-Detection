#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include "detector.hpp"

using namespace cv;

static const char* keys =
{
    "{ |  image   |         |  Source image }"
    "{ |  method  |  Hough  |  A method to work with }"
};

int main(int argc, char** argv)
{
    cv::CommandLineParser parser( argc, argv, keys );
    // Parse and validate input parameters
    std::string image_file = parser.get<std::string>( "image" );
    std::string method_name = parser.get<std::string>( "method" );
    Mat src;    

    /// Read the image
    src = imread( image_file );
    CV_Assert( !src.empty() );

    Ptr<Detector> detector(detectorCreation(method_name));
    detector->init(src);
    detector->count();
    detector->draw();

    return 0;
}