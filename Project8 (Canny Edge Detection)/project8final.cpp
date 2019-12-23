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
using namespace std;
class Pixel
{
    private:
        int r, g, b, totalnum;
    public:
        Pixel()
        {
            r = 0;
            g = 0;
            b = 0;
            totalnum = -1;
        }
        Pixel(int total)
        {
           totalnum = total; 
        }
        Pixel(int x, int y, int z)
        {
            r = x; g = y; b = z; totalnum = -1;
        }
        int totalvalue()
        {
            if (totalnum != -1)
            {
                return totalnum;
            }   
            string s, s1, s2;
            s = to_string(r);
            s1 = to_string(g);
            s2 = to_string(b);
            string total = s + s1 + s2;
            return stoi(total);

        }
        string toString()
        {
            return "" + totalvalue();
        }
};

vector<Pixel> outputppm;

void GrayScaleImage(const char *filename)
{
  ifstream imageFile(filename);
  short int colorSize;
  imageFile >> imageType;
  imageFile >> WIDTH;
  imageFile >> HEIGHT;
  imageFile >> colorSize;
  vector<Pixel> image(WIDTH * HEIGHT);
  int r, g, b, r1, r2, g1, g2, b1, b2;
  int index = 0;
  while (index < image.size())
  {
      imageFile >> r >> g >> b >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;
      Pixel p = Pixel(r, g, b);
      Pixel p1 = Pixel(r1, g1, b1);
      Pixel p2 = Pixel(r2, g2, b2);
      int average = (p.totalvalue() + p1.totalvalue() + p2.totalvalue()) / 3;
      image[index] = Pixel(average);
  }
  colorSize += 1;
  imageFile.close();
  outputppm = image;
}
void WriteToPPM(vector<Pixel> image)
{
ofstream output;
output.open("project8ppm.ppm");
output << imageType << WIDTH << HEIGHT << "255" << endl;
for (int w = 0; w < WIDTH; w++)
{
    for (int h = 0; h < HEIGHT; h++)
        for (int i = 0; i < 8; i++)
            output << image[h * WIDTH + w].totalvalue() << " ";
}
}
int main()
{
GrayScaleImage("image.ppm");
WriteToPPM(outputppm);
}
