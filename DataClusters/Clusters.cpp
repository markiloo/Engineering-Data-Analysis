#include <iostream>
#include <random>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <iomanip>

/*
  DataClusters - Project 2

  Clusters.cpp
  by: Marc Adrian D. Ignacio

*/

using namespace std;

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

    Cluster(double arg_standardDeviation, double arg_relativeFrequency, 
            double arg_xCoordMean, double arg_yCoordMean, 
            char arg_clusterName)
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

double GenerateGaussianRand(default_random_engine &arg_generator); 
double getDouble(string message);
int getInt(string message);
int generateInt(int min, int max);
char getChar(string message);

void PlayGame(default_random_engine &generator, 
              vector<Cluster> &arg_dataClusters, 
              int cumulativeFrequency);
void GenerateData(int totalOcurr, 
                  default_random_engine &generator,
                  int cumulativeFrequency, 
                  vector<Cluster> &arg_dataClusters);



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

    dataClusters.push_back(Cluster(standardDeviation, 
                                  relativeFrequency, 
                                  xMean, yMean, typeName));

    cumulativeFrequency = cumulativeFrequency + relativeFrequency;

  }

  char userInput = 'a';
  while(userInput != 'G' && userInput != 'P' && userInput != 'g' && userInput != 'p')
  {
    userInput = getChar("Enter G to generate data\nEnter P to play game\nInput: ");

    if (userInput == 'G' || userInput == 'g')
    {
      GenerateData((int)totalOccurences,
                  generator,
                  cumulativeFrequency, 
                  dataClusters);
    }
    else if (userInput == 'P' || userInput == 'p')
    {
      PlayGame(generator, dataClusters, cumulativeFrequency);
    }
  }

  cout << "Program Ended!" << endl;

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

char getChar(string message)
{
  char userInput;

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

void GenerateData(int totalOcurr, 
                  default_random_engine &generator,
                  int cumulativeFrequency, 
                  vector<Cluster> &arg_dataClusters)
{
  int occurencesGenerated = 0;

  while(occurencesGenerated < totalOcurr)
  {
    double totalFreq = 0;
    int randomNumber = generateInt(0, cumulativeFrequency);

    for(int i = 0; i < arg_dataClusters.size(); i++)
    {
      if (randomNumber < totalFreq + arg_dataClusters[i].GetRelativeFrequency())
      {
        arg_dataClusters[i].SetxCoord(GenerateGaussianRand(generator));
        arg_dataClusters[i].SetyCoord(GenerateGaussianRand(generator));
        occurencesGenerated = occurencesGenerated + 1;
        break;
      }
      totalFreq += arg_dataClusters[i].GetRelativeFrequency();
    }
  }

  ofstream file;

  file.open("Data.text");
  
  for(int i = 0; i < totalOcurr; i++)
  {
    for(int j = 0; j < arg_dataClusters.size(); j++)
    {
      if(i < arg_dataClusters[j].xCoord.size())
      {
        file << arg_dataClusters[j].xCoord[i] << "," 
                << arg_dataClusters[j].yCoord[i] 
                << "," << arg_dataClusters[j].getName()
                << "," << " \t";
      }
    }
    file << "\n";
  }

  file.close();

}

void PlayGame(default_random_engine &generator,  
              vector<Cluster> &arg_dataClusters, 
              int cumulativeFrequency)
{
  bool isGameOver = false;
  int correctAnswers = 0;
  int totalQuestions = 0;

  cout << endl;

  cout << "Guess the type!" << endl;

  while (isGameOver == false)
  {
    double totalFreq = 0;
    char generatedType;
    int randomNumber = generateInt(0, cumulativeFrequency);

    for(int i = 0; i < arg_dataClusters.size(); i++)
    {
      if (randomNumber <= totalFreq + arg_dataClusters[i].GetRelativeFrequency())
      {
        cout << "Parameter 1: " << GenerateGaussianRand(generator)*arg_dataClusters[i].GetStandardDeviation() + arg_dataClusters[i].GetXMean() << endl;
        cout << "Parameter 2: " << GenerateGaussianRand(generator)*arg_dataClusters[i].GetStandardDeviation() + arg_dataClusters[i].GetYMean() << endl;
        generatedType = arg_dataClusters[i].getName();
        break;
      }
      totalFreq += arg_dataClusters[i].GetRelativeFrequency();
    }

    char *choices = new char[arg_dataClusters.size()];

    cout << "Your Type Choices are ";

    for(int i = 0; i < arg_dataClusters.size(); i++)
    {
      cout << arg_dataClusters[i].getName() << ",";
      choices[i] = arg_dataClusters[i].getName();
    }

    cout << endl;

    cout << "Type 1 to Exit" << endl;

    char answer = getChar("Enter Type: ");
    if(answer >= 'a' && answer <= 'z') 
    {
      answer = answer - 32;
    }
    else if (answer == '1')
    {
      isGameOver = true;
      break;
    }
    else if (answer < 'A' || answer > 'Z')
    {
      while (answer < 'A' || answer > 'Z')
      {
        answer = getChar("Enter Type: ");
        if(answer == '1')
        {
          isGameOver = true;
          break;
        }
      }
      if(isGameOver == true)
      {
        break;
      }
    }

    if(answer == generatedType)
    {
      cout << "Correct!" << endl;
      correctAnswers += 1;
    }
    else 
    {
      cout << "Wrong!" << endl;
    }

    totalQuestions += 1;
    cout << endl;
    cout << "Score: " << correctAnswers << "/" << totalQuestions << " - " << round((correctAnswers/(double) totalQuestions) * 100) << "%" << endl;

  } 
}