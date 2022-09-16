cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_COMPILER "g++")
project(Ising VERSION 0.1.0)

include(CTest)
enable_testing()
include_directories( include )
add_link_options(-fopenmp)
add_compile_options(-fopenmp)
set(SOURCE_FILES src/main.cpp
                 lib/Lattice2D.cpp
                 lib/LatticeBase.cpp)
add_executable(Ising ${SOURCE_FILES})
find_package(GSL REQUIRED)
target_link_libraries(Ising GSL::gsl GSL::gslcblas)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)