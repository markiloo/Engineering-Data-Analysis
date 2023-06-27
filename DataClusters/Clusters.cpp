#include <iostream>
#include <random>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

double GenerateGaussianRand(default_random_engine &arg_generator); 

class Cluster 
{
  private:
    double standardDeviation;
    double relativeFrequency;
    double xCoordMean;
    double yCoordMean;

  public:
    vector<double> xCoord;
    vector<double> yCoord;

    Cluster(double arg_standardDeviation, double arg_relativeFrequency, double arg_xCoordMean, double arg_yCoordMean)
    {
      standardDeviation = arg_standardDeviation;
      relativeFrequency = arg_relativeFrequency;
      xCoordMean = arg_xCoordMean;
      yCoordMean = arg_yCoordMean;
    }

    void SetxCoord(double arg_value)
    {
      xCoord.push_back(arg_value*standardDeviation + xCoordMean);
    }

    void SetyCoord(double arg_value)
    {
      yCoord.push_back(arg_value*standardDeviation + yCoordMean);
    }

    double GetRelativeFrequency()
    {
      return relativeFrequency;
    }

};

int main()
{
  default_random_engine generator((unsigned) time(nullptr));

  Cluster *test_cluster = new Cluster(5, 1000, 5, 10);

  for(int i = 0; i < test_cluster->GetRelativeFrequency(); i++)
  {
    test_cluster->SetxCoord(GenerateGaussianRand(generator));
    test_cluster->SetyCoord(GenerateGaussianRand(generator));
  }



  return 0;
}

double GenerateGaussianRand(default_random_engine &arg_generator) 
{
  normal_distribution<double> distribution(0, 1);

  return distribution(arg_generator);
}