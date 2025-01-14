#ifndef TSPGENETIC_CONFIG_H
#define TSPGENETIC_CONFIG_H

#include <iostream>
#include <vector>

// klasa sluzaca do wczytania danych z pliku konfiguracyjnego i przechowywanie danych
class Config {
public:
    std::string mode;

    std::string dataFile;
    double worseAcceptanceProbability;
    double alpha;
    int neighbourDefinition;
    int stopSeconds;
    bool initialPathFromNearestNeighbour;

    std::string outputFileName;
    int runsNumber;
    bool showProgress;
    
    // metoda wczytujaca konfiguracje z pliku JSON o podanej nazwie
    void loadData(const std::string& fileName);
};


#endif //TSPGENETIC_CONFIG_H
