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
float threedpoints[8][3]
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
float twodpoints[8][2] //3D points after perspective projection, set as 0's for placeholders
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
float focal_length = 5;
auto pointer_matrix = threedpoints;

void perspective_matrices(float constant_matrices[3][3], float DDDpointset[4][1], float r_matrix[3][4],
                          float DDpointset[3][1]);

//project rotated 3D points into 2D points
void perspective_projection(float twodpoints[8][2], float threedpoints[8][3])
{
float DDDpointset[4][1]
        {
            0, // X COORDINATE --> 3D Point
            0, // Y COORDINATE --> 3D Point
            0, // Z COORDINATE --> 3D Point
            1, // ARBITRARY CONSTANT
        };
float DDpointset[3][1]
        {
            0, // X COORDINATE --> 2D Point
            0, // Y COORDINATE --> 2D Point
            1, // ARBITRARY CONSTANT
        };
//empty threedpoints into DDDpointset (1 point at a time)
float constant_matrices[3][3]
        {
            focal_length, 0, 2,
            0, focal_length, 2,
            0, 0, 1
        };
float r_matrix[3][4]
        {
            0.5, -0.1, 0.7, 0.1,
            0.5, -0.5, -0.7, 0.5,
            0.5, -0.5, -0.7, -0.1
        };
for (int row = 0; row < 8; row ++)
{
    for (int col = 0; col < 3; col ++)
    {
        DDDpointset[col][0] = threedpoints[row][col];
    }
    //multiply DDDpointset by camera matrices and focal lengths
    perspective_matrices(constant_matrices, DDDpointset, r_matrix, DDpointset);
    //redump DDpointset into twodpoints
    twodpoints[row][0] = DDpointset[0][0];
    twodpoints[row][1] = DDpointset[1][0];
}
}

void perspective_matrices(float constant_matrices[3][3], float DDDpointset[4][1], float r_matrix[3][4], float DDpointset[3][1])
{
//multiply DDDpointset by r_matrix, store in placeholder
float placeholder[3][1]
        {
                r_matrix[0][0] * DDDpointset[0][0] + r_matrix[0][1] * DDDpointset[1][0] + r_matrix[0][2] * DDDpointset[2][0] + r_matrix[0][3] * DDDpointset[3][0],
                r_matrix[1][0] * DDDpointset[0][0] + r_matrix[1][1] * DDDpointset[1][0] + r_matrix[1][2] * DDDpointset[2][0] + r_matrix[1][3] * DDDpointset[3][0],
                r_matrix[2][0] * DDDpointset[0][0] + r_matrix[2][1] * DDDpointset[1][0] + r_matrix[2][2] * DDDpointset[2][0] + r_matrix[2][3] * DDDpointset[3][0],
        };
//multiple placeholder by constant_matrices, store in pointer
float pointer_DD[3][1]
        {
                constant_matrices[0][0] * placeholder[0][0] + constant_matrices[0][1] * placeholder[1][0] + constant_matrices[0][2] * placeholder[2][0],
                constant_matrices[1][0] * placeholder[0][0] + constant_matrices[1][1] * placeholder[1][0] + constant_matrices[1][2] * placeholder[2][0],
                constant_matrices[2][0] * placeholder[0][0] + constant_matrices[2][1] * placeholder[1][0] + constant_matrices[2][2] * placeholder[2][0]
        };
//set pointer to DDpointset
DDpointset = pointer_DD;
}

//rotate 3D points counter clockwise around the y-axis
void ccw_rotation(float threedpoints[8][3], float theta)
{
    float rotation_matrix[3][3]
    {
        cos(theta), -sin(theta), 0,
        sin(theta), cos(theta), 0,
        0, 0, 1
    };
    for (int row_master = 0; row_master < 8; row_master++)
    {
        for (int col_master = 0; col_master < 3; col_master++)
        {
            float prod = 0;
            for (int k = 0; k < 8; k++)
            {
                float *a = rotation_matrix[row_master, k];
                float *b = pointer_matrix[k, col_master];
                prod += *a * *b;
            }
            threedpoints[row_master][col_master] = prod;
        }
    }
}

//push 2D points onto the Mat image which would be pushed back into video frame
void push_twodpoints(float twodpoints[8][2], Mat image)
{
    Point point_a(twodpoints[0][0], twodpoints[0][1]);
    Point point_b(twodpoints[1][0], twodpoints[1][1]);
    Point point_c(twodpoints[2][0], twodpoints[2][1]);
    Point point_d(twodpoints[3][0], twodpoints[3][1]);
    Point point_e(twodpoints[4][0], twodpoints[4][1]);
    Point point_f(twodpoints[5][0], twodpoints[5][1]);
    Point point_g(twodpoints[6][0], twodpoints[6][1]);
    Point point_h(twodpoints[7][0], twodpoints[7][1]);
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
    Mat img = Mat::zeros( 4, 4, CV_8U );
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
    for (int i = 0; i < 8; i++)
    {
        cout << "X: " << twodpoints[i][0] << " Y: " << twodpoints[i][1] << endl;
    }
    /*
     * Add mat img to the video
     * Make / release video
     */
}