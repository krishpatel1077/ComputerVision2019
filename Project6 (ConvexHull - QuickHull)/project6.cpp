//Krish Patel
//Zacharias Project 6
//Period 3
#include <iostream>
#include <fstream>
#include <ctime>
#include <math.h>
#include <cstdlib>
#include <algorithm>
#include "math.h"
#define NUM_POINTS 1000
#define PPM_WIDTH 800
using namespace std;
//Point Class
class Point
{
private:
  double x, y;
public:
  Point()
  {
    x = 0;
    y = 0;
  }
  Point(double x1, double y1)
  {
    x = x1;
    y = y1;
  }
  double getX()
  {
    return x;
  }
  double getY()
  {
    return y;
  }
};
//Initialize PPM writer array and array of Points
int[PPM_WIDTH][PPM_WIDTH] pixelarray;
Point[NUM_POINTS] parray;
//Initialize drawing helper methods (drawLine, removeLine)
void drawLine(Point p1, Point p2)
{
  double x1, y1, x2, y2;
  x1 = p1.getX();
  x2 = p2.getX();
  y1 = p1.getY();
  y2 = p2.getY();
  double deltax, deltay;
  deltax = x2-x1;
  deltay = y2-y1;
  int increment;
  increment = 1;
  if (abs(deltax) >= abs(deltay))
  {
    if (x1 > x2)
    {
      double temp = y1;
      y1 = y2;
      y2 = temp;
      deltay *= -1;
      double temp2 = x1;
      x1 = x2;
      x2 = temp2;
      deltax *= -1;
    }
    if (deltay < 0)
    {
      increment *= -1;
      deltay *= -1;
    }
    double j = y1;
    double epsilon = deltay-deltax;
    for (int i = (int) x1; i <= (int) (x2-1); i++)
    {
      pixelarray[i][(int)j] = 1;
      if (epsilon >= 0)
      {
        j += increment;
        epsilon -= deltax;
      }
        epsilon += deltay;
    }
  }
  else
  {
    if (y1 > y2)
    {
      double temp = y1;
      y1 = y2;
      y2 = temp;
      deltay = -deltay;
      double temp2 = x1;
      x1 = x2;
      x2 = temp2;
      deltax = -deltax;
    }
    if (deltax < 0)
    {
      increment *= -1;
      deltax *= -1;
    }
    double j = x1;
    double epsilon = deltay - deltax;
    for (int i = (int) y1; i <= (int) (y2-1); i++)
    {
      pixelarray[(int) j][i] = 1;
      if (epsilon >= 0)
      {
        j += increment;
        epsilon -= deltay;
      }
        epsilon += deltax;
    }
  }
}
void removeLine(Point p1, Point p2)
{
  double x1, y1, x2, y2;
  x1 = p1.getX();
  x2 = p2.getX();
  y1 = p1.getY();
  y2 = p2.getY();
  double deltax, deltay;
  deltax = x2-x1;
  deltay = y2-y1;
  int increment;
  increment = 1;
  if (abs(deltax) >= abs(deltay))
  {
    if (x1 > x2)
    {
      double temp = y1;
      y1 = y2;
      y2 = temp;
      deltay *= -1;
      double temp2 = x1;
      x1 = x2;
      x2 = temp2;
      deltax *= -1;
    }
    if (deltay < 0)
    {
      increment *= -1;
      deltay *= -1;
    }
    double j = y1;
    double epsilon = deltay-deltax;
    for (int i = (int) (x1+1); i <= (int) (x2-1); i++)
    {
      pixelarray[i][(int)j] = 1;
      if (epsilon >= 0)
      {
        j += increment;
        epsilon -= deltax;
      }
        epsilon += deltay;
    }
  }
  else
  {
    if (y1 > y2)
    {
      double temp = y1;
      y1 = y2;
      y2 = temp;
      deltay = -deltay;
      double temp2 = x1;
      x1 = x2;
      x2 = temp2;
      deltax = -deltax;
    }
    if (deltax < 0)
    {
      increment *= -1;
      deltax *= -1;
    }
    double j = x1;
    double epsilon = deltay - deltax;
    for (int i = (int) (y1+1); i <= (int) (y2-1); i++)
    {
      pixelarray[(int) j][i] = 1;
      if (epsilon >= 0)
      {
        j += increment;
        epsilon -= deltay;
      }
        epsilon += deltax;
    }
  }
}
//Helper Methods for Point Array
int realsize(Point[] parray)
{
  int size;
  for (int i = 0; i < sizeof(parray); i++)
  {
    if (parray[index] != null)
    {
      size++;
    }
  }
  return size;
}
void arrayDump(Point[] a, Point[] b)
{
//a is target, b is dumper
for (int index = 0; index < sizeof(a); index++)
{
  a[index] = b[index];
}
}
Point minimumX(Point[] parray)
{
Point minP;
double minimum = 800;
for (int index = 0; index < NUM_POINTS; index++)
{
  Point p = parray[index];
  if (p.getX() < minimum)
  {
    minimum = p.getX();
    minP = p;
  }
}
return minP;
}
Point maximumX(Point[] parray)
{
  Point maxP;
  double maximum = 800;
  for (int index = 0; index < NUM_POINTS; index++)
  {
    Point p = parray[index];
    if (p.getX() < maximum)
    {
      maximum = p.getX();
      maxP = p;
    }
  }
  return maxP;
}
double distance(Point a, Point b)
{
return sqrt((b.getX() - a.getX()) * ((b.getX() - a.getX()) + (b.getY() - a.getY()) * ((b.getY() - a.getY()));
}
Point maximumdistance(Point[] parray, Point a, Point b)
{
  double distanceA, distanceB = 0;
  Point p;
  for (int index = 0; index < realsize(parray); index++)
  {
    Point point = parray[index];
    if (distance(a, point) > distanceA && distance(b, point) > distanceB)
    {
      p = point;
      distanceA = distance(a, point);
      distanceB = distance(b, point);
    }
  }
}
bool AboveLine(Point target, Point a, Point b)
{
  return ((b.getX() - a.getX()) * (target.getY() - a.getY()) - (b.getY() - a.getY()) * (target.getX() - a.getX())) > 0;
}
//Call QuickHull for parray
void QuickHull(Point[] parray)
{
Point a = minimumX(parray);
Point b = maximumX(parray);
Point[NUM_POINTS] pabove;
Point[NUM_POINTS] pbelow;
int aboveindex = 0;
int belowindex = 0;
for (int index = 0; index < NUM_POINTS; index++)
{
  if (AboveLine(parray[index], a, b))
  {
    pabove[aboveindex] = parray[index];
    aboveindex++;
  }
  else
  {
    pbelow[belowindex] = parray[index];
    belowindex++;
  }
}
Point[realsize(pabove)] s1;
arrayDump(s1, pabove);
Point[realsize(pbelow)] s2;
arrayDump(s2, pbelow);

FindHull(s1, a, b);
FindHull(s2, a, b);
}
void FindHull(Point[] parray, Point P, Point Q)
{
if (sizeof(parray) < 1)
{
  return;
}

}
//Main Driver
int main()
{
  //Initialize random point generator each run
  srand (time(NULL));
  //Create PPM file and begin output stream
  ofstream output;
  output.open("project2ppm.ppm");
  output << "P3 800 800 6" << endl;
  for (int i = 0; i < PPM_WIDTH; i++)
  {
    for (int j = 0; j < PPM_WIDTH; j++)
    {
      pixelarray[i][j] = false;
    }
  }
  //Initialize Array of Points
  for (int i = 0; i < NUM_POINTS; i++)
  {
    double rando = (double)rand() / (double)RAND_MAX;
    double x = (rando * 800 + 0.05);
    double rand1 = (double)rand() / (double)RAND_MAX;
    double y = (rand1 * 800 + 0.05);
    parray[i] = new Point(x, y);
  }
  //Call QuickHull for parray
  QuickHull(parray);
  //Output pixelarray onto the PPM (Black and White)
  for (int a = 790; a >= 0; a--)
  {
    for (int b = 0; b < 800; b++)
    {
      if (pixelarray[a][b] == 1)
      {
        output << "0 0 0 ";
      }
      else if (pixelarray[a][b] == 2)
      {
        ouput << "1 0 0 ";
      }
      else
      {
        output << "1 1 1 ";
      }
    }
    output << endl;
  }
  return 0;
}
