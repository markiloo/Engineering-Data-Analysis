#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <random>

using namespace std;

int generateNumber(double min, double max, 
                    default_random_engine &arg_generator);

int main ()
{

  default_random_engine gen((unsigned) time(nullptr));

  cout << generateNumber(0, 1.2, gen) << endl;

  return 0;
}

  int generateNumber(double min, double max, 
                    default_random_engine &arg_generator) 
  {
    uniform_real_distribution<double> distribution(min, max);

    return distribution(arg_generator);
  }
