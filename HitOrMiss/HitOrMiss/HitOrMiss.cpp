#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

class game
{
private:
    string word;
    string guess{};
    string fillIn{};
    unsigned size{};
    char choice{};
    int hits{};
    int misses{};
    int lives{};
    
public:
    game();
    inline void welcome();
    inline void generateWord();
    inline bool isIsogram(const string&) const;
    inline bool checkLength() const;
    inline void checkHitsMisses(const string&);    
    inline void beginPlay();
    inline bool playAgain(const char&) const;
};

game::game() {}

inline void game::welcome()
{
    std::cout << std::endl;
    std::cout << "          }   {               ___ " << std::endl;
    std::cout << "          (O O)              (O O) " << std::endl;
    std::cout << "    /------\\ /                \\ /-------\\ " << std::endl;
    std::cout << "   / |BULL| o                  o| COW  | \\ " << std::endl;
    std::cout << "  *  |-,--|                     |------|  * " << std::endl;
    std::cout << "     ^    ^                     ^      ^ " << std::endl;
    std::cout << std::endl;
    cout << "=============================================================\n";
    cout << "\n*** Welcome to Hit or Miss ***\n\n";
    cout << "Try to guess the hidden word.\n\n";
    cout << "The hidden word is an isogram (no repeating letters).\n\n";
    cout << "For simplicity, only lower case letters are to be used.\n\n";
    cout << "[Hits] will show the correct letters in the right place.\n\n";
    cout << "[Misses] will show the correct letters in the wrong place\n\n";
    cout << "*** GOOD LUCK ***\n\n";
    cout << "==============================================================\n";
}

inline void game::generateWord()
{
    vector <string> isograms =
    {
        "ab", "bakery", "cabinet", "daughter",
        "education", "fishmonger", "game", "habit",
        "income", "janitor", "kilogram", "lethargic", "math"
    };
    int getWord = rand() % isograms.size();
    word = isograms[getWord];
    size = word.size();
    lives = word.size() + 4;
    fillIn = string(word.size(), '-');
}

inline bool game::isIsogram(const string& guess) const
{
    for (unsigned i = 0; i < guess.length(); i++)
    {
        for (unsigned j = i + 1; j < guess.length(); j++)
        {
            if (guess[i] == guess[j])
            {                
                return false;
            }
        }
    }
    return true;
}

inline bool game::checkLength() const
{
    if (guess.length() > size || guess.length() < size)
    {       
        return false;
    }
    return true;
}

inline void game::checkHitsMisses(const string& guess)
{   
    for (unsigned i = 0; i < size; i++)
    {
        for (unsigned j = 0; j < size; j++)
        {
            if (word[i] == guess[j])
            {
                if (i == j)
                    hits++;
                else
                    misses++;
            }
        }
    }    
}

inline bool game::playAgain(const char& choice) const
{
    if (choice == 'Y' || choice == 'y')
        return true;
    return false;
}

inline void game::beginPlay()
{
    welcome();
    generateWord();

    do {        

        hits = 0; misses = 0;

        cout << "\nThe word is " << size << " letters\n\n";
        cout << fillIn;

        cout << "\n\n\nGuess the word: ";
        cin >> guess;

        if (guess == word)
            cout << "\n\n\n*** You Win ***\n";       

        else if (!isIsogram(guess) && !checkLength())
            cout << "The word is " << size
            << " letters, and no repeating letters please!\n";

        else if (!checkLength())
            cout << "Try again, the word is " << size << " letters!\n";

        else if (!isIsogram(guess))
            cout << "No repeating letters please!\n";

        else
        {
            checkHitsMisses(guess);
            cout << "You have " << hits << " HITS and " << misses << " MISSES\n";
            lives--;
            cout << "You have " << lives << " lives left!\n";
        }
        

        if (lives == 0)
            cout << "\n\n\n*** You lost, better luck next time ***\n";
    } while (guess != word && lives != 0);

    cout << "Play Again?\n[ Y or N ]\n";
    cin >> choice;
    if (playAgain(choice))
    {
        system("cls");
        beginPlay();
    }
    else
    {
        cout << "*** Thanks for playing ***\n";
        return;
    }
}

int main()
{
    srand(time(0));

    game g;

    g.beginPlay();

    cout << endl;
    system("pause");
    return 0;
   
}

