// lab1_task7.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

// Функция для вычисления биномиальных коэффициентов C(N, k) для k = 0..N
vector<long long> computeBinomialRow(int N) {
    vector<long long> row(N + 1, 1);
    for (int k = 1; k <= N; ++k) {
        // Используем рекуррентную формулу: C(n, k) = C(n, k-1) * (n - k + 1) / k
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

    // Разбор аргументов командной строки
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

    // Обязательное условие: должен быть задан -a
    if (!flag_a) {
        cerr << "Ошибка: Требуется указать ключ -a N." << endl;
        return 1;
    }

    // Вычисляем строку биномиальных коэффициентов
    vector<long long> coeffs = computeBinomialRow(N);

    // Выводим на экран
    cout << "Биномиальные коэффициенты степени " << N << ":" << endl;
    for (size_t i = 0; i < coeffs.size(); ++i) {
        if (i > 0) cout << "   "; // три пробела
        cout << coeffs[i];
    }
    cout << endl;

    // Если задан -d — записываем в файл
    if (flag_d) {
        ofstream file(outputFile);
        if (!file.is_open()) {
            cerr << "Ошибка: Не удалось открыть файл для записи: " << outputFile << endl;
            return 1;
        }

        for (size_t i = 0; i < coeffs.size(); ++i) {
            if (i > 0) file << "   ";
            file << coeffs[i];
        }
        file << endl;

        // Если также задан -e — дописываем автора
        if (flag_e) {
            file << "Автор — " << author << endl;
        }

        file.close();
        cout << "Результат записан в файл: " << outputFile << endl;
    }

    return 0;
}