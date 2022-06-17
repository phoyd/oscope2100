cmake_minimum_required(VERSION 3.8)

project(oscope2100)

# oscope

set(oscope2100_src 
  src/ConfigFile.cpp  
  src/oscope2100_common.cpp  
  src/oscope2100_interface.cpp  
  src/oscope2100_usb.cpp)

add_executable(oscope2100 ${oscope2100_src})

## disable gtk headers spitting deprecation warnings.

target_compile_options(oscope2100 PRIVATE
     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
      -Wall -Wno-deprecated-declarations>
     $<$<CXX_COMPILER_ID:MSVC>:
          /W4>)

## pthreads

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(oscope2100 PRIVATE Threads::Threads)

## gtk2

find_package(GTK2 2.0 REQUIRED gtk)
target_include_directories(oscope2100 PRIVATE ${GTK2_INCLUDE_DIRS})
target_link_libraries(oscope2100 PRIVATE ${GTK2_LIBRARIES})

## libusb

find_path(LIBUSB_INCLUDE_DIR
  NAMES 
    libusb.h
  PATH_SUFFIXES 
    "include" 
    "libusb" 
    "libusb-1.0")

find_library(LIBUSB_LIBRARY
  NAMES 
    usb
  PATH_SUFFIXES 
    "lib" 
    "lib32" 
    "lib64")

target_include_directories(oscope2100 PRIVATE ${LIBUSB_INCLUDE_DIR})
target_link_libraries(oscope2100 PRIVATE ${LIBUSB_LIBRARY})

## installation

install(TARGETS oscope2100 DESTINATION bin)
set(SHAREDIR ${CMAKE_INSTALL_PREFIX}/share/dso2100)
configure_file(udev/dso2100.rules.in dso2100.rules @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/dso2100.rules DESTINATION ${SHAREDIR}) 

# dsoextractfw

add_executable(dsoextractfw src/dsoextractfw.c)

## bfd

find_path (LIBBFD_INCLUDE_DIRS
  NAMES 
    bfd.h
  PATHS 
    ENV CPATH)

find_library (LIBBFD_LIBRARIES
  NAMES 
    bfd
  PATHS
    ENV LIBRARY_PATH
    ENV LD_LIBRARY_PATH)

target_include_directories(dsoextractfw PRIVATE ${LIBBFD_INCLUDE_DIRS})
target_link_libraries(dsoextractfw PRIVATE ${LIBBFD_LIBRARIES})

## installation

install(TARGETS dsoextractfw DESTINATION bin)
