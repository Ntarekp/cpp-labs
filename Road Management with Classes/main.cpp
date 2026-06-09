#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>   // for setw() — formatting output
using namespace std;

const int MAX = 100;

// ═══════════════════════════════════════════════════════
// CLASS 1: City
// Responsibility: store and manage a single city's data
// ═══════════════════════════════════════════════════════
class City {
private:
    int index;
    string name;

public:
    // Default constructor — empty city
    City() {
        index = 0;
        name = "";
    }

    // Parameterized constructor
    City(int i, string n) {
        index = i;
        name = n;
    }

    // Setters
    void setIndex(int i) { index = i; }
    void setName(string n) { name = n; }

    // Getters
    int getIndex() { return index; }
    string getName() { return name; }

    // Display this city
    void display() {
        cout << index << ". " << name << endl;
    }
};


// ═══════════════════════════════════════════════════════
// CLASS 2: RoadNetwork
// Responsibility: manage roads and budgets between cities
// ═══════════════════════════════════════════════════════
class RoadNetwork {
private:
    int roads[MAX][MAX];       // 1 = road exists, 0 = no road
    double budget[MAX][MAX];   // budget in billion RWF

public:
    // Constructor — initialize everything to zero
    RoadNetwork() {
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                roads[i][j] = 0;
                budget[i][j] = 0.0;
            }
        }
    }

    // Add a road between two cities (by their array positions)
    void addRoad(int i, int j) {
        roads[i][j] = 1;
        roads[j][i] = 1;  // both directions
    }

    // Add budget for a road
    bool addBudget(int i, int j, double b) {
        // Validation: road must exist first
        if (roads[i][j] == 0) {
            return false;  // failed
        }
        budget[i][j] = b;
        budget[j][i] = b;
        return true;  // success
    }

    // Check if road exists
    bool roadExists(int i, int j) {
        return roads[i][j] == 1;
    }

    // Get budget for a road
    double getBudget(int i, int j) {
        return budget[i][j];
    }

    // Display road adjacency matrix
    void displayRoads(int cityCount) {
        cout << "\nRoad Adjacency Matrix:\n\n";
        for (int i = 0; i < cityCount; i++) {
            for (int j = 0; j < cityCount; j++) {
                cout << roads[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Display budget adjacency matrix
    void displayBudgets(int cityCount) {
        cout << "\nBudget Adjacency Matrix:\n\n";
        for (int i = 0; i < cityCount; i++) {
            for (int j = 0; j < cityCount; j++) {
                cout << fixed << setprecision(1)
                     << setw(7) << budget[i][j];
            }
            cout << endl;
        }
    }
};


// ═══════════════════════════════════════════════════════
// CLASS 3: InfraSystem
// Responsibility: menus, user interaction, file handling
// ═══════════════════════════════════════════════════════
class InfraSystem {
private:
    City cities[MAX];      // array of City objects
    int cityCount;         // how many cities stored
    RoadNetwork network;   // the road network object

    // ── Private helper: find city array position by name ──
    int findByName(string name) {
        for (int i = 0; i < cityCount; i++) {
            if (cities[i].getName() == name)
                return i;
        }
        return -1;  // not found
    }

    // ── Private helper: find city array position by index ──
    int findByIndex(int idx) {
        for (int i = 0; i < cityCount; i++) {
            if (cities[i].getIndex() == idx)
                return i;
        }
        return -1;
    }

public:
    // Constructor
    InfraSystem() {
        cityCount = 0;
    }

    // ── MENU 1: Add Cities ─────────────────────────────
    void addCities() {
        int n;
        cout << "\nEnter the number of cities to add: ";
        cin >> n;
        cin.ignore();

        for (int i = 0; i < n; i++) {
            string newName;
            cout << "Enter the name for city "
                 << (cityCount + 1) << ": ";
            getline(cin, newName);

            // Validation: no duplicates
            if (findByName(newName) != -1) {
                cout << "City already exists! Skipping.\n";
                i--;
                continue;
            }

            // Create city using constructor
            cities[cityCount] = City(cityCount + 1, newName);
            cityCount++;
        }
        cout << "Cities added successfully.\n";
    }

    // ── MENU 2: Add Road ───────────────────────────────
    void addRoad() {
        string city1, city2;
        cin.ignore();
        cout << "\nEnter the name of the first city: ";
        getline(cin, city1);
        cout << "Enter the name of the second city: ";
        getline(cin, city2);

        int i = findByName(city1);
        int j = findByName(city2);

        if (i == -1 || j == -1) {
            cout << "One or both cities not found!\n";
            return;
        }
        if (i == j) {
            cout << "A city cannot connect to itself!\n";
            return;
        }
        if (network.roadExists(i, j)) {
            cout << "Road already exists!\n";
            return;
        }

        network.addRoad(i, j);
        cout << "Road added successfully between "
             << city1 << " and " << city2 << "\n";
    }

    // ── MENU 3: Add Budget ─────────────────────────────
    void addBudget() {
        string city1, city2;
        cin.ignore();
        cout << "\nEnter the name of the first city: ";
        getline(cin, city1);
        cout << "Enter the name of the second city: ";
        getline(cin, city2);

        int i = findByName(city1);
        int j = findByName(city2);

        if (i == -1 || j == -1) {
            cout << "One or both cities not found!\n";
            return;
        }

        double b;
        cout << "Enter the budget for the road: ";
        cin >> b;

        if (!network.addBudget(i, j, b)) {
            cout << "No road exists between these cities.\n"
                 << "Please add a road first.\n";
            return;
        }

        cout << "Budget added successfully for the road between "
             << city1 << " and " << city2 << "\n";
    }

    // ── MENU 4: Edit City ──────────────────────────────
    void editCity() {
        int idx;
        cout << "\nEnter the index of the city to edit: ";
        cin >> idx;
        cin.ignore();

        int pos = findByIndex(idx);
        if (pos == -1) {
            cout << "City not found!\n";
            return;
        }

        string newName;
        cout << "Enter the new name for city: ";
        getline(cin, newName);

        if (findByName(newName) != -1) {
            cout << "A city with that name already exists!\n";
            return;
        }

        cities[pos].setName(newName);
        cout << "City updated successfully.\n";
    }

    // ── MENU 5: Search City ────────────────────────────
    void searchCity() {
        int idx;
        cout << "\nEnter the index of the city to search: ";
        cin >> idx;

        int pos = findByIndex(idx);
        if (pos == -1) {
            cout << "City not found!\n";
            return;
        }

        cout << "City found: ";
        cities[pos].display();
    }

    // ── MENU 6: Display Cities ─────────────────────────
    void displayCities() {
        cout << "\nCities:\n";
        for (int i = 0; i < cityCount; i++) {
            cities[i].display();
        }
    }

    // ── MENU 7: Display Roads ──────────────────────────
    void displayRoads() {
        displayCities();
        network.displayRoads(cityCount);
    }

    // ── MENU 8: Display All + Save Files ──────────────
    void displayAll() {
        displayCities();
        network.displayRoads(cityCount);
        network.displayBudgets(cityCount);
        saveToFiles();
    }

    // ── FILE HANDLING: Save to cities.txt & roads.txt ──
    void saveToFiles() {
        // Save cities.txt
        ofstream cf("cities.txt");
        cf << "Index\tCity_Name\n";
        for (int i = 0; i < cityCount; i++) {
            cf << cities[i].getIndex() << "\t"
               << cities[i].getName() << "\n";
        }
        cf.close();

        // Save roads.txt
        ofstream rf("roads.txt");
        rf << "Nbr\tRoad\t\t\tBudget\n";
        int num = 1;
        for (int i = 0; i < cityCount; i++) {
            for (int j = i + 1; j < cityCount; j++) {
                if (network.roadExists(i, j)) {
                    rf << num++ << ".\t"
                       << cities[i].getName() << "-"
                       << cities[j].getName() << "\t\t"
                       << network.getBudget(i, j) << "\n";
                }
            }
        }
        rf.close();

        cout << "\nData saved to cities.txt and roads.txt\n";
    }

    // ── SHOW MENU ──────────────────────────────────────
    void showMenu() {
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

    // ── RUN: main loop ─────────────────────────────────
    void run() {
        int choice;
        do {
            showMenu();
            cin >> choice;

            switch (choice) {
                case 1: addCities();     break;
                case 2: addRoad();       break;
                case 3: addBudget();     break;
                case 4: editCity();      break;
                case 5: searchCity();    break;
                case 6: displayCities(); break;
                case 7: displayRoads();  break;
                case 8: displayAll();    break;
                case 9: cout << "Exiting. Goodbye!\n"; break;
                default: cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 9);
    }
};


// ═══════════════════════════════════════════════════════
// MAIN — just create the system and run it
// ═══════════════════════════════════════════════════════
int main() {
    InfraSystem system;
    system.run();
    return 0;
}
