//
//  main.cpp
//  HarrisSIFT
//
//  Created by Rafael Vareto on 5/8/16.
//  Copyright © 2016 Rafael Vareto. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace std;

int main(int argc, const char * argv[]) {
    if (argc == 3) {
        cv::Mat imageA = cv::imread( string(argv[1]) );
        cv::Mat imageB = cv::imread( string(argv[2]) );
        
        cv::Mat greyA = cv::imread( string(argv[1]), cv::IMREAD_GRAYSCALE );
        cv::Mat greyB = cv::imread( string(argv[2]), cv::IMREAD_GRAYSCALE );
        
        /** SIFT **/
        cv::Ptr<cv::Feature2D> sift = cv::xfeatures2d::SIFT::create();
        std::vector<cv::KeyPoint> keypointsA, keypointsB;
        
        sift->detect(imageA, keypointsA);
        sift->detect(imageB, keypointsB);
        
        /** HARRIS **/
        cv::Mat cornerA = cv::Mat::zeros( imageA.size(), CV_32FC1 );
        cv::Mat cornerB = cv::Mat::zeros( imageB.size(), CV_32FC1 );
        cv::cornerHarris( greyA, cornerA, 4, 5, 0.05, cv::BORDER_DEFAULT );
        cv::cornerHarris( greyB, cornerB, 4, 5, 0.05, cv::BORDER_DEFAULT );
        
        cv::imshow("Harris", cornerB);
        cv::waitKey();

        
    } else {
        cerr << "You have inserted wrong parameters: \n"
        << "./HarrisSIFT [image01] [image02]" << endl;
    }
    
    return 0;
}
