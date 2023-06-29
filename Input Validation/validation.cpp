#include <iostream>

using namespace std;

int getInt(string message);

int main()
{

  int input = getInt("Enter a number:");

  return 0;
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