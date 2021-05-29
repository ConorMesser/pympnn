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

### Windows

1. Requirements  
   a. MSVC (Microsoft Studio Visual Code)  
   b. cmake  
2. Build the mpnn library  
   a. Create build directory  
   b. In the CMake GUI, specify source code directory (*pympnn* directory) and where to build the binaries (build directory)  
   c. Configure and Generate  
   d. Navigate into build directory and run `cmake --build .`
3. Move *mpnn.dll* library file from from build dir (perhaps in *./build/Debug/*) to local library (i.e. */Windows/System32*)  
4. Build pympnn library in the boost directory  
   a. Create build directory  
   b. In the CMake GUI, specify source code directory (*pympnn* directory) and where to build the binaries (build directory)  
   c. Configure and Generate  
&nbsp;&nbsp;&nbsp;    - If this fails, you may have to specify the *MPNN_LIB* and *MULTIANN_PATH* paths manually  
   d. Navigate into build directory and run `cmake --build .`  
5. Move *pympnn.dll* library file to python interpreter library
6. Run test suites to ensure proper installation  

## History

This project descends from a tarball at:
http://msl.cs.uiuc.edu/~yershova/software/MPNN/MPNN.htm
