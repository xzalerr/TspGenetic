#include "DataGenerator.h"
#include <iostream>
#include <fstream>
#include <string>

void DataGenerator::loadTSPLIB(std::string name) {
    // otwórz plik
    std::fstream input(name);
    if (!input.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku!\n";
        return;
    }

    std::string line;
    int n = 0;  // rozmiar macierzy

    // pomijanie nagłówka, wyszukiwanie DIMENSION
    while (std::getline(input, line)) {
        if (line.rfind("DIMENSION") == 0) {
            // parsowanie rozmiaru
            std::sscanf(line.c_str(), "DIMENSION: %d", &n);
        } else if (line == "EDGE_WEIGHT_SECTION") {
            break;  // przerwij, gdy znajdziesz sekcję wag
        }
    }

    // alokacja pamięci na macierz
    matrix.clear();
    matrix.resize(n, std::vector<int>(n));
    matrixSize = n;

    // wczytywanie wartości macierzy wag
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            input >> matrix[i][j];
        }
    }

    input.close();
}
