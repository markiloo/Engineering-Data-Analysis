#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#ifndef LINEFIT_H
#define LINEFIT_H

using namespace std;

class LineFit
{
  private:
    string file_adress;
    double slope;
    double Y_intercept;
    double sum_of_x = 0;
    double sum_of_x_squared = 0;
    double sum_of_y = 0;
    double sum_of_x_times_y = 0;
    double n = 0;

    vector<double> X_coordinates;
    vector<double> Y_coordinates;

    void ComputeSlope();
    void ComputeIntercept();
    void ComputeSums();

  public:
    LineFit(vector<double> &X_coord, vector<double> &Y_coord);

    double GetIntercept()
    {
      return Y_intercept;
    }

    double GetSlope()
    {
      return slope;
    }
 
};

#endif