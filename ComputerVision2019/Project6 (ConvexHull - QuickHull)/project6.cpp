//Krish Patel
//Zacharias Period 3
//11/25/19
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>
int nsize = 75;
int nwidth = 800;
int n = 0;
using namespace std;
class Point
{
private:
    double x;
    double y;
public:
    Point(double x1, double y1)
    {
        x = x1;
        y = y1;
    }
    Point()
    {
        x = 0.0;
        y = 0.0;
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
vector<Point> pvector;
bool pixelarray[800][800];
vector<Point> convexHull;
void drawLine(Point p1, Point p2)
{
    double x1;
    double y1;
    double x2;
    double y2;
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
            pixelarray[i][(int)j] = true;
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
            y1 = temp;
            deltay = -deltay;
            double temp2 = x1;
            x1 = temp;
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
            pixelarray[(int) j][i] = true;
            if (epsilon >= 0)
            {
                j += increment;
                epsilon -= deltay;
            }
            epsilon += deltax;
        }
    }
}
Point minimumX(vector<Point> parray)
{
    Point minP;
    double minimum = 800;
    for (int index = 0; index < nsize; index++)
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
double distance(Point p1, Point p2)
{
    return sqrt((p2.getX()-p1.getX()) * (p2.getX()-p1.getX()) + (p2.getY()-p1.getY()) + (p2.getY()-p1.getY()));
}
Point maximumdistance(const vector<Point>& parray, Point a, Point b)
{
Point maxim;
double distance = 0.0;
for (auto p : parray)
{
    double value = abs((p.getY() - a.getY()) * (b.getX() - a.getX()) - (b.getY() - a.getY()) * (p.getX() - a.getX()));
    if (value > distance)
    {
        distance = value;
        maxim = p;
    }
}
return maxim;
}
Point maximumX(vector<Point> parray)
{
    Point maxP;
    double maximum = 0;
    for (int index = 0; index < nsize; index++)
    {
        auto p = parray[index];
        if (p.getX() > maximum)
        {
            maximum = p.getX();
            maxP = p;
        }
    }
    return maxP;
}
bool AboveLine(Point target, Point a, Point b)
{
    double deltay = b.getY() - a.getY();
    double deltax = b.getX() - a.getX();
    double slope = deltay/deltax;
    bool toRet = false;
    double value = ((slope * target.getX()) + (a.getY() - slope * a.getX()));
    if (target.getY() > value)
    {
        toRet = true;
    }
    return toRet;
}
//Update this method
double area(Point a, Point b, Point c)
{
    return abs((a.getX()*(b.getY()-c.getY()) + b.getX()*(c.getY()-a.getY())+ c.getX()*(a.getY()-b.getY()))/2.0);
}
bool insideTriangle(Point v1, Point v2, Point v3, Point target)
{
    double A = area(v1, v2, v3);
    double A1 = area(v1, v2, target);
    double A2 = area(v2, v3, target);
    double A3 = area(v1, v3, target);
    return (A == A1 + A2 + A3) > 0;
}
void FindHull(const vector<Point>& parray, Point p, Point q)
{
    vector<Point> s1;
    s1.resize(nsize);
    vector<Point> s2;
    s1.resize(nsize);
    int s1size = 0;
    int s2size = 0;
    Point c = maximumdistance(parray, p, q);
    n++;
    convexHull.resize(n);
    convexHull[n-1] = c;
    if ((parray).empty())
    {
        return;
    }
    else
    {
        //Loop below has problems -- Check the triangle correctly
        for (auto point : parray)
        {
            if (insideTriangle(p, q, c, point))
            {

            }
            else
            {
                if (AboveLine(point, p, c))
                {
                    s1[s1size] = point;
                    s1size++;
                }
                else if (AboveLine(point, q, c))
                {
                    s2[s2size] = point;
                    s2size++;
                }
                else
                {

                }

            }
        }
    }
        s1.resize(s1.size());
        s2.resize(s1.size());
        FindHull(s1, p, c);
        FindHull(s2, q, c);
}
void QuickHull(const vector<Point>& parray)
{
    Point a = minimumX(parray);
    n++;
    convexHull.resize(n);
    convexHull[n-1] = a;
    Point b = maximumX(parray);
    n++;
    convexHull.resize(n);
    convexHull[n-1] = b;
    vector<Point> pabove;
    pabove.resize(parray.size());
    vector<Point> pbelow;
    pbelow.resize(parray.size());
    int aboveindex = 0;
    int belowindex = 0;
    for (auto index : parray)
    {
        if (AboveLine(index, a, b))
        {
            pabove[aboveindex] = index;
            aboveindex++;
        }
        else
        {
            pbelow[belowindex] = index;
            belowindex++;
        }
    }
    pabove.resize(pabove.size());
    pbelow.resize(pbelow.size());
    FindHull(pabove, a, b);
    FindHull(pbelow, a, b);
}
int main()
{
    pvector.resize(nsize);
    //Initialize random point generator each run
    srand (time(nullptr));
    //Create PPM file and begin output stream
    ofstream output;
    output.open("project6ppm.ppm");
    output << "P3 800 800 6" << endl;
    for (int i = 0; i < nwidth; i++)
    {
        for (int j = 0; j < nwidth; j++)
        {
            pixelarray[i][j] = false;
        }
    }
    //Initialize Array of Points
    for (int index = 0; index < nsize; index++)
    {
        double rando;
        rando = (double) rand() / (double) RAND_MAX;
        double x = (rando * 800 + 0.05);
        double rand1;
        rand1 = (double) rand() / (double) RAND_MAX;
        double y = (rand1 * 800 + 0.05);
        Point p = Point(x, y);
        pvector[index] = p;
    }
    QuickHull(pvector);
    convexHull.shrink_to_fit();
    for (auto index = 1; convexHull.size() > index; index++)
    {
        cout << "(" << convexHull[index].getX() << ", " << convexHull[index].getY() << ") ";
        drawLine(convexHull[index], convexHull[index-1]);
    }
    for (int a = 790; a >= 0; a--)
    {
        for (int b = 0; b < nwidth; b++)
        {
            if (pixelarray[a][b])
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
