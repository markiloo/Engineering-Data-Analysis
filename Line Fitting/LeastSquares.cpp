
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

    void ComputeSlope()
    {
      double numerator;
      double denominator;

      numerator = n*sum_of_x_times_y - (sum_of_x * sum_of_y);
      denominator = n*sum_of_x_squared - sum_of_x * sum_of_x;

      slope = numerator/denominator;
    }

    void ComputeIntercept()
    {
      double numerator;
      double denominator;

      numerator = sum_of_y - slope*sum_of_x;
      denominator = n;

      Y_intercept = numerator/denominator;
    }

    void ComputeSums()
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

    void load_data()
    {
      /*
      This function reads numerical data from a csv file
      wherein each line of the file corresponds to data,
      it ends reading when invalid input is encountered
      */
      ifstream target_file;

      target_file.open(file_adress);
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

        if (number_of_strings != 2)
        {
          end_of_data = true;
        }
        else
        {
          int i = 0;
          double values[2];
          stringstream data_stream_to_process(buffer);
          while (data_stream_to_process >> points[i])
          {

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
  
  public:
    LineFit(string target)
    {
      file_adress = target;
      load_data();
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

int main ()
{
  string target_address;

  cout << "Enter Address of file: ";
  getline(cin, target_address);

  while (isFileReal(target_address) == false || target_address.length() < 1)
  {
    cout << "Address doesn't exist please check your input." << endl;
    cout << "Remember to include the file extension." << endl;
    cout << "Here's what you entered: " << target_address << endl;
    cout << "Enter Address of file: ";
    getline(cin, target_address);
  }

  LineFit data(target_address);

  cout << setprecision(7);
  cout << "Slope: "<< data.GetSlope() << endl;
  cout << "Intercept: "<<data.GetIntercept() << endl;

  return 0;
}

bool isFileReal(string address)
{
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
