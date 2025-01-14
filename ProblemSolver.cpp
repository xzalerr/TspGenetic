#include "ProblemSolver.h"
#include "DataGenerator.h"
#include <algorithm>
#include <random>
#include <utility>
#include <vector>

void ProblemSolver::initialPopulation(int popSize) {
    population.clear();
    population.resize(popSize, std::vector<int>(generator.matrixSize));

    std::vector<int> perm(generator.matrixSize);
    for(int i = 0; i < generator.matrixSize; i++) {
        perm[i] = i;
    }

    for(int i = 0; i < popSize; i++) {
        bool unique = false;
        while(!unique) {
            shuffleArray(perm);
            unique = isUnique(population, perm, i);
        }
        population[i] = perm;
    }
}

// agortym fishera-yatesa do shufflowania tablicy - https://bost.ocks.org/mike/shuffle/
void ProblemSolver::shuffleArray(std::vector<int>& vec) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0, 1.0);
    int index;
    int n = vec.size();
    while(n>0) {
        index = std::floor(dist(gen) * n--);
        std::swap(vec[index], vec[n]);
    }
}

std::vector<double> ProblemSolver::calcFitness(std::vector<std::vector<int>> pop) {
    int popSize = pop.size();
    std::vector<int> costAllPermutations(popSize);
    for(int i  = 0; i < popSize; i++) {
        costAllPermutations[i] = findCost(pop[i]);
    }
    
    int maxCost = *std::max_element(costAllPermutations.begin(), costAllPermutations.end());

    std::vector<double> populationFitness(popSize);
    for(int i = 0; i < popSize; i++) {
        populationFitness[i] = maxCost - costAllPermutations[i];
    }

    int sumFitness = std::accumulate(populationFitness.begin(), populationFitness.end(), 0);

    std::vector<double> populationFitnessPercentage(popSize);
    for(int i = 0; i < popSize; i++) {
        populationFitnessPercentage[i] = populationFitness[i] / sumFitness;
    }
    return populationFitnessPercentage;
}

bool ProblemSolver::isUnique(std::vector<std::vector<int>> results, std::vector<int> permutation, int count) {
    /* przechodzimy przez tyle pierwszych tablic ile ich dotychczasowo wygenerowano
    sprawdzamy wartosc po wartosci czy sa unikalne */
    for(int i = 0; i < count; i++) {
        if(results[i] == permutation) return false;
    }
    return true;
}

std::vector<int> ProblemSolver::selectPermutation(std::vector<double> fitness) {
    int popSize = population.size();
    std::vector<double> cumulativeFitness(popSize);
    cumulativeFitness[0] = fitness[0];
    for(int i = 1; i < popSize; i ++) {
        cumulativeFitness[i] = cumulativeFitness[i-1] + fitness[i];
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0, 1.0);
    double random = dist(gen);

    for(int i = 0; i < popSize; i++) {
        if(random < cumulativeFitness[i]) {
            return population[i];
        }
    }
    return population[popSize-1];
}

void ProblemSolver::crossover(std::vector<int> parent1, std::vector<int> parent2, std::vector<int> child1, std::vector<int> child2) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, generator.matrixSize-1);

    int index = dist(gen);

    // pierwsza czesc pierwszego dziecka z pierwszego rodzica, druga z drugiego unikajac powtorzen
    for(int i = 0; i < index; i++) {
        child1[i] = parent1[i];
    }
    int indexChild1 = index;
    for(int i = 0; i < generator.matrixSize; i++) {
        bool found = false;
        for(int j = 0; j < index; j++) {
            if(parent2[i] == child1[j]) {
                found = true;
                break;
            }
        }
        if(!found) {
            child1[indexChild1] = parent2[i];
            indexChild1++;
        }
    }

    // pierwsza czesc drugiego dziecka z drugiego rodzica, druga z pierwszego unikajac powtorzen
    for(int i = 0; i < index; i++) {
        child2[i] = parent2[i];
    }
    int indexChild2 = index;
    for(int i = 0; i < generator.matrixSize; i++) {
        bool found = false;
        for(int j = 0; j < index; j++) {
            if(parent1[i] == child2[j]) {
                found = true;
                break;
            }
        }
        if(!found) {
            child2[indexChild2] = parent1[i];
            indexChild2++;
        }
    }
}

void ProblemSolver::mutationSwap(std::vector<int> path) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, generator.matrixSize-1);

    int first = dist(gen);
    int second = dist(gen);
    while(second == first) {
        second = dist(gen);
    }

    std::swap(path[first], path[second]);
}

void ProblemSolver::mutationInverse(std::vector<int> path) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, generator.matrixSize-1);
    int low = dist(gen);

    int high = dist(gen);
    while(high == low) {
        high = dist(gen);
    }
    if (low > high) {
        std::swap(low, high);
    }

    for (int i = low, j = high; i < j; i++, j--) {
        std::swap(path[i], path[j]);
    }
}

int ProblemSolver::findCost(std::vector<int> path) {
    int n = path.size();
    int cost = 0;
    // dodawaj do kosztu calkowitego wartosci kolejnych przejsc miedzy miastami zadanymi w path
    for(int i = 0; i < n-1; i++) {
        cost += generator.matrix[path[i]][path[i+1]];
    }
    // komiwojazer musi powrocic do miasta startowego wiec dodaj koszt przejscia z ostatniego do pierwszego
    cost += generator.matrix[path[n-1]][path[0]];
    return cost;
}

std::pair<int, std::vector<int>> ProblemSolver::geneticAlg(int popSize, double stopTime, double crossoverProb, double mutationProb, bool useSwapMutation) {
    initialPopulation(popSize);
    std::vector<double> fitness = calcFitness(population);

    auto start = std::chrono::steady_clock::now();
    std::pair<int, std::vector<int>> bestSolution = {INT_MAX, {}};

    while (std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count() < stopTime) {
        // Selekcja rodziców
        std::vector<std::vector<int>> parents;
        for (int i = 0; i < static_cast<int>(crossoverProb * popSize); i++) {
            parents.emplace_back(selectPermutation(fitness));
        }

        // Tworzenie dzieci przez crossover
        std::vector<std::vector<int>> children;
        for (int i = 0; i + 1 < parents.size(); i += 2) {
            std::vector<int> child1(generator.matrixSize);
            std::vector<int> child2(generator.matrixSize);
            crossover(parents[i], parents[i + 1], child1, child2);
            children.push_back(child1);
            children.push_back(child2);
        }

        // Mutacja dzieci
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist(0.0, 1.0);

        for (auto& child : children) {
            if (dist(gen) < mutationProb) {
                if (useSwapMutation) {
                    mutationSwap(child);
                } else {
                    mutationInverse(child);
                }
            }
        }

        // Aktualizacja populacji (elitarna selekcja)
        population.insert(population.end(), children.begin(), children.end());
        fitness = calcFitness(population);

        // Znajdź najlepsze rozwiązanie w obecnej populacji
        for (int i = 0; i < population.size(); i++) {
            int cost = findCost(population[i]);
            if (cost < bestSolution.first) {
                bestSolution = {cost, population[i]};
            }
        }

        // Zmniejszenie populacji do początkowego rozmiaru (zachowanie najlepszych)
        std::vector<std::pair<int, std::vector<int>>> sortedPopulation(population.size());
        for (int i = 0; i < population.size(); i++) {
            sortedPopulation[i] = {findCost(population[i]), population[i]};
        }

        std::sort(sortedPopulation.begin(), sortedPopulation.end());
        population.clear();
        for (int i = 0; i < popSize; i++) {
            population.push_back(sortedPopulation[i].second);
        }
        fitness = calcFitness(population);
    }

    return bestSolution;
}

