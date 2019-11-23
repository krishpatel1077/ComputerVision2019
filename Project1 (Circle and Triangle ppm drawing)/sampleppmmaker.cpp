#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main()
{
  int rows, cols;
  rows = 20;
  cols = 10;
  int pixelarr[rows][cols];
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      if (i > 5 && i < 12) {
        if (j > 3 && j < 7)
        {
          pixelarr[i][j] = 1;
        }
      }
      else if ((i == 5 || i == 12) && (j > 3 && j < 7))
      {
        pixelarr[i][j] = 1;
      }
      else
      {
        pixelarr[i][j] = 0;
      }
    }
  }
  ofstream output;
  output.open("ppmtester1.ppm");
  output << "P3 20 10 1";
  output << "\n";
  for (int r = 0; r < rows; r++)
  {
    for (int c = 0; c < cols; c++)
    {
      if (pixelarr[r][c] == 0)
      {
        output << ("0 0 0 ");
      }
      else
      output  <<("1 1 1 ");
    }
    output << '\n';
  }
  return 0;
}
