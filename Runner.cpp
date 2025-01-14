// #include "Runner.h"
// #include <climits>
// #include <cstddef>
// #include <string>
// #include <fstream>
// #include <utility>


// Runner::Runner(Config& config, DataGenerator& generator, ProblemSolver& ps) {
//    this->config = config;
//    this->generator = generator;
//    this->ps = ps;
// }

// void Runner::executeTest() {
//     // wczyttaj dane z pliku i zapisz w macierzy
//     generator.loadTSPLIB(config.dataFile);
//     // ustaw parametry na podstawie danych z pliku
//     ps.changeParameters(
//         ps.generateTemp(generator.matrix, generator.matrixSize, config.worseAcceptanceProbability, 500),
//         config.alpha, 
//         config.neighbourDefinition, 
//         config.stopSeconds, 
//         config.initialPathFromNearestNeighbour
//     );
//     // wykonaj algorytm, ktory nie zapisuje danych do pliku
//     ps.simAnnealing(generator.matrix, generator.matrixSize);
// }

// void Runner::executeSimulation() {
//     // uwtorz plik wyjsciowy o zadanej w pliku nazwie
//     std::string outputName = config.outputFileName;
//     std::fstream output(outputName, std::ios::out);

//     output << "nr;czas;koszt\n";

//     // wczytaj dane z pliku i zapisz w macierzy
//     generator.loadTSPLIB(config.dataFile);
//     ps.changeParameters(
//         ps.generateTemp(generator.matrix, generator.matrixSize, config.worseAcceptanceProbability, 500),
//         config.alpha, 
//         config.neighbourDefinition, 
//         config.stopSeconds, 
//         config.initialPathFromNearestNeighbour
//     );

//     // zmienna sprawdzajaca najlepszy uzyskany wynik w ciagu calej symulacji    
//     std::pair<int, int*> minResult = std::make_pair(INT_MAX, nullptr);

//     /*
//     wykonaj algorytm (zapisujaca chwilowe najlepsze wyniki do pliku zadanego jako parametr) 
//     zadana liczbe razy i zaleznie od danych z pliku wyswietlaj postep lub nie
//     zapisuj najlepszy wynik, bo najlepsza sciezka bedzie zapisana do pliku
//     */
//     for(int i = 0; i < config.runsNumber; i++) {
//         if(config.showProgress) std::cout << "Currently running test " << i+1 << "/" << config.runsNumber << "\n";
//         auto temp = ps.simAnnealing(generator.matrix, generator.matrixSize, i, output);
//         if(temp.first < minResult.first) {
//             delete[] minResult.second;
//             minResult = temp;
//         } else {
//             delete[] temp.second;
//         }
//     }

//     output << "\nNajlepsza znaleziona ścieka:\n";
//     for(int i = 0; i < generator.matrixSize; i++) {
//         output << minResult.second[i] << "-";
//     }
//     output << minResult.second[0] << "\n";
//     output.close();
// }

