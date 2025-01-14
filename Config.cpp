#include "Config.h"
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

void Config::loadData(const std::string& fileName) {
    // otworz plik konfiguracyjny o nazwie podanej jako parametr
    std::ifstream file(fileName);
    if(!file.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku konfiguracyjnego!\n";
        return;
    }
    /* wczytanie danych z otwartego pliku i przeksztalcenie do obiektu json za pomoca
     * biblioteki nlohmaann/json.hpp
     */
    json data = json::parse(file);
    mode = data.at("mode").get<std::string>(); 
    /* w zaleznosci od trybu, wczytujemy odpowiednie dane konfiguracyjne.
     * tryb "test" laduje ustawienia specyficzne dla testow, podczas gdy tryb "simulation"
     * laduje dane przeznaczone do symulacji.
     */
    if(mode=="test") {
        const auto& testData = data.at("test");
        dataFile = testData.at("dataFile").get<std::string>();
        worseAcceptanceProbability = testData.at("worseAcceptanceProbability").get<double>();
        alpha = testData.at("alpha").get<double>();
        neighbourDefinition = testData.at("neighbourDefinition").get<int>();
        stopSeconds = testData.at("stopSeconds").get<int>();
        initialPathFromNearestNeighbour = testData.at("initialPathFromNearestNeighbour").get<bool>();
    } else if(mode=="simulation") {
        const auto& simData = data.at("simulation");
        dataFile = simData.at("dataFile").get<std::string>();
        worseAcceptanceProbability = simData.at("worseAcceptanceProbability").get<double>();
        alpha = simData.at("alpha").get<double>();
        neighbourDefinition = simData.at("neighbourDefinition").get<int>();
        stopSeconds = simData.at("stopSeconds").get<int>();
        initialPathFromNearestNeighbour = simData.at("initialPathFromNearestNeighbour").get<bool>();

        outputFileName = simData.at("outputFileName").get<std::string>();
        runsNumber = simData.at("runsNumber").get<int>();
        showProgress = simData.at("showProgress").get<bool>();
    } else {
        std::cerr << "Niepoprawny tryb: " << mode << ", do wyboru są opcje test i simulation!\n";
    }
}