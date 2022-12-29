cmake_minimum_required(VERSION 3.0.0)
project(Ising VERSION 0.1.0)

include_directories( include )
set (LIB_FILES lib/LatticeBase.cpp
		lib/Lattice2D.cpp)
add_executable(Ising ${LIB_FILES} 
		src/main.cpp)
add_executable(timing ${LIB_FILES} 
		src/timing.cpp)
find_package(OpenMP REQUIRED)
find_package(GSL REQUIRED)
target_link_libraries(Ising PUBLIC OpenMP::OpenMP_CXX GSL::gsl GSL::gslcblas)
target_link_libraries(timing PUBLIC OpenMP::OpenMP_CXX GSL::gsl GSL::gslcblas)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
