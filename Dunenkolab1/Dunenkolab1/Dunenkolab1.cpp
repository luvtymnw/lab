#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

// Structure representing a pipeline segment
struct PipelineSegment {
    string kmMark;
    double lengthKm = 0.0;
    double diameterMm = 0.0;
    bool isUnderRepair = false;
};

// Structure representing a gas compressor station
struct CompressorStation {
    string name;
    int totalWorkshops = 0;
    int activeWorkshops = 0;
    int classLevel = 0;
};

// Template function for safe input with validation
template <typename T>
T getValidInput(const string& sect) {
    T value;
    while (true) {
        cout << sect;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. \n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

// Display the main menu
void showMenu() {
    cout << "\n   PIPELINE MANAGEMENT SYSTEM\n";
    cout << "--------------------------------\n";
    cout << "1. Add Pipeline Segment\n";
    cout << "2. Add Compressor Station\n";
    cout << "3. View All Objects\n";
    cout << "4. Toggle Pipe Repair Status\n";
    cout << "5. Manage Station Workshops\n";
    cout << "6. Save All Data\n";
    cout << "7. Load Data\n";
    cout << "8. Save Pipe Only\n";
    cout << "9. Save Station Only\n";
    cout << "0. Exit\n";
    cout << "--------------------------------\n";
}

// Create a new pipeline segment
void addPipeline(PipelineSegment& pipe) {
    cout << "\n--- Adding New Pipeline Segment ---\n";
    cout << "Enter kilometers ";
    getline(cin, pipe.kmMark);

    pipe.lengthKm = getValidInput<double>("Enter length (km): ");
    while (pipe.lengthKm <= 0) {
        cout << "Length must be positive. ";
        pipe.lengthKm = getValidInput<double>("Enter length (km): ");
    }

    pipe.diameterMm = getValidInput<double>("Enter diameter (mm): ");
    while (pipe.diameterMm <= 0) {
        cout << "Diameter must be positive. ";
        pipe.diameterMm = getValidInput<double>("Enter diameter (mm): ");
    }

    pipe.isUnderRepair = false;
    cout << "Pipeline segment added successfully!\n";
}

// Create a new compressor station
void addStation(CompressorStation& station) {
    cout << "\n--- Adding New Compressor Station ---\n";
    cout << "Enter station name: ";
    getline(cin, station.name);

    station.totalWorkshops = getValidInput<int>("Enter total number of workshops: ");
    while (station.totalWorkshops <= 0) {
        cout << "Total workshops must be positive. ";
        station.totalWorkshops = getValidInput<int>("Enter total number of workshops: ");
    }

    station.activeWorkshops = getValidInput<int>("Enter number of active workshops: ");
    while (station.activeWorkshops < 0 || station.activeWorkshops > station.totalWorkshops) {
        cout << "Active workshops cannot exceed total workshops. ";
        station.activeWorkshops = getValidInput<int>("Enter number of active workshops: ");
    }

    station.classLevel = getValidInput<int>("Enter station class (1-5): ");
    while (station.classLevel < 1 || station.classLevel > 5) {
        cout << "Class must be between 1 and 5. ";
        station.classLevel = getValidInput<int>("Enter station class (1-5): ");
    }

    cout << "Compressor station added successfully!\n";
}

// Display all stored objects
void displayObjects(const PipelineSegment& pipe, const CompressorStation& station) {
    cout << "\n--- CURRENT OBJECTS ---\n";

    cout << "\nPIPELINE SEGMENT:\n";
    if (pipe.kmMark.empty()) {
        cout << "  No data available\n";
    } else {
        cout << "  Kilometer mark: " << pipe.kmMark << "\n";
        cout << "  Length: " << pipe.lengthKm << " km\n";
        cout << "  Diameter: " << pipe.diameterMm << " mm\n";
        cout << "  Repair status: " << (pipe.isUnderRepair ? "Under repair" : "Operational") << "\n";
    }

    cout << "\nCOMPRESSOR STATION:\n";
    if (station.name.empty()) {
cout << "  No data available\n";
    } else {
        cout << "  Name: " << station.name << "\n";
        cout << "  Workshops: " << station.activeWorkshops << " / " << station.totalWorkshops << "\n";
        cout << "  Class: " << station.classLevel << "\n";
    }
}

// Toggle repair status of the pipeline
void toggleRepairStatus(PipelineSegment& pipe) {
    if (pipe.kmMark.empty()) {
        cout << "Error: No pipeline segment exists. Please add one first.\n";
        return;
    }

    cout << "\nCurrent status: " << (pipe.isUnderRepair ? "Under repair" : "Operational") << "\n";
    cout << "1. Mark as under repair\n";
    cout << "2. Mark as operational\n";

    int choice = getValidInput<int>("Select option: ");
    if (choice == 1) {
        pipe.isUnderRepair = true;
        cout << "Pipeline marked as under repair.\n";
    } else if (choice == 2) {
        pipe.isUnderRepair = false;
        cout << "Pipeline marked as operational.\n";
    } else {
        cout << "Invalid option.\n";
    }
}

// Manage active workshops at the station
void manageWorkshops(CompressorStation& station) {
    if (station.name.empty()) {
        cout << "Error: No compressor station exists. Please add one first.\n";
        return;
    }

    cout << "\nCurrent workshops: " << station.activeWorkshops << " / " << station.totalWorkshops << "\n";
    cout << "1. Start a workshop\n";
    cout << "2. Stop a workshop\n";

    int action = getValidInput<int>("Select action: ");
    if (action == 1) {
        if (station.activeWorkshops < station.totalWorkshops) {
            station.activeWorkshops++;
            cout << "Workshop started. Now " << station.activeWorkshops << " active.\n";
        } else {
            cout << "All workshops are already active.\n";
        }
    } else if (action == 2) {
        if (station.activeWorkshops > 0) {
            station.activeWorkshops--;
            cout << "Workshop stopped. Now " << station.activeWorkshops << " active.\n";
        } else {
            cout << "No active workshops to stop.\n";
        }
    } else {
        cout << "Invalid option.\n";
    }
}

// Save pipeline data to an output stream
void savePipe(const PipelineSegment& pipe, ofstream& out) {
    out << "PIPE\n";
    out << pipe.kmMark << "\n";
    out << pipe.lengthKm << "\n";
    out << pipe.diameterMm << "\n";
    out << pipe.isUnderRepair << "\n";
}

// Save station data to an output stream
void saveStation(const CompressorStation& station, ofstream& out) {
    out << "STATION\n";
    out << station.name << "\n";
    out << station.totalWorkshops << "\n";
    out << station.activeWorkshops << "\n";
    out << station.classLevel << "\n";
}

// Save all data to a single file
void saveAll(const PipelineSegment& pipe, const CompressorStation& station) {
    ofstream file("pipeline_data.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open file for writing.\n";
        return;
    }

    if (!pipe.kmMark.empty()) {
        savePipe(pipe, file);
    }
    if (!station.name.empty()) {
        saveStation(station, file);
    }

    file.close();
    cout << "Data saved successfully to pipeline_data.txt\n";
}

// Load pipeline data from input stream
void loadPipe(PipelineSegment& pipe, ifstream& in) {
    getline(in, pipe.kmMark);
    in >> pipe.lengthKm >> pipe.diameterMm >> pipe.isUnderRepair;
    in.ignore();
}

// Load station data from input stream
void loadStation(CompressorStation& station, ifstream& in) {
    getline(in, station.name);
    in >> station.totalWorkshops >> station.activeWorkshops >> station.classLevel;
    in.ignore();
}

// Load all data from file
void loadAll(PipelineSegment& pipe, CompressorStation& station) {
    ifstream file("pipeline_data.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open file for reading.\n";
        return;
    }

    pipe.kmMark.clear();
    station.name.clear();

    string type;
    while (getline(file, type)) {
        if (type == "PIPE") {
            loadPipe(pipe, file);
        } else if (type == "STATION") {
loadStation(station, file);
        }
    }

    file.close();
    cout << "Data loaded successfully from pipeline_data.txt\n";
}

// Handle user menu selection
void processChoice(int choice, PipelineSegment& pipe, CompressorStation& station) {
    switch (choice) {
        case 1:
            addPipeline(pipe);
            break;
        case 2:
            addStation(station);
            break;
        case 3:
            displayObjects(pipe, station);
            break;
        case 4:
            toggleRepairStatus(pipe);
            break;
        case 5:
            manageWorkshops(station);
            break;
        case 6:
            saveAll(pipe, station);
            break;
        case 7:
            loadAll(pipe, station);
            break;
        case 8: {
            ofstream f("pipe.txt");
            if (f.is_open()) {
                savePipe(pipe, f);
                f.close();
                cout << "Pipe saved to pipe.txt\n";
            } else {
                cout << "Failed to save pipe.\n";
            }
            break;
        }
        case 9: {
            ofstream f("station.txt");
            if (f.is_open()) {
                saveStation(station, f);
                f.close();
                cout << "Station saved to station.txt\n";
            } else {
                cout << "Failed to save station.\n";
            }
            break;
        }
        case 0:
            cout << "Exiting program.\n";
            exit(0);
        default:
            cout << "Invalid choice. Please try again.\n";
    }
}

// Main program loop
int main() {
    PipelineSegment currentPipe;
    CompressorStation currentStation;

    while (true) {
        showMenu();
        int option = getValidInput<int>("Enter your choice: ");
        processChoice(option, currentPipe, currentStation);
    }

    return 0;
}
