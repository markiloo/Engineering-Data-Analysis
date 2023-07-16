
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <string>

/*
  LeastSquares line fit calculator

  LeastSquares.cpp
  By: Marc Adrian D. Ignacio
*/

using namespace std;

class LineFit
{
  private:
    double slope;
    double Y_intercept;
    double sum_of_x = 0;
    double sum_of_x_squared = 0;
    double sum_of_y = 0;
    double sum_of_x_times_y = 0;
    double n = 0;

    vector<double> X_coordinates;
    vector<double> Y_coordinates;

    void ComputeSlope()
    {
      /*
      This function computes for the slope
      using least squares method
      */
      double numerator;
      double denominator;

      numerator = n*sum_of_x_times_y - (sum_of_x * sum_of_y);
      denominator = n*sum_of_x_squared - sum_of_x * sum_of_x;

      slope = numerator/denominator;
    }

    void ComputeIntercept()
    {
      /*
      This function computes for the intercept using least
      squares method
      */
      double numerator;
      double denominator;

      numerator = sum_of_y - slope*sum_of_x;
      denominator = n;

      Y_intercept = numerator/denominator;
    }

    void ComputeSums()
    {
      /*
      This function computes the sums
      that are needed for the least
      squares method
      */
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
  
  public:
    LineFit(vector<double> &X_coords, vector<double> &Y_coords)
    {
      X_coordinates = X_coords;
      Y_coordinates = Y_coords;
      ComputeSums();
      ComputeSlope();
      ComputeIntercept();
    }

    double GetIntercept()
    {
      return Y_intercept;
    }

    double GetSlope()
    {
      return slope;
    }
 
};

bool isFileReal(string address);
void load_data(string file_address, vector<double> &X_coordinates, vector<double> &Y_coordinates);

int main ()
{
  string target_address;
  vector<double> X_values;
  vector<double> Y_values;

  //getting address of the target file
  cout << "Enter Address of file: ";
  getline(cin, target_address);

  //checking if there is input
  while (isFileReal(target_address) == false || target_address.length() < 1)
  {
    cout << "Address doesn't exist please check your input." << endl;
    cout << "Remember to include the file extension." << endl;
    cout << "Here's what you entered: " << target_address << endl;
    cout << "Enter Address of file: ";
    getline(cin, target_address);
  }

  //loading the data into the vectors
  load_data(target_address, X_values, Y_values);
  //creating line fit class using the vectors
  LineFit data(X_values, Y_values);

  cout << setprecision(7);
  cout << "Slope: "<< data.GetSlope() << endl;
  cout << "Intercept: "<<data.GetIntercept() << endl;
  cout << endl;

  cout << "Y = " << data.GetSlope() << "x" << " + "<< data.GetIntercept() << endl;

  cout << endl << "End of Program. Enter any alphanumeric to exit" << endl;
  char buf; 
  cin >> buf;

  return 0;
}

bool isFileReal(string address)
{
  /*
  This functions returns a boolean value
  that indicates if the address of the file
  is real or not
  */
  ifstream file;
  address.erase(address.find_last_not_of(" \t\n\r\f\v") + 1);
  file.open(address);

  if(file)
  {
    return true;
  }
  else
  {
    return false;
  }

}

void load_data(string file_address, vector<double> &X_coordinates, vector<double> &Y_coordinates)
{
  /*
  This function reads numerical data from a csv file
  wherein each line of the file corresponds to data,
  it ends reading when invalid input is encountered
  */

  ifstream target_file;

  target_file.open(file_address);
  bool end_of_data = false;
  string buffer;

  string *points = new string[2]; 
  
  while(target_file.eof() == false && end_of_data == false)
  {
    getline(target_file, buffer);
    buffer.erase(buffer.find_last_not_of(" \t\n\r\f\v") + 1);
    stringstream data_stream(buffer);
    string raw_string_data;

    string *points = new string[2];

    int number_of_strings = 0;
    while (data_stream.eof() == false)
    {
      data_stream >> raw_string_data;
      number_of_strings++;
    }

    if (number_of_strings < 2)
    {
      end_of_data = true;
    }
    else
    {
      int i = 0;
      double values[2];
      stringstream data_stream_to_process(buffer);
      while (data_stream_to_process.eof() == false && i < 2)
      {
        
        data_stream_to_process >> points[i];

        try
        {
          values[i] = stod(points[i]);
        }
        catch(const std::exception& e)
        {
          end_of_data = true;
          break;
        }

        i++;
      } 
      if(end_of_data == false)
      { 
        X_coordinates.push_back(values[0]);
        Y_coordinates.push_back(values[1]);    
      }
    }
  }
}