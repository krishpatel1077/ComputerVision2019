#include <iostream>
#include <fstream>
#include <vector>
#include "math.h"
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;
int WIDTH;
int HEIGHT;
string imageType;
vector<int> outputppm;
//Methods go here
void GrayScaleImage(const char *file)
{
  ifstream imageFile(file);
  short int colorSize;
  imageFile >> imageType;
  imageFile >> WIDTH;
  imageFile >> HEIGHT;
  imageFile >> colorSize;
  vector<int> image(WIDTH * HEIGHT);
  int r, g, b, r1, r2, g1, g2, b1, b2;
  int index = 0;
  if (imageType.compare("P3") == 0)
  {
    while (index < image.size())
      {
        imageFile >> r >> g >> b >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;
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
  ofstream output;
  output.open("project8ppm.ppm");
  output << imageType << " " << WIDTH << " " << HEIGHT << " 255" << endl;
  for (int h = 0; h < HEIGHT; h++)
  {
    for (int w = 0; w < WIDTH; w++)
    {
      output << image[h*WIDTH + w] << " " << image[h*WIDTH + w] << " " << image[h*WIDTH + w] << " " << image[h*WIDTH + w] << " " << image[h*WIDTH + w] << " " << image[h*WIDTH + w] << " " << image[h*WIDTH + w] << " " << image[h*WIDTH + w] << " " << image[h*WIDTH + w] << " ";
    }
    output << endl;
  }
  outputppm = image;
}
void GaussianBlur(vector<int> imagevector)
{
  int filtersize = 5;
  for (int h = 4; h < HEIGHT-4; h++)
  {
    for (int w = 4; w < WIDTH-4; w++)
    {
      int sum;
      for (int i = 0; i < filtersize; i++)
      {
          for (int j = 0; j < filtersize; j++)
          {
            
          }
      }
    }
  }
}
//Main driver
int main()
{
  //GrayScale using input ppm file image.ppm
  GrayScaleImage("image.ppm");
  //Gaussian Blur using project8ppm.ppm
  GaussianBlur(outputppm);
  return 0;
}
