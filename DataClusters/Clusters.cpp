#include <iostream>
#include <random>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <iomanip>

using namespace std;

double GenerateGaussianRand(default_random_engine &arg_generator); 
double getDouble(string message);
int getInt(string message);
int generateInt(int min, int max);

class Cluster 
{
  private:
    double standardDeviation;
    double relativeFrequency;
    double xCoordMean;
    double yCoordMean;
    char clusterName;

  public:
    vector<double> xCoord;
    vector<double> yCoord;

    Cluster(double arg_standardDeviation, double arg_relativeFrequency, double arg_xCoordMean, double arg_yCoordMean, char arg_clusterName)
    {
      standardDeviation = arg_standardDeviation;
      relativeFrequency = arg_relativeFrequency;
      xCoordMean = arg_xCoordMean;
      yCoordMean = arg_yCoordMean;
      clusterName = arg_clusterName;
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

    double GetStandardDeviation()
    {
      return standardDeviation;
    }

    double GetXMean()
    {
      return xCoordMean;
    }

    double GetYMean()
    {
      return yCoordMean;
    }

    char getName()
    {
      return clusterName;
    }

};

int main()
{
  const int totalOccurences = 5000;
  double cumulativeFrequency = 0;
  default_random_engine generator((unsigned) time(nullptr));
  srand((unsigned) time(nullptr));

  int numberOfClusters = getInt("Enter number of Types: ");
  while (numberOfClusters <= 0)
  {
    cout << "Valid input is from (1-26)" << endl;
    numberOfClusters = getInt("Enter numer of Types: ");
  }

  cout << endl;

  //generating vector for clusters
  vector<Cluster> dataClusters;

  for(int i = 0; i < numberOfClusters; i++)
  {

    char typeName = 'A' + i;

    cout << "Enter Setting for Type " << typeName << endl;

    double xMean = getDouble("Enter Parameter 1 Mean: ");
    double yMean = getDouble("Enter Paramter 2 Mean: ");

    double relativeFrequency = getDouble("Enter Relative Frequency: ");
    
    while (relativeFrequency <= 0)
    {
    cout << "Valid input is a positive number" << endl;
    relativeFrequency = getDouble("Enter Relative Frequency: ");
    }

    double standardDeviation = getDouble("Enter Standard Deviation: ");

    while (standardDeviation <= 0)
    {
    cout << "Valid input is a positive number" << endl;
    standardDeviation = getDouble("Enter Relative Frequency: ");
    }

    cout << "------------------------------" << endl;

    dataClusters.push_back(Cluster(standardDeviation, relativeFrequency, xMean, yMean, typeName));

    cumulativeFrequency = cumulativeFrequency + relativeFrequency;

  }

  int occurencesGenerated = 0;

  while(occurencesGenerated < totalOccurences)
  {
    double totalFreq = 0;
    int randomNumber = generateInt(0, cumulativeFrequency);

    for(int i = 0; i < dataClusters.size(); i++)
    {
      if (randomNumber < totalFreq + dataClusters[i].GetRelativeFrequency())
      {
        dataClusters[i].SetxCoord(GenerateGaussianRand(generator));
        dataClusters[i].SetyCoord(GenerateGaussianRand(generator));
        occurencesGenerated = occurencesGenerated + 1;
        break;
      }
      totalFreq += dataClusters[i].GetRelativeFrequency();
    }
  }

  ofstream file;

  file.open("Data.txt");
  
  for(int i = 0; i < totalOccurences; i++)
  {
    for(int j = 0; j < dataClusters.size(); j++)
    {
      if(i < dataClusters[j].xCoord.size())
      {
        file << dataClusters[j].xCoord[i] << "," << dataClusters[j].yCoord[i] << "," << dataClusters[j].getName() << "," << " \t";
      }
    }
    file << "\n";
  }

  file.close();

  return 0;
}

double GenerateGaussianRand(default_random_engine &arg_generator) 
{
  normal_distribution<double> distribution(0, 1);

  return distribution(arg_generator);
}

int generateInt(int min, int max) 
{
  int number = rand();
  while(number < min || number > max)
  {
    number = rand();
  }

  return number;
}


double getDouble(string message) 
{
  double userInput = 0;

  do 
  {
    if(cin.good() == false)
    {
      cin.clear();
      cin.ignore(INT_MAX, '\n');
    }

    cout << message;
    cin >> userInput;

  } while(cin.good() == false);

  cin.ignore(INT_MAX, '\n');

  return userInput;
}

int getInt(string message) 
{
  int userInput = 0;

  do 
  {
    if(cin.good() == false)
    {
      cin.clear();
      cin.ignore(INT_MAX, '\n');
    }

    cout << message;
    cin >> userInput;

  } while(cin.good() == false);

  cin.ignore(INT_MAX, '\n');

  return userInput;
}