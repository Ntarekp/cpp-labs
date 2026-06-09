#include <iostream>
#include <fstream>
#include <string>
using namespace std;


///─── CONSTANTS ───────────────────────────────────────────

const int MAX = 100;


/// ──────────── CREATE A STRUCTURE FOR THE CITY ───────────

struct City
{
    int index;
    string name;
};


///─────────────────────────── Setup Global Data for cities budgets and roads ───────────────────

int roads[MAX][MAX];
double budget[MAX][MAX];

City cities[MAX];

int cityCount = 0;


///─────────────────────────── Set up Helper function to find Cities by name ─────────────────────

int findCityByName(string name)
{
    for(int i = 0; i < cityCount; i++)
    {
        if(cities[i].name == name)
            return i; // Returns array position (0-based)
    }

    return -1; // Not found
}


///─────────────────────────── First Menu (Add Cities) ──────────────────────────

void addCities()
{
    int n;

    cout << "Enter the number of cities to add: " << endl;
    cin >> n;

    cin.ignore(); // Clear leftover newline from buffer

    for(int i = 0; i < n; i++)
    {
        string newName;

        cout << "Enter the name of the city "
             << (cityCount + 1) << ": ";

        getline(cin, newName);

        // Validation: no duplicate cities
        if(findCityByName(newName) != -1)
        {
            cout << "City already exists! Skipping.\n";

            i--; // Don't count this attempt
            continue;
        }

        cities[cityCount].index = cityCount + 1;
        cities[cityCount].name = newName;

        cityCount++;
    }

    cout << "Cities added successfully.\n";
}


///─── MENU 2: Add Road ─────────────────────────────────────

void addRoad()
{
    string city1, city2;

    cin.ignore();

    cout << "\nEnter the name of the first city: " << endl;
    getline(cin, city1);

    cout << "\nEnter the name of the second city: " << endl;
    getline(cin, city2);

    int i = findCityByName(city1);
    int j = findCityByName(city2);

    if(i == -1 || j == -1)
    {
        cout << "\nOne or both cities not found!\n";
        return;
    }

    if(i == j)
    {
        cout << "A city cannot have a road to itself!\n";
        return;
    }

    roads[i][j] = 1;
    roads[j][i] = 1;

    cout << "Road added successfully between "
         << city1 << " and " << city2 << endl;
}


/// ─── MENU 3: Add Budget ───────────────────────────────────

void addBudget()
{
    string city1, city2;

    cin.ignore();

    cout << "\nEnter the name of the first city: ";
    getline(cin, city1);

    cout << "\nEnter the name of the second city: ";
    getline(cin, city2);

    int i = findCityByName(city1);
    int j = findCityByName(city2);

    if(i == -1 || j == -1)
    {
        cout << "One or both cities not found!\n";
        return;
    }

    if(roads[i][j] == 0)
    {
        cout << "No road exists between these cities. Add a road first!\n";
        return;
    }

    double b;

    cout << "Enter the budget for the road: ";
    cin >> b;

    budget[i][j] = b;
    budget[j][i] = b;

    cout << "Budget added successfully for the road between "
         << city1 << " and " << city2 << endl;
}


/// ─── MENU 4: Edit City ────────────────────────────────────

void editCity()
{
    int idx;

    cout << "\nEnter the index of the city to edit: ";
    cin >> idx;

    cin.ignore();

    if(idx < 1 || idx > cityCount)
    {
        cout << "CITY NOT FOUND!\n";
        return;
    }


    cout << "City Found: "
         << cities[idx - 1].index
         << ". "
         << cities[idx - 1].name
         << "\n";

    string newName;

    cout << "Enter the new city name: ";
    getline(cin, newName);

    // Validation for duplicate city names
    if(findCityByName(newName) != -1)
    {
        cout << "City already exists!\n";
        return;
    }

    cities[idx - 1].name = newName;

    cout << "City updated successfully.\n";
}


/// ─── MENU 5: Search City ──────────────────────────────────

void searchCity()
{
    int idx;

    cout << "\nEnter the index of the city to search: ";
    cin >> idx;

    if(idx < 1 || idx > cityCount)
    {
        cout << "City not found!\n";
        return;
    }

    cout << "City Found: "
         << cities[idx - 1].index
         << ". "
         << cities[idx - 1].name
         << "\n";
}


/// ─── MENU 6: Display Cities ───────────────────────────────

void displayCities()
{
    cout << "\nCities:\n";

    for(int i = 0; i < cityCount; i++)
    {
        cout << cities[i].index
             << ". "
             << cities[i].name
             << "\n";
    }
}


/// ─── MENU 7: Display Roads (Adjacency Matrix) ─────────────

void displayRoads()
{
    displayCities();

    cout << "\nRoad Adjacency Matrix:\n\n";

    for(int i = 0; i < cityCount; i++)
    {

        for(int j = 0; j < cityCount; j++)
        {
            cout << roads[i][j] << " ";
        }

        cout << "\n";
    }
}
/// ─── MENU 7B: Display CitiesBudget (Adjacency Matrix) ─────────────
void displayBudget()
{
    cout << "\nCities Budget Adjacency Matrix:\n\n";
    for (int i = 0; i < cityCount; i++)
    {
        for (int j = 0; j< cityCount; j++)
        {
            cout << budget[i][j] << "\t";
        }
        cout << "\n";
    }
}


/// ─── MENU 8: Display All Data ─────────────────────────────

void displayAll()
{
    // CHANGE:
    // Reused existing function instead of rewriting code

    displayRoads();
    displayBudget();

    ///-----------Saving to file---------
    ofstream cf("Cities.txt");
    cf << "Index\tCity_name\n";

    for(int i = 0; i < cityCount; i++)
    {
        cf << cities[i].index << "\t" <<cities[i].name << "\n";
        cf.close();
    }
    ;

    ofstream rf("Roads.txt");
    rf << "Nbr\tRoad\t\tBudget\n";

    int num = 1;
    for (int i = 0; i < cityCount; i++)
    {
        for (int j = i+1; j < cityCount; j++)
        {
            if (roads[i][j] == 1)
            {
                rf << num++ << ".\t"
                   << cities[i].name << "-" << cities[j].name
                   << "\t\t" << budget[i][j] << "\n";
            }
        }
    }
    rf.close();
    cout << "\nData saved to cities.txt and roads.txt\n";
}


/// ─── MENU DISPLAY ─────────────────────────────────────────
void showMenu()
{
    cout << "\nMenu:\n";
    cout << "1. Add new city(ies)\n";
    cout << "2. Add roads between cities\n";
    cout << "3. Add the budget for roads\n";
    cout << "4. Edit city\n";
    cout << "5. Search for a city using its index\n";
    cout << "6. Display cities\n";
    cout << "7. Display roads\n";
    cout << "8. Display recorded data on console\n";
    cout << "9. Exit\n";
    cout << "\nEnter your choice: ";
}

int main()
{
    /// Initialize all arrays to zero
    for(int i = 0; i < MAX; i++)
    {
        for(int j = 0; j < MAX; j++)
        {
            roads[i][j] = 0;
            budget[i][j] = 0.0;
        }
    }

    int choice;

    do
    {
        showMenu();

        cin >> choice;

        switch(choice)
        {
            case 1:
                addCities();
                break;

            case 2:
                addRoad();
                break;

            case 3:
                addBudget();
                break;

            case 4:
                editCity();
                break;

            case 5:
                searchCity();
                break;

            case 6:
                displayCities();
                break;

            case 7:
                displayRoads();
                break;

            case 8:
                displayAll();
                break;

            case 9:
                cout << "Exiting....\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    }
    while(choice != 9);

    return 0;
}
