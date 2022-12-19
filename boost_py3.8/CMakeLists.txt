cmake_minimum_required(VERSION 3.22)
include(ExternalProject)

# Adding customized cmake module for building boost
list(APPEND CMAKE_MODULE_PATH  "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_COMPILER "/usr/bin/g++-9")
message(STATUS "Using C++11 standard")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(MULTIANN_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/../include")

message(STATUS "MULTIANN Header Path:  ${MULTIANN_INCLUDE_PATH}")


project(test_mpnn)

  # Find default python libraries and interpreter
  # Need to specify which python interpreter to locate devel files todo DEBUG
  find_package(PythonInterp 3.8 REQUIRED)
  message(STATUS "Using ${PYTHON_VERSION_STRING}")
  find_package(PythonLibs 3.8 REQUIRED)
  include(cmake/Modules/BuildBoost) # Custom module

  # Find mpnn library
  find_library(MPNN_LIB libmpnn.so)
  find_path(MULTIANN_PATH mpnn/multiann.h)

  include_directories(${Boost_INCLUDE_DIR} ${PYTHON_INCLUDE_DIRS} ${MULTIANN_INCLUDE_PATH} ${usr/local/include/mpnn})
  link_directories(${Boost_LIBRARY_DIR} ${usr/local/lib})

  # Build and link the pylib module
  add_library(pympnn SHARED pympnn.cpp)
  target_link_libraries(pympnn ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} ${MPNN_LIB})
  target_include_directories(pympnn PUBLIC ${MULTIANN_PATH}/mpnn)
  add_dependencies(pympnn Boost)

  # Tweaks the name of the library to match what Python expects
  set_target_properties(pympnn PROPERTIES SUFFIX .so)
  set_target_properties(pympnn PROPERTIES PREFIX "")

