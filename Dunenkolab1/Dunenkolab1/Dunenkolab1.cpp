#include <iostream>
#include <fstream>
#include <string>
#include <limits>

struct Pipe {
    std::string km_mark;
    double length_km;
    int diameter_mm;
    bool under_repair;

    void input() {
        std::cout << "Enter km mark: ";
        std::cin.ignore();
        std::getline(std::cin, km_mark);

        std::cout << "Enter length (km): ";
        while (!(std::cin >> length_km) || length_km <= 0) {
            std::cout << "Invalid input. Enter a positive number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "Enter diameter (mm): ";
        while (!(std::cin >> diameter_mm) || diameter_mm <= 0) {
            std::cout << "Invalid input. Enter a positive integer: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        under_repair = false;
    }

    void display() const {
        std::cout << "Pipe:\n";
        std::cout << "  KM Mark: " << km_mark << "\n";
        std::cout << "  Length: " << length_km << " km\n";
        std::cout << "  Diameter: " << diameter_mm << " mm\n";
        std::cout << "  Under repair: " << (under_repair ? "Yes" : "No") << "\n";
    }

    void toggle_repair() {
        under_repair = !under_repair;
        std::cout << "Repair status toggled.\n";
    }

    void save(std::ofstream& out) const {
        out << km_mark << "\n"
            << length_km << "\n"
            << diameter_mm << "\n"
            << under_repair << "\n";
    }

    bool load(std::ifstream& in) {
        if (!std::getline(in, km_mark)) return false;
        if (!(in >> length_km)) return false;
        if (!(in >> diameter_mm)) return false;
        if (!(in >> under_repair)) return false;
        in.ignore(); // skip newline after bool
        return true;
    }
};

struct CompressorStation {
    std::string name;
    int total_workshops;
    int active_workshops;
    int station_class;

    void input() {
        std::cout << "Enter station name: ";
        std::cin.ignore();
        std::getline(std::cin, name);

        std::cout << "Enter total number of workshops: ";
        while (!(std::cin >> total_workshops) || total_workshops <= 0) {
            std::cout << "Invalid input. Enter a positive integer: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        active_workshops = total_workshops; // initially all active

        std::cout << "Enter station class (1-5): ";
        while (!(std::cin >> station_class) || station_class < 1 || station_class > 5) {
            std::cout << "Invalid input. Enter an integer from 1 to 5: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    void display() const {
        std::cout << "Compressor Station:\n";
        std::cout << "  Name: " << name << "\n";
        std::cout << "  Total workshops: " << total_workshops << "\n";
        std::cout << "  Active workshops: " << active_workshops << "\n";
        std::cout << "  Station class: " << station_class << "\n";
    }

    void start_workshop() {
        if (active_workshops < total_workshops) {
            active_workshops++;
            std::cout << "Workshop started. Active: " << active_workshops << "\n";
        }
        else {
            std::cout << "All workshops are already active.\n";
        }
    }

    void stop_workshop() {
        if (active_workshops > 0) {
            active_workshops--;
            std::cout << "Workshop stopped. Active: " << active_workshops << "\n";
        }
        else {
            std::cout << "No workshops to stop.\n";
        }
    }

    void save(std::ofstream& out) const {
        out << name << "\n"
            << total_workshops << "\n"
            << active_workshops << "\n"
            << station_class << "\n";
    }

    bool load(std::ifstream& in) {
        if (!std::getline(in, name)) return false;
        if (!(in >> total_workshops)) return false;
        if (!(in >> active_workshops)) return false;
        if (!(in >> station_class)) return false;
        in.ignore(); // skip newline after int
        return true;
    }
};

int get_menu_choice() {
    int choice;
    std::cout << "\nMenu:\n";
    std::cout << "1. Add Pipe\n";
    std::cout << "2. Add Compressor Station\n";
    std::cout << "3. View all objects\n";
    std::cout << "4. Edit Pipe (toggle repair)\n";
    std::cout << "5. Edit Compressor Station (start/stop workshop)\n";
    std::cout << "6. Save to file\n";
    std::cout << "7. Load from file\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose an option: ";

    while (!(std::cin >> choice) || choice < 0 || choice > 7) {
        std::cout << "Invalid choice. Enter 0-7: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return choice;
}

void edit_compressor_station(CompressorStation& cs) {
    if (cs.name.empty()) {
        std::cout << "No compressor station exists.\n";
        return;
    }

    int action;
    std::cout << "1. Start workshop\n2. Stop workshop\nChoose: ";
    while (!(std::cin >> action) || (action != 1 && action != 2)) {
        std::cout << "Invalid choice. Enter 1 or 2: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (action == 1) {
        cs.start_workshop();
    }
    else {
        cs.stop_workshop();
    }
}

int main() {
    Pipe pipe;
    CompressorStation cs;
    bool pipe_exists = false;
    bool cs_exists = false;

    while (true) {
        int choice = get_menu_choice();

        switch (choice) {
        case 1: {
            pipe.input();
            pipe_exists = true;
            break;
        }
        case 2: {
            cs.input();
            cs_exists = true;
            break;
        }
        case 3: {
            if (pipe_exists) pipe.display();
            else std::cout << "No pipe data.\n";

            if (cs_exists) cs.display();
            else std::cout << "No compressor station data.\n";
            break;
        }
        case 4: {
            if (!pipe_exists) {
                std::cout << "No pipe to edit.\n";
            }
            else {
                pipe.toggle_repair();
            }
            break;
        }
        case 5: {
            if (!cs_exists) {
                std::cout << "No compressor station to edit.\n";
            }
            else {
                edit_compressor_station(cs);
            }
            break;
        }
        case 6: {
            std::string filename;
            std::cout << "Enter filename to save: ";
            std::cin.ignore();
            std::getline(std::cin, filename);

            std::ofstream out(filename);
            if (!out) {
                std::cout << "Error opening file for writing.\n";
                break;
            }

            out << pipe_exists << "\n";
            if (pipe_exists) pipe.save(out);

            out << cs_exists << "\n";
            if (cs_exists) cs.save(out);

            out.close();
            std::cout << "Data saved successfully.\n";
            break;
        }
        case 7: {
            std::string filename;
            std::cout << "Enter filename to load: ";
            std::cin.ignore();
            std::getline(std::cin, filename);

            std::ifstream in(filename);
            if (!in) {
                std::cout << "Error opening file for reading.\n";
                break;
            }

            in >> pipe_exists;
            in.ignore();
            if (pipe_exists && !pipe.load(in)) {
                std::cout << "Error loading pipe data.\n";
                pipe_exists = false;
            }

            in >> cs_exists;
            in.ignore();
            if (cs_exists && !cs.load(in)) {
                std::cout << "Error loading compressor station data.\n";
                cs_exists = false;
            }

            in.close();
            std::cout << "Data loaded successfully.\n";
            break;
        }
        case 0: {
            std::cout << "Exiting...\n";
            return 0;
        }
        }
    }
}