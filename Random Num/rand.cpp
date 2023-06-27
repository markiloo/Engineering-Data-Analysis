
#include <iostream> 
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <fstream>

using namespace std;


double GenerateFloat();

int main()
{

  srand( (unsigned) time(NULL));


  const int number_of_elements = 100000;
  double floating_numbers[number_of_elements];

  cout << "Working" << endl;

  for(int i = 0; i < number_of_elements; i++)
    floating_numbers[i] = GenerateFloat();

  
  ofstream output_file; 
  output_file.open("output.csv");

  for(double number: floating_numbers)
  {
    output_file << number << endl;
  }

  cout << "Done!" << endl;

  return 0;

}

double GenerateFloat() 
{

  double number = (rand() + rand()/RAND_MAX)/(1.0 * RAND_MAX);
 
  return number;
}