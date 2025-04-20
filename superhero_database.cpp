/*
  superhero_database.cpp

  A simple C++ program that manages a database of obscure superheroes using parallel arrays
  for names, superpowers, and weaknesses and a multidimensional array for years and comic universes.
  It implements case-insensitive search, alphabetical sorting, and display in uppercase or lowercase.
  It also allows dynamically adding new superheroes and includes a unique ranking for each hero.

 
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
using namespace std;

// Maximum capacity for our superhero database
const int MAX_HEROES = 50;

// Parallel arrays for name, superpower, weakness.
string names[MAX_HEROES] = {
    "ForgetMeNot", "Hindsight Lad", "Skin", "Bailey Hoskins", "Apalla",
    "Alpha", "Lionheart", "Krypto", "Plastic Man", "Mr. Immortal"
};

string powers[MAX_HEROES] = {
    "People forget he exists unless looking at him",
    "Can analyze battles after they happen",
    "Has six extra feet of stretchable skin",
    "Can create a massive explosion",
    "Manifestation of Earth's sun, heat blasts",
    "Hyperkinetic energy manipulation",
    "Super strength, sword combat",
    "Super strength, flight",
    "Extreme elasticity, shape-shifting",
    "Cannot die, resurrects instantly"
};

string weaknesses[MAX_HEROES] = {
    "Isolation due to his power",
    "Only useful after the fact",
    "Gray pallor, hygiene issues",
    "The explosion kills him",
    "Lost power and memory",
    "Reckless use of power",
    "Cannot reunite with her children",
    "Still has a dog's intelligence",
    "Vulnerable to extreme cold",
    "No other powers, reckless"
};

// Multidimensional array for extra data.
// Column 0: Year Introduced (stored as string)
// Column 1: Comic Universe (Marvel, DC, or Other)
string extraData[MAX_HEROES][2] = {
    {"2014", "Marvel"},
    {"1993", "Marvel"},
    {"1994", "Marvel"},
    {"2016", "Marvel"},
    {"1977", "Marvel"},
    {"2012", "Marvel"},
    {"2004", "Marvel"},
    {"1955", "DC"},
    {"1941", "DC"},
    {"1989", "Marvel"}
};

// Unique ranking for each superhero (bonus). Rankings must be unique.
int ranking[MAX_HEROES] = {
    7, 5, 6, 8, 4, 9, 3, 10, 2, 1
};

// Current count of superheroes in the database.
int superheroCount = 10;


// Helper functions to convert a string to all uppercase or lowercase.
string toUppercase(const string &s) {
    string temp = s;
    transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
    return temp;
}

string toLowercase(const string &s) {
    string temp = s;
    transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
    return temp;
}

// Displays one superhero's data (with option to convert text case)
void displayHero(int index, bool toUpper) {
    string name = (toUpper) ? toUppercase(names[index]) : toLowercase(names[index]);
    string power = (toUpper) ? toUppercase(powers[index]) : toLowercase(powers[index]);
    string weak = (toUpper) ? toUppercase(weaknesses[index]) : toLowercase(weaknesses[index]);
    string year = extraData[index][0];
    string universe = extraData[index][1];

    cout << "-------------------------------------------" << endl;
    cout << "Name:           " << name << endl;
    cout << "Superpower:     " << power << endl;
    cout << "Weakness:       " << weak << endl;
    cout << "Year Introduced:" << year << endl;
    cout << "Comic Universe: " << universe << endl;
    cout << "Ranking:        " << ranking[index] << endl;
}

// Function to display all superheroes.
void displayAllHeroes(bool toUpper) {
    for (int i = 0; i < superheroCount; i++) {
        displayHero(i, toUpper);
    }
}

// Search for a superhero by name (case-insensitive).
void searchByName() {
    cout << "Enter the superhero name to search: ";
    string searchName;
    getline(cin, searchName);
    string sName = toLowercase(searchName);
    bool found = false;
    for (int i = 0; i < superheroCount; i++) {
        if (toLowercase(names[i]).find(sName) != string::npos) {
            displayHero(i, false);
            found = true;
        }
    }
    if (!found)
        cout << "No superhero found with the name containing \"" << searchName << "\"." << endl;
}

// Search for superheroes by superpower (case-insensitive substring match).
void searchByPower() {
    cout << "Enter the superpower keyword to search: ";
    string key;
    getline(cin, key);
    string sKey = toLowercase(key);
    bool found = false;
    for (int i = 0; i < superheroCount; i++) {
        if (toLowercase(powers[i]).find(sKey) != string::npos) {
            displayHero(i, false);
            found = true;
        }
    }
    if (!found)
        cout << "No superheroes found with the superpower keyword \"" << key << "\"." << endl;
}

// Sort superheroes alphabetically by name (using bubble sort)
// Swaps parallel arrays and the corresponding multidimensional and ranking arrays.
void sortHeroesAlphabetically() {
    for (int i = 0; i < superheroCount - 1; i++) {
        for (int j = 0; j < superheroCount - i - 1; j++) {
            if (toLowercase(names[j]) > toLowercase(names[j+1])) {
                swap(names[j], names[j+1]);
                swap(powers[j], powers[j+1]);
                swap(weaknesses[j], weaknesses[j+1]);
                // Swap the entire row in extraData
                swap(extraData[j][0], extraData[j+1][0]);
                swap(extraData[j][1], extraData[j+1][1]);
                // Swap the ranking ensuring the ranking moves with the hero
                swap(ranking[j], ranking[j+1]);
            }
        }
    }
    cout << "Superheroes have been sorted alphabetically by name." << endl;
}

// Add a new superhero dynamically.
void addHero() {
    if (superheroCount >= MAX_HEROES) {
        cout << "Cannot add new superhero. Maximum capacity reached." << endl;
        return;
    }

    cout << "Enter superhero name: ";
    getline(cin, names[superheroCount]);

    cout << "Enter superpower: ";
    getline(cin, powers[superheroCount]);

    cout << "Enter weakness: ";
    getline(cin, weaknesses[superheroCount]);

    cout << "Enter year introduced: ";
    string yearInput;
    getline(cin, yearInput);
    extraData[superheroCount][0] = yearInput;

    cout << "Enter comic universe (Marvel, DC, or Other): ";
    getline(cin, extraData[superheroCount][1]);

    // Enter ranking ensuring uniqueness
    int newRank;
    bool validRank;
    do {
        validRank = true;
        cout << "Enter unique ranking (an integer): ";
        cin >> newRank;
        cin.ignore(); // clear newline
        // Check if ranking exists already.
        for (int i = 0; i < superheroCount; i++) {
            if (ranking[i] == newRank) {
                cout << "Ranking already exists for another superhero. Enter a different ranking." << endl;
                validRank = false;
                break;
            }
        }
    } while (!validRank);
    ranking[superheroCount] = newRank;

    superheroCount++;
    cout << "New superhero added successfully!" << endl;
}

// Display superheroes sorted by ranking (lowest ranking number first)
// This function uses a temporary vector of indices so that the main arrays remain unmodified.
void displayHeroesByRanking() {
    vector<int> indices;
    for (int i = 0; i < superheroCount; i++) {
        indices.push_back(i);
    }
    // Sort indices based on ranking value (assuming lower ranking number is "better")
    sort(indices.begin(), indices.end(), [](int a, int b) {
        return ranking[a] < ranking[b];
    });
    cout << "Superheroes sorted by unique ranking:" << endl;
    for (int idx : indices) {
        displayHero(idx, false);
    }
}

int main() {
    int choice;
    bool exitProgram = false;
    while (!exitProgram) {
        cout << "\n=============== Superhero Database Menu ===============" << endl;
        cout << "1. Search for a superhero by name" << endl;
        cout << "2. Find superheroes by superpower" << endl;
        cout << "3. Sort superheroes alphabetically" << endl;
        cout << "4. Display all superheroes (choose uppercase or lowercase)" << endl;
        cout << "5. Add a new superhero" << endl;
        cout << "6. Display superheroes sorted by ranking" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // clear newline from input

        switch(choice) {
            case 1:
                searchByName();
                break;
            case 2:
                searchByPower();
                break;
            case 3:
                sortHeroesAlphabetically();
                break;
            case 4: {
                int caseChoice;
                cout << "Enter 1 for UPPERCASE display or 2 for lowercase display: ";
                cin >> caseChoice;
                cin.ignore();
                bool toUpper = (caseChoice == 1);
                displayAllHeroes(toUpper);
                break;
            }
            case 5:
                addHero();
                break;
            case 6:
                displayHeroesByRanking();
                break;
            case 0:
                exitProgram = true;
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
