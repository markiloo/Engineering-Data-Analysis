#include <iostream>
#include <sstream>

using namespace std;

string GetString(string message);
int GetInt(string message);

int main()
{

  cout << GetInt("Enter message: ");

  return 0;
}

string GetString(string message) 
{
  string userInput;
  cout << message;

  getline(cin, userInput);

  return userInput;
}

int GetInt(string message)
{
  bool isInputValid = false;
  string word;

  while(isInputValid == false)
  {
    stringstream stream(GetString(message));

    int length = 0;
    while(stream >> word)
    {
      if (length > 1)
      {
        cout << "Invalid input. Please enter a number." << endl;
        break;
      }
      length++;
    }

    if(length == 1)
    {
      isInputValid = true;
    }

  }

  return stoi(word);
}