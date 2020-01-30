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
vector<float> outputppm;

void ReadToVector(vector<float> outputppm, const char *file)
{
    ifstream imageFile(file);
    short int colorSize;
    imageFile >> imageType;
    imageFile >> WIDTH;
    imageFile >> HEIGHT;
    imageFile >> colorSize;
    vector<float> image(WIDTH * HEIGHT);
    int r, g, b;
    int index = 0;
    if (imageType.compare("P3") == 0)
    {
    while (index < image.size())
      {
        imageFile >> r >> g >> b;
        string total = to_string(r) + to_string(g) + to_string(b);
        int t = stoi(total);
        image[index++] = t;
      }
    }
    colorSize += 1;
    if (colorSize != 256)
        for (int i = 0; i < image.size(); i++)
            image[i] = (image[i] + 1) * (256 / colorSize) - 1;
    imageFile.close();
    outputppm = image;
}

void coins1()
{
ReadToVector(outputppm, "coins1.ppm");

}

void coins2()
{

}
void coins3()
{

}    
int main()
{

}