#include <iostream>
#include <fstream>
#include <ctime>
#include <math.h>
#include <algorithm>
#include <chrono>
#define PPMWIDTH 800
#define CHOOGMANSIZE 1000000
using namespace std;
class Point {
    private:
        double x;
        double y;
    public:
        Point() {
            x = (double) rand() / RAND_MAX;
            y = (double) rand() / RAND_MAX;
        }
        Point(double x1, double y1) {
            x = x1;
            y = y1;
        }
        double getX() {
            return x;
        }
        double getY() {
            return y;
        }
};
bool compareX(Point a, Point b) {
    return a.getX() < b.getX();
}
bool compareY(Point a, Point b) {
    return a.getY() < b.getY();
}
struct RGBgrid {
    bool r, b, g;
    RGBgrid () {
        r = true;
        g = true;
        b = true;
    }
    RGBgrid(bool r, bool g, bool b) {
        r = r;
        g = g;
        b = b;
    }
};
void dp(RGBgrid pixMap[], Point parray[], Point cpARR[]) {
    for (int i = 0; i < CHOOGMANSIZE; i++) {
        int x = (int) (parray[i].getX() * PPMWIDTH);
        int y = (int) (parray[i].getY() * PPMWIDTH);
        pixMap[y * PPMWIDTH + x] = RGBgrid (false, false, false);
    }
    for (int i = 0; i < 2; i++) {
        int x = (int) (cpARR[i].getX() * PPMWIDTH);
        int y = (int) (cpARR[i].getY() * PPMWIDTH);
        pixMap[y * PPMWIDTH + x] = RGBgrid (true, false, false);
    }
}
void gI(RGBgrid pixMap[]) {
    ofstream imageFile;
    imageFile.open("image.ppm");
    imageFile << "P3 " << PPMWIDTH << " " << PPMWIDTH << " 1" << endl;
    for (int y = PPMWIDTH - 1; y >= 0; y--) {
        for (int x = 0; x < PPMWIDTH; x++)
            imageFile << (int) pixMap[y * PPMWIDTH + x].r << " " << (int) pixMap[y * PPMWIDTH + x].g << " " << (int) pixMap[y * PPMWIDTH + x].b << " ";
        imageFile << endl;
   }
}
double distance(Point p1, Point p2) {
    return sqrt((p2.getX() - p1.getX()) * (p2.getX() - p1.getX()) + (p2.getY() - p1.getY()) * (p2.getY() - p1.getY()));
}
double min(double x, double y) {
    return x < y ? x : y;
}
Point* cpgbl;
double* minD;
double bruteForce(Point parray[], int n) {
    Point* cpARR = new Point[2];
    double md = 1;
    double temp;
    for (int i = 0; i <= n; i++)
        for (int j = i + 1; j <= n; j++) {
            temp = distance(parray[i], parray[j]);
            if (temp < md) {
                md = temp;
                cpARR[0] = parray[i];
                cpARR[1] = parray[j];
            }
        }
    if (md < *minD) {
        cpgbl[0] = cpARR[0];
        cpgbl[1] = cpARR[1];
        *minD = md;
    }
    delete[] cpARR;
    return md;
}
double utilityStrip(Point strip[], int n, double d) {
    Point* cpARR = new Point[2];
    double md = d;
    double temp;
    sort(strip, strip + n, compareY);
    int count;
    for (int i = 0; i < n; i++) {
        count = 0;
        for (int j = i + 1; j < n && (strip[j].getY() - strip[i].getY()) < d; j++) {
            temp = distance(strip[i], strip[j]);
            if (temp < md) {
                md = temp;
                cpARR[0] = strip[i];
                cpARR[1] = strip[j];
            }
            if (++count > 7)
                break;
        }
    }
    if (md < *minD) {
        cpgbl[0] = cpARR[0];
        cpgbl[1] = cpARR[1];
        *minD = md;
    }
    delete[] cpARR;
    return md;
}
double cPS(Point parray[], int n) {
    if (n <= 3)
        return bruteForce(parray, n);
    int mid = n / 2;
    Point mp = parray[mid];
    double md = min(cPS(parray, mid), cPS(parray + mid, n - mid));
    Point* strip = new Point[n];
    int count = 0;
    for (int i = 0; i < n; i++)
        if (abs(parray[i].getX() - mp.getX()) < md) {
            strip[count] = parray[i];
            count++;
        }
    md = min(utilityStrip(strip, count, md), md);
    delete[] strip;
    return md;
}
double cPB(Point parray[], int n) {
    if (n <= 3)
        return bruteForce(parray, n);
    int mid = n / 2;
    Point mp = parray[mid];
    double md = min(cPB(parray, mid), cPB(parray + mid, n - mid));
    Point* strip = new Point[n];
    int count = 0;
    for (int i = 0; i < n; i++)
        if (abs(parray[i].getX() - mp.getX()) < md) {
            strip[count] = parray[i];
            count++;
        }
    md = min(bruteForce(strip, count), md);
    delete[] strip;
    return md;
}
void cS(Point parray[]) {
    minD = new double(1);
    cpgbl = new Point[2];
    sort(parray, parray + CHOOGMANSIZE, compareX);
    cPS(parray, CHOOGMANSIZE);
}
void cB(Point parray[]) {
    minD = new double(1);
    cpgbl = new Point[2];
    sort(parray, parray + CHOOGMANSIZE, compareX);
    cPB(parray, CHOOGMANSIZE);
}
int main() {
    srand((unsigned)time(NULL));
    Point* parray = new Point[CHOOGMANSIZE];
    RGBgrid* pixMap = new RGBgrid[PPMWIDTH * PPMWIDTH];
    cout << "Number of Points:\t" << CHOOGMANSIZE << endl;
    std::chrono::high_resolution_clock::time_point begin, end;
    minD = new double(1);
    cpgbl = new Point[2];
  //   begin = std::chrono::high_resolution_clock::now();
  //   bruteForce(parray, CHOOGMANSIZE);
  //   end = std::chrono::high_resolution_clock::now();
	// cout << "Brute Force:\t\t" << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << endl;
  //   delete minD;
  //   delete[] cpgbl;
    begin = std::chrono::high_resolution_clock::now();
    cB(parray);
    end = std::chrono::high_resolution_clock::now();
	cout << "Recursive (BF):\t\t" << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << endl;
    delete minD;
    delete[] cpgbl;
    begin = std::chrono::high_resolution_clock::now();
    cS(parray);
    end = std::chrono::high_resolution_clock::now();
	cout << "Recursive (nlogn):\t" << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << endl;
    dp(pixMap, parray, cpgbl);
    delete minD;
    delete[] cpgbl;
    gI(pixMap);
    return 0;
}
