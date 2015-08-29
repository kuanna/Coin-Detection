#include "detector.hpp"

using namespace cv;

class Threshold : public Detector {
public:
    Threshold() {};
   
    void init( Mat &src )
    {
        image = src;
		minEllipse.clear();
    }

    int count()
    {
        int thresh = 100;
        int max_thresh = 255;
		Mat gray_image;
		
        imshow( " ", image );
		
		//Resize and flip
        int size_height = image.size().height;
        int size_width = image.size().width;
        if (size_height > size_width )
        {
            cv::transpose(image, image);
            cv::flip(image, image, 1);
            size_height = image.size().height;
            size_width = image.size().width;
        }
        if (size_width > 640 )
        {
            resize( image, image, Size(640,480) );
            cvtColor( image, gray_image, CV_BGR2GRAY );
        }
        else
		{
            cvtColor( image, gray_image, CV_BGR2GRAY );
		}
		
        /// Reduce the noise so we avoid false circle detection
        GaussianBlur( gray_image, gray_image, Size(9, 9), 2, 2 );
		
		/// Filling empty spots with Morph 
        Mat kernel;
        kernel = Mat::ones( 6, 6, CV_8UC1);
        kernel = kernel * 255;
        morphologyEx(gray_image, gray_image, MORPH_OPEN, kernel);
		
		/// Detect edges using Threshold
		Mat threshold_output;
        threshold( gray_image, threshold_output, thresh, 255, THRESH_OTSU);
        //imshow("Threshold", threshold_output);

        /// Find contours
		vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

        /// Find the rotated rectangles and ellipses for each contour
        vector<RotatedRect> minRect( contours.size() );
        for( int i = 0; i < contours.size(); i++ )
        {     
            minRect[i] = minAreaRect( Mat(contours[i]));
            if ( contours[i].size() > 5 )
            { 
                double area = cv::contourArea( contours[i]);
                if ( ( area < 57600 ) && ( area > 300 ) )
                {
                      minEllipse.push_back(fitEllipse( Mat(contours[i])));
                }
            }
        }

        return minEllipse.size(); 
    }

    void draw()
    { 
		RNG rng(12345);
		/// Draw ellipses
        for( int i = 0; i < minEllipse.size(); i++ )
        {
			Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
            // ellipse
			ellipse(image, minEllipse[i], color, 2, 8);
        }
        imshow("Ellipses", image);
        std::cout<< "number of coins:\t" << minEllipse.size() << std::endl;
	}
    
    cv::vector<cv::Vec3f> write_circles()
	{
		return cv::vector<cv::Vec3f>();
	}

	cv::vector<cv::RotatedRect> write_ellipse()
	{
		return minEllipse;
	}
	
private:
    Mat image;
	vector<RotatedRect> minEllipse;
};

cv::Ptr<Detector> createDetectorThreshold() 
{
    return cv::Ptr<Detector>(new Threshold());
}