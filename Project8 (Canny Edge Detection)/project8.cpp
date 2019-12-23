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
  outputppm = image;
}
void GaussianBlur(vector<int> imagevector)
{
  int filtersize = 3;
  int index = filtersize - 1;
  for (int h = index; h < HEIGHT-index; h++)
  {
    for (int w = index; w < WIDTH-index; w++)
    {
      int sum = imagevector[h * WIDTH + w];
      for (int i = 1; i < filtersize; i++)
      {
          for (int j = 1; j < filtersize; j++)
          {
            sum += imagevector[(h+i) * WIDTH + (w+j)];
            sum += imagevector[(h+i) * WIDTH + (w-j)];
            sum += imagevector[(h-i) * WIDTH + (w+j)];
            sum += imagevector[(h-i) * WIDTH + (w-j)];
          }
      }
      double average = (double) sum / (filtersize * filtersize - 1);
      cout << average << endl;
      imagevector[h * WIDTH + w] = (int) average;
    }
  }
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
      output << image[h*WIDTH + w] << " " << image[h*WIDTH + w] << " " << image[h*WIDTH + w] << " " << image[h*WIDTH + w] << " " << image[h*WIDTH + w] << " " << image[h*WIDTH + w] << " " << image[h*WIDTH + w] << " " << image[h*WIDTH + w] << " " << image[h*WIDTH + w] << " ";
    }
    output << endl;
  }
}
//Main driver
int main()
{
  //GrayScale using input ppm file image.ppm
  GrayScaleImage("image.ppm");
  //Gaussian Blur using project8ppm.ppm
  GaussianBlur(outputppm);
  WriteToPPM(outputppm);
  return 0;
}
