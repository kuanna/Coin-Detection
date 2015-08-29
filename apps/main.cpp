#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include "detector.hpp"

using namespace cv;

static const char* keys =
{
    "{ |  image   |             |  Source image }"
	"{ |  camera  |  false      |  Source camera}"
    "{ |  method  |  Hough      |  A method to work with }"
	"{ |  method  |  Threshold  |  A method to work with }"
};

int main(int argc, char** argv)
{
    cv::CommandLineParser parser( argc, argv, keys );
    // Parse and validate input parameters
    std::string image_file = parser.get<std::string>( "image" );
	bool use_camera = parser.get<bool>("camera");
    std::string method_name = parser.get<std::string>( "method" );
	
	Mat src; 
	Ptr<Detector> detector(detectorCreation(method_name));
	if(!image_file.empty())
	{    
		/// Read the image
		src = imread( image_file );
		CV_Assert( !src.empty() );
		detector->init(src);
		detector->count();
		detector->draw();
		waitKey(0);
	}
	else if (use_camera)
	{
		VideoCapture cap(0); // open the default camera
		if(!cap.isOpened())  // check if we succeeded
		{
			return -1;
		}

		for(;;)
		{
			cap >> src; // get a new frame from camera
			detector->init(src);
			detector->count();
			detector->draw();
			if(waitKey(30) >= 0) 
			{
				break;
			}
		}
	}

    return 0;
}