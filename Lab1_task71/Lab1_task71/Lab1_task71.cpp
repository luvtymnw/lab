// lab1_task7.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;
vector<long long> computeBinomialRow(int N) {
    vector<long long> row(N + 1, 1);
    for (int k = 1; k <= N; ++k) {
        
        row[k] = row[k - 1] * (N - k + 1) / k;
    }
    return row;
}

int main(int argc, char* argv[]) {
    int N = -1;                // аргумент для -a
    string outputFile = "";    // аргумент для -d
    string author = "";        // аргумент для -e
    bool flag_a = false;
    bool flag_d = false;
    bool flag_e = false;

    
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        if (arg == "-a" && i + 1 < argc) {
            N = atoi(argv[++i]);
            if (N < 0) {
                cerr << "Ошибка: N должно быть неотрицательным целым числом." << endl;
                return 1;
            }
            flag_a = true;
        }
        else if (arg == "-d" && i + 1 < argc) {
            outputFile = argv[++i];
            flag_d = true;
        }
        else if (arg == "-e" && i + 1 < argc) {
            author = argv[++i];
            flag_e = true;
        }
        else {
            cerr << "Ошибка: Неизвестный параметр или отсутствует аргумент: " << arg << endl;
            return 1;
        }
    }

    
    if (!flag_a) {
        cerr << "Ошибка: Требуется указать ключ -a N." << endl;
        return 1;
    }

    
    vector<long long> coeffs = computeBinomialRow(N);

   
    cout << "binominal coefficients " << N << ":" << endl;
    for (size_t i = 0; i < coeffs.size(); ++i) {
        if (i > 0) cout << "   "; 
        cout << coeffs[i];
    }
    cout << endl;

   
    if (flag_d) {
        ofstream file(outputFile);
        if (!file.is_open()) {
            cerr << "Error. Can't open: " << outputFile << endl;
            return 1;
        }

        for (size_t i = 0; i < coeffs.size(); ++i) {
            if (i > 0) file << "   ";
            file << coeffs[i];
        }
        file << endl;

        
        if (flag_e) {
            file << "Autor- " << author << endl;
        }

        file.close();
        cout << "the resut is saved: " << outputFile << endl;
    }

    return 0;
}