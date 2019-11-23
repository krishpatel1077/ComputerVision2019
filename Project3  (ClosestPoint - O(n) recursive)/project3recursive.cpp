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
public:
  int x, y;
  Point(int x1, int y1)
  {
    x = x1;
    y = y1;
  }
};
int FLT_MAX = 99999;
int n = 400;
int pixelarray[800][800];
Point* parray[400];
Point* PointLEFT[200];
Point* PointRIGHT[200];

int compareX(const void* a, const void* b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1 -> x - p2 -> x);
}
int compareY(const void* a, const void* b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1 -> y - p2 -> y);
}
int distance(Point p, Point p1)
{
  return sqrt((p1.x - p.x) * (p1.x - p.x) + (p1.y - p.y) * (p1.y - p.y));
}
int minimum(int a, int b)
{
  if (a < b)
  return a;

  return b;
}
//(below) must be recursively done. Right now it is iterative, this should be changed.
int* ClosestPair(Point* pointarray, int n)
{
  int toRet[5] = {0, 0, 0, 0, 0};
  int min = FLT_MAX;
  for (int i = 0; i < n; i++)
  {
    for (int j = i+1; j < n; j++)
    {
      if (distance(pointarray[i], pointarray[j]) < min)
      {
        toRet[0] = distance(pointarray[i], pointarray[j]);
        toRet[1] = pointarray[i].x;
        toRet[2] = pointarray[i].y;
        toRet[3] = pointarray[j].x;
        toRet[4] = pointarray[j].y;
      }
    }
  }
  return toRet;
}
using namespace std;
int main()
{
  srand (time(NULL));
  ofstream output;
  output.open("project3ppm.ppm");
  output << "P3 800 800 1" << endl;
  for (int i = 0; i < 800; i++)
  {
    for (int j = 0; j < 800; j++)
    {
      pixelarray[i][j] = 0;
    }
  }
  for (int i = 0; i < 400; i++)
  {
    double randomint = (double)rand() / (double)RAND_MAX;
    int x = (int) (randomint * 800 + 0.05);
    double randomint1 = (double)rand() / (double)RAND_MAX;
    int y = (int) (randomint1 * 800 + 0.05);
    parray[i] = new Point(x, y);
  }

  qsort(parray, n, sizeof(Point), compareX);
  for (int i = 0; i < n; i++)
  {
    if (i < n/2)
    {
      PointLEFT[i-0] = parray[i];
    }
    PointRIGHT[i-(n/2)] = parray[i];
  }

  int* d1[5] = ClosestPair(PointLEFT, n/2);
  int* d2[5] = ClosestPair(PointRIGHT, n/2);
  int distancemin = minimum(d1[0], d2[0]);
  if (distancemin == d1[0])
  {
    pixelarray[d1[1]][d1[2]] = 2;
    pixelarray[d1[3]][d1[4]] = 2;
  }
  else
  {
    pixelarray[d2[1]][d2[2]] = 2;
    pixelarray[d2[3]][d2[4]] = 2;
  }
  /*
use min distance d on either side of halfway mark, find the ClosestPair recursively
  */
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
