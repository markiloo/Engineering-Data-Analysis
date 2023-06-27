
#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

long long int generateRand(unsigned long long int *seed);
double generateDecimal(unsigned long long int *seed);

int main() 
{

    unsigned long long int seed = (unsigned long long) time(NULL);
    double minValue = generateDecimal(&seed);

    cout << "Running!" << endl;

    for(long long int i = 1; i <= 5000000000; i++) 
    {
      if (i % 1000000000 == 0)
        cout << i << "\r";

      double number = generateDecimal(&seed);
      if (number < minValue) 
      {
        minValue = number;
      }
    }

    cout << endl;
    cout << minValue << endl;

  return 0;

}

long long int generateRand(unsigned long long int *seed) 	
{
  unsigned long long int multiplier = 214013;
  unsigned long long int increment = 2531011;
  unsigned long long int modulo = 4294967296;

  // unsigned long long int multiplier = 1140671485;
  // unsigned long long int increment = 12820163;
  // unsigned long long int modulo = 16777216;


  unsigned long long int number = multiplier * (*seed) + increment;

  number = number % modulo; 

  *seed = number;

  return number;

}

double generateDecimal(unsigned long long int *seed) 
{
  return (generateRand(seed) + 1) / (double) (4294967296 + 2);
}

