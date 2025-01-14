#ifndef TSPGENETIC_DATAGENERATOR_H
#define TSPGENETIC_DATAGENERATOR_H

#include <string>
#include <vector>

// klasa do generowania losowych grafow
class DataGenerator {
public:
    std::vector<std::vector<int>> matrix;
    int matrixSize;

    // funkcja wczytujaca dane z pliku w formacie TSPLIB
    void loadTSPLIB(std::string name);
};


#endif //TSPGENETIC_DATAGENERATOR_H
