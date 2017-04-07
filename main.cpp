#include "main.hpp"

#include <fstream> 
using namespace cv;
using namespace std;
//using namespace FlyCapture2;

void setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour)
{
using namespace cv;
    int fontface = cv::FONT_HERSHEY_SIMPLEX;
    double scale = 0.4;
    int thickness = 1;
    int baseline = 0;
    
   	Size text = cv::getTextSize(label, fontface, scale, thickness, &baseline);
    Rect r = cv::boundingRect(contour);
    
    
    
    Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
    rectangle(im, pt + cv::Point(0, baseline), pt + Point(text.width, -text.height), CV_RGB(255, 255, 255), CV_FILLED);
    putText(im, label, pt, fontface, scale, CV_RGB(0, 0, 0), thickness, 8);
    
    
    double xNot = r.x + ((r.width - text.width) / 2);
    double yNot = r.y + ((r.height + text.height) / 2);
    
    
    cout << "x: " << xNot << " y: " << yNot << endl;

    
    
};

void contour(cv::Mat& imgThresholded, cv::Mat& imgOriginal, cv::Mat& img)
{
using namespace cv;
    Mat bw;
    //Finding the Edges of the image
    Canny(imgThresholded, bw, 0, 50, 5);
    vector<std::vector<cv::Point> > contours;
    
    //go thru edges until the contours are completed
    findContours(bw, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    
    /// Approximate contours to polygons + get bounding rects and circles
    vector<vector<Point> > contours_draw(contours.size());
    vector<cv::Point> contours_poly;
    
    for (int i = 0; i < contours.size(); i++) //set labels or identify shapes in this loop
    {
        
        //Area inside the Contours
        double area = cv::contourArea(contours[i]);
        
        //Rectangles = A rectangular bound around circle
        //countours/ellipse.
        cv::Rect rectangle = cv::boundingRect(contours[i]);
        int radius = rectangle.width / 2;
        //Checking for if width and height are similar enough to be a circle
        bool BoundingRecForCircles = abs(1 - ((double)rectangle.width / rectangle.height)) <= 0.2;
        //Theorectical Error = 1 - (Actual Area / theorectical area)
        bool Error = abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.2;
        
        bool AreaBound = (area < 1000);// && (area > 500);
        
        
        
        if (BoundingRecForCircles && Error && AreaBound)
        {
            
            setLabel(imgOriginal, "CIR", contours[i]);
            
            
        }
    }
}


void cleanImage(cv::Mat& imgThresholded)
{
using namespace cv;
    //morphological opening (remove small objects from the foreground)
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    //morphological closing (fill small holes in the foreground)
    dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
}



int main(int argc, char** argv)
{
  ///*
	
  //VideoCapture cap("/home/jojo/Desktop/test videos/test2.avi"); //capture the video from web cam
   VideoCapture cap(0);
	
    if (!cap.isOpened())  // if not success, exit program
    {
        cout << "Cannot open the web cam" << endl;
        return -1;
    }
    //*/
    int count = 0;
    
    //4096 x 2160
   
	/*
	Error error;
	Camera camera;
	CameraInfo camInfo;

	// Connect the camera
   	error = camera.Connect( 0 );
    	if ( error != PGRERROR_OK )
   	 {
     	   std::cout << "Failed to connect to camera" << std::endl;     
      	 return false;
   	 }	
	error = camera.StartCapture();
   	if ( error == PGRERROR_ISOCH_BANDWIDTH_EXCEEDED )
   	 {
     	   std::cout << "Bandwidth exceeded" << std::endl;     
      	  return false;
   	 }	 
   	 else if ( error != PGRERROR_OK )
    	 {
     	   std::cout << "Failed to start image capture" << std::endl;     
      	  return false;
   	 } 
	//*/
	





    
    while (true)
    {
    	
	
	/*

		Image rawImage;
		Error error = camera.RetrieveBuffer( &rawImage );
		if ( error != PGRERROR_OK )
		{
			std::cout << "capture error" << std::endl;
			continue;
		}
		
		// convert to rgb
	   	 Image rgbImage;
       		 rawImage.Convert( PIXEL_FORMAT_BGR, &rgbImage );
       
		// convert to OpenCV Mat
		unsigned int rowBytes = (double)rgbImage.GetReceivedDataSize()/(double)rgbImage.GetRows();       
		cv::Mat imgOriginal = cv::Mat(rgbImage.GetRows(), rgbImage.GetCols(), CV_8UC3, rgbImage.GetData(),rowBytes);
		//*/

    	
       ///*

	Mat imgOriginal;
  

        
        cap.grab(); // read a new frame from video
        

        if(count % 5 == 0){  
         	
		bool bSuccess = cap.retrieve(imgOriginal);
		
		if (!bSuccess) //if not success, break loop
		{
		    cout << "Cannot read a frame from video stream" << endl;
		    break;
		}
	       //*/
	    
		//Makes the frame into a matrix
		cv::Mat black = cv::Mat::zeros(imgOriginal.size().height, imgOriginal.size().width, CV_8UC3);
		
		cv::Mat imgHSV;
		
		//Convert the captured frame from RGB to HSV
		cv::cvtColor(imgOriginal, imgHSV, cv::COLOR_BGR2HSV);
		
		
		//this creates 2 images to check both ranges
		cv::Mat red1, red2;
		
		//These two checks for ranges of red from (340-360) and (0-20)
		cv::inRange(imgHSV, cv::Scalar(0, 70, 50), cv::Scalar(10, 255, 255), red1);
		cv::inRange(imgHSV, cv::Scalar(170, 70, 50),cv::Scalar(180, 255, 255),red2);
		
		//Combining both red1 and red2 to get full scope of red
		cv::Mat imgThresholded = red1 | red2;
		
		
		// Clean all the small circles from the image
		cleanImage(imgThresholded);
	      
		//contour()
		contour(imgThresholded, imgOriginal, black);
	      
		//show the original image
	       	cv::imshow("Original", imgOriginal);

	}
    	
		if (cv::waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
		    cout << "esc key is pressed by user" << endl;
		    break;
		}
		count++;
	 	
      }
      
    
    return 0;
    
}
