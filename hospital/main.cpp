// =====================================================================
// HEADERS — Libraries we need
// =====================================================================
#include <iostream>   // cout, cin — for input/output to console
#include <fstream>    // ofstream, ifstream — for reading/writing files
#include <string>     // string type and string operations
#include <iomanip>    // setw() — for formatting columns in output
#include <sstream>    // stringstream — for splitting lines when loading files

using namespace std;  // so we don't write std::cout every time


// =====================================================================
// CLASS 1: Patient
// Think of this as a "form" — every patient fills this same form
// =====================================================================
class Patient {
public:
    // Data members (the fields on the form)
    string id;          // Auto-generated: P001, P002, P003...
    string name;        // Full name e.g. "Jean Baptiste"
    int    age;         // Age between 0 and 120
    string diagnosis;   // e.g. "Malaria", "Diabetes"
    string hospital;    // Name of assigned hospital e.g. "CHUK"
    int    priority;    // 1=Emergency, 2=Urgent, 3=Normal

    // -------------------------------------------
    // DEFAULT CONSTRUCTOR
    // Called when we do: Patient p;
    // Sets everything to zero/empty so no garbage values
    // -------------------------------------------
    Patient() {
        id        = "";
        name      = "";
        age       = 0;
        diagnosis = "";
        hospital  = "";
        priority  = 0;
    }

    // -------------------------------------------
    // PARAMETERIZED CONSTRUCTOR
    // Called when we do: Patient p("P001","Alice",28,...);
    // The word "this->" means "this object's own variable"
    // -------------------------------------------
    Patient(string pid, string pname, int page,
            string pdiag, string phosp, int ppri) {
        id        = pid;
        name      = pname;
        age       = page;
        diagnosis = pdiag;
        hospital  = phosp;
        priority  = ppri;
    }

    // -------------------------------------------
    // MEMBER FUNCTION: getPriorityLabel()
    // Converts int priority to a readable word
    // 1 → "Emergency", 2 → "Urgent", 3 → "Normal"
    // -------------------------------------------
    string getPriorityLabel() {
        if (priority == 1) return "Emergency";
        if (priority == 2) return "Urgent";
        return "Normal";
    }

    // -------------------------------------------
    // MEMBER FUNCTION: display()
    // Prints one patient row in a formatted table
    // setw(n) means "use n characters wide" for alignment
    // left = align text to the left side of the column
    // -------------------------------------------
    void display() {
        cout << left
             << setw(8)  << id
             << setw(22) << name
             << setw(6)  << age
             << setw(15) << hospital
             << setw(12) << getPriorityLabel()
             << diagnosis << "\n";
    }
};


// =====================================================================
// CLASS 2: Hospital
// Just stores the hospital's number and name
// =====================================================================
class Hospital {
public:
    int    index;   // 1 to 5
    string name;    // e.g. "King Faisal"

    // Default constructor
    Hospital() {
        index = 0;
        name  = "";
    }

    // Parameterized constructor
    Hospital(int i, string n) {
        index = i;
        name  = n;
    }
};


// =====================================================================
// CLASS 3: PatientSystem
// The MAIN class — manages everything
// =====================================================================
class PatientSystem {
private:
    // ---- Data Storage ----
    static const int MAX = 100;   // Maximum patients the system can hold
    Patient  patients[MAX];       // Array of Patient objects — our main data store
    int      patientCount;        // How many patients are currently in the array

    Hospital hospitals[5];        // Fixed array of 5 hospitals
    int      idCounter;           // Tracks last ID number used (starts at 0)
    bool     sortedByID;          // Tracks if array is currently sorted by ID
                                  // (Binary search only works when this is true)

    // ============================================================
    // PRIVATE HELPER: generateID()
    // Auto-generates IDs: P001, P002, ... P099, P100
    // Called internally every time a patient is added
    // ============================================================
    string generateID() {
        idCounter++;  // Increment the counter first

        string id = "P";  // Start with the letter P

        // Pad with zeros to keep IDs always 4 characters long
        if      (idCounter < 10)  id += "00" + to_string(idCounter); // P001
        else if (idCounter < 100) id += "0"  + to_string(idCounter); // P042
        else                      id +=        to_string(idCounter);  // P100

        return id;
    }

    // ============================================================
    // PRIVATE HELPER: getHospitalName()
    // Takes hospital index (1-5), returns hospital name
    // ============================================================
    string getHospitalName(int idx) {
        for (int i = 0; i < 5; i++) {
            if (hospitals[i].index == idx)
                return hospitals[i].name;
        }
        return "Unknown";  // Safety fallback (should never reach here after validation)
    }

    // ============================================================
    // PRIVATE HELPER: printHeader()
    // Prints the column headers for the patient table
    // ============================================================
    void printHeader() {
        cout << "\n" << left
             << setw(8)  << "ID"
             << setw(22) << "Name"
             << setw(6)  << "Age"
             << setw(15) << "Hospital"
             << setw(12) << "Priority"
             << "Diagnosis\n";
        cout << string(75, '-') << "\n";
        // string(75, '-') creates "---...---" (75 dashes) as a separator line
    }

public:
    // ============================================================
    // CONSTRUCTOR — Runs once when PatientSystem object is created
    // Sets starting values and loads the 5 hospitals
    // ============================================================
    PatientSystem() {
        patientCount = 0;        // 0 patients at the start
        idCounter    = 0;        // ID counter starts at 0 (first patient = P001)
        sortedByID   = false;    // Array not sorted yet

        // Load the 5 Rwanda hospitals into the fixed array
        hospitals[0] = Hospital(1, "CHUK");
        hospitals[1] = Hospital(2, "King Faisal");
        hospitals[2] = Hospital(3, "Butaro");
        hospitals[3] = Hospital(4, "Kibagabaga");
        hospitals[4] = Hospital(5, "Ruhengeri");
    }


    // ============================================================
    // MENU 1: addPatient()
    // Collects patient data from user, validates it, stores it
    // ============================================================
    void addPatient() {
        // Guard: check if array is full
        if (patientCount >= MAX) {
            cout << "System full! Cannot add more patients.\n";
            return;
        }

        string name, diagnosis;
        int age, hospIdx, priority;

        cout << "\n========== ADD NEW PATIENT ==========\n";

        // -- Get Name --
        cout << "Enter patient name: ";
        cin.ignore();             // Clears leftover newline from previous cin >>
        getline(cin, name);       // getline allows spaces in the name

        // -- Get Age WITH VALIDATION --
        cout << "Enter age: ";
        cin >> age;
        while (age < 0 || age > 120) {
            // Loop keeps asking until valid
            cout << "Invalid age! Must be between 0 and 120. Try again: ";
            cin >> age;
        }

        // -- Get Diagnosis --
        cout << "Enter diagnosis: ";
        cin.ignore();
        getline(cin, diagnosis);

        // -- Show hospitals, Get Hospital Index WITH VALIDATION --
        cout << "\nAvailable Hospitals:\n";
        for (int i = 0; i < 5; i++)
            cout << "  " << hospitals[i].index << ". " << hospitals[i].name << "\n";
        cout << "Enter hospital index (1-5): ";
        cin >> hospIdx;
        while (hospIdx < 1 || hospIdx > 5) {
            cout << "Invalid! Please enter a number from 1 to 5: ";
            cin >> hospIdx;
        }

        // -- Get Priority WITH VALIDATION --
        cout << "Enter priority (1=Emergency, 2=Urgent, 3=Normal): ";
        cin >> priority;
        while (priority < 1 || priority > 3) {
            cout << "Invalid! Please enter 1, 2, or 3: ";
            cin >> priority;
        }

        // -- Create Patient and Store --
        string newID    = generateID();            // Auto-generates e.g. P004
        string hospName = getHospitalName(hospIdx); // Gets name from index

        // Store the new Patient object at position patientCount in the array
        patients[patientCount] = Patient(newID, name, age, diagnosis, hospName, priority);
        patientCount++;      // Increase the count
        sortedByID = false;  // Array is no longer sorted after adding

        cout << "\nPatient added successfully. ID: " << newID << "\n";
    }


    // ============================================================
    // MENU 2: displayAll()
    // Shows every patient in a formatted table
    // ============================================================
    void displayAll() {
        if (patientCount == 0) {
            cout << "\nNo patients in the system.\n";
            return;
        }

        cout << "\n========== ALL PATIENTS (" << patientCount << " total) ==========";
        printHeader();  // Print column headers

        // Loop through every patient and call their display() function
        for (int i = 0; i < patientCount; i++)
            patients[i].display();

        cout << string(75, '-') << "\n";
    }


    // ============================================================
    // MENU 3A: bubbleSortByAge()
    //
    // HOW BUBBLE SORT WORKS:
    // - Compare two ADJACENT (side-by-side) elements
    // - If the left one is BIGGER, SWAP them
    // - Do this across the whole array — the biggest value
    //   "bubbles up" to the end like a bubble in water
    // - Repeat for remaining unsorted portion
    //
    // EXAMPLE with ages: [45, 28, 34, 31]
    // Pass 1: compare 45,28 → swap → [28,45,34,31]
    //         compare 45,34 → swap → [28,34,45,31]
    //         compare 45,31 → swap → [28,34,31,45] ← 45 bubbled to end
    // Pass 2: compare 28,34 → no swap
    //         compare 34,31 → swap → [28,31,34,45]
    // Pass 3: compare 28,31 → no swap (swapped=false → STOP early!)
    //
    // Time Complexity:
    //   Best Case  O(n)   — already sorted, detect with swapped flag
    //   Average    O(n²)  — random data
    //   Worst Case O(n²)  — reverse sorted data
    // ============================================================
    void bubbleSortByAge() {
        // Outer loop: number of passes needed
        for (int i = 0; i < patientCount - 1; i++) {
            bool swapped = false;  // Track if ANY swap happened this pass

            // Inner loop: compare adjacent pairs
            // After pass i, the last i elements are already sorted
            // so we only go up to patientCount-1-i
            for (int j = 0; j < patientCount - 1 - i; j++) {
                if (patients[j].age > patients[j + 1].age) {
                    // SWAP the two patients
                    Patient temp      = patients[j];
                    patients[j]       = patients[j + 1];
                    patients[j + 1]   = temp;
                    swapped = true;
                }
            }

            // OPTIMIZATION: If no swap occurred in this entire pass,
            // the array is already sorted — stop early
            // This is what gives us O(n) best case
            if (!swapped) break;
        }

        sortedByID = false;  // Sorting by age breaks our ID ordering
        cout << "Patients sorted by age successfully.\n";
    }


    // ============================================================
    // MENU 3B: selectionSortByPriority()
    //
    // HOW SELECTION SORT WORKS:
    // - Divide array into SORTED (left) and UNSORTED (right) parts
    // - Each pass: FIND the MINIMUM in the unsorted part
    // - SWAP that minimum into the first position of unsorted part
    // - The sorted part grows by 1 each pass
    //
    // EXAMPLE with priorities: [3, 1, 2, 1, 2]
    // Pass 0: min in [3,1,2,1,2] is 1 at index 1 → swap 3 and 1
    //         → [1, 3, 2, 1, 2]
    // Pass 1: min in [3,2,1,2] is 1 at index 3 → swap 3 and 1
    //         → [1, 1, 2, 3, 2]
    // Pass 2: min in [2,3,2] is 2 at index 2 → no swap needed
    //         → [1, 1, 2, 3, 2]
    // ... and so on
    //
    // Time Complexity: O(n²) in ALL cases (best, average, worst)
    // Because the inner loop always runs fully to find the minimum
    // ============================================================
    void selectionSortByPriority() {
        for (int i = 0; i < patientCount - 1; i++) {
            int minIdx = i;  // Assume current position has minimum

            // Scan the rest of the unsorted portion for a smaller priority
            for (int j = i + 1; j < patientCount; j++) {
                if (patients[j].priority < patients[minIdx].priority)
                    minIdx = j;  // Found new minimum
            }

            // Only swap if minimum is not already in correct position
            if (minIdx != i) {
                Patient temp       = patients[i];
                patients[i]        = patients[minIdx];
                patients[minIdx]   = temp;
            }
        }

        sortedByID = false;
        cout << "Patients sorted by priority successfully.\n";
    }

    void sortMenu() {
        cout << "\n========== SORT PATIENTS ==========\n";
        cout << "Sort by:\n";
        cout << "1. Age (Bubble Sort)\n";
        cout << "2. Priority (Selection Sort)\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        if      (choice == 1) bubbleSortByAge();
        else if (choice == 2) selectionSortByPriority();
        else                  cout << "Invalid choice.\n";
    }


    // ============================================================
    // MENU 4A: linearSearchByName()
    //
    // HOW LINEAR SEARCH WORKS:
    // - Start at position 0 in the array
    // - Check: does this patient's name match what we want?
    // - If YES → display it
    // - If NO  → move to next position
    // - Continue until end of array
    //
    // EXAMPLE: searching for "Marie" in [Alice, Eric, Marie, Jean]
    // Check index 0: Alice == Marie? NO → move on
    // Check index 1: Eric  == Marie? NO → move on
    // Check index 2: Marie == Marie? YES → display!
    // Check index 3: Jean  == Marie? NO → end
    //
    // Time Complexity:
    //   Best Case  O(1) — target is the very first element
    //   Average    O(n) — target is somewhere in the middle
    //   Worst Case O(n) — target is last or not found (checked all n)
    // ============================================================
    void linearSearchByName() {
        string target;
        cout << "Enter patient name to search: ";
        cin.ignore();
        getline(cin, target);

        bool found = false;
        printHeader();

        // Check every element one by one
        for (int i = 0; i < patientCount; i++) {
            if (patients[i].name == target) {
                patients[i].display();
                found = true;
                // Note: we don't break — we show ALL patients with this name
            }
        }

        if (!found)
            cout << "No patient found with name: " << target << "\n";
    }


    // ============================================================
    // PRIVATE HELPER: sortByID()
    // Sorts patients by their ID string before binary search
    // "P001" < "P002" < "P010" etc. — string comparison works correctly
    // ============================================================
    void sortByID() {
        cout << "Sorting by ID first (required for Binary Search)...\n";
        for (int i = 0; i < patientCount - 1; i++) {
            for (int j = 0; j < patientCount - 1 - i; j++) {
                if (patients[j].id > patients[j + 1].id) {
                    Patient temp    = patients[j];
                    patients[j]     = patients[j + 1];
                    patients[j + 1] = temp;
                }
            }
        }
        sortedByID = true;
        cout << "Array sorted by ID.\n";
    }


    // ============================================================
    // MENU 4B: binarySearchByID()
    //
    // HOW BINARY SEARCH WORKS:
    // - Array MUST be sorted first (by ID in our case)
    // - Look at the MIDDLE element
    // - If it's our target → FOUND!
    // - If target > middle → search only the RIGHT half (discard left)
    // - If target < middle → search only the LEFT half (discard right)
    // - Repeat on the remaining half until found or empty
    //
    // EXAMPLE: find P004 in [P001, P002, P003, P004, P005, P006, P007]
    //          lo=0, hi=6, mid=3 → patients[3].id = P004 → FOUND!
    //
    // EXAMPLE: find P006 in [P001, P002, P003, P004, P005, P006, P007]
    //          lo=0, hi=6, mid=3 → P004 < P006 → lo = mid+1 = 4
    //          lo=4, hi=6, mid=5 → P006 == P006 → FOUND!
    //
    // Time Complexity:
    //   Best Case  O(1)     — target is at the middle on first check
    //   Average    O(log n) — e.g. 1000 patients needs at most 10 checks
    //   Worst Case O(log n) — target not found
    //
    // WHY O(log n)?
    //   Each step HALVES the search space:
    //   n → n/2 → n/4 → n/8 → ... → 1
    //   That's log₂(n) steps
    // ============================================================
    void binarySearchByID() {
        // REQUIREMENT: array must be sorted by ID
        if (!sortedByID) {
            cout << "\nBinary search requires sorted data.\n";
            sortByID();
        }

        string target;
        cout << "Enter Patient ID: ";
        cin >> target;

        int lo = 0;                  // Start of search range
        int hi = patientCount - 1;   // End of search range
        bool found = false;

        while (lo <= hi) {
            // Find the middle index
            // We write lo + (hi-lo)/2 instead of (lo+hi)/2
            // to avoid integer overflow when lo+hi is very large
            int mid = lo + (hi - lo) / 2;

            if (patients[mid].id == target) {
                // FOUND — display and stop
                cout << "\nPatient found:\n";
                printHeader();
                patients[mid].display();
                found = true;
                break;
            } else if (patients[mid].id < target) {
                // Target is in the RIGHT half
                lo = mid + 1;
            } else {
                // Target is in the LEFT half
                hi = mid - 1;
            }
        }

        if (!found)
            cout << "Patient with ID '" << target << "' not found.\n";
    }

    void searchMenu() {
        cout << "\n========== SEARCH PATIENT ==========\n";
        cout << "Search by:\n";
        cout << "1. Name (Linear Search)\n";
        cout << "2. ID   (Binary Search)\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        if      (choice == 1) linearSearchByName();
        else if (choice == 2) binarySearchByID();
        else                  cout << "Invalid choice.\n";
    }


    // ============================================================
    // MENU 5: updatePatient()
    // Find a patient by ID and update one of their fields
    // ============================================================
    void updatePatient() {
        string searchID;
        cout << "\n========== UPDATE PATIENT RECORD ==========\n";
        cout << "Enter Patient ID to update: ";
        cin >> searchID;

        // Linear search to find the patient
        int foundIdx = -1;  // -1 means "not found yet"
        for (int i = 0; i < patientCount; i++) {
            if (patients[i].id == searchID) {
                foundIdx = i;
                break;  // Stop as soon as we find it
            }
        }

        if (foundIdx == -1) {
            cout << "Patient with ID '" << searchID << "' not found.\n";
            return;
        }

        // Show current record before changing it
        cout << "\nCurrent record:\n";
        printHeader();
        patients[foundIdx].display();

        cout << "\nWhat would you like to update?\n";
        cout << "1. Name\n";
        cout << "2. Age\n";
        cout << "3. Diagnosis\n";
        cout << "4. Hospital\n";
        cout << "5. Priority\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter new name: ";
                cin.ignore();
                getline(cin, patients[foundIdx].name);
                cout << "Name updated successfully.\n";
                break;

            case 2:
                cout << "Enter new age: ";
                cin >> patients[foundIdx].age;
                while (patients[foundIdx].age < 0 || patients[foundIdx].age > 120) {
                    cout << "Invalid! Enter 0-120: ";
                    cin >> patients[foundIdx].age;
                }
                cout << "Age updated successfully.\n";
                break;

            case 3:
                cout << "Enter new diagnosis: ";
                cin.ignore();
                getline(cin, patients[foundIdx].diagnosis);
                cout << "Diagnosis updated successfully.\n";
                break;

            case 4: {
                cout << "Available Hospitals:\n";
                for (int i = 0; i < 5; i++)
                    cout << "  " << hospitals[i].index << ". " << hospitals[i].name << "\n";
                cout << "Enter new hospital index (1-5): ";
                int hi;
                cin >> hi;
                while (hi < 1 || hi > 5) {
                    cout << "Invalid! Enter 1-5: ";
                    cin >> hi;
                }
                patients[foundIdx].hospital = getHospitalName(hi);
                cout << "Hospital updated successfully.\n";
                break;
            }

            case 5:
                cout << "Enter new priority (1=Emergency, 2=Urgent, 3=Normal): ";
                cin >> patients[foundIdx].priority;
                while (patients[foundIdx].priority < 1 || patients[foundIdx].priority > 3) {
                    cout << "Invalid! Enter 1, 2, or 3: ";
                    cin >> patients[foundIdx].priority;
                }
                cout << "Priority updated successfully.\n";
                break;

            default:
                cout << "Invalid choice. No changes made.\n";
                return;
        }
        cout << "Patient record updated.\n";
    }


    // ============================================================
    // MENU 6: deletePatient()
    // Find patient by ID, remove them from the array
    //
    // HOW DELETION FROM ARRAY WORKS:
    // Array: [P001, P002, P003, P004, P005]
    // Delete P003 (index 2):
    // Shift left starting from index 2:
    //   patients[2] = patients[3]  → [P001, P002, P004, P004, P005]
    //   patients[3] = patients[4]  → [P001, P002, P004, P005, P005]
    // patientCount--               → [P001, P002, P004, P005] (count=4)
    // The last duplicate is "ignored" since count says only 4 exist
    // ============================================================
    void deletePatient() {
        string searchID;
        cout << "\n========== DISCHARGE PATIENT ==========\n";
        cout << "Enter Patient ID to discharge: ";
        cin >> searchID;

        // Find the patient
        int foundIdx = -1;
        for (int i = 0; i < patientCount; i++) {
            if (patients[i].id == searchID) {
                foundIdx = i;
                break;
            }
        }

        if (foundIdx == -1) {
            cout << "Patient not found.\n";
            return;
        }

        // Emergency patients need extra confirmation
        if (patients[foundIdx].priority == 1) {
            char confirm;
            cout << "\n!!! WARNING !!!\n";
            cout << patients[foundIdx].name << " is an EMERGENCY patient.\n";
            cout << "Discharging an emergency patient could be dangerous.\n";
            cout << "Are you absolutely sure? (y/n): ";
            cin >> confirm;
            if (confirm != 'y' && confirm != 'Y') {
                cout << "Discharge cancelled. Patient kept in system.\n";
                return;
            }
        }

        // Save name before deletion for confirmation message
        string name = patients[foundIdx].name;

        // Shift all elements after foundIdx one position to the LEFT
        for (int i = foundIdx; i < patientCount - 1; i++) {
            patients[i] = patients[i + 1];
        }
        patientCount--;  // One fewer patient

        cout << name << " has been successfully discharged.\n";
    }


    // ============================================================
    // MENU 7: displayByHospital()
    // Show only patients assigned to a chosen hospital
    // ============================================================
    void displayByHospital() {
        cout << "\n========== PATIENTS BY HOSPITAL ==========\n";
        cout << "Select hospital:\n";
        for (int i = 0; i < 5; i++)
            cout << "  " << hospitals[i].index << ". " << hospitals[i].name << "\n";
        cout << "Enter hospital index (1-5): ";
        int idx;
        cin >> idx;
        while (idx < 1 || idx > 5) {
            cout << "Invalid! Enter 1-5: ";
            cin >> idx;
        }

        string hospName = getHospitalName(idx);
        cout << "\nPatients assigned to " << hospName << ":";
        printHeader();

        bool found = false;
        for (int i = 0; i < patientCount; i++) {
            if (patients[i].hospital == hospName) {
                patients[i].display();
                found = true;
            }
        }

        if (!found)
            cout << "No patients currently assigned to " << hospName << ".\n";
    }


    // ============================================================
    // MENU 8: saveToFile()
    // Writes all data to patients.txt and hospitals.txt
    //
    // FILE FORMAT (pipe-delimited for easy reloading):
    // P001|Alice Uwase|28|CHUK|Malaria|1
    // P002|Eric Nkurunziza|45|Butaro|Diabetes|3
    //
    // WHY PIPE '|'?
    // Patient names can have spaces ("Jean Baptiste")
    // If we used spaces as delimiters, we'd confuse name spaces with field separators
    // The pipe character | never appears in names or diagnoses
    // ============================================================
    void saveToFile() {
        // --- Save patients ---
        ofstream pFile("patients.txt");
        if (!pFile.is_open()) {
            cout << "Error: Could not open patients.txt for writing.\n";
            return;
        }

        // Write each patient as pipe-delimited row
        for (int i = 0; i < patientCount; i++) {
            pFile << patients[i].id       << "|"
                  << patients[i].name     << "|"
                  << patients[i].age      << "|"
                  << patients[i].hospital << "|"
                  << patients[i].diagnosis<< "|"
                  << patients[i].priority << "\n";
        }
        pFile.close();

        // --- Save hospitals ---
        ofstream hFile("hospitals.txt");
        if (!hFile.is_open()) {
            cout << "Error: Could not open hospitals.txt for writing.\n";
            return;
        }

        hFile << "Index|Hospital Name\n";
        for (int i = 0; i < 5; i++) {
            hFile << hospitals[i].index << "|" << hospitals[i].name << "\n";
        }
        hFile.close();

        cout << "Data saved successfully to patients.txt and hospitals.txt\n";
    }


    // ============================================================
    // loadFromFile()
    // Called ONCE at startup — reads patients.txt back into array
    //
    // HOW stringstream WORKS:
    // line = "P001|Alice Uwase|28|CHUK|Malaria|1"
    // We create a stringstream from the line, then use getline(ss, field, '|')
    // to read each piece separated by '|' into separate variables
    // ============================================================
    void loadFromFile() {
        ifstream file("patients.txt");
        if (!file.is_open()) {
            cout << "(No saved file found — starting fresh)\n";
            return;
        }

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;  // Skip blank lines

            stringstream ss(line);       // Turn the line into a stream
            string id, name, ageStr, hospital, diagnosis, priorityStr;

            // Extract each field separated by '|'
            getline(ss, id,         '|');
            getline(ss, name,       '|');
            getline(ss, ageStr,     '|');
            getline(ss, hospital,   '|');
            getline(ss, diagnosis,  '|');
            getline(ss, priorityStr,'|');

            // Convert string numbers to int
            int age      = stoi(ageStr);
            int priority = stoi(priorityStr);

            // Store the reconstructed patient
            patients[patientCount++] = Patient(id, name, age, diagnosis, hospital, priority);

            // Update idCounter to the highest number seen
            // id.substr(1) removes the "P" → "001" → stoi gives 1
            int num = stoi(id.substr(1));
            if (num > idCounter) idCounter = num;
        }

        file.close();
        cout << patientCount << " patients loaded from file.\n";
    }


    // ============================================================
    // run() — The main menu loop
    // Keeps showing the menu until user picks 9 (Exit)
    // ============================================================
    void run() {
        loadFromFile();  // Load saved data on startup

        int choice;
        do {
            cout << "\n\n=============================================\n";
            cout << "   RWANDA HOSPITAL PATIENT MANAGEMENT SYSTEM  \n";
            cout << "=============================================\n";
            cout << " 1. Add new patient\n";
            cout << " 2. Display all patients\n";
            cout << " 3. Sort patients (by age or priority)\n";
            cout << " 4. Search for a patient\n";
            cout << " 5. Update patient record\n";
            cout << " 6. Delete patient (discharge)\n";
            cout << " 7. Display patients by hospital\n";
            cout << " 8. Save data to file\n";
            cout << " 9. Exit\n";
            cout << "=============================================\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: addPatient();        break;
                case 2: displayAll();        break;
                case 3: sortMenu();          break;
                case 4: searchMenu();        break;
                case 5: updatePatient();     break;
                case 6: deletePatient();     break;
                case 7: displayByHospital(); break;
                case 8: saveToFile();        break;
                case 9: cout << "\nExiting system. Data saved. Goodbye!\n";
                        saveToFile(); break;   // Auto-save on exit
                default: cout << "Invalid choice! Please enter 1-9.\n";
            }

        } while (choice != 9);
    }

}; // end class PatientSystem


// ============================================================
// main() — Entry point of the program
// Creates ONE PatientSystem object and calls run()
// ============================================================
int main() {
    PatientSystem system;  // Creates object — constructor runs here
    system.run();          // Starts the menu loop
    return 0;              // Program ends cleanly
}
