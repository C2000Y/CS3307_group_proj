#include "HangedManInterface.h"
using namespace std;

void CHangedManInterface::HangedManGameDisplay()
{

   const int maxWrong = 8;

   srand(static_cast<unsigned int>(time(0)));
   random_shuffle(words.begin(), words.end());
   const string correctWord = words[0];
   int wrong = 0;
   string soFar(correctWord.size(), '-');
   string used = "";

   cout << "\t\t\tWelcome to Hangman!" << endl;
   cout << "\t\t\t-------------------\n"
        << endl;
   cout << "You have " << (maxWrong - wrong) << " guesses, goodluck!" << endl;

   while ((wrong < maxWrong) && (soFar != correctWord))
   {
      cout << "\nYou've used the following letters:\n"
           << used << endl;
      cout << "So far, the word is: " << soFar << endl;

      char guess;
      cout << "\n\nEnter your guess: ";
      cin >> guess;
      guess = tolower(guess);

      while (used.find(guess) != string::npos)
      {
         cout << "\nYou've guessed " << guess << endl;
         cout << "Enter your guess again: ";
         cin >> guess;
         guess = toupper(guess);
      }

      used += guess;

      if (correctWord.find(guess) != string::npos)
      {
         cout << " correct " << guess << " is in the word.\n";
         for (unsigned int i = 0; i < correctWord.length(); ++i)
         {
            if (correctWord[i] == guess)
            {
               soFar[i] = guess;
            }
         }
      }
      else
      {
         ++wrong;
         int guessLeft = maxWrong - wrong;
         cout << "Sorry, " << guess << " isn't in the word.\n";
         cout << "You have " << (guessLeft) << " guesses left.\n";
         if (guessLeft == 7)
         {
            cout << " |/        " << endl;
            cout << " |         " << endl;
            cout << " |         " << endl;
            cout << " |         " << endl;
            cout << " |         " << endl;
            cout << " |         " << endl;
            cout << "_|___      " << endl;
         }
         if (guessLeft == 6)
         {
            cout << " __________" << endl;
            cout << " |/      | " << endl;
            cout << " |         " << endl;
            cout << " |         " << endl;
            cout << " |         " << endl;
            cout << " |         " << endl;
            cout << " |         " << endl;
            cout << "_|___      " << endl;
         }
         if (guessLeft == 5)
         {
            cout << " __________ " << endl;
            cout << " |/      |  " << endl;
            cout << " |     (o_o)" << endl;
            cout << " |          " << endl;
            cout << " |          " << endl;
            cout << " |          " << endl;
            cout << " |          " << endl;
            cout << "_|___       " << endl;
         }
         if (guessLeft == 4)
         {
            cout << " __________ " << endl;
            cout << " |/      |  " << endl;
            cout << " |     (o_o)" << endl;
            cout << " |       |  " << endl;
            cout << " |          " << endl;
            cout << " |          " << endl;
            cout << " |          " << endl;
            cout << "_|___       " << endl;
         }
         if (guessLeft == 3)
         {
            cout << " __________ " << endl;
            cout << " |/      |  " << endl;
            cout << " |     (>_<)" << endl;
            cout << " |      \\|/ " << endl;
            cout << " |          " << endl;
            cout << " |          " << endl;
            cout << " |          " << endl;
            cout << "_|___       " << endl;
         }
         if (guessLeft == 2)
         {
            cout << " __________ " << endl;
            cout << " |/      |  " << endl;
            cout << " |     (>_<)" << endl;
            cout << " |      \\|/ " << endl;
            cout << " |       |  " << endl;
            cout << " |          " << endl;
            cout << " |          " << endl;
            cout << "_|___       " << endl;
         }
         if (guessLeft == 1)
         {
            cout << " __________  " << endl;
            cout << " |/      |   " << endl;
            cout << " |     (*_*) " << endl;
            cout << " |      \\|/  " << endl;
            cout << " |       |   " << endl;
            cout << " |      / \\ " << endl;
            cout << " |           " << endl;
            cout << "_|___        " << endl;
         }
      }
   }
   if (wrong == maxWrong)
   {
      cout << "Game over, you've been hanged!";
      cout << " __________ " << endl;
      cout << " |/      |  " << endl;
      cout << " |     (x_x)" << endl;
      cout << " |      \\|/ " << endl;
      cout << " |       |  " << endl;
      cout << " |      / \\" << endl;
      cout << " |          " << endl;
      cout << "_|___       " << endl;
   }
   else
   {
      cout << "Congratulations! You win!" << endl;
      cout << "      (0_0)" << endl;
      cout << "       \\|/ " << endl;
      cout << "        |  " << endl;
      cout << "       / \\" << endl;
   }

}

CHangedManInterface::CHangedManInterface()
{
}
CHangedManInterface::~CHangedManInterface()
{
}