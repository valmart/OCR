#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

int main( int argc, char** argv ) {
    Mat src, src_gray, dst;
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
    Mat grad;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    // Load an image
    src = imread( argv[1], 1 );
    GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

    // Convert to Gray
    cvtColor( src, src_gray, CV_RGB2GRAY );
    imwrite("Traitment/GreyTestImage.jpg", src_gray);

    // Threshold (binarization)
    threshold(src_gray, dst , 0, 255, CV_THRESH_BINARY+CV_THRESH_OTSU);
    imwrite( "Traitment/BinarizationTestImage.jpg", dst);

    // Gradient X
    Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x, abs_grad_x );

    // Gradient Y
    Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );

    // Total Gradient (approximate)
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
    imwrite( "Traitment/SobelTestImage.jpg", grad);
}