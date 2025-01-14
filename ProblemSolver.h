#ifndef TSPGENETIC_PROBLEMSOLVER_H
#define TSPGENETIC_PROBLEMSOLVER_H

#include "DataGenerator.h"
#include <utility>
#include <vector>

// klasa zawierajaca metody do rozwiazywana problemu komiwojazera metoda podzialu i ograniczen
class ProblemSolver {
public: 
    DataGenerator generator;
    std::vector<std::vector<int>> population;
    ProblemSolver(DataGenerator& generator) : generator(generator) {}
    ~ProblemSolver() {}
    std::pair<int, std::vector<int>> geneticAlg(int popSize, double stopTime, double crossoverProb, double mutationProb, bool useSwapMutation);
    // funckja generujaca poczatkowa populacje, z num mozliwych permutacji
    void initialPopulation(int popSize);
    // funckja do tworzenia losowej permutacji
    void shuffleArray(std::vector<int>& vec);
    // funkcja do obliczania oceny funkcji
    std::vector<double> calcFitness(std::vector<std::vector<int>> pop);
    // funkcja sprawdzajaca czy permutacja jest unikalna w dotychczasowej populacji
    bool isUnique(std::vector<std::vector<int>> results, std::vector<int> permutation, int count);
    //funkcja wybierajaca w sposob zalezny od oceny funkcji permutacje z populacji
    std::vector<int> selectPermutation(std::vector<double> fitness);
    //funkcja krzyzowania
    void crossover(std::vector<int> parent1, std::vector<int> parent2, std::vector<int> child1, std::vector<int> child2);
    //funkcja mutacji swapem
    void mutationSwap(std::vector<int> path);
    //funkcja mutacji inversem
    void mutationInverse(std::vector<int> path);
    // funkcja znajdujaca koszt sciezki
    int findCost(std::vector<int> path);

};


#endif //TSPGENETIC_PROBLEMSOLVER_H
