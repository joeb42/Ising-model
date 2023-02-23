cmake_minimum_required(VERSION 3.0.0)
project(Ising_MPI VERSION 0.1.0)

include_directories( include )
add_executable(Ising 
		src/main.cpp
        src/LatticeWorker.cpp)
find_package(MPI REQUIRED)
find_package(GSL REQUIRED)
target_link_libraries(Ising PUBLIC GSL::gsl GSL::gslcblas)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
