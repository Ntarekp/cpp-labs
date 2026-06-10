/*
 * ================================================================
 *   RSSB CONTRIBUTION ZONE MANAGEMENT SYSTEM
 *   Language      : C++
 *   Data Structures: Graph (Adjacency Matrix) + Singly Linked List
 * ================================================================
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

/* ================================================================
 *  CONSTANTS
 * ================================================================ */
const int MAX_ZONES = 20;    // maximum zones the system can hold
const int NAME_LEN  = 100;   // max characters in a zone name

/* ================================================================
 *  CONTRIBUTOR NODE  (used by the Linked List)
 *  Each node stores one contributor's data plus a pointer
 *  to the next node in the chain.
 * ================================================================ */
struct Contributor
{
    string contributorID;
    string fullName;
    int    zoneIndex;
    string type;                 // "Employee" or "Employer"
    double monthlyContribution;
    Contributor *next;           // pointer to the next node

    // Constructor – makes creating a node easier
    Contributor(string id, string name, int zone,
                string t, double contrib)
        : contributorID(id), fullName(name), zoneIndex(zone),
          type(t), monthlyContribution(contrib), next(nullptr) {}
};

/* ================================================================
 *  LINKED LIST CLASS
 *  Manages all contributor records using a singly linked list.
 *
 *  Visual model:
 *  head -> [RSSB-001] -> [RSSB-002] -> [RSSB-003] -> nullptr
 * ================================================================ */
class ContributorList
{
private:
    Contributor *head;   // pointer to the first node
    int count;           // total number of contributors

public:
    /* ---- Constructor ---- */
    ContributorList() : head(nullptr), count(0) {}

    /* ---- Destructor: free all heap-allocated nodes ---- */
    ~ContributorList()
    {
        Contributor *current = head;
        while (current != nullptr)
        {
            Contributor *temp = current;
            current = current->next;
            delete temp;
        }
    }

    /* ----------------------------------------------------------
     * insertAtEnd()
     * Creates a new node and appends it to the end of the list.
     * Steps:
     *   1. Check that the ID is unique.
     *   2. Validate inputs.
     *   3. Create node.
     *   4. If list is empty, new node becomes head.
     *      Otherwise, walk to the last node and attach.
     * ---------------------------------------------------------- */
    bool insertAtEnd(string id, string name, int zone,
                     string type, double contrib)
    {

        // --- Validation ---
        if (id.empty() || name.empty())
        {
            cout << "Error: ID and name cannot be empty.\n";
            return false;
        }
        if (type != "Employee" && type != "Employer")
        {
            cout << "Error: Type must be exactly 'Employee' or 'Employer'.\n";
            return false;
        }
        if (contrib <= 0)
        {
            cout << "Error: Monthly contribution must be greater than zero.\n";
            return false;
        }

        // --- Check unique ID ---
        if (searchByID(id, false) != nullptr)
        {
            cout << "Error: Contributor ID '" << id << "' already exists.\n";
            return false;
        }

        // --- Create the new node on the heap ---
        Contributor *newNode = new Contributor(id, name, zone, type, contrib);

        // --- Attach the node ---
        if (head == nullptr)
        {
            // List is empty; new node is the first (and only) node
            head = newNode;
        }
        else
        {
            // Walk to the last node
            Contributor *current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;   // attach at the end
        }

        count++;
        return true;
    }

    /* ----------------------------------------------------------
     * searchByID()
     * Walks the list comparing IDs. Returns a pointer to the
     * matching node, or nullptr if not found.
     * 'verbose' controls whether a message is printed.
     * ---------------------------------------------------------- */
    Contributor* searchByID(const string &id, bool verbose = true)
    {
        Contributor *current = head;
        while (current != nullptr)
        {
            if (current->contributorID == id)
            {
                if (verbose)
                {
                    cout << "\nContributor found:\n";
                    cout << string(65, '-') << "\n";
                    cout << left
                         << setw(12) << "ID"
                         << setw(25) << "Name"
                         << setw(6)  << "Zone"
                         << setw(12) << "Type"
                         << "Monthly(RWF)\n";
                    cout << string(65, '-') << "\n";
                    cout << left
                         << setw(12) << current->contributorID
                         << setw(25) << current->fullName
                         << setw(6)  << current->zoneIndex
                         << setw(12) << current->type
                         << fixed << setprecision(0)
                         << current->monthlyContribution << "\n";
                    cout << string(65, '-') << "\n";
                }
                return current;
            }
            current = current->next;
        }
        if (verbose)
            cout << "Contributor with ID '" << id << "' not found.\n";
        return nullptr;
    }

    /* ----------------------------------------------------------
     * deleteByID()
     * Removes a node from the list by its ID.
     * Steps:
     *   1. If list is empty, report and return.
     *   2. If head matches, update head and delete.
     *   3. Otherwise, keep a 'previous' pointer and walk until
     *      the match is found, then re-link and delete.
     * ---------------------------------------------------------- */
    bool deleteByID(const string &id)
    {
        if (head == nullptr)
        {
            cout << "List is empty. Nothing to delete.\n";
            return false;
        }

        // Case 1: the head node matches
        if (head->contributorID == id)
        {
            Contributor *temp = head;
            head = head->next;  // move head forward
            delete temp;        // free memory
            count--;
            cout << "Contributor '" << id << "' deleted successfully.\n";
            return true;
        }

        // Case 2: search from second node onward
        Contributor *prev    = head;
        Contributor *current = head->next;

        while (current != nullptr)
        {
            if (current->contributorID == id)
            {
                prev->next = current->next;  // bypass the node
                delete current;              // free memory
                count--;
                cout << "Contributor '" << id << "' deleted successfully.\n";
                return true;
            }
            prev    = current;
            current = current->next;
        }

        cout << "Contributor with ID '" << id << "' not found.\n";
        return false;
    }

    /* ----------------------------------------------------------
     * displayAll()
     * Walks the entire list from head to nullptr and prints
     * each contributor's details in a formatted table.
     * ---------------------------------------------------------- */
    void displayAll() const
    {
        cout << "\n" << string(69, '-') << "\n";
        cout << "  RSSB CONTRIBUTOR RECORDS\n";
        cout << string(69, '-') << "\n";
        cout << left
             << setw(12) << "ID"
             << setw(25) << "Name"
             << setw(6)  << "Zone"
             << setw(12) << "Type"
             << "Monthly(RWF)\n";
        cout << string(69, '-') << "\n";

        if (head == nullptr)
        {
            cout << "  No contributors recorded.\n";
        }
        else
        {
            Contributor *current = head;
            while (current != nullptr)
            {
                cout << left
                     << setw(12) << current->contributorID
                     << setw(25) << current->fullName
                     << setw(6)  << current->zoneIndex
                     << setw(12) << current->type
                     << fixed << setprecision(0)
                     << current->monthlyContribution << "\n";
                current = current->next;
            }
        }

        cout << string(69, '-') << "\n";
        cout << "Total contributors: " << count << "\n";
    }

    int getCount() const
    {
        return count;
    }
};

/* ================================================================
 *  GRAPH CLASS
 *  Manages zones, the route adjacency matrix, and the cost matrix.
 *
 *  Zones are 1-indexed:
 *    zoneNames[1] = "City of Kigali"
 *    adjMatrix[i][j] = 1 means a route exists between zone i and j
 *    costMatrix[i][j] = operational cost in Million RWF
 * ================================================================ */
class ZoneGraph
{
private:
    int    numZones;
    string zoneNames[MAX_ZONES];          // index 1..numZones
    int    adjMatrix[MAX_ZONES][MAX_ZONES];
    double costMatrix[MAX_ZONES][MAX_ZONES];

public:
    /* ---- Constructor: zero out all matrices ---- */
    ZoneGraph() : numZones(0)
    {
        for (int i = 0; i < MAX_ZONES; i++)
            for (int j = 0; j < MAX_ZONES; j++)
            {
                adjMatrix[i][j]  = 0;
                costMatrix[i][j] = 0.0;
            }
    }

    /* ----------------------------------------------------------
     * getZoneIndex()
     * Linear search through zone names (case-insensitive-ish).
     * Returns the 1-based index, or -1 if not found.
     * ---------------------------------------------------------- */
    int getZoneIndex(const string &name) const
    {
        for (int i = 1; i <= numZones; i++)
        {
            // Compare after converting both to lowercase
            string a = zoneNames[i], b = name;
            transform(a.begin(), a.end(), a.begin(), ::tolower);
            transform(b.begin(), b.end(), b.begin(), ::tolower);
            if (a == b) return i;
        }
        return -1;
    }

    /* ----------------------------------------------------------
     * isNameTaken()
     * Returns true if a zone with that name already exists.
     * ---------------------------------------------------------- */
    bool isNameTaken(const string &name) const
    {
        return getZoneIndex(name) != -1;
    }

    int getNumZones() const
    {
        return numZones;
    }

    string getZoneName(int index) const
    {
        if (index >= 1 && index <= numZones)
            return zoneNames[index];
        return "";
    }

    /* ----------------------------------------------------------
     * preloadZones()
     * Called once at startup to insert the 5 existing RSSB zones.
     * ---------------------------------------------------------- */
    void preloadZones()
    {
        zoneNames[1] = "City of Kigali";
        zoneNames[2] = "Eastern Province";
        zoneNames[3] = "Western Province";
        zoneNames[4] = "Northern Province";
        zoneNames[5] = "Southern Province";
        numZones = 5;
    }

    /* ----------------------------------------------------------
     * preloadRoutes()
     * Loads the 8 existing transfer routes and their costs.
     * Sets both adj[i][j] and adj[j][i] (undirected graph).
     * ---------------------------------------------------------- */
    void preloadRoutes()
    {
        // Helper lambda to set both directions at once
        auto addRoute = [&](int i, int j, double cost)
        {
            adjMatrix[i][j]  = adjMatrix[j][i]  = 1;
            costMatrix[i][j] = costMatrix[j][i] = cost;
        };

        addRoute(1, 2, 12.5);  // Kigali – Eastern Province
        addRoute(1, 3, 18.3);  // Kigali – Western Province
        addRoute(1, 4, 14.7);  // Kigali – Northern Province
        addRoute(1, 5, 16.2);  // Kigali – Southern Province
        addRoute(2, 4, 22.8);  // Eastern – Northern Province
        addRoute(3, 5, 19.4);  // Western – Southern Province
        addRoute(4, 3, 25.1);  // Northern – Western Province
        addRoute(5, 2, 20.6);  // Southern – Eastern Province
    }

    /* ----------------------------------------------------------
     * addZone()
     * Adds one new zone; the index is assigned automatically
     * as numZones + 1.
     * ---------------------------------------------------------- */
    bool addZone(const string &name)
    {
        if (numZones >= MAX_ZONES - 1)
        {
            cout << "Error: Maximum zone capacity reached.\n";
            return false;
        }
        if (isNameTaken(name))
        {
            cout << "Error: Zone name '" << name << "' already exists.\n";
            return false;
        }
        if (name.empty())
        {
            cout << "Error: Zone name cannot be empty.\n";
            return false;
        }
        numZones++;
        zoneNames[numZones] = name;
        return true;
    }

    /* ----------------------------------------------------------
     * registerRoute()
     * Registers a route between two zones by name.
     * Validates: both zones exist, not the same zone,
     * route not already registered.
     * ---------------------------------------------------------- */
    bool registerRoute(const string &name1, const string &name2)
    {
        int i = getZoneIndex(name1);
        int j = getZoneIndex(name2);

        if (i == -1)
        {
            cout << "Error: Zone '" << name1 << "' not found.\n";
            return false;
        }
        if (j == -1)
        {
            cout << "Error: Zone '" << name2 << "' not found.\n";
            return false;
        }
        if (i == j)
        {
            cout << "Error: Cannot add a route from a zone to itself.\n";
            return false;
        }
        if (adjMatrix[i][j] == 1)
        {
            cout << "Error: Route between '" << name1
                 << "' and '" << name2 << "' already registered.\n";
            return false;
        }

        adjMatrix[i][j] = adjMatrix[j][i] = 1;
        cout << "Route added successfully between "
             << name1 << " and " << name2 << ".\n";
        return true;
    }

    /* ----------------------------------------------------------
     * addRouteCost()
     * Sets the cost for an already-registered route.
     * ---------------------------------------------------------- */
    bool addRouteCost(const string &name1, const string &name2, double cost)
    {
        int i = getZoneIndex(name1);
        int j = getZoneIndex(name2);

        if (i == -1)
        {
            cout << "Error: Zone '" << name1 << "' not found.\n";
            return false;
        }
        if (j == -1)
        {
            cout << "Error: Zone '" << name2 << "' not found.\n";
            return false;
        }
        if (adjMatrix[i][j] == 0)
        {
            cout << "No route registered between these zones. Cannot add cost.\n";
            return false;
        }
        costMatrix[i][j] = costMatrix[j][i] = cost;
        cout << "Cost recorded successfully for route "
             << name1 << " - " << name2 << ".\n";
        return true;
    }

    /* ----------------------------------------------------------
     * editZoneName()
     * Changes the name stored at a given index.
     * ---------------------------------------------------------- */
    bool editZoneName(int index, const string &newName)
    {
        if (index < 1 || index > numZones)
        {
            cout << "Error: Invalid zone index.\n";
            return false;
        }
        if (isNameTaken(newName))
        {
            cout << "Error: Zone name '" << newName << "' already exists.\n";
            return false;
        }
        zoneNames[index] = newName;
        cout << "Zone updated successfully.\n";
        return true;
    }

    /* ----------------------------------------------------------
     * searchZone()
     * Finds a zone by name and prints its connected routes.
     * ---------------------------------------------------------- */
    void searchZone(const string &name) const
    {
        int idx = getZoneIndex(name);
        if (idx == -1)
        {
            cout << "Zone '" << name << "' not found.\n";
            return;
        }

        cout << "\nZone found: [" << idx << "] " << zoneNames[idx] << "\n";
        cout << "Connected routes:\n";

        bool hasRoute = false;
        for (int j = 1; j <= numZones; j++)
        {
            if (adjMatrix[idx][j] == 1)
            {
                cout << "  -> " << left << setw(25) << zoneNames[j]
                     << " Cost: " << costMatrix[idx][j] << " M RWF\n";
                hasRoute = true;
            }
        }
        if (!hasRoute)
            cout << "  No routes connected to this zone.\n";
    }

    /* ----------------------------------------------------------
     * displayZones()
     * Lists all zone indices and names.
     * ---------------------------------------------------------- */
    void displayZones() const
    {
        cout << "\nZones:\n";
        for (int i = 1; i <= numZones; i++)
            cout << i << ". " << zoneNames[i] << "\n";
    }

    /* ----------------------------------------------------------
     * displayAdjMatrix()
     * Prints the route adjacency matrix (0/1 grid).
     * ---------------------------------------------------------- */
    void displayAdjMatrix() const
    {
        cout << "\nRoute adjacency matrix:\n  ";
        for (int i = 1; i <= numZones; i++)
            cout << setw(3) << i;
        cout << "\n";

        for (int i = 1; i <= numZones; i++)
        {
            cout << setw(2) << i << " ";
            for (int j = 1; j <= numZones; j++)
                cout << setw(3) << adjMatrix[i][j];
            cout << "\n";
        }
    }

    /* ----------------------------------------------------------
     * displayCostMatrix()
     * Prints the cost matrix with decimal values.
     * ---------------------------------------------------------- */
    void displayCostMatrix() const
    {
        cout << "\nCost adjacency matrix (Million RWF):\n";
        cout << setw(8) << " ";
        for (int i = 1; i <= numZones; i++)
            cout << setw(7) << i;
        cout << "\n";

        for (int i = 1; i <= numZones; i++)
        {
            cout << setw(7) << i << " ";
            for (int j = 1; j <= numZones; j++)
                cout << fixed << setprecision(1) << setw(7) << costMatrix[i][j];
            cout << "\n";
        }
    }

    /* ----------------------------------------------------------
     * displayAll()
     * Combines zones + both matrices in one call (menu option 8).
     * ---------------------------------------------------------- */
    void displayAll() const
    {
        displayZones();
        displayAdjMatrix();
        displayCostMatrix();
    }

    /* ----------------------------------------------------------
     * saveToFiles()
     * Writes zones.txt and routes.txt.
     * ---------------------------------------------------------- */
    void saveToFiles() const
    {
        // ---- zones.txt ----
        ofstream zonesFile("zones.txt");
        if (!zonesFile)
        {
            cout << "Error: Could not open zones.txt for writing.\n";
        }
        else
        {
            zonesFile << left << setw(8) << "Index" << "Zone_Name\n";
            for (int i = 1; i <= numZones; i++)
                zonesFile << left << setw(8) << i << zoneNames[i] << "\n";
            zonesFile.close();
            cout << "Zones saved to zones.txt\n";
        }

        // ---- routes.txt ----
        ofstream routesFile("routes.txt");
        if (!routesFile)
        {
            cout << "Error: Could not open routes.txt for writing.\n";
        }
        else
        {
            routesFile << left
                       << setw(6)  << "Nbr"
                       << setw(45) << "Route"
                       << "Cost_MRWF\n";

            int routeNum = 1;
            // Only iterate upper triangle to avoid duplicates
            for (int i = 1; i <= numZones; i++)
            {
                for (int j = i + 1; j <= numZones; j++)
                {
                    if (adjMatrix[i][j] == 1)
                    {
                        string route = zoneNames[i] + "-" + zoneNames[j];
                        routesFile << left
                                   << setw(6)  << (to_string(routeNum) + ".")
                                   << setw(45) << route
                                   << fixed << setprecision(1)
                                   << costMatrix[i][j] << "\n";
                        routeNum++;
                    }
                }
            }
            routesFile.close();
            cout << "Routes saved to routes.txt\n";
        }
    }
};

/* ================================================================
 *  HELPER: safely read a full line (handles leftover newlines)
 * ================================================================ */
string getLine(const string &prompt = "")
{
    if (!prompt.empty()) cout << prompt;
    string line;
    getline(cin, line);
    return line;
}

/* ================================================================
 *  HELPER: safely read an integer with validation
 * ================================================================ */
int getInt(const string &prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Please enter a whole number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

/* ================================================================
 *  HELPER: safely read a double with validation
 * ================================================================ */
double getDouble(const string &prompt)
{
    double value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

/* ================================================================
 *  MENU DISPLAY
 * ================================================================ */
void displayMenu()
{
    cout << "\n" << string(60, '-') << "\n";
    cout << "     RSSB CONTRIBUTION ZONE MANAGEMENT SYSTEM\n";
    cout << string(60, '-') << "\n";
    cout << " 1.  Add new zone(s)\n";
    cout << " 2.  Register route between zones\n";
    cout << " 3.  Add operational cost for a route\n";
    cout << " 4.  Edit zone name\n";
    cout << " 5.  Search for a zone by name\n";
    cout << " 6.  Display zones\n";
    cout << " 7.  Display routes (adjacency matrix)\n";
    cout << " 8.  Display all recorded data\n";
    cout << " 9.  Add contributor\n";
    cout << " 10. Search contributor by ID\n";
    cout << " 11. Delete contributor by ID\n";
    cout << " 12. Display all contributors\n";
    cout << " 13. Save zones and routes to files\n";
    cout << " 14. Exit\n";
    cout << string(60, '-') << "\n";
    cout << "Enter your choice: ";
}

/* ================================================================
 *  MAIN
 * ================================================================ */
int main()
{

    // --- Instantiate the two main data structures ---
    ZoneGraph       graph;
    ContributorList contributors;

    // --- Pre-load startup data ---
    graph.preloadZones();
    graph.preloadRoutes();

    // Pre-load 5 contributors
    contributors.insertAtEnd("RSSB-001", "Uwimana Claudine",    1, "Employee", 15600);
    contributors.insertAtEnd("RSSB-002", "Habimana Patrick",    2, "Employee", 22400);
    contributors.insertAtEnd("RSSB-003", "Mukamana Grace",      3, "Employer", 185000);
    contributors.insertAtEnd("RSSB-004", "Nkurunziza Theogene", 4, "Employee", 18900);
    contributors.insertAtEnd("RSSB-005", "Gasana Innocent",     5, "Employer", 230000);

    int choice;

    do
    {
        displayMenu();
        choice = getInt("");

        switch (choice)
        {

        /* ---- 1. Add new zone(s) ---- */
        case 1:
        {
            int n = getInt("Enter the number of zones to add: ");
            if (n <= 0)
            {
                cout << "Please enter a positive number.\n";
                break;
            }

            for (int k = 0; k < n; k++)
            {
                int nextIndex = graph.getNumZones() + 1;
                string name = getLine("Enter the name for zone "
                                      + to_string(nextIndex) + ": ");
                graph.addZone(name);
            }
            cout << "Zones added successfully.\n";
            break;
        }

        /* ---- 2. Register route between zones ---- */
        case 2:
        {
            string z1 = getLine("Enter the name of the first zone:  ");
            string z2 = getLine("Enter the name of the second zone: ");
            graph.registerRoute(z1, z2);
            break;
        }

        /* ---- 3. Add operational cost for a route ---- */
        case 3:
        {
            string z1 = getLine("Enter the name of the first zone:  ");
            string z2 = getLine("Enter the name of the second zone: ");
            double cost = getDouble("Enter the operational cost (Million RWF): ");
            graph.addRouteCost(z1, z2, cost);
            break;
        }

        /* ---- 4. Edit zone name ---- */
        case 4:
        {
            int idx = getInt("Enter the index of the zone to edit: ");
            string newName = getLine("Enter the new name for zone "
                                     + to_string(idx) + ": ");
            graph.editZoneName(idx, newName);
            break;
        }

        /* ---- 5. Search zone by name ---- */
        case 5:
        {
            string name = getLine("Enter zone name to search: ");
            graph.searchZone(name);
            break;
        }

        /* ---- 6. Display zones ---- */
        case 6:
        {
            graph.displayZones();
            break;
        }

        /* ---- 7. Display adjacency matrices ---- */
        case 7:
        {
            graph.displayAdjMatrix();
            graph.displayCostMatrix();
            break;
        }

        /* ---- 8. Display all recorded data ---- */
        case 8:
        {
            graph.displayAll();
            break;
        }

        /* ---- 9. Add contributor ---- */
        case 9:
        {
            string id   = getLine("Enter contributor ID: ");
            string name = getLine("Enter full name: ");

            graph.displayZones();
            int zone = getInt("Enter zone index: ");

            cout << "Enter type (Employee/Employer): ";
            string type = getLine("");

            double contrib = getDouble("Enter monthly contribution (RWF): ");

            if (contributors.insertAtEnd(id, name, zone, type, contrib))
                cout << "Contributor added successfully.\n";
            break;
        }

        /* ---- 10. Search contributor by ID ---- */
        case 10:
        {
            string id = getLine("Enter contributor ID to search: ");
            contributors.searchByID(id);
            break;
        }

        /* ---- 11. Delete contributor by ID ---- */
        case 11:
        {
            string id = getLine("Enter contributor ID to delete: ");
            contributors.deleteByID(id);
            break;
        }

        /* ---- 12. Display all contributors ---- */
        case 12:
        {
            contributors.displayAll();
            break;
        }

        /* ---- 13. Save to files ---- */
        case 13:
        {
            graph.saveToFiles();
            break;
        }

        /* ---- 14. Exit ---- */
        case 14:
        {
            cout << "\nExiting RSSB System. Goodbye!\n";
            break;
        }

        default:
            cout << "Invalid choice. Please enter a number between 1 and 14.\n";
        }

    }
    while (choice != 14);

    return 0;
}
