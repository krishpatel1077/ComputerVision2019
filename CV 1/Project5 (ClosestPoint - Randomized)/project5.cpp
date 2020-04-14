//Name: Krish Patel
//Project 5 Zacharias
//Date: 11/6/2019
#include <iostream>
#include <fstream>
#include <ctime>
#include <math.h>
#include <chrono>
#include <unordered_map>
#include <algorithm>
#include <random>

#define PPM_WIDTH 800
#define N_POINTS 100000

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
        Point(double x, double y) {
            x = x;
            y = y;
        }
        double getX() {
            return x;
        }
        double getY() {
            return y;
        }
        friend ostream& operator<<(ostream &strm, const Point &a) {
            return strm << "(" << a.x << ", " << a.y << ")";
        }

};

bool compareX(Point a, Point b) {
    return a.getX() < b.getX();
}

bool compareY(Point a, Point b) {
    return a.getY() < b.getY();
}

struct Color {
    bool r, b, g;
    Color () {
        this->r = true;
        this->g = true;
        this->b = true;
    }
    Color(bool r, bool g, bool b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

void dP(Color pixeldraw[], Point pixelarray[], Point closestPair[]) {
    for (int i = 0; i < N_POINTS; i++) {
        int x = (int) (pixelarray[i].getX() * PPM_WIDTH);
        int y = (int) (pixelarray[i].getY() * PPM_WIDTH);
        pixeldraw[y * PPM_WIDTH + x] = Color (false, false, false);
    }
    for (int i = 0; i < 2; i++) {
        int x = (int) (closestPair[i].getX() * PPM_WIDTH);
        int y = (int) (closestPair[i].getY() * PPM_WIDTH);
        pixeldraw[y * PPM_WIDTH + x] = Color (true, false, false);
    }
}

void gI(Color pixeldraw[]) {
    ofstream imageFile;
    imageFile.open("image.ppm");

    imageFile << "P3 " << PPM_WIDTH << " " << PPM_WIDTH << " 1" << endl;

    for (int y = PPM_WIDTH - 1; y >= 0; y--) {
        for (int x = 0; x < PPM_WIDTH; x++)
            imageFile << (int) pixeldraw[y * PPM_WIDTH + x].r << " " << (int) pixeldraw[y * PPM_WIDTH + x].g << " " << (int) pixeldraw[y * PPM_WIDTH + x].b << " ";
        imageFile << endl;
   }
}

double distance(Point p1, Point p2) {
    return sqrt((p2.getX() - p1.getX()) * (p2.getX() - p1.getX()) + (p2.getY() - p1.getY()) * (p2.getY() - p1.getY()));
}

double min(double x, double y) {
    return x < y ? x : y;
}

unordered_map<int, Point*>* makeDictionary(Point* pixelarray, int n, int num_squares, double side_length) {
    unordered_map<int, Point*>* dict = new unordered_map<int, Point*>();

    int x, y;
    for (int i = 0; i <= n; i++) {
        x = (int) (pixelarray[i].getX() / side_length);
        y = (int) (pixelarray[i].getY() / side_length);
        (*dict)[y * num_squares + x] = &pixelarray[i];
    }

    return dict;
}

Point* closestDictionary(Point* pixelarray) {
    double min_distance = 1;
    double side_length = min_distance / 2;
    int num_squares = (int) (1 / side_length);
    unordered_map<int, Point*>* dict = makeDictionary(pixelarray, -1, num_squares, side_length);
    Point* closestPair = new Point[2];

    int x, y;
    double temp_distance = 1;
    double other_distance = 1;

    Point* temp;
    Point* other;

    for (int i = 0; i < N_POINTS; i++) {
        cout << min_distance << endl;
        x = (int) (pixelarray[i].getX() / side_length);
        y = (int) (pixelarray[i].getY() / side_length);
        for (int ty = y - 2; ty <= y + 2; ty++)
            for (int tx = x - 2; tx <= x + 2; tx++) {
                if (dict->find(ty * num_squares + tx) != dict->end()) {
                    temp = dict->at(ty * num_squares + tx);
                    temp_distance = distance(pixelarray[i], *temp);
                    if (temp_distance < other_distance) {
                        other_distance = temp_distance;
                        other = temp;
                    }
                }
            }
        if (other_distance < min_distance) {
            min_distance = other_distance;
            side_length = min_distance / 2;
            num_squares = (int) (1 / side_length);
            closestPair[0] = pixelarray[i];
            closestPair[1] = *other;
            delete dict;
            dict = makeDictionary(pixelarray, i, num_squares, side_length);
        } else {
            (*dict)[y * num_squares + x] = &pixelarray[i];
        }
        temp_distance = 1;
        other_distance = 1;
        //cout << closestPair[0] << " " << closestPair[1] << endl;
    }
    return closestPair;
}

int main() {
    int seed = (unsigned)time(NULL);

    Point* pixelarray = new Point[N_POINTS];

    shuffle(pixelarray, pixelarray + N_POINTS, default_random_engine(seed));


    Color* pixeldraw = new Color[PPM_WIDTH * PPM_WIDTH];

    cout << "Number of Points:\t" << N_POINTS << endl;

    std::chrono::high_resolution_clock::time_point begin, end;

    begin = std::chrono::high_resolution_clock::now();

    Point* closestPair = closestDictionary(pixelarray);

    end = std::chrono::high_resolution_clock::now();
	cout << "Closest Pair(s):\t" << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << endl;

    cout << closestPair[0] << " " << closestPair[1] << endl;

    dP(pixeldraw, pixelarray, closestPair);

    gI(pixeldraw);

    return 0;
}
