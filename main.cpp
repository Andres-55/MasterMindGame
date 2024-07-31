#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

string generateCode(int length, bool allowDuplicates) 
{
    string answer;
    if(allowDuplicates)
    {
        for(int i = 0; i < length; i++)
          {
            char num = (rand() % 8) + '1';
            answer += num;
          }
    }
    else
    {
      char array[length];
      for(int i = 0; i < length; i++)
        {
          array[i] = '0';
        }
      
      for(int i = 0; i < length; i++)
        {
          char num;
          bool check = 1;
          while(check)
            {
              num = (rand() % 8) + '1';
              check = 0;
              for(int j = 0; j < answer.length(); j++)
                {
                  if(answer[j] == num)
                  {
                    check = 1;
                  }
                }
            }
          answer += num;
        }
    }
    return answer;
}

void checkGuess(const string& answer, const string& guess, int& correctP, int& correctC) 
{
    correctP = 0;
    correctC = 0;
    bool checked[8] = {false};

    for (int i = 0; i < answer.size(); i++) 
    {
        if (answer[i] == guess[i]) 
        {
            correctP++;
            checked[answer[i] - '1'] = true;
        }
    }

    for (int i = 0; i < answer.size(); i++) 
    {
        if (!checked[guess[i] - '1']) 
        {
            for (int j = 0; j < answer.size(); j++) 
            {
                if (j != i && answer[j] == guess[i]) 
                {
                    correctC++;
                    checked[guess[i] - '1'] = true;
                    break;
                }
            }
        }
    }
}

int main(int argc, char** argv) 
{
    srand(time(0));

    int length;
    int duplicate;
    bool allowDuplicates;
    string array[10];
    cout << "Enter the length of the code (4-8): ";
    cin >> length;
    while(length < 4 || length > 8)
        {
          cout << "Incorrect length. Please enter a number between 4 and 8: ";
          cin >> length;
        }
  
    cout << endl << "Allow duplicates? (0 for no, 1 for yes): ";
    cin >> duplicate;
  
    while(duplicate < 0 || duplicate > 1)
    {
      cout << "Incorrect answer. Please enter 0 or 1: ";
      cin >> duplicate;
    }
    allowDuplicates = duplicate;
  
    string answer = generateCode(length, allowDuplicates);
    cout << endl << "Start Game" << endl <<"You have 10 tries to guess the code." << endl;

    int attempts = 1;
    while (true) 
    {
        if(attempts > 10)
        {
          cout << "You ran out of attempts. The answer was: " << answer << endl;
          break;
        }
        cout << "Attempt " << attempts << ". Enter your guess: ";
      
        string guess;
        cin >> guess;
        bool check = 1;
        while(check)
          {
            check = 0;
            if(guess.length() != length)
              {
              cout << "Invalid length. Please enter " << length << " characters." << endl;
              cin >> guess;
              check = 1;
              }

            for(int i = 0; i < guess.length(); i++)
              {
                if(guess[i] < '1' || guess[i] > '8')
                {
                  cout << "Invalid characters. Please use characters '1' to '8'." << endl;
                  cin >> guess;
                  check = 1;
                  break;
                }
              }
          }
        array[attempts - 1] = guess;
        for(int i = 9; i >= 0; i--)
          {
            cout << "|" << array[i] << "|" << endl;
          }

        int correctPosition, correctColor;
        checkGuess(answer, guess, correctPosition, correctColor);

        attempts++;
        if (correctPosition == length) 
        {
            cout << "Congratulations! You guessed the code in " << attempts << " attempts." << endl;
            break;
        } 
        else 
        {
            cout << endl << "Correct position: " << correctPosition << ", Correct color: " << correctColor << endl << endl;
        }
    }

    return 0;
}