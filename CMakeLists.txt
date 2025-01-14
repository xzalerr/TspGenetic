cmake_minimum_required(VERSION 3.27)
project(TspGeneric)

set(CMAKE_CXX_STANDARD 17)

add_executable(TspMetaheuristic main.cpp
        DataGenerator.cpp
        DataGenerator.h
        ProblemSolver.cpp
        ProblemSolver.h)

include(FetchContent)
FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.10.4
)
FetchContent_MakeAvailable(json)
target_link_libraries(TspMetaheuristic nlohmann_json::nlohmann_json)