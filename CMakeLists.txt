cmake_minimum_required(VERSION 3.14)
project(Clashes VERSION 1.0
	            DESCRIPTION "Protein-Ligand clashes C++"
		        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Find pybind11
find_package(pybind11 REQUIRED)
# Openbabel libs
include_directories(include /usr/include/openbabel3)
link_directories(/usr/lib)

# Add the main library
add_library(clashes_cpp SHARED src/clashes.cpp)
target_link_libraries(clashes_cpp PRIVATE openbabel)

# Add the Python bindings
# pybind11_add_module(clashes python/bindings.cpp)
# target_link_libraries(clashes PRIVATE clashes_cpp)

# Create executable
add_executable(clashes_exe src/main.cpp src/clashes.cpp)
target_link_libraries(clashes_exe clashes_cpp openbabel)
