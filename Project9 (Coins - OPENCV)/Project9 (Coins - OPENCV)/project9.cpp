//Krish Patel
//Zacharias Period 3
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

//global variables
int pCount;
int dCount;
int qCount;
int nCount;
int main(int argc, char** argv) {
    const char* filename = argc >= 2 ? argv[1] : "coinsEasy.jpg";
    Mat src = imread(samples::findFile(filename), IMREAD_COLOR);

    if (src.empty()) {
        printf(" Error opening image\n");
        printf(" Program Arguments: [image_name -- default %s] \n", filename);
        return -1;
    }
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, gray, Size(5, 5), 20);
    vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 2, 70, 104, 52, 85, 120);
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // draw the circle center
        circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );
        if (radius >= 86 && radius < 95)
            putText(src, "PENNY.", center, FONT_HERSHEY_COMPLEX_SMALL, 0.8, Scalar(200,200,250), 1, CV_8U);
        // draw the circle outline
        circle( src, center, radius, Scalar(0, 0,255), 10, 8, 0 );
    }
    for (size_t index = 0; index < circles.size(); index++)
    {
        cout << cvRound(circles[index][2]) << endl;
        int radius = cvRound(circles[index][2]);
        if (radius >= 86 && radius < 95)
        {
            pCount++;
        }
    }
    float total = 0.0;
    total = (float)(pCount * 0.01) + (float)(nCount * 0.05) + (float)(dCount * 0.1) + (float)(qCount * 0.25);
    cout << "Penny Count: " << pCount << endl;
    cout << "TOTAL COIN COUNT ($$$): " << total << endl;
    namedWindow("Detected Circles");
    imshow("Detected Circles", src);
    waitKey();
    return 0;
}