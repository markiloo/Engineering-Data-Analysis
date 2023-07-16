#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "LineFit.h"

LineFit::LineFit(vector<double> &X_coord, vector<double> &Y_coord)
{
  X_coordinates = X_coord;
  Y_coordinates = Y_coord;

  ComputeSums();
  ComputeSlope();
  ComputeIntercept();
}

void LineFit::ComputeSlope()
{
  double numerator;
  double denominator;

  numerator = n*sum_of_x_times_y - (sum_of_x * sum_of_y);
  denominator = n*sum_of_x_squared - sum_of_x * sum_of_x;

  slope = numerator/denominator;
}

void LineFit::ComputeIntercept()
{
  double numerator;
  double denominator;

  numerator = sum_of_y - slope*sum_of_x;
  denominator = n;

  Y_intercept = numerator/denominator;
}

void LineFit::ComputeSums()
{
  n = X_coordinates.size();

  for(int i = 0; i < X_coordinates.size(); i++)
  {
    double x = X_coordinates[i];
    double y = Y_coordinates[i];
  
    sum_of_x = sum_of_x + x;
    sum_of_x_squared = sum_of_x_squared + (x*x);
    sum_of_y = sum_of_y + y;
    sum_of_x_times_y = sum_of_x_times_y + (x*y);
  }

}

