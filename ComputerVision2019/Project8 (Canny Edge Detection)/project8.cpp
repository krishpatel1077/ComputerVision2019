#include <iostream>
#include <fstream>
#include <vector>
#include "math.h"
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <string>
using namespace std;
int WIDTH;
int HEIGHT;
string imageType;
vector<int> outputppm;
//Methods go here
void readToVector(const char *file)
{
  ifstream imageFile(file);
  short int colorSize;
  imageFile >> imageType;
  imageFile >> WIDTH;
  imageFile >> HEIGHT;
  imageFile >> colorSize;
  vector<int> image(WIDTH * HEIGHT);
  int r, g, b;
  int index = 0;
  if (imageType.compare("P3") == 0)
  {
    while (index < image.size())
      {
        imageFile >> r >> g >> b;
        string s1 = to_string(r);
        string s2 = to_string(g);
        string s3 = to_string(b);
        int t1 = stoi(s1);
        int t2 = stoi(s2);
        int t3 = stoi(s3);
        if (t1 == t2 == t3)
        image[index++] = t1;
        else
        image[index++] = (int)((t1 + t2 + t3)/3);
      }
  }
  colorSize += 1;
  if (colorSize != 256)
    for (int i = 0; i < image.size(); i++)
      image[i] = (image[i] + 1) * (256 / colorSize) - 1;
  imageFile.close();
  outputppm = image;
}
int matrixMulti(double gk[][3], int array[])
{
double total = 0;
total += gk[0][0] * array[0];
total += gk[0][1] * array[1];
total += gk[0][2] * array[2];
total += gk[1][0] * array[3];
total += gk[1][1] * array[4];
total += gk[1][2] * array[5];
total += gk[2][0] * array[6];
total += gk[2][1] * array[7];
total += gk[2][2] * array[8];
total = total/25;
return (int)total;
}
void gaussianBlur(vector<int> image)
{
vector<int> pointer = image;
double gk[3][3];
gk[0][0] = 1/16;
gk[0][2] = 1/16;
gk[2][0] = 1/16;
gk[2][2] = 1/16;
gk[0][1] = 1/8;
gk[1][2] = 1/8;
gk[1][0] = 1/8;
gk[2][1] = 1/8;
gk[1][1] = 1/4;
int array[9];
for (int w = 0; w < WIDTH-1; w++)
  for (int h = 0; h < HEIGHT-1; h++)
  {
    array[0] = image[h * WIDTH + w];
    array[1] = image[h * WIDTH + (w+1)];
    array[2] = image[h * WIDTH + (w+2)];
    array[3] = image[(h+1) * WIDTH + w];
    array[4] = image[(h+1) * WIDTH + (w+1)];
    array[5] = image[(h+1) * WIDTH + (w+2)];
    array[6] = image[(h+2) * WIDTH + w];
    array[7] = image[(h+2) * WIDTH + (w+1)];
    array[8] = image[(h+2) * WIDTH + (w+2)];


    pointer[(h+1) * WIDTH + (w+1)] = matrixMulti(gk, array);    
  }
outputppm = pointer;
}
void WriteToPPM(vector<int> image)
{
  ofstream output;
  output.open("project8ppm.ppm");
  output << imageType << " " << WIDTH << " " << HEIGHT << " 255" << endl;
  for (int h = 0; h < HEIGHT; h++)
  {
    for (int w = 0; w < WIDTH; w++)
    {
      output << image[h * WIDTH + w] << " " << image[h * WIDTH + w] << " " << image[h * WIDTH + w] << " " << image[h * WIDTH + w] << " " << image[h * WIDTH + w] << " " << image[h * WIDTH + w] << " " << image[h * WIDTH + w] << " " << image[h * WIDTH + w] << " " << image[h * WIDTH + w] << " ";
    }
    output << endl;
  }
}
void nonMaxSuppression(vector<int> image)
{

}
//Main driver
int main()
{
  //GrayScale using input ppm file image.ppm
  readToVector("image.ppm");
  //Gaussian Blur using project8ppm.ppm
   gaussianBlur(outputppm);
   nonMaxSuppression(outputppm);
  WriteToPPM(outputppm);
  return 0;
}
