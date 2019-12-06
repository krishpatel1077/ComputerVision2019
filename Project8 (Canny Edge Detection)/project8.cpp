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
//Methods go here
vector<unsigned char> GrayScaleImage(const char *file)
{
  int wtemp, htemp;
  string iT;
  ifstream imageFile(file, ios::in | ios::binary);
  short int colorSize;
  imageFile >> iT >> wtemp >> htemp >> colorSize;
  imageType = iT;
  WIDTH = wtemp;
  HEIGHT = htemp;
  vector<unsigned char> image(WIDTH * HEIGHT);
  unsigned char r, g, b;
  int index = 0;
  if (imageType.compare("P3") == 0)
  {
    while (index < image.size())
      if (imageFile >> r >> g >> b)
        image[index++] = (unsigned char)(r + g + b) / 3;
      else
        cerr << "/* ERROR: PPM file was not read correctly */" << '\n';
  }
  else if (imageType.compare("P6") == 0)
  {
    unsigned char temp[3];
    while (index < image.size())
      if (imageFile.read((char *)temp, 3))
        image[index++] = (unsigned char)((temp[1] + temp[2] + temp[3]) / 3);
      else
        cerr << "/* ERROR: PPM file was not read correctly */" << '\n';
  }
  colorSize += 1;
  if (colorSize != 256)
    for (int i = 0; i < image.size(); i++)
      image[i] = (image[i] + 1) * (256 / colorSize) - 1;
  imageFile.close();
  return image;
}
void GaussianFilter(vector<unsigned char> image)
{
}
//Main driver
int main()
{
  //GrayScale the inputted ppm file
  cout << "WIDTH: " << WIDTH << endl;
  cout << "HEIGHT: " << HEIGHT << endl;
  cout << "PPM TYPE: " << imageType << endl;
  ofstream output;
  output.open("project8ppm.ppm");
  output << imageType << " " << WIDTH << " " << HEIGHT << " 255" << endl;
  vector<unsigned char> imageMagik;
  imageMagik = GrayScaleImage("image.ppm");
  //Apply Gaussian Filter
  for (int h = 0; h < HEIGHT; h++)
  {
    for (int w = 0; w < WIDTH; w++)
    {
      output << imageMagik[h*WIDTH + w] << " ";
    }
    output << endl;
  }
  return 0;
}
