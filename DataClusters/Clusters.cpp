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

//cluster class holding the data of the clusters
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

    Cluster(double arg_standardDeviation, 
            double arg_relativeFrequency, 
            double arg_xCoordMean, double arg_yCoordMean, 
            char arg_clusterName)
    {
      standardDeviation = arg_standardDeviation;
      relativeFrequency = arg_relativeFrequency;
      xCoordMean = arg_xCoordMean;
      yCoordMean = arg_yCoordMean;
      clusterName = arg_clusterName;
    }

    double SetxCoord(double arg_value)
    {
      double value = arg_value*standardDeviation + xCoordMean;
      xCoord.push_back(value);
      return value;
    }

    double SetyCoord(double arg_value)
    {
      double value = arg_value*standardDeviation + yCoordMean;
      yCoord.push_back(value);
      return value;
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
                    
char getChar(string message);

void PlayGame(default_random_engine &generator, 
              vector<Cluster> &arg_dataClusters, 
              double cumulativeFrequency);
void GenerateData(int totalOcurr, 
                  default_random_engine &generator,
                  double cumulativeFrequency, 
                  vector<Cluster> &arg_dataClusters);

int generateDecimal(double min, 
                    double max, 
                    default_random_engine &arg_generator);

int main()
{
  int totalOccurences;
  double cumulativeFrequency = 0;

  //initializing generator with seed
  default_random_engine generator((unsigned) time(nullptr));

  cout << "Note: When input is null. The program waits until input is entered" << endl;

  //getting number of types
  int numberOfClusters = getInt("Enter number of Types: ");
  while (numberOfClusters <= 0)
  {
    cout << "Valid input is from (1-26)" << endl;
    numberOfClusters = getInt("Enter numer of Types: ");
  }

  cout << endl;

  //generating vector for clusters
  vector<Cluster> dataClusters;

  //getting setting of the clusters
  for(int i = 0; i < numberOfClusters; i++)
  {

    char typeName = 'A' + i;

    cout << "Enter Setting for Type " << typeName << endl;

    double xMean = getDouble("Enter Parameter 1 Mean: ");
    double yMean = getDouble("Enter Paramter 2 Mean: ");

    double standardDeviation = getDouble("Enter Standard Deviation: ");

    while (standardDeviation <= 0)
    {
    cout << "Valid input is a positive number" << endl;
    standardDeviation = getDouble("Enter Standard Deviation: ");
    }


    double relativeFrequency = getDouble("Enter Relative Frequency: ");
    
    while (relativeFrequency <= 0)
    {
    cout << "Valid input is a positive number" << endl;
    relativeFrequency = getDouble("Enter Relative Frequency: ");
    }

    cout << "------------------------------" << endl;

    dataClusters.push_back(Cluster(standardDeviation, 
                                  relativeFrequency, 
                                  xMean, yMean, typeName));

    cumulativeFrequency = cumulativeFrequency + relativeFrequency;

  }

  //getting the mode that the program will be run at
  char userInput = 'a';
  while(userInput != 'G' && userInput != 'P' && userInput != 'g' && userInput != 'p')
  {
    userInput = getChar("Enter G to generate data\nEnter P to play game\nInput: ");

    if (userInput == 'G' || userInput == 'g')
    {
      totalOccurences = getInt("Enter number of Occurences: ");

      while (totalOccurences <= 0)
      {
        cout << "Valid input is a positive counting number!" << endl;
        totalOccurences = getInt("Enter number of Occurences: ");
      }

      GenerateData((int)totalOccurences,
                  generator,
                  cumulativeFrequency, 
                  dataClusters);
    }

    else if (userInput == 'P' || userInput == 'p')
    {
      PlayGame(generator, dataClusters, cumulativeFrequency);
    }

    else
    {
      cout << "Invalid input!" << endl;
    }

  }

  cout << "Program Ended!" << endl;

  return 0;
}


//function to generate gaussian rand
double GenerateGaussianRand(default_random_engine &arg_generator) 
{
  normal_distribution<double> distribution(0, 1);

  return distribution(arg_generator);
}

//function to generate a random number
int generateNumber(double min, double max, 
                  default_random_engine &arg_generator) 
{
  uniform_real_distribution<double> distribution(min, max);

  return distribution(arg_generator);
}

//function to get a double
double getDouble(string message) 
{
  double userInput = 0;

  do 
  {
    if(cin.good() == false)
    {
      cout << "Wrong input. Please enter a number\n";
      cin.clear();
      cin.ignore(INT_MAX, '\n');
    }

    cout << message;
    cin >> userInput;

  } while(cin.good() == false);

  cin.ignore(INT_MAX, '\n');

  return userInput;
}

//function to get an int
int getInt(string message) 
{
  double userInput = 0;

  do 
  {
    if(cin.good() == false || userInput != (int) userInput)
    {
      cout << "Wrong input. Please enter an integer\n";
      cin.clear();
      cin.ignore(INT_MAX, '\n');
    }

    cout << message;
    cin >> userInput;

  } while(cin.good() == false || userInput != (int) userInput);

  cin.ignore(INT_MAX, '\n');

  return (int) userInput;
}

//function to get a character
char getChar(string message)
{
  char userInput;

  do 
  {
    if(cin.good() == false)
    {
      cout << "Wrong input. Please enter a character\n";
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
                  double cumulativeFrequency, 
                  vector<Cluster> &arg_dataClusters)
{

  ofstream file;
  file.open("Data.txt");

  int occurencesGenerated = 0;
  string delimeter = " \t";

  while(occurencesGenerated < totalOcurr)
  {
    double totalFreq = 0;
    int randomNumber = generateNumber(0, cumulativeFrequency, generator);

    for(int i = 0; i < arg_dataClusters.size(); i++)
    {
      if (randomNumber < totalFreq + arg_dataClusters[i].GetRelativeFrequency())
      {
        file << arg_dataClusters[i].SetxCoord(GenerateGaussianRand(generator));
        file << delimeter;
        file << arg_dataClusters[i].SetyCoord(GenerateGaussianRand(generator));
        file << delimeter;
        file << arg_dataClusters[i].getName();
        file << endl; 
        occurencesGenerated = occurencesGenerated + 1;
        break;
      }
      totalFreq += arg_dataClusters[i].GetRelativeFrequency();
    }
  }

  file << "\n By Marc Adrian D. Ignacio";
  file.close();

}

void PlayGame(default_random_engine &generator,  
              vector<Cluster> &arg_dataClusters, 
              double cumulativeFrequency)
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
    int randomNumber = generateNumber(0, cumulativeFrequency, generator);
    char choiceBound = arg_dataClusters[arg_dataClusters.size() - 1].getName();

    for(int i = 0; i < arg_dataClusters.size(); i++)
    {
      if (randomNumber <= totalFreq + arg_dataClusters[i].GetRelativeFrequency())
      {
        cout << "Parameter 1: " 
              << GenerateGaussianRand(generator)*arg_dataClusters[i].GetStandardDeviation() + arg_dataClusters[i].GetXMean()
              << endl;
        cout << "Parameter 2: " 
              << GenerateGaussianRand(generator)*arg_dataClusters[i].GetStandardDeviation() + arg_dataClusters[i].GetYMean() 
              << endl;
        generatedType = arg_dataClusters[i].getName();
        break;
      }
      totalFreq += arg_dataClusters[i].GetRelativeFrequency();
    }

    cout << "Your Type Choices are ";

    for(int i = 0; i < arg_dataClusters.size(); i++)
    {
      cout << arg_dataClusters[i].getName() << ",";
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
    if (answer < 'A' || answer > choiceBound)
    {
      while (answer < 'A' || answer > choiceBound)
      {
        cout << "Not a valid choice!" << endl;
        answer = getChar("Enter Type: ");
        if(answer == '1')
        {
          isGameOver = true;
          break;
        }
        else if(answer >= 'a' && answer <= 'z') 
        {
          answer = answer - 32;
        }
      }
      if(isGameOver == true)
      {
        break;
      }
    }

    if(answer == generatedType)
    {
      cout << "\nCorrect!" << endl;
      correctAnswers += 1;
    }
    else 
    {
      cout << "\nWrong! - The correct type is: " 
            << generatedType 
            << endl;
    }

    totalQuestions += 1;
    cout << endl;
    cout << "Score: " 
          << correctAnswers 
          << "/" << totalQuestions 
          << " - " 
          << round((correctAnswers/(double) totalQuestions) * 100) 
          << "%" << endl;

  } 
}
