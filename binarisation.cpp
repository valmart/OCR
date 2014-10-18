#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables

int threshold_value = 0;
int threshold_type = 3;;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat src, src_gray, dst;
char* window_name = "Threshold Demo";

char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
char* trackbar_value = "Value";

void Threshold_Demo( int, void*, IplImage*, char* );

int main( int argc, char** argv )
{
IplImage *source = cvLoadImage(argv[1]);
IplImage *destination = cvCreateImage(
				      cvSize( source->width, source->height ), IPL_DEPTH_8U, 1 );

  src = imread( argv[1], 1 );
  cvtColor( src, src_gray, CV_RGB2GRAY );
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );
  Threshold_Demo( 0, 0, destination, argv[2] );
  //threshold( src_gray, destination, 97, 255, 1);
  
  //imshow( window_name, destination );
  
  
  while(true)
    {
      int c;
      c = waitKey( 20 );
      if( (char)c == 27 )
	{ break; }
    }
}

void Threshold_Demo( int, void*, IplImage *destination, char *name )
{
  /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
  */

  threshold( src_gray, dst, 150, max_BINARY_value,1);
  //  cvSaveImage(name, destination);
  imshow( window_name, dst );
}
