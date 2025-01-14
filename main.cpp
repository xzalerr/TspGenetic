#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include "ProblemSolver.h"
#include "DataGenerator.h"

#ifdef __APPLE__
#include <mach-o/dyld.h>
#elif _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// metoda odczytujaca w czasie runtime sciezke do pliku wykonywalnego w zaleznosci od systemu operacyjnego
std::string getExecutablePath() {
    char path[1024];
    uint32_t size = sizeof(path);

#ifdef __APPLE__
    if(_NSGetExecutablePath(path, &size) == 0) {
        return std::string(path);
    }
#elif _WIN32
    if(GetModuleFileName(NULL, path, size) != 0) {
        return std::string(path);
    }
#else
    if(readlink("/proc/self/exe", path, size) != -1) {
        return std::string(path+"\0");
    }
#endif
    return "";
}

// metoda zwracajaca sciezke do pliku konfiguracyjnego w zaleznosci od sciezki do pliku wykonywalnego
std::string getConfigFilePath() {
    std::string exePath = getExecutablePath();
    if (exePath.empty()) {
        std::cerr << "Nie udalo sie odczytac sciezki do pliku wykonywalnego!\n";
        return "";
    }
    std::filesystem::path exeDir = std::filesystem::path(exePath).parent_path();
    std::filesystem::path dirPath = std::filesystem::path(exeDir).parent_path();
    std::string configPath = dirPath.string() + "/config.json";

    return configPath;
}

int main() {
    // // wczytanie konfiguracji
    // Config config;
    // std::string path = getConfigFilePath();
    // if (path.empty()) {
    //     return 1;
    // }
    // config.loadData(path);

    // // utworzenie obiektow potrzebych do dzialania programu
    // DataGenerator generator;
    // ProblemSolver ps;
    // Runner runner(config, generator, ps);

    // // wybor trybu dzialania programu
    // if (config.mode == "test") {
    //     runner.executeTest();
    // } else if (config.mode == "simulation") {
    //     runner.executeSimulation();
    // } else {
    //     std::cerr << "Nie ma takiej opcji!\n";
    // }

    DataGenerator dg;
    dg.loadTSPLIB("/Users/rafalzalecki/CLionProjects/TspGenetic/graphs/ftv47.atsp");
    ProblemSolver solver(dg);
    auto result = solver.geneticAlg(1000, 10, 0.8, 0.01, false);
    std::cout<<"Best cost: " << result.first << "\n";
}