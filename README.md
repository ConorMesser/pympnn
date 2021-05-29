# Python Wrapper - Nearest Neighbor Library for Motion Planning

## Original forked repo:
University of Illinois  
Authors:  Anna Yershova;
          Steven M. LaValle  
Contributors: Andrew Wagner (Updated to use git and cmake, fixed some warnings)

## Python Wrapper
Contributor: Conor Messer (modified source for functionality and ease of use with Boost wrapper)

## Contents

The following directories are included in this distribution:

include:   The C++ header files for mpnn  
src:       The source code of the library  
mpnn_wrapper_boost_3.6: The boost module to wrap the mpnn library  
test:      Sample code that uses the library

## Build Instructions

### Linux

1. Build the mpnn library  
   a. Create build directory & navigate into it  
   b. Run `cmake ../.`  
   c. Run `cmake --build .`  
2. Move *mpnn.so* file from build dir to local library (i.e. */usr/local/lib/*)  
3. Build pympnn library in the boost dir  
   a. Create build directory & navigate to it  
   b. Run `cmake ../.`  
   c. Run `cmake --build .`  
4. Move *pympnn.so* file to python interpreter library (i.e. */usr/lib/python3.6/*)
5. Run test suites (C++ and Python) to ensure proper installation


## History

This project descends from a tarball at:
http://msl.cs.uiuc.edu/~yershova/software/MPNN/MPNN.htm
