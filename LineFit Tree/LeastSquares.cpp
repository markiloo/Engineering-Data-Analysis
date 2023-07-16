
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <string>
#include "LineFitter/LineFit.h"

/*
  LeastSquares line fit calculator

  LeastSquares.cpp
  By: Marc Adrian D. Ignacio
*/

using namespace std;

bool isFileReal(string address);
void load_data(vector<double> &X_coordinates, vector<double> &Y_coordinates, string file_address);

int main ()
{
  string target_address;
  
  vector<double> X;
  vector<double> Y;

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

  load_data(X,Y,target_address);

  LineFit data(X,Y);

  cout << setprecision(7);
  cout << "Slope: "<< data.GetSlope() << endl;
  cout << "Intercept: "<<data.GetIntercept() << endl;
  cout << endl;

  cout << "Y = " << data.GetSlope() << "x" << " + "<< data.GetIntercept() << endl;

  cout << endl << "End of Program. Enter any key to continue" << endl;
  char buf; 
  cin >> buf;

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

void load_data(vector<double> &X_coordinates, vector<double> &Y_coordinates, string file_address)
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


