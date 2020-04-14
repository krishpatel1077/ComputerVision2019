//Krish Patel
//Period 3 Zacharias
//Project 2
#include <iostream>
#include <fstream>
#include <string>
#include "math.h"
#include <ctime>
#include <cstdlib>
using namespace std;
class Point
{
private:
  int x, y;
public:
  Point(int x1, int y1)
  {
    x = x1;
    y = y1;
  }
  int getX(){ return x; }
  int getY(){ return y; }
  void setX(int x4){ x = x4; }
  void setY(int y4){ y = y4; }
  double distance(Point* other)
  {
    int x1 = other -> getX();
    int y1 = other -> getY();
    return sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));
  }
};
int pixelarray[800][800];
Point* parray[40];
int main()
{
  srand (time(NULL));
  ofstream output;
  output.open("project2ppm.ppm");
  output << "P3 800 800 1" << endl;
  for (int i = 0; i < 800; i++)
  {
    for (int j = 0; j < 800; j++)
    {
      pixelarray[i][j] = 0;
    }
  }
  for (int i = 0; i < 40; i++)
  {
    double rando = (double)rand() / (double)RAND_MAX;
    int x = (int) (rando * 800 + 0.05);
    double rand1 = (double)rand() / (double)RAND_MAX;
    int y = (int) (rand1 * 800 + 0.05);
    parray[i] = new Point(x, y);
  }
  double mindistance = parray[0] -> distance(parray[1]);
  Point *p1 = parray[0];
  Point *p2 = parray[1];
  for (int a = 0; a < 40; a++)
  {
    for (int b = 0; b < 40; b++)
    {
      if (a == b)
      {}
      else
      {
      if (parray[a] -> distance(parray[b]) < mindistance)
      {
        mindistance = parray[a] -> distance(parray[b]);
        p1 = parray[a];
        p2 = parray[b];
      }
    }
    }
  }
  for (int x = 0; x < 40; x++)
  {
    pixelarray[parray[x] -> getX()][parray[x] -> getY()] = 1;
  }
  pixelarray[p1 -> getX()][p1 -> getY()] = 2;
  pixelarray[p2 -> getX()][p2 -> getY()] = 2;
  for (int a = 790; a >= 0; a--)
  {
    for (int b = 0; b < 800; b++)
    {
      if (pixelarray[a][b] == 0)
      {
        output << "1 1 1 ";
      }
      else if (pixelarray[a][b] == 1)
      {
        output << "0 0 0 ";
      }
      else
      {
        output << "1 0 0 ";
      }
    }
    output << endl;
  }
  return 0;
}
