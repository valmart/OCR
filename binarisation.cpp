#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <iostream>

using namespace cv;

static double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0) {
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1 * dx2 + dy1 * dy2) / sqrt((dx1 * dx1 + dy1 * dy1) * (dx2 * dx2 + dy2 * dy2) + 1e-10);
}

int main( int argc, char** argv ) {
    Mat src, src_gray, dst, grad;
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
    int scale = 1;
    int delta = 0;

    // Load an image
    src = imread( argv[1], 1 );
    GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

    // Convert to Gray
    cvtColor( src, src_gray, CV_RGB2GRAY );
    imwrite("Traitment/GreyTestImage.jpg", src_gray);

    // Threshold (binarization)
    adaptiveThreshold(src_gray, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 3, 1);
    imwrite("Traitment/BinarizationTestImage.jpg", dst);

        // Gradient X
    Sobel( src_gray, grad_x, CV_16S, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x, abs_grad_x );

        // Gradient Y
    Sobel( src_gray, grad_y, CV_16S, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );

        // Total Gradient (approximate)
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
    imwrite("Traitment/SobelTestImage.jpg", grad);

    cv::Mat bw;
    cv::Canny(grad, bw, 0, 50, 5);
    // Find contours
    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(bw.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    std::vector<cv::Point> approx;
    dst = src.clone();
    for (int i = 0; i < contours.size(); i++) {
        // Approximate contour with accuracy proportional to the contour perimeter
        cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.02, true);
        // Skip small or non-convex objects
        if (std::fabs(cv::contourArea(contours[i])) < 100 || !cv::isContourConvex(approx))
            continue;
        if (approx.size() >= 4 && approx.size() <= 6) {
            // Number of vertices of polygonal curve
            int vtc = approx.size();
            // Get the cosines of all corners
            std::vector<double> cos;
            for (int j = 2; j < vtc+1; j++)
                cos.push_back(angle(approx[j%vtc], approx[j-2], approx[j-1]));
            // Sort ascending the cosine values
            std::sort(cos.begin(), cos.end());
            // Get the lowest and the highest cosine
            double mincos = cos.front();
            double maxcos = cos.back();
            // Use the degrees obtained above and the number of vertices to determine the shape of the contour
            if (vtc == 4 && mincos >= -0.1 && maxcos <= 0.3) {
                cv::Rect r = cv::boundingRect(contours[i]);
                cv::Mat subImage(src, r);
                cv::Mat test;
                cv::imwrite("Traitment/PlateTestImage.jpg", subImage);
                GaussianBlur(subImage, subImage, Size(3,3), 0, 0, BORDER_DEFAULT );
                cvtColor(subImage, test, CV_RGB2GRAY );
                adaptiveThreshold(test, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 3, 1);
                imshow("Traitment/BinarizationTestImage.jpg", dst);
                cv::waitKey(0);
            }
        }
    }
    //next
}