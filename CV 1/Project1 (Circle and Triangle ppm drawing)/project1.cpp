//Krish Patel
//Period 3
//Zacharias
//9/13/19
#include <iostream>
#include <fstream>
#include <string>
#include "math.h"
#include <ctime>
#include <cstdlib>
using namespace std;
bool pixelarray[800][800];
int xy[2];
void ppmwriteline(int x1, int y1, int x2, int y2);
void ppmwrtecircle(int x, int y, double radius);
void intersection(int x1, int x2, int x3, int y1, int y2, int y3, double slope1, double slope2, double slope3);
int main(){
  srand (time(NULL));
  ofstream output;
  output.open("project1ppm.ppm");
  output << "P3 800 800 1" << endl;
  for (int i = 0; i < 800; i++)
  {
    for (int j = 0; j < 800; j++)
    {
      pixelarray[i][j] = false;
    }
  }

  double rando = (double)rand() / (double)RAND_MAX;
  int x1 = (int) (rando * 800 + 0.05);
  double rand1 = (double)rand() / (double)RAND_MAX;
  int y1 = (int) (rand1 * 800 + 0.05);
  double rand2 = (double)rand() / (double)RAND_MAX;
  int x2 = (int) (rand2 * 800 + 0.05);
  double rand3 = (double)rand() / (double)RAND_MAX;
  int y2 = (int) (rand3 * 800 + 0.05);
  double rand4 = (double)rand() / (double)RAND_MAX;
  int x3 = (int) (rand4 * 800 + 0.05);
  double rand5 = (double)rand() / (double)RAND_MAX;
  int y3 = (int) (rand5 * 800 + 0.05);
  cout << "(x1, y1); (x2, y2); (x3, y3)" << endl;
  cout << "(" << x1 << ", " << y1 << ")" << endl;
  cout << "(" << x2 << ", " << y2 << ")" << endl;
  cout << "(" << x3 << ", " << y3 << ")" << endl;

  pixelarray[x1][y1] = true;
  pixelarray[x2][y2] = true;
  pixelarray[x3][y3] = true;

  ppmwriteline(x1, y1, x2, y2);
  ppmwriteline(x2, y2, x3, y3);
  ppmwriteline(x3, y3, x1, y1);

  //FIND THE X4, Y4 VALUE

  cout << endl;

  int mx1 = (x1 + x2) * 0.5;
  int mx2 = (x2 + x3) * 0.5;
  int my1 = (y1 + y2) * 0.5;
  int my2 = (y2 + y3) * 0.5;
  int mx3 = (x1 + x3) * 0.5;
  int my3 = (y1 + y3) * 0.5;
  cout << "(mx1, my1); (mx2, my2); (mx3, my3)" << endl;
  cout << "(" << mx1 << ", " << my1 << ")" << endl;
  cout << "(" << mx2 << ", " << my2 << ")" << endl;
  cout << "(" << mx3 << ", " << my3 << ")" << endl;

  double slope1 = (double)(y2 - y1)/(x2 - x1);
  double slope2 = (double)(y3 - y2)/(x3 - x2);
  double slope3 = (double)(y3 - y1)/(x3 - x1);

  double p1 = -1 / slope1;
  double p2 = -1 / slope2;
  double p3 = -1 / slope3;

  intersection(mx1, mx2, mx3, my1, my2, my3, p1, p2, p3);
  int x4 = xy[0];
  int y4 = xy[1];

  double a = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
  double b = sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2));
  double c = sqrt((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1));
  double s = (a + b + c) * 0.5;

  double a1, b1, c1, s1;
  a1 = sqrt((mx2-mx1)*(mx2-mx1)+(my2-my1)*(my2-my1));
  b1 = sqrt((mx3-mx2)*(mx2-mx2)+(my3-my2)*(my3-my2));
  c1 = sqrt((mx3-mx1)*(mx3-mx1)+(my3-my1)*(my3-my1));
  s1 = (a1 + b1 + c1) * 0.5;
  double mslope1 = (double)(my2-my1)/(mx2-mx1);
  double mslope2 = (double)(my3-my2)/(mx3-mx2);
  double mslope3 = (double)(my3-my1)/(mx3-mx1);
  double mp1 = -1 / mslope1;
  double mp2 = -1 / mslope2;
  double mp3 = -1 / mslope3;
  int mmx1 = (mx1 + mx2)/2;
  int mmx2 = (mx2 + mx3)/2;
  int mmx3 = (mx3 + mx1)/2;
  int mmy1 = (my1 + my2)/2;
  int mmy2 = (my2 + my3)/2;
  int mmy3 = (my3 + my1)/2;
  intersection(mmx1, mmx2, mmx3, mmy1, mmy2, mmy3, mp1, mp2, mp3);
  int centerx = xy[0];
  int centery = xy[1];
  cout << endl;
  cout << "circumcenter(x4, y4)" << endl;
  cout << "(" << x4 << ", " << y4 << ")" << endl;

  double cradius = sqrt((x4 - x1) * (x4 - x1) + (y4 - y1) * (y4 - y1));
  cout << "Outer radius " << cradius << endl;
  ppmwrtecircle(x4, y4, cradius);
  double perimiter = a + b + c;
  int ix4 = (b * x1 + c * x2 + a * x3)/perimiter;
  int iy4 = (b * y1 + c * y2 + a * y3)/perimiter;
  double iradius = sqrt(((s-a) * (s-b) * (s-c)) / s);
  cout << endl;
  cout << "incenter(ix4, iy4)" << endl;
  cout << "(" << ix4 << ", " << iy4 << ")" << endl;
  cout << "Inner radius " << iradius << endl;
  ppmwrtecircle(ix4, iy4, iradius);


  double ninepointradius = cradius/2;
  cout << endl;
  cout << "ninepointcenter(ox4, oy4)" << endl;
  cout << "(" << centerx << ", " << centery << ")" << endl;
  cout << "Nine Point Circle radius " << ninepointradius << endl;
  ppmwrtecircle(centerx, centery, ninepointradius);
  for (int a = 790; a >= 0; a--)
  {
    for (int b = 0; b < 800; b++)
    {
      if (pixelarray[a][b] == true)
      {
        output << "0 0 0 ";
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
void ppmwrtecircle(int cx, int cy, double radius)
{
  int x, y, xmax, y2, y2_new, ty;
  xmax = (int) (radius * 0.70710678); // maximum x at radius/sqrt(2)
  y = (int) radius;
  y2 = y * y;
  ty = (2 * y) - 1;
  y2_new = y2;
  for (x = 0; x <= xmax; x++)
  {
  if ((y2 - y2_new) >= ty)
  {
  y2 -= ty;
  y -= 1;
  ty -= 2;
  }
  if (cx + x < 800 && cy + y < 800)
  pixelarray[cx + x][cy + y] = true;
  else
  {}
  if (cx + x < 800 && cy - y > 0)
  pixelarray[cx + x][cy - y] = true;
  else
  {}
  if (cx - x > 0 && cy + y < 800)
  pixelarray[cx - x][cy + y] = true;
  else
  {}
  if (cx - x > 0 && cy - y > 0)
  pixelarray[cx - x][cy - y] = true;
  else
  {}

  if (cx + y < 800 && cy + x < 800)
  pixelarray[cx + y][cy + x] = true;
  else
  {}
  if (cx + y < 800 && cy - x > 0)
  pixelarray[cx + y][cy - x] = true;
  else
  {}
  if (cx - y > 0 && cy + x < 800)
  pixelarray[cx - y][cy + x] = true;
  else
  {}
  if (cx - y > 0 && cy - x > 0)
  pixelarray[cx - y][cy - x] = true;
  else
  {}

  y2_new -= (2 * x) - 3;
  }
}
void ppmwriteline(int x1, int y1, int x2, int y2)
{
  int deltax = x2-x1;
  int deltay = y2-y1;
  int inc = 1;
  if (abs(deltax) >= abs(deltay))
  {
    if (x1 > x2)
    {
      int temp = y1;
      y1 = y2;
      y2 = temp;
      deltay *= -1;
      int temp2 = x1;
      x1 = x2;
      x2 = temp2;
      deltax *= -1;
    }
    if (deltay < 0)
    {
      inc *= -1;
      deltay *= -1;
    }
    int j = y1;
    int epsilon = deltay-deltax;
    for (int i = x1; i <= x2-1; i++)
    {
      pixelarray[i][j] = true;
      if (epsilon >= 0)
      {
        j += inc;
        epsilon -= deltax;
      }
        epsilon += deltay;
    }
  }
  else
  {
    if (y1 > y2)
    {
      int temp = y1;
      y1 = y2;
      y2 = temp;
      deltay = -deltay;
      int temp2 = x1;
      x1 = x2;
      x2 = temp2;
      deltax = -deltax;
    }
    if (deltax < 0)
    {
      inc *= -1;
      deltax *= -1;
    }
    int j = x1;
    int epsilon = deltay - deltax;
    for (int i = y1; i <= y2-1; i++)
    {
      pixelarray[j][i] = true;
      if (epsilon >= 0)
      {
        j += inc;
        epsilon -= deltay;
      }
        epsilon += deltax;
    }
  }
}
void intersection(int x1, int x2, int x3, int y1, int y2, int y3, double slope1, double slope2, double slope3){
    double numerator1x = ((slope1 * x1) - (slope2 * x2) + y2 - y1);
    double denomiator1x = slope1-slope2;
    double tot1x = numerator1x / denomiator1x;
    int intersectionx = (int) tot1x;
    double numerator1y = slope2 * slope1 * x2 - slope1 * y2 + y1 * slope2 - slope2 * slope1 * x1;
    double denominator1y = slope2 - slope1;
    double tot1y = numerator1y / denominator1y;
    int intersectiony = (int) tot1y;

    xy[0] = intersectionx;
    xy[1] = intersectiony;
}
