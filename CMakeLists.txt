cmake_minimum_required(VERSION 2.8.12)

project(bonus)

# enable c++11 support
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")

# expose minisat header files
include_directories(${CMAKE_SOURCE_DIR}/minisat)

# create the main executable
## change .cpp files if needed
add_executable(${PROJECT_NAME} main.cc Tseitin_transform.cc parser.cc tokenizer.cc Tree_to_nnf.cc treeNode.cc dpll.cc)
# link MiniSAT libraries
target_link_libraries(${PROJECT_NAME} minisat-lib-static)

# create the executable for tests
add_executable(tests test.cpp Tseitin_transform.cc dpll.cc parser.cc tokenizer.cc Tree_to_nnf.cc treeNode.cc)
# link MiniSAT libraries
target_link_libraries(tests minisat-lib-static)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
