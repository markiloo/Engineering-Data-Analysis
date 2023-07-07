
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

/*
  LeastSquares line fit calculator

  LeastSquares.cpp
  By: Marc Adrian D. Ignacio
*/

using namespace std;

class Data
{
  private:
    string file_adress;
  
  public:
    vector<vector<double>> XY_points;

    Data(string target)
    {
      file_adress = target;
    }
 
};


int main ()
{
  /*
  This function reads numerical data from a csv file
  wherein each line of the file
  */

  ifstream target_file;

  target_file.open("test.csv");
  bool end_of_data = false;
  string buffer;

  string *points = new string[2]; 
  
  while(target_file.eof() == false && end_of_data == false)
  {
    getline(target_file, buffer);
    stringstream data_stream(buffer);
    string raw_string_data;

    string *points = new string[2];

    int number_of_strings = 0;
    while (data_stream.eof() == false)
    {
      data_stream >> raw_string_data;
      number_of_strings++;
    }

    if (number_of_strings > 2)
    {
      end_of_data = true;
    }
    else
    {
      int i = 0;
      stringstream data_stream_to_process(buffer);
      while (data_stream_to_process >> points[i])
      {
        cout << points[i] << endl;
        i++;
      }
      
    }

  }

  return 0;
}
