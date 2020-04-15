/*
 * Created by homeuser (Krish Patel) on 4/14/20.
*/
#include <opencv2/opencv.hpp>
#include <cstdio>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

/*
 * global variables (CUBE):
 * 3D point array, 2D Point array, Pointer for 3D points, focal point for perspective projection
*/
float threedpoints[3][8]
{
    -1, -1, -1, //Point A, row 1
    -1, 1, -1, //Point B, row 2
    -1, -1, 1, //Point C, row 3
    -1, 1, 1, //Point D, row 4
    1, 1, 1, //Point E, row 5
    1, 1, -1, //Point F, row 6
    1, -1, 1, //Point G, row 7
    1, -1, -1 //Point H, row 8
};
float twodpoints[2][8] //3D points after perspective projection, set as 0's for placeholders
{
    0, 0, //Point A, row 1
    0, 0, //Point B, row 2
    0, 0, //Point C, row 3
    0, 0, //Point D, row 4
    0, 0, //Point E, row 5
    0, 0, //Point F, row 6
    0, 0, //Point G, row 7
    0, 0 //Point H, row 8
};
auto pointer_matrix = threedpoints;
float focal_point = 5;

//project rotated 3D points into 2D points
void perspective_projection(float twodpoints[2][8], float threedpoints[3][8])
{

}

//rotate the 3d matrix using an argument of theta (angle of rotation counterclockwise along the y axis
void ccw_rotation(float threedpoints[3][8], float theta)
{
    float rotation_matrix[3][3] = { {cos(theta), sin(theta), 0}, {-sin(theta), cos(theta), 0}, {0, 0, 1} };
    for (int row_master = 0; row_master < 3; row_master++)
    {
        for (int col_master = 0; col_master < 8; col_master++)
        {
            float prod = 0;
            for (int k = 0; k < 3; k++)
            {
                float a = rotation_matrix[row_master, k];
                float b = pointer_matrix[k, col_master];
                prod += a*b;
            }
            threedpoints[row_master][col_master] = prod;
        }
    }
}

//push 2D points onto the Mat image which would be pushed back into video frame
void push_twodpoints(float twodpoints[2][8], Mat image)
{
    Point point_a(twodpoints[0][0], twodpoints[1][0]);
    Point point_b(twodpoints[1][0], twodpoints[1][1]);
    Point point_c(twodpoints[2][0], twodpoints[1][2]);
    Point point_d(twodpoints[3][0], twodpoints[1][3]);
    Point point_e(twodpoints[4][0], twodpoints[1][4]);
    Point point_f(twodpoints[5][0], twodpoints[1][5]);
    Point point_g(twodpoints[6][0], twodpoints[1][6]);
    Point point_h(twodpoints[7][0], twodpoints[1][7]);
    line(image, point_a, point_b, Scalar(0, 255, 0));
    line(image, point_a, point_c, Scalar(0, 255, 0));
    line(image, point_a, point_h, Scalar(0, 255, 0));
    line(image, point_b, point_d, Scalar(0, 255, 0));
    line(image, point_b, point_f, Scalar(0, 255, 0));
    line(image, point_c, point_d, Scalar(0, 255, 0));
    line(image, point_c, point_g, Scalar(0, 255, 0));
    line(image, point_d, point_e, Scalar(0, 255, 0));
    line(image, point_e, point_f, Scalar(0, 255, 0));
    line(image, point_e, point_g, Scalar(0, 255, 0));
    line(image, point_f, point_h, Scalar(0, 255, 0));
    line(image, point_g, point_h, Scalar(0, 255, 0));
}
int main()
{
    Mat img = Mat::zeros( 4, 4, CV_8UC3 );
    /*
     * Initialize the VideoWriter and relevant args, as well as the Mat img used as a frame
     * Video = 36 frames / second (10 seconds long)
     * Rotate counter clockwise around the y axis
     */
    for (int theta = 0; theta < 360; theta++)
    {
        //use Mat img to add frames to
        float rad_theta = (float) (theta * M_PI / 180.0);
        pointer_matrix = threedpoints;
        ccw_rotation(threedpoints, rad_theta);
        perspective_projection(twodpoints, threedpoints);
        push_twodpoints(twodpoints, img);
    }
    /*
     * Add mat img to the video
     * Make / release video
     */
}