#include <iostream>
#include "cv.h"
#include "highgui.h"

using namespace std;

int main( int argc, char** argv ) {
  //load color image specified by first argument
  IplImage *source = cvLoadImage( argv[1]);

  // create new image structure 
  // for the grayscale output image
  IplImage *destination = cvCreateImage( 
					cvSize( source->width, source->height ), IPL_DEPTH_8U, 1 );

  // set type CV_RGB2GRAY to convert 
  // RGB image to grayscale 
  cvCvtColor( source, destination, CV_RGB2GRAY );

  // save grayscale image to a file specified by 
  // second argument
  cvSaveImage( argv[2], destination );
  return 0;
}
